#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace chrono;

const int MAX_SIZE = 10000;

void generateRandomNumbers(int arr[], int n) {
    for (int i = 0; i < n; ++i) {
        arr[i] = rand() % (n * 10) + 1;
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; ++i)
        cout << arr[i] << " ";
    cout << endl;
}

int binarySearch(int arr[], int n, int target, long long &comparisons) {
    int left = 0, right = n - 1;
    comparisons = 0;

    while (left <= right) {
        comparisons++;
        int mid = left + (right - left) / 2;
        comparisons++;
        if (arr[mid] == target) return mid;
        comparisons++;
        if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

int exponentialSearch(int arr[], int n, int target, long long &comparisons) {
    comparisons = 0;
    if (n == 0) return -1;
    if (arr[0] == target) return 0;

    int i = 1;
    while (i < n && arr[i] <= target) {
        comparisons += 2;
        i *= 2;
    }

    int left = i / 2, right = min(i, n - 1);
    while (left <= right) {
        comparisons++;
        int mid = left + (right - left) / 2;
        comparisons++;
        if (arr[mid] == target) return mid;
        comparisons++;
        if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

void quickSort(int arr[], int low, int high, long long &comparisons) {
    if (low < high) {
        int pivot = arr[high], i = low - 1;
        for (int j = low; j < high; j++) {
            comparisons++;
            if (arr[j] <= pivot) {
                i++;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[high]);
        int pi = i + 1;

        quickSort(arr, low, pi - 1, comparisons);
        quickSort(arr, pi + 1, high, comparisons);
    }
}

void merge(int arr[], int left, int mid, int right, long long &comparisons) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int L[MAX_SIZE], R[MAX_SIZE];

    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        comparisons++;
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(int arr[], int left, int right, long long &comparisons) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid, comparisons);
        mergeSort(arr, mid + 1, right, comparisons);
        merge(arr, left, mid, right, comparisons);
    }
}

int main() {
    srand(time(0));

    int choice, algo, n;
    int data[MAX_SIZE], copy[MAX_SIZE];

    while (true) {
        cout << "\n1. Sort\n2. Search\n0. Exit\nChoice: ";
        cin >> choice;

        if (choice == 0) break;

        cout << "Enter number of elements: ";
        cin >> n;
        if (n <= 0 || n > MAX_SIZE) {
            cout << "Invalid size.\n";
            continue;
        }

        generateRandomNumbers(data, n);
        cout << "Generated array:\n";
        printArray(data, n);

        if (choice == 1) {
            cout << "1. Quick Sort\n2. Merge Sort\nChoice: ";
            cin >> algo;
            for (int i = 0; i < n; i++) copy[i] = data[i];

            long long comparisons = 0;
            auto start = high_resolution_clock::now();

            if (algo == 1)
                quickSort(copy, 0, n - 1, comparisons);
            else
                mergeSort(copy, 0, n - 1, comparisons);

            auto end = high_resolution_clock::now();
            auto duration = duration_cast<nanoseconds>(end - start);

            cout << "Sorted array:\n";
            printArray(copy, n);
            cout << "Time taken: " << duration.count() << " ns\n";
            cout << "Comparisons: " << comparisons << endl;
        }

        else if (choice == 2) {
            sort(data, data + n); // use std::sort for simplicity
            cout << "Sorted array:\n";
            printArray(data, n);

            int target;
            cout << "Enter target to search: ";
            cin >> target;
            cout << "1. Binary Search\n2. Exponential Search\nChoice: ";
            cin >> algo;

            int result = -1;
            long long comparisons = 0;
            auto start = high_resolution_clock::now();

            if (algo == 1)
                result = binarySearch(data, n, target, comparisons);
            else
                result = exponentialSearch(data, n, target, comparisons);

            auto end = high_resolution_clock::now();
            auto duration = duration_cast<nanoseconds>(end - start);

            if (result != -1)
                cout << "Found at index: " << result << endl;
            else
                cout << "Not found.\n";

            cout << "Time taken: " << duration.count() << " ns\n";
            cout << "Comparisons: " << comparisons << endl;
        }
    }
    return 0;
}
