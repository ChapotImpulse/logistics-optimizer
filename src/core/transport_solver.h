#pragma once
#include <vector>

namespace core {
    struct TransportResult {
        std::vector<std::vector<double>> plan;
        double total_cost;
    };

    class TransportSolver {
    public:
        TransportResult solve(const std::vector<std::vector<double>>& costs,
                              const std::vector<double>& supply,
                              const std::vector<double>& demand);
    private:
        std::vector<std::vector<double>> initial_plan(const std::vector<std::vector<double>>& costs,
                                                      const std::vector<double>& supply,
                                                      const std::vector<double>& demand);
        double calculate_cost(const std::vector<std::vector<double>>& plan,
                              const std::vector<std::vector<double>>& costs);
    };
}
