#include <iostream>
#include <omp.h>

void result(int num_thread);

int main() 
{
    int num_threads1 = 3;
    int num_threads2 = 1;

    omp_set_num_threads(num_threads1);
    #pragma omp parallel if (num_threads1 > 1)
    {
        result(1);
    }

    omp_set_num_threads(num_threads2);
    #pragma omp parallel if (num_threads2 > 1)
    {
        result(2);
    }

    return 0;
}

void result(int num_thread) {
        int thread_id = omp_get_thread_num();
        int num_threads = omp_get_num_threads();

        std::string res = "Parallel region " + std::to_string(num_thread) + ": Thread " + std::to_string(thread_id) + " of " + std::to_string(num_threads) + "\n";
        std::cout << res;
}
