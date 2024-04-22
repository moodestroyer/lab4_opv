#include <iostream>
#include <omp.h>
#include <algorithm>
#include <mutex>

int main() {
    int k, N;
    std::cout << "Num of threads: ";
    std::cin >> k;
    std::cout << "Value of N: ";
    std::cin >> N;

    int* numbers = new int[N];
    for (int i = 0; i < N; ++i) {
        numbers[i] = i + 1;
    }

    int actualThreads = std::min(k, N);

    int* results = new int[actualThreads];
    int totalSum = 0;

    std::mutex outputMutex;

#pragma omp parallel num_threads(actualThreads) reduction(+:totalSum)
    {
        int rank = omp_get_thread_num();
        int sum = 0;

#pragma omp for schedule(static) 
        for (int i = 0; i < N; ++i) {
            sum += numbers[i];
        }

#pragma omp critical
        {
            results[rank] = sum;
        }

#pragma omp barrier 

#pragma omp master
        {
            std::sort(results, results + actualThreads);

            for (int i = 0; i < actualThreads; ++i) {
                std::lock_guard<std::mutex> lock(outputMutex);
                std::cout << "[" << i << "]: Sum = " << results[i] << std::endl;
                totalSum += results[i];
            }

            std::cout << "Sum = " << totalSum << std::endl;
        }
    }

    delete[] numbers;
    delete[] results;

    return 0;
}