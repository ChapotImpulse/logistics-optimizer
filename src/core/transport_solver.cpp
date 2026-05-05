#include "transport_solver.h"
#include <numeric>
#include <stdexcept>

namespace core {
    TransportResult TransportSolver::solve(const std::vector<std::vector<double>>& costs,
                                           const std::vector<double>& supply,
                                           const std::vector<double>& demand) {
        if (costs.empty() || supply.empty() || demand.empty())
            throw std::invalid_argument("Empty input data");

        auto plan = initial_plan(costs, supply, demand);
        double cost = calculate_cost(plan, costs);

        return {plan, cost};
    }

    std::vector<std::vector<double>> TransportSolver::initial_plan(
        const std::vector<std::vector<double>>& costs,
        const std::vector<std::vector<double>>& supply,
        const std::vector<double>>& demand) {
        
        size_t m = supply.size();
        size_t n = demand.size();
        std::vector<std::vector<double>> plan(m, std::vector<double>(n, 0.0));

        size_t i = 0, j = 0;
        std::vector<double> rem_s = supply;
        std::vector<double> rem_d = demand;

        while (i < m && j < n) {
            double val = std::min(rem_s[i], rem_d[j]);
            plan[i][j] = val;
            rem_s[i] -= val;
            rem_d[j] -= val;
            if (rem_s[i] == 0) i++;
            if (rem_d[j] == 0) j++;
        }
        return plan;
    }

    double TransportSolver::calculate_cost(const std::vector<std::vector<double>>& plan,
                                           const std::vector<std::vector<double>>& costs) {
        double total = 0.0;
        for (size_t i = 0; i < plan.size(); ++i)
            for (size_t j = 0; j < plan[0].size(); ++j)
                total += plan[i][j] * costs[i][j];
        return total;
    }
}
