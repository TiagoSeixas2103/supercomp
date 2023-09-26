//g++ -g -Wall -fopenmp -o critical critical.cpp
// ./critical
#include <iostream>
#include <unistd.h>
#include <omp.h>
using namespace std;

int main() {
    int a = 0;

    #pragma omp parallel
    {
        #pragma omp critical
        a = a + omp_get_thread_num();
    }

    cout << a << "\n";
}
