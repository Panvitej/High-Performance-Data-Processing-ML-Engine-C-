#ifndef SCALER_H
#define SCALER_H

#include <vector>
#include <cmath>

class StandardScaler {
private:
    std::vector<double> mean;
    std::vector<double> stddev;

public:
    void fit(const std::vector<std::vector<double>>& X) {
        int n = X.size();
        int features = X[0].size();

        mean.resize(features, 0.0);
        stddev.resize(features, 0.0);

        // Compute mean
        for (auto& row : X)
            for (int j = 0; j < features; j++)
                mean[j] += row[j];

        for (int j = 0; j < features; j++)
            mean[j] /= n;

        // Compute stddev
        for (auto& row : X)
            for (int j = 0; j < features; j++)
                stddev[j] += std::pow(row[j] - mean[j], 2);

        for (int j = 0; j < features; j++)
            stddev[j] = std::sqrt(stddev[j] / n);
    }

    std::vector<std::vector<double>> transform(
        const std::vector<std::vector<double>>& X) {

        std::vector<std::vector<double>> result = X;

        for (auto& row : result)
            for (int j = 0; j < row.size(); j++)
                row[j] = (row[j] - mean[j]) / (stddev[j] + 1e-8);

        return result;
    }
};

#endif
