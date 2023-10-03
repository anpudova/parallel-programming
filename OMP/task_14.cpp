#include <iostream>
#include <omp.h>

int main() {

    int result = 0;
    
    #pragma omp parallel for reduction(+:result)
    for (int i = 0; i < 210; i++) {
        result += 2 * i + 1;
    }

    printf("Result = %d \n", result);
}