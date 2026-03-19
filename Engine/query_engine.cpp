#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <functional>
#include <stdexcept>
#include <algorithm>
#include <numeric>

// ========================== DATAFRAME ==========================
class DataFrame {
private:
    std::unordered_map<std::string, std::vector<double>> data;

public:
    void add_column(const std::string& name) {
        data[name] = {};
    }

    void append(const std::string& col, double value) {
        data[col].push_back(value);
    }

    std::vector<double>& get_column(const std::string& col) {
        if (!data.count(col))
            throw std::runtime_error("Column not found: " + col);
        return data[col];
    }

    size_t rows() const {
        if (data.empty()) return 0;
        return data.begin()->second.size();
    }

    std::vector<std::string> columns() const {
        std::vector<std::string> cols;
        for (auto& kv : data) cols.push_back(kv.first);
        return cols;
    }

    DataFrame select(const std::vector<std::string>& cols) const {
        DataFrame result;
        for (auto& c : cols) {
            if (!data.count(c))
                throw std::runtime_error("Column not found: " + c);
            result.data[c] = data.at(c);
        }
        return result;
    }

    DataFrame filter(std::function<bool(size_t)> predicate) const {
        DataFrame result;
        for (auto& kv : data)
            result.add_column(kv.first);

        for (size_t i = 0; i < rows(); i++) {
            if (predicate(i)) {
                for (auto& kv : data)
                    result.data[kv.first].push_back(kv.second[i]);
            }
        }
        return result;
    }

    void print(size_t limit = 10) const {
        auto cols = columns();
        for (auto& c : cols) std::cout << c << "\t";
        std::cout << "\n";

        for (size_t i = 0; i < std::min(limit, rows()); i++) {
            for (auto& c : cols)
                std::cout << data.at(c)[i] << "\t";
            std::cout << "\n";
        }
    }
};

// ========================== OPERATORS ==========================
enum class Op { GT, LT, EQ, GTE, LTE };

class Condition {
public:
    std::string column;
    double value;
    Op op;

    bool evaluate(const DataFrame& df, size_t row) const {
        const auto& col = df.get_column(column);
        double v = col[row];

        switch (op) {
            case Op::GT: return v > value;
            case Op::LT: return v < value;
            case Op::EQ: return v == value;
            case Op::GTE: return v >= value;
            case Op::LTE: return v <= value;
        }
        return false;
    }
};

// ========================== AGGREGATIONS ==========================
class Aggregator {
public:
    static double sum(const std::vector<double>& v) {
        return std::accumulate(v.begin(), v.end(), 0.0);
    }

    static double mean(const std::vector<double>& v) {
        return sum(v) / v.size();
    }

    static double min(const std::vector<double>& v) {
        return *std::min_element(v.begin(), v.end());
    }

    static double max(const std::vector<double>& v) {
        return *std::max_element(v.begin(), v.end());
    }

    static size_t count(const std::vector<double>& v) {
        return v.size();
    }
};

// ========================== QUERY ENGINE ==========================
class QueryEngine {
private:
    const DataFrame& df;

public:
    QueryEngine(const DataFrame& dataframe) : df(dataframe) {}

    DataFrame where(const std::vector<Condition>& conditions) const {
        return df.filter([&](size_t i) {
            for (const auto& cond : conditions)
                if (!cond.evaluate(df, i))
                    return false;
            return true;
        });
    }

    DataFrame select(const std::vector<std::string>& cols) const {
        return df.select(cols);
    }

    void aggregate(const std::string& col) const {
        const auto& data = df.get_column(col);

        std::cout << "SUM: " << Aggregator::sum(data) << "\n";
        std::cout << "AVG: " << Aggregator::mean(data) << "\n";
        std::cout << "MIN: " << Aggregator::min(data) << "\n";
        std::cout << "MAX: " << Aggregator::max(data) << "\n";
        std::cout << "COUNT: " << Aggregator::count(data) << "\n";
    }
};

// ========================== DEMO ==========================
int main() {
    DataFrame df;

    df.add_column("age");
    df.add_column("salary");

    for (int i = 0; i < 100; i++) {
        df.append("age", 20 + i % 30);
        df.append("salary", 3000 + i * 50);
    }

    QueryEngine engine(df);

    // WHERE age > 30 AND salary > 4000
    std::vector<Condition> conditions = {
        {"age", 30, Op::GT},
        {"salary", 4000, Op::GT}
    };

    auto filtered = engine.where(conditions);

    std::cout << "Filtered Data:\n";
    filtered.print();

    std::cout << "\nSelected Columns:\n";
    auto selected = filtered.select({"age"});
    selected.print();

    std::cout << "\nAggregations on salary:\n";
    QueryEngine(filtered).aggregate("salary");

    return 0;
}
