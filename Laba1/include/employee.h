#pragma once
#include <string>
#include <vector>

class Employee {
public:
    static constexpr int NAME_SIZE = 10;

    int num{};
    char name[NAME_SIZE]{};
    double hours{};

    Employee() = default;

    Employee(int n, const std::string& nm, double h);

    std::string getName() const;
    double salary(double rate) const;

    bool operator==(const Employee& other) const;
};

std::vector<Employee> readEmployees(const std::string& filename);
void writeEmployees(const std::string& filename, const std::vector<Employee>& list);

std::vector<std::string> readReport(const std::string& filename);
