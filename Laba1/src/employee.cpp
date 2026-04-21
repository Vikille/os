#include "employee.h"
#include <fstream>
#include <stdexcept>
#include <cstring>

Employee::Employee(int n, const std::string& nm, double h)
    : num(n), hours(h)
{
    if (nm.size() >= NAME_SIZE)
        throw std::runtime_error("Name too long");

    std::strncpy(name, nm.c_str(), NAME_SIZE - 1);
    name[NAME_SIZE - 1] = '\0';
}

std::string Employee::getName() const {
    return std::string(name);
}

double Employee::salary(double rate) const {
    return hours * rate;
}

bool Employee::operator==(const Employee& other) const {
    return num == other.num &&
           std::strcmp(name, other.name) == 0 &&
           hours == other.hours;
}

std::vector<Employee> readEmployees(const std::string& filename) {
    std::ifstream fin(filename, std::ios::binary);
    if (!fin)
        throw std::runtime_error("Cannot open binary file: " + filename);

    std::vector<Employee> list;
    Employee e;

    while (fin.read(reinterpret_cast<char*>(&e), sizeof(Employee))) {
        list.push_back(e);
    }

    return list;
}

void writeEmployees(const std::string& filename, const std::vector<Employee>& list) {
    std::ofstream fout(filename, std::ios::binary);
    if (!fout)
        throw std::runtime_error("Cannot create binary file: " + filename);

    for (const auto& e : list) {
        fout.write(reinterpret_cast<const char*>(&e), sizeof(Employee));
    }
}

std::vector<std::string> readReport(const std::string& filename) {
    std::ifstream fin(filename);
    if (!fin)
        throw std::runtime_error("Cannot open report file: " + filename);

    std::vector<std::string> lines;
    std::string s;

    while (std::getline(fin, s)) {
        lines.push_back(s);
    }

    return lines;
}
