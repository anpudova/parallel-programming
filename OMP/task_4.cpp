#include <iostream>
#include <omp.h>

int main() {
    int a[10] = {10, 4, 7, 1, 15, 8, 9, 2, 6, 3};
    int b[10] = {5, 12, 8, 20, 3, 17, 1, 9, 6, 11};
    
    int min_a = a[0];
    int max_b = b[0];

    #pragma omp parallel num_threads(2)
    {
        int thread_id = omp_get_thread_num();

        if (thread_id == 0) {
            for (int i = 1; i < 10; ++i) {
                if (a[i] < min_a) {
                    min_a = a[i];
                }
            }
        } else if (thread_id == 1) {
            for (int i = 1; i < 10; ++i) {
                if (b[i] > max_b) {
                    max_b = b[i];
                }
            }
        }
    }

    printf("Min value in a: %d \n", min_a);
    printf("Max value in b: %d \n", max_b);

    return 0;
}
