#include "simulation.h"
#include <cmath>
#include <numeric>

namespace core {
    SimResult MonteCarloSimulation::run(size_t iterations, 
                                        const std::vector<double>& base_demand,
                                        double deficit_penalty,
                                        double storage_cost) {
        std::mt19937 gen(42);
        std::vector<double> results;
        results.reserve(iterations);

        for (size_t k = 0; k < iterations; ++k) {
            double scenario_cost = 0.0;
            std::normal_distribution<> d; // σ настраивается под задачу
            
            for (size_t j = 0; j < base_demand.size(); ++j) {
                double sim_demand = std::max(0.0, d(gen) + base_demand[j]);
                // Упрощённая логика сравнения с запасом (запас = base_demand[j])
                if (sim_demand > base_demand[j])
                    scenario_cost += (sim_demand - base_demand[j]) * deficit_penalty;
                else
                    scenario_cost += (base_demand[j] - sim_demand) * storage_cost;
            }
            results.push_back(scenario_cost);
        }

        double mean = std::accumulate(results.begin(), results.end(), 0.0) / results.size();
        double var = 0.0;
        for (double v : results) var += (v - mean) * (v - mean);
        var /= results.size();

        double risk = 0.0;
        double threshold = mean + 1.5 * std::sqrt(var); // пример порога
        for (double v : results) if (v > threshold) risk++;
        risk /= results.size();

        return {mean, var, risk};
    }
}
