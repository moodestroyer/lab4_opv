#include <iostream>
#include <random>
#include <omp.h>

int main() {
    setlocale(LC_ALL, "Russian");
    int num_points = 10000000; 
    int num_inside_circle = 0;
    int num_threads = 4;

    double start_time = omp_get_wtime(); 

    #pragma omp parallel num_threads(num_threads)
    {
        unsigned int seed = omp_get_thread_num();
        std::mt19937 rng(seed);
        std::uniform_real_distribution<double> dist(0, 1);

        int local_inside_circle = 0;

        #pragma omp for
        for (int i = 0; i < num_points; i++) {
            double x = dist(rng);
            double y = dist(rng);
            if (x * x + y * y <= 1.0 * 1.0) {
                local_inside_circle++;
            }
        }

        #pragma omp atomic
        num_inside_circle += local_inside_circle;
    }

    double end_time = omp_get_wtime(); 

    double pi = 4.0 * num_inside_circle / num_points;

    std::cout << "Потоки = " << num_threads << std::endl;
    std::cout << "Точки = " << num_points << std::endl;
    std::cout << "Число Пи = " << pi << std::endl;
    std::cout << "Сколько времени заняло: " << end_time - start_time << " секунд" << std::endl; 

    return 0;
}
