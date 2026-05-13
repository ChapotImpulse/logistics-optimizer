#include "../core/transport_solver.h"
#include "../core/simulation.h"
#include "../io/csv_reader.h"
#include <filesystem>
#include <iostream>
#include <iomanip>
#include <windows.h>

namespace fs = std::filesystem;

int main(int argc, char *argv[]) {
  SetConsoleOutputCP(65001); 
  SetConsoleCP(65001);

  std::string path;

  if (argc > 1) {
    path = argv[1];
  } else {

    fs::path exe_path = fs::current_path();
    path = (exe_path / "data" / "balanced.csv").string();
  }

  try {
    std::cout << "Loading: " << path << std::endl;
    auto data = io::CsvReader::read(path);

        core::TransportSolver solver;
        auto det_result = solver.solve(data.costs, data.supply, data.demand);
        std::cout << "[DET] Мин. затраты: " << det_result.total_cost << "\n";

        core::MonteCarloSimulation sim;
        auto stoch_result = sim.run(10000, data.demand);
        std::cout << "[STOCH] Средние: " << stoch_result.mean_cost 
                  << " | Риск: " << std::fixed << std::setprecision(2) 
                  << stoch_result.deficit_risk * 100 << "%\n";
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << "\n";
        return 1;
    }
    return 0;
}
