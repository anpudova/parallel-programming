#include <iostream>
#include <mpi.h>

int const n = 12;
void print(int* a, int start, int size);

int main(int argc, char** argv) {

    int size, rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int step = n / size + 1;
    int* b = new int[step];

    if (rank == 0) {
        int* a = new int[n];
        
        for (int i = 0; i < n; i++) {
            a[i] = i + 1;
            printf("%d ", a[i]);
        }
        printf("\n");

        int start = step;
        for (int i = 1; i < size; i++) {
            if ((start + step) >= n) {
                MPI_Send(a + start, n - start, MPI_INT, i, 10, MPI_COMM_WORLD);
                break;
            } else {
                MPI_Send(a + start, step, MPI_INT, i, 10, MPI_COMM_WORLD);
            }
            start += step;
        }

        printf("Process %d: ", rank);
        print(a, 0, step);
        printf("\n");

    } else {
        b = new int[step];

        if ((rank * step + step) - n < step) {
            printf("Process %d: ", rank);
            int block_size;
            if (rank * step + step > n) {
                block_size = n - rank * step;
            } else {
                block_size = step;
            }
            MPI_Recv(b, block_size, MPI_INT, 0, 10, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            print(b, 0, block_size);
            printf("\n");
        }
    }

    MPI_Finalize();

    return 0;
}


void print(int* a, int start, int size) {
    for (int i = start; i < size; i++) {
        printf("%d ", a[i]);
    }
}