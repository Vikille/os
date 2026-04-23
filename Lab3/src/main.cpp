#include <windows.h>
#include <iostream>
#include <vector>
#include "marker.h"

using namespace std;

DWORD WINAPI MarkerThread(LPVOID lpParam) {
    MarkerData* data = static_cast<MarkerData*>(lpParam);

    WaitForSingleObject(data->startEvent, INFINITE);
    srand(data->id);

    while (true) {
        int r = rand() % data->size;

        EnterCriticalSection(data->cs);
        if (data->arr[r] == 0) {
            Sleep(5);
            data->arr[r] = data->id;
            data->markedCount++;
            Sleep(5);
            LeaveCriticalSection(data->cs);
        } else {
            cout << "Marker " << data->id
                 << " blocked. Marked: " << data->markedCount
                 << " Index: " << r << endl;

            LeaveCriticalSection(data->cs);
            SetEvent(data->finishedEvent);

            HANDLE events[2] = { data->continueEvent, data->stopEvent };
            DWORD res = WaitForMultipleObjects(2, events, FALSE, INFINITE);

            if (res == WAIT_OBJECT_0 + 1) {
                EnterCriticalSection(data->cs);
                for (int i = 0; i < data->size; ++i) {
                    if (data->arr[i] == data->id) data->arr[i] = 0;
                }
                LeaveCriticalSection(data->cs);
                return 0;
            }
        }
    }
}

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    int size;
    cout << "Enter array size: ";
    cin >> size;

    int* arr = new int[size];
    for (int i = 0; i < size; ++i) arr[i] = 0;

    int n;
    cout << "Enter number of marker threads: ";
    cin >> n;

    vector<HANDLE> threads(n);
    vector<MarkerData> data(n);

    CRITICAL_SECTION cs;
    InitializeCriticalSection(&cs);

    HANDLE startEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

    vector<HANDLE> finishedEvents(n);
    vector<HANDLE> stopEvents(n);
    vector<HANDLE> continueEvents(n);

    for (int i = 0; i < n; ++i) {
        finishedEvents[i] = CreateEvent(NULL, FALSE, FALSE, NULL);
        stopEvents[i] = CreateEvent(NULL, TRUE, FALSE, NULL);
        continueEvents[i] = CreateEvent(NULL, TRUE, FALSE, NULL);

        data[i].id = i + 1;
        data[i].arr = arr;
        data[i].size = size;
        data[i].markedCount = 0;
        data[i].startEvent = startEvent;
        data[i].stopEvent = stopEvents[i];
        data[i].continueEvent = continueEvents[i];
        data[i].finishedEvent = finishedEvents[i];
        data[i].cs = &cs;

        threads[i] = CreateThread(NULL, 0, MarkerThread, &data[i], 0, NULL);
    }

    SetEvent(startEvent);

    int alive = n;

    while (alive > 0) {
        WaitForMultipleObjects(n, finishedEvents.data(), TRUE, INFINITE);

        cout << "Array: ";
        for (int i = 0; i < size; ++i) cout << arr[i] << ' ';
        cout << endl;

        int killId;
        cout << "Enter marker id to stop: ";
        cin >> killId;

        SetEvent(stopEvents[killId - 1]);
        WaitForSingleObject(threads[killId - 1], INFINITE);

        cout << "Array after removal: ";
        for (int i = 0; i < size; ++i) cout << arr[i] << ' ';
        cout << endl;

        ResetEvent(finishedEvents[killId - 1]);
        alive--;

        for (int i = 0; i < n; ++i) {
            if (i != killId - 1) {
                ResetEvent(finishedEvents[i]);
                SetEvent(continueEvents[i]);
            }
        }
    }

    DeleteCriticalSection(&cs);

    for (int i = 0; i < n; ++i) {
        CloseHandle(threads[i]);
        CloseHandle(finishedEvents[i]);
        CloseHandle(stopEvents[i]);
        CloseHandle(continueEvents[i]);
    }

    CloseHandle(startEvent);
    delete[] arr;

    return 0;
}
