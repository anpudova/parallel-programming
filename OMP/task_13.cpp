#include <iostream>
#include <omp.h>
#include <math.h>

int main() {
    int a[30] = {1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1};
    int p = 2;
    int result = 0;
    int n = 30;

    #pragma omp parallel for reduction(+:result)
    for (int i = 0; i < n; i++) {
        int power = n - i - 1;
        int digit = a[i];
        result += digit * pow(p, power);
    }

    printf("Result = %d \n", result);
}