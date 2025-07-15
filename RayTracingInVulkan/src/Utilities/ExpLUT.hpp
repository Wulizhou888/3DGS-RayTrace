#include <iostream>
#include <cmath>
#include <vector>

struct LinearSegment {
    float k;
    float b;
};

std::vector<LinearSegment> generateExpLUT(int segments, float xmin, float xmax) {
    std::vector<LinearSegment> table;
    float step = (xmax - xmin) / segments;

    for (int i = 0; i < segments; ++i) {
        float x = xmin + i * step;

        float k = -std::exp(-x);  // Slope
        float b = std::exp(-x);   // Intercept

        table.push_back({k, b});
    }

    return table;
}