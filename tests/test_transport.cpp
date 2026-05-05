#include <gtest/gtest.h>
#include "core/transport_solver.h"

TEST(TransportTest, BalancedInput) {
    core::TransportSolver solver;
    std::vector<std::vector<double>> costs = {{4, 6, 8}, {3, 5, 2}};
    std::vector<double> supply = {20, 30};
    std::vector<double> demand = {15, 25, 10};
    auto res = solver.solve(costs, supply, demand);
    EXPECT_GT(res.total_cost, 0);
    EXPECT_EQ(res.plan.size(), 2);
}

TEST(TransportTest, InvalidInput) {
    core::TransportSolver solver;
    EXPECT_THROW(solver.solve({}, {}, {}), std::invalid_argument);
}
