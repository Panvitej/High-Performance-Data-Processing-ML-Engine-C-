#ifndef STATS_H
#define STATS_H

#include <vector>
#include <numeric>
#include <cmath>

class Stats {
public:
    static double mean(const std::vector<double>& v) {
        return std::accumulate(v.begin(), v.end(), 0.0) / v.size();
    }

    static double variance(const std::vector<double>& v) {
        double m = mean(v);
        double sum = 0;

        for (double x : v)
            sum += (x - m) * (x - m);

        return sum / v.size();
    }

    static double stddev(const std::vector<double>& v) {
        return std::sqrt(variance(v));
    }
};

#endif
