//g++ -g -Wall -fopenmp -o pi pi.cpp
// ./pi

#include<stdio.h>
#include<stdlib.h>
#include <iostream>
#include <omp.h>
using namespace std;

int main() {

    int N  = 1000000000;
    int dentro_circulo = 0;

    unsigned int seed = 100;
    double init_time, final_time;
    init_time = omp_get_wtime();
    #pragma omp parallel for reduction(+:dentro_circulo)
    for (int i = 0; i < N; i++) {
        double x = (double)rand_r(&seed) / RAND_MAX;
        double y = (double)rand_r(&seed) / RAND_MAX;

        if (x*x + y*y <= 1.0) {
            dentro_circulo++;
        }
    }
    final_time = omp_get_wtime() - init_time;
    

    double pi_estimado = 4 * (double)dentro_circulo / N;
    cout << "Time: " << final_time << endl;
    cout << "Pi: " << pi_estimado << endl;
}