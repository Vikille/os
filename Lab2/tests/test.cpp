#include <gtest/gtest.h>
#include <windows.h>
#include <vector>
#include "../include/threads.h"

TEST(Lab2Tests, MinMaxCorrect) {
    int arr[] = {5, 10, -3, 20, 7};
    ThreadData data{};
    data.arr = arr;
    data.size = 5;

    HANDLE h = CreateThread(NULL, 0, MinMaxThread, &data, 0, NULL);
    WaitForSingleObject(h, INFINITE);
    CloseHandle(h);

    EXPECT_EQ(data.minVal, -3);
    EXPECT_EQ(data.maxVal, 20);
}

TEST(Lab2Tests, AverageCorrect) {
    int arr[] = {10, 20, 30, 40};
    ThreadData data{};
    data.arr = arr;
    data.size = 4;

    HANDLE h = CreateThread(NULL, 0, AverageThread, &data, 0, NULL);
    WaitForSingleObject(h, INFINITE);
    CloseHandle(h);

    EXPECT_DOUBLE_EQ(data.avg, 25.0);
}

TEST(Lab2Tests, ReplaceMinMax) {
    int arr[] = {1, 5, 3, 9, 2};
    ThreadData data{};
    data.arr = arr;
    data.size = 5;

    HANDLE h1 = CreateThread(NULL, 0, MinMaxThread, &data, 0, NULL);
    HANDLE h2 = CreateThread(NULL, 0, AverageThread, &data, 0, NULL);

    WaitForSingleObject(h1, INFINITE);
    WaitForSingleObject(h2, INFINITE);

    CloseHandle(h1);
    CloseHandle(h2);

    for (int i = 0; i < 5; ++i) {
        if (arr[i] == data.minVal || arr[i] == data.maxVal) {
            arr[i] = static_cast<int>(data.avg);
        }
    }

    EXPECT_EQ(arr[0], 4);
    EXPECT_EQ(arr[3], 4);
}

TEST(Lab2Tests, SingleElementArray) {
    int arr[] = {42};
    ThreadData data{};
    data.arr = arr;
    data.size = 1;

    HANDLE h1 = CreateThread(NULL, 0, MinMaxThread, &data, 0, NULL);
    HANDLE h2 = CreateThread(NULL, 0, AverageThread, &data, 0, NULL);

    WaitForSingleObject(h1, INFINITE);
    WaitForSingleObject(h2, INFINITE);

    CloseHandle(h1);
    CloseHandle(h2);

    EXPECT_EQ(data.minVal, 42);
    EXPECT_EQ(data.maxVal, 42);
    EXPECT_DOUBLE_EQ(data.avg, 42.0);
}

TEST(Lab2Tests, NegativeNumbers) {
    int arr[] = {-10, -20, -30};
    ThreadData data{};
    data.arr = arr;
    data.size = 3;

    HANDLE h1 = CreateThread(NULL, 0, MinMaxThread, &data, 0, NULL);
    HANDLE h2 = CreateThread(NULL, 0, AverageThread, &data, 0, NULL);

    WaitForSingleObject(h1, INFINITE);
    WaitForSingleObject(h2, INFINITE);

    CloseHandle(h1);
    CloseHandle(h2);

    EXPECT_EQ(data.minVal, -30);
    EXPECT_EQ(data.maxVal, -10);
    EXPECT_DOUBLE_EQ(data.avg, -20.0);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
