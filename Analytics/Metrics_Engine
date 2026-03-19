#ifndef METRICS_H
#define METRICS_H

#include <vector>
#include <cmath>

class Metrics {
public:
    static double mse(const std::vector<double>& y_true,
                      const std::vector<double>& y_pred) {
        double sum = 0.0;
        int n = y_true.size();

        for (int i = 0; i < n; i++) {
            double diff = y_true[i] - y_pred[i];
            sum += diff * diff;
        }
        return sum / n;
    }

    static double mae(const std::vector<double>& y_true,
                      const std::vector<double>& y_pred) {
        double sum = 0.0;
        int n = y_true.size();

        for (int i = 0; i < n; i++) {
            sum += std::abs(y_true[i] - y_pred[i]);
        }
        return sum / n;
    }

    static double r2(const std::vector<double>& y_true,
                     const std::vector<double>& y_pred) {

        double mean = 0.0;
        for (double v : y_true) mean += v;
        mean /= y_true.size();

        double ss_total = 0.0, ss_res = 0.0;

        for (int i = 0; i < y_true.size(); i++) {
            ss_total += (y_true[i] - mean) * (y_true[i] - mean);
            ss_res += (y_true[i] - y_pred[i]) * (y_true[i] - y_pred[i]);
        }

        return 1 - (ss_res / ss_total);
    }
};

#endif
