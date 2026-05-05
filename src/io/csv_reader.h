#pragma once
#include <string>
#include <vector>

namespace io {
    struct DataInput {
        std::vector<std::vector<double>> costs;
        std::vector<double> supply;
        std::vector<double> demand;
    };

    class CsvReader {
    public:
        static DataInput read(const std::string& path);
    private:
        static std::vector<std::string> split(const std::string& line, char delim);
    };
}
