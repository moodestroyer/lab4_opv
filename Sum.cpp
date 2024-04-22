#include <iostream>
#include <omp.h>
#include <ctime>
#include <chrono>

void printMaxThreads() {
    int max_threads = omp_get_max_threads();
    std::cout << "Максимальное количество потоков: " << max_threads << std::endl;
}

int main() {

    setlocale(LC_ALL, "Russian");
    const int size = 10000;

    int* arr = new int[size];
    srand(time(nullptr));
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 100;
    }

    int sum = 0;
    auto start_time = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    auto end_time = std::chrono::high_resolution_clock::now();
    std::cout << "Сумма без использования потоков: " << sum << std::endl;
    std::cout << "Сколько времени заняло: " << std::chrono::duration_cast<std::chrono::duration<double>>(end_time - start_time).count() << " секунд" << std::endl;

    sum = 0;
    start_time = std::chrono::high_resolution_clock::now();

#pragma omp parallel num_threads(4) for reduction(+:sum)
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    end_time = std::chrono::high_resolution_clock::now();
    std::cout << "Сумма с использованием потоков: " << sum << std::endl;
    std::cout << "Сколько времени заняло: " << std::chrono::duration_cast<std::chrono::duration<double>>(end_time - start_time).count() << " секунд" << std::endl;

    delete[] arr;

    return 0;
}