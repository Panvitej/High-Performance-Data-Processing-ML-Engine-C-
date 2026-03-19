#ifndef CORRELATION_H
#define CORRELATION_H

#include <vector>
#include <cmath>

class Correlation {
public:
    static double pearson(const std::vector<double>& x,
                          const std::vector<double>& y) {

        int n = x.size();
        double sum_x = 0, sum_y = 0;
        double sum_xy = 0, sum_x2 = 0, sum_y2 = 0;

        for (int i = 0; i < n; i++) {
            sum_x += x[i];
            sum_y += y[i];
            sum_xy += x[i] * y[i];
            sum_x2 += x[i] * x[i];
            sum_y2 += y[i] * y[i];
        }

        double numerator = (n * sum_xy - sum_x * sum_y);
        double denominator = std::sqrt(
            (n * sum_x2 - sum_x * sum_x) *
            (n * sum_y2 - sum_y * sum_y)
        );

        return numerator / (denominator + 1e-10);
    }

    static std::vector<std::vector<double>> correlation_matrix(
        const std::vector<std::vector<double>>& X) {

        int features = X[0].size();
        std::vector<std::vector<double>> matrix(
            features, std::vector<double>(features, 0.0));

        for (int i = 0; i < features; i++) {
            for (int j = 0; j < features; j++) {
                std::vector<double> col_i, col_j;

                for (auto& row : X) {
                    col_i.push_back(row[i]);
                    col_j.push_back(row[j]);
                }

                matrix[i][j] = pearson(col_i, col_j);
            }
        }

        return matrix;
    }
};

#endif
