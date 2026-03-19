#ifndef OUTLIER_H
#define OUTLIER_H

#include <vector>
#include <cmath>

class OutlierDetector {
public:
    static std::vector<int> detect_zscore(
        const std::vector<double>& data,
        double threshold = 3.0) {

        double mean = 0;
        for (double v : data) mean += v;
        mean /= data.size();

        double stddev = 0;
        for (double v : data)
            stddev += (v - mean) * (v - mean);

        stddev = std::sqrt(stddev / data.size());

        std::vector<int> outliers;

        for (int i = 0; i < data.size(); i++) {
            double z = std::abs((data[i] - mean) / (stddev + 1e-8));
            if (z > threshold)
                outliers.push_back(i);
        }

        return outliers;
    }
};

#endif
