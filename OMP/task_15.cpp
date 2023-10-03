#include <iostream>
#include <vector>
#include <omp.h>
#include <algorithm>

bool is_prime(int num) {
    if (num <= 1) {
        return false;
    }
    if (num <= 3) {
        return true;
    }
    if (num % 2 == 0 || num % 3 == 0) {
        return false;
    }
    for (int i = 5; i * i <= num; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    int start, end;

    std::cout << "Enter the start of the range: ";
    std::cin >> start;

    std::cout << "Enter the end of the range: ";
    std::cin >> end;

    if (start > end) {
        std::cout << "Invalid range!" << std::endl;
        return 1;
    }

    int num_threads = omp_get_max_threads();

    std::vector<int> primes;

    #pragma omp parallel for num_threads(num_threads)
    for (int num = start; num <= end; num++) {
        if (is_prime(num)) {
            #pragma omp critical
            primes.push_back(num);
        }
    }

    printf("Prime numbers in the range %d to %d: \n", start, end);
    std::sort(primes.begin(), primes.end());
    for (int prime : primes) {
        printf("%d ", prime);
    }
    printf("\n");

}