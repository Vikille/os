#include <windows.h>
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include "employee.h"

void runProcess(const std::string& cmd) {
    STARTUPINFOA si{};
    PROCESS_INFORMATION pi{};
    si.cb = sizeof(si);

    std::vector<char> buf(cmd.begin(), cmd.end());
    buf.push_back('\0');

    if (!CreateProcessA(nullptr, buf.data(), nullptr, nullptr, FALSE, 0, nullptr, nullptr, &si, &pi)) {
        DWORD err = GetLastError();
        throw std::runtime_error("Process start error: " + std::to_string(err));
    }

    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}

int main() {
    try {
        std::string bin, rep;
        int count;
        double rate;

        std::cout << "Enter binary filename: ";
        std::cin >> bin;

        std::cout << "Enter number of records: ";
        std::cin >> count;

        runProcess("creator " + bin + " " + std::to_string(count));

        auto employees = readEmployees(bin);
        std::cout << "\nBinary file content:\n";
        for (const auto& e : employees) {
            std::cout << e.num << " " << e.getName() << " " << e.hours << "\n";
        }

        std::cout << "\nEnter report filename: ";
        std::cin >> rep;

        std::cout << "Enter pay per hour: ";
        std::cin >> rate;

        runProcess("reporter " + bin + " " + rep + " " + std::to_string(rate));

        auto report = readReport(rep);
        std::cout << "\nReport:\n";
        for (const auto& line : report) {
            std::cout << line << "\n";
        }

        return 0;

    } catch (const std::exception& ex) {
        std::cerr << "Main error: " << ex.what() << "\n";
        return 1;
    }
}
