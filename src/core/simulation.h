#pragma once
#include <vector>
#include <random>

namespace core {
    struct SimResult {
        double mean_cost;
        double variance;
        double deficit_risk;
    };

    class MonteCarloSimulation {
    public:
        SimResult run(size_t iterations, 
                      const std::vector<double>& base_demand,
                      double deficit_penalty = 10.0,
                      double storage_cost = 1.0);
    };
}
