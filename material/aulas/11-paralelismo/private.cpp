//g++ -g -Wall -fopenmp -o private private.cpp
// ./private
#include <iostream>
#include <unistd.h>
#include <omp.h>
using namespace std;

int main() {

    int iam;
    #pragma omp parallel private(iam)
    {
        iam = omp_get_thread_num();
        #pragma omp critical
        cout <<  "Hello from thread number " << iam << "\n";
    }

    return 0;

}
