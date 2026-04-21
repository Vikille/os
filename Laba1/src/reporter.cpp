#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdexcept>
#include "employee.h"

int main(int argc, char* argv[]) {
    try {
        if (argc != 4)
            throw std::runtime_error("Usage: reporter <bin_file> <report_file> <rate>");

        std::string bin = argv[1];
        std::string rep = argv[2];
        double rate = std::stod(argv[3]);

        auto employees = readEmployees(bin);

        std::ofstream fout(rep);
        if (!fout)
            throw std::runtime_error("Cannot create report file: " + rep);

        fout << "Report for file \"" << bin << "\"\n";
        fout << "Num\tName\tHours\tSalary\n";

        for (const auto& e : employees) {
            fout << e.num << "\t"
                 << e.getName() << "\t"
                 << e.hours << "\t"
                 << std::fixed << std::setprecision(2)
                 << e.salary(rate) << "\n";
        }

        return 0;

    } catch (const std::exception& ex) {
        std::cerr << "Reporter error: " << ex.what() << "\n";
        return 1;
    }
}
