#ifndef ADV_LINEAR_REGRESSION_H
#define ADV_LINEAR_REGRESSION_H

#include <vector>
#include <cmath>
#include <random>
#include <thread>
#include <mutex>

class AdvancedLinearRegression {
private:
    std::vector<double> weights;
    double bias;

    double learning_rate;
    int epochs;
    double lambda; // L2 regularization

public:
    AdvancedLinearRegression(int features,
                             double lr = 0.01,
                             int ep = 1000,
                             double reg = 0.01)
        : learning_rate(lr), epochs(ep), lambda(reg) {
        weights.resize(features);
        initialize_weights();
        bias = 0.0;
    }

    void initialize_weights() {
        std::mt19937 gen(42);
        std::normal_distribution<> d(0, 1);

        for (auto &w : weights)
            w = d(gen) * 0.01;
    }

    double predict_single(const std::vector<double>& x) const {
        double result = bias;
        for (size_t i = 0; i < weights.size(); i++)
            result += weights[i] * x[i];
        return result;
    }

    std::vector<double> predict(const std::vector<std::vector<double>>& X) const {
        std::vector<double> preds(X.size());

        for (size_t i = 0; i < X.size(); i++)
            preds[i] = predict_single(X[i]);

        return preds;
    }

    void fit(const std::vector<std::vector<double>>& X,
             const std::vector<double>& y,
             int num_threads = 4) {

        int n = X.size();
        int features = weights.size();

        for (int epoch = 0; epoch < epochs; epoch++) {

            std::vector<double> grad_w(features, 0.0);
            double grad_b = 0.0;

            std::mutex grad_mutex;
            std::vector<std::thread> threads;

            auto worker = [&](int start, int end) {
                std::vector<double> local_grad_w(features, 0.0);
                double local_grad_b = 0.0;

                for (int i = start; i < end; i++) {
                    double pred = predict_single(X[i]);
                    double error = pred - y[i];

                    for (int j = 0; j < features; j++) {
                        local_grad_w[j] += error * X[i][j];
                    }

                    local_grad_b += error;
                }

                std::lock_guard<std::mutex> lock(grad_mutex);
                for (int j = 0; j < features; j++)
                    grad_w[j] += local_grad_w[j];

                grad_b += local_grad_b;
            };

            int chunk = n / num_threads;

            for (int t = 0; t < num_threads; t++) {
                int start = t * chunk;
                int end = (t == num_threads - 1) ? n : start + chunk;
                threads.emplace_back(worker, start, end);
            }

            for (auto& th : threads)
                th.join();

            // Average gradients + regularization
            for (int j = 0; j < features; j++) {
                grad_w[j] = (grad_w[j] / n) + lambda * weights[j];
            }

            grad_b /= n;

            // Update weights
            for (int j = 0; j < features; j++) {
                weights[j] -= learning_rate * grad_w[j];
            }

            bias -= learning_rate * grad_b;
        }
    }

    double mse(const std::vector<std::vector<double>>& X,
               const std::vector<double>& y) const {

        double error = 0.0;
        int n = X.size();

        for (int i = 0; i < n; i++) {
            double diff = predict_single(X[i]) - y[i];
            error += diff * diff;
        }

        return error / n;
    }

    const std::vector<double>& get_weights() const {
        return weights;
    }

    double get_bias() const {
        return bias;
    }
};

#endif
