#include <iostream>
#include <cstdlib>
#include <ctime>
#include <mpi.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    const int n = 10;
    int* data = nullptr;
    
    if (rank == 1) {
        data = new int[n];
        srand(time(nullptr));
        for (int i = 0; i < n; i++) {
            data[i] = rand() % 100;
        }
        
        for (int dest = 0; dest < size; dest++) {
            if (dest != 1) {
                MPI_Send(data, n, MPI_INT, dest, 0, MPI_COMM_WORLD);
            }
        }
    }
    else {
        int recvCount;
        MPI_Status status;
        
        MPI_Probe(1, 0, MPI_COMM_WORLD, &status);
        MPI_Get_count(&status, MPI_INT, &recvCount);
        
        int* recvData = new int[recvCount];
        
        MPI_Recv(recvData, recvCount, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        
        std::cout << "Процесс " << rank << " принял следующий массив:" << std::endl;
        for (int i = 0; i < recvCount; i++) {
            std::cout << recvData[i] << " ";
        }
        std::cout << std::endl;
        
        delete[] recvData;
    }
    
    if (data != nullptr) {
        delete[] data;
    }
    
    MPI_Finalize();
    
    return 0;
}