#include <iostream>
#include <omp.h>
#include <string>

int main() {
    int num_threads = 8;
    omp_set_num_threads(num_threads);

    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        int num_threads = omp_get_num_threads();
        
        std::string res = "Thread ID: " + std::to_string(thread_id) + " of " + std::to_string(num_threads) + " threads. Hello World!\n";
        std::cout << res;
    }

    return 0;
}