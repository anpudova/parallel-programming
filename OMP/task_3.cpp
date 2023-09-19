#include <iostream>
#include <omp.h>

int main()
{
	int a = 7;
	int b = 10;

	printf("Before 1 parallel region: a = %d, b = %d \n", a, b);

	#pragma omp parallel num_threads(2) private(a) firstprivate(b)
	{
		a = 7;
		int num = omp_get_thread_num();
        
		a += num;
		b += num;

		printf("In 1 parallel region : a = %d, b = %d \n", a, b);
	}

	printf("After 1 parallel region : a = %d, b = %d \n", a, b);

	printf("Before 2 parallel region: a = %d, b = %d \n", a, b);

	#pragma omp parallel num_threads(4) shared(a) private(b)
	{
		b = 10;
		int num = omp_get_thread_num();

		#pragma omp atomic
		a -= num;
		b -= num;

		printf("In 2 parallel region : a = %d, b = %d \n", a, b);
	}

	printf("After 2 parallel region : a = %d, b = %d", a, b);
}
