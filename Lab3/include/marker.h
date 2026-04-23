#ifndef MARKER_H
#define MARKER_H

#include <windows.h>

struct MarkerData {
    int id;
    int* arr;
    int size;
    int markedCount;
    HANDLE startEvent;
    HANDLE stopEvent;
    HANDLE continueEvent;
    HANDLE finishedEvent;
    CRITICAL_SECTION* cs;
};

DWORD WINAPI MarkerThread(LPVOID lpParam);

#endif
