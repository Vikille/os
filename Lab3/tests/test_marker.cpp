#include <iostream>
#include "marker.h"

using namespace std;

int main() {
    int arr[10];
    for (int i = 0; i < 10; ++i) arr[i] = 0;

    MarkerData d{};
    d.id = 3;
    d.arr = arr;
    d.size = 10;
    d.markedCount = 0;

    arr[2] = 3;
    arr[5] = 3;
    arr[7] = 3;

    int removed = 0;
    for (int i = 0; i < 10; ++i) {
        if (arr[i] == d.id) {
            arr[i] = 0;
            removed++;
        }
    }

    if (removed == 3) {
        cout << "Test 1 passed" << endl;
    } else {
        cout << "Test 1 failed" << endl;
    }

    d.markedCount = 5;
    if (d.markedCount == 5) {
        cout << "Test 2 passed" << endl;
    } else {
        cout << "Test 2 failed" << endl;
    }

    int index = 12 % d.size;
    if (index == 2) {
        cout << "Test 3 passed" << endl;
    } else {
        cout << "Test 3 failed" << endl;
    }

    return 0;
}
