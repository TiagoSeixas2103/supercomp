// g++ -g -Wall -fopenmp -o fib fib.cpp
// ./fib

#include <iostream>
#include <omp.h>

using namespace std;

int fib(int n) {
    int x, y;
    if (n < 2) return n;
    x = fib(n-1);
    y= fib(n-2);
    return x+y;
}

int main() {
    int NW = 40;
    float time = omp_get_wtime();
    fib(NW);
    time = omp_get_wtime() - time;
    cout << "Tempo em segundos: " << time << endl;

}