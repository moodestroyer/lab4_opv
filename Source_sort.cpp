#include <iostream>
#include <vector>
#include <random>
#include <omp.h>

void merge(std::vector<int>& array, int left, int middle, int right) {
    int n1 = middle - left + 1;
    int n2 = right - middle;

    std::vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; ++i)
        L[i] = array[left + i];
    for (int j = 0; j < n2; ++j)
        R[j] = array[middle + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            array[k] = L[i];
            ++i;
        }
        else {
            array[k] = R[j];
            ++j;
        }
        ++k;
    }

    while (i < n1) {
        array[k] = L[i];
        ++i;
        ++k;
    }

    while (j < n2) {
        array[k] = R[j];
        ++j;
        ++k;
    }
}

void mergeSort(std::vector<int>& array, int left, int right) {
    if (left < right) {
        int middle = left + (right - left) / 2;

        mergeSort(array, left, middle);
        mergeSort(array, middle + 1, right);

        merge(array, left, middle, right);
    }
}

int main() {
    const int size = 1000;
    std::vector<int> array(size);

    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, size);
    for (int i = 0; i < size; ++i) {
        array[i] = dis(gen);
    }

    std::cout << "Original array: ";
    for (int i = 0; i < size; ++i)
        std::cout << array[i] << " ";
    std::cout << std::endl;

    double start_time = omp_get_wtime();
    mergeSort(array, 0, size - 1);
    double end_time = omp_get_wtime();

    std::cout << "Sorted array: ";
    for (int i = 0; i < size; ++i)
        std::cout << array[i] << " ";
    std::cout << std::endl;

    std::cout << "Time taken: " << end_time - start_time << " seconds" << std::endl;

    return 0;
}