#include <gtest/gtest.h>
#include "core/simulation.h"
#include <cmath>
#include <stdexcept>

// Тест 1: Базовый запуск Монте-Карло (сбалансированные данные)
TEST(SimulationTest, BalancedScenarioBasicRun) {
    core::MonteCarloSimulation sim;
    std::vector<double> base_demand = {15.0, 25.0, 10.0};
    auto res = sim.run(10000, base_demand, 10.0, 1.0);
    
    EXPECT_GE(res.mean_cost, 0.0);
    EXPECT_GE(res.variance, 0.0);
    EXPECT_GE(res.deficit_risk, 0.0);
    EXPECT_LE(res.deficit_risk, 1.0);
}

// Тест 2: Несбалансированная задача (спрос > запас) -> проверка штрафов
TEST(SimulationTest, UnbalancedScenarioDeficitPenalty) {
    core::MonteCarloSimulation sim;
    // Спрос увеличен на 20%, имитирует реальный риск дефицита
    std::vector<double> high_demand = {20.0, 30.0, 15.0};
    auto res = sim.run(5000, high_demand, 50.0, 1.0); // Высокий штраф за дефицит
    
    EXPECT_GT(res.mean_cost, 0.0);
    // При высоком штрафе и превышении спроса риск должен быть значимым
    EXPECT_GT(res.deficit_risk, 0.05); 
}

// Тест 3: Граничные условия и обработка пустых данных
TEST(SimulationTest, EmptyDemandHandling) {
    core::MonteCarloSimulation sim;
    std::vector<double> empty_demand;
    
    // Ожидается корректная обработка без выброса исключений
    auto res = sim.run(100, empty_demand, 1.0, 1.0);
    EXPECT_EQ(res.mean_cost, 0.0);
    EXPECT_EQ(res.deficit_risk, 0.0);
}

// Тест 4: Нулевое число итераций
TEST(SimulationTest, ZeroIterations) {
    core::MonteCarloSimulation sim;
    std::vector<double> demand = {10.0};
    
    auto res = sim.run(0, demand, 1.0, 1.0);
    EXPECT_EQ(res.mean_cost, 0.0);
    EXPECT_EQ(res.variance, 0.0);
}
