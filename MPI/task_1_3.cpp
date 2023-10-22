#include <iostream>
#include <cstdlib>
#include <ctime>
#include <mpi.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    if (size != 2) {
        if (rank == 0) {
            std::cerr << "Эта программа должна быть запущена на двух процессах." << std::endl;
        }
        MPI_Finalize();
        return 1;
    }
    
    const int n = 10;
    int* a = nullptr;
    
    if (rank == 0) {
        a = new int[n];
        srand(time(nullptr));
        for (int i = 0; i < n; i++) {
            a[i] = rand() % 100;
        }
        
        MPI_Send(a, n, MPI_INT, 1, 0, MPI_COMM_WORLD);
    }
    
    if (rank == 1) {
        a = new int[n];
        MPI_Recv(a, n, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        
        std::cout << "Процесс " << rank << " принял следующий массив:" << std::endl;
        for (int i = 0; i < n; i++) {
            std::cout << a[i] << " ";
        }
        std::cout << std::endl;
    }
    
    delete[] a;
    MPI_Finalize();
    
    return 0;
}