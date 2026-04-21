#ifndef THREADS_H
#define THREADS_H

#include <windows.h>

struct ThreadData {
    int* arr;
    int size;
    int minVal;
    int maxVal;
    double avg;
};

DWORD WINAPI MinMaxThread(LPVOID lpParam);
DWORD WINAPI AverageThread(LPVOID lpParam);

#endif
