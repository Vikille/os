#include <iostream>
#include <vector>
#include <stdexcept>
#include "employee.h"

int main(int argc, char* argv[]) {
    try {
        if (argc != 3)
            throw std::runtime_error("Usage: creator <binary_file> <count>");

        std::string filename = argv[1];
        int count = std::stoi(argv[2]);

        if (count <= 0)
            throw std::runtime_error("Count must be positive");

        std::vector<Employee> list;
        list.reserve(count);

        for (int i = 0; i < count; i++) {
            int num;
            std::string name;
            double hours;

            std::cout << "Enter num, name, hours for employee " << (i + 1) << ":\n";
            std::cin >> num >> name >> hours;

            list.emplace_back(num, name, hours);
        }

        writeEmployees(filename, list);
        return 0;

    } catch (const std::exception& ex) {
        std::cerr << "Creator error: " << ex.what() << "\n";
        return 1;
    }
}
