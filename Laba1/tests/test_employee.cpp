#include "employee.h"
#include <cassert>
#include <iostream>

int main() {
    Employee e(1, "Ivan", 10.0);

    assert(e.num == 1);
    assert(e.getName() == "Ivan");
    assert(e.hours == 10.0);
    assert(e.salary(100) == 1000.0);

    std::cout << "Employee tests passed.\n";
    return 0;
}
