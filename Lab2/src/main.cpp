#include <windows.h>
#include <iostream>
#include <new>
#include "threads.h"

using namespace std;

DWORD WINAPI MinMaxThread(LPVOID lpParam) {
    ThreadData* data = static_cast<ThreadData*>(lpParam);
    int minVal = data->arr[0];
    int maxVal = data->arr[0];

    for (int i = 1; i < data->size; ++i) {
        if (data->arr[i] < minVal) minVal = data->arr[i];
        if (data->arr[i] > maxVal) maxVal = data->arr[i];
        Sleep(7);
    }

    data->minVal = minVal;
    data->maxVal = maxVal;

    cout << "Thread min_max: min = " << minVal
         << ", max = " << maxVal << endl;

    return 0;
}

DWORD WINAPI AverageThread(LPVOID lpParam) {
    ThreadData* data = static_cast<ThreadData*>(lpParam);
    long long sum = 0;

    for (int i = 0; i < data->size; ++i) {
        sum += data->arr[i];
        Sleep(12);
    }

    data->avg = static_cast<double>(sum) / data->size;

    cout << "Thread average: avg = " << data->avg << endl;

    return 0;
}

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    int n;
    cout << "Enter array size: ";
    cin >> n;

    int* arr = new (nothrow) int[n];

    cout << "Enter " << n << " integers:" << endl;
    for (int i = 0; i < n; ++i) cin >> arr[i];

    ThreadData data{};
    data.arr = arr;
    data.size = n;

    HANDLE hMinMax = CreateThread(NULL, 0, MinMaxThread, &data, 0, NULL);
    HANDLE hAverage = CreateThread(NULL, 0, AverageThread, &data, 0, NULL);

    WaitForSingleObject(hMinMax, INFINITE);
    WaitForSingleObject(hAverage, INFINITE);

    CloseHandle(hMinMax);
    CloseHandle(hAverage);

    cout << "Main: replacing min and max with average value." << endl;

    for (int i = 0; i < n; ++i) {
        if (arr[i] == data.minVal || arr[i] == data.maxVal) {
            arr[i] = static_cast<int>(data.avg);
        }
    }

    cout << "Result array: ";
    for (int i = 0; i < n; ++i) cout << arr[i] << ' ';
    cout << endl;

    delete[] arr;
    return 0;
}
