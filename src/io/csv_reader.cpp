#include "csv_reader.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <stdexcept>

namespace io {

std::vector<std::string> CsvReader::split(const std::string &line, char delim) {
  std::vector<std::string> tokens;
  std::stringstream ss(line);
  std::string token;
  while (std::getline(ss, token, delim)) {
    token.erase(0, token.find_first_not_of(" \t"));
    token.erase(token.find_last_not_of(" \t") + 1);
    if (!token.empty()) {
      tokens.push_back(token);
    }
  }
  return tokens;
}

DataInput CsvReader::read(const std::string &path) {
  std::ifstream file(path);
  if (!file.is_open())
    throw std::runtime_error("Cannot open file: " + path);

  DataInput data;
  std::string line;
  int line_num = 0;

  while (std::getline(file, line)) {
    if (line.empty() || line.find_first_not_of(" \t") == std::string::npos)
      continue;

    line_num++;

    if (!line.empty() && line.back() == '\r')
      line.pop_back();

    try {
      if (line_num == 1) {
        size_t colon_pos = line.find(':');
        std::string values_str = (colon_pos != std::string::npos)
                                     ? line.substr(colon_pos + 1)
                                     : line;

        auto tokens = split(values_str, ' ');
        for (const auto &token : tokens) {
          data.supply.push_back(std::stod(token));
        }
      } else if (line_num == 2) {
        size_t colon_pos = line.find(':');
        std::string values_str = (colon_pos != std::string::npos)
                                     ? line.substr(colon_pos + 1)
                                     : line;

        auto tokens = split(values_str, ' ');
        for (const auto &token : tokens) {
          data.demand.push_back(std::stod(token));
        }
      } else if (line_num >= 3) {
        if (line.find("costs") != std::string::npos)
          continue;

        auto tokens = split(line, ' ');
        std::vector<double> row;
        for (const auto &token : tokens) {
          row.push_back(std::stod(token));
        }
        if (!row.empty()) {
          data.costs.push_back(row);
        }
      }
    } catch (const std::exception &e) {
      throw std::runtime_error("Error parsing line " +
                               std::to_string(line_num) + ": " +
                               std::string(e.what()));
    }
  }

  if (data.supply.empty())
    throw std::runtime_error("Supply vector is empty");
  if (data.demand.empty())
    throw std::runtime_error("Demand vector is empty");
  if (data.costs.empty())
    throw std::runtime_error("Cost matrix is empty");
  if (data.costs.size() != data.supply.size())
    throw std::runtime_error("Cost matrix rows (" +
                             std::to_string(data.costs.size()) +
                             ") don't match supply size (" +
                             std::to_string(data.supply.size()) + ")");

  return data;
}

}
