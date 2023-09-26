//g++ -g -Wall -fopenmp -o race race.cpp
// ./race
#include <iostream>
#include <unistd.h>
#include <omp.h>
using namespace std;

int main() {
    int a = 0;

    #pragma omp parallel
    {
        a = a + omp_get_thread_num();
    }

    cout << a << "\n";
}
