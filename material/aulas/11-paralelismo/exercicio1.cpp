//g++ -g -Wall -fopenmp -o exercicio1 exercicio1.cpp
// ./exercicio1
#include <iostream>
#include <unistd.h>
#include <omp.h>

using namespace std;

double funcao1() {
    sleep(3);
    return 47;
}

double funcao2() {
    sleep(3);
    return -11.5;
}

int main() {
    double res_func1, res_func2;

    #pragma omp parallel
    {
        #pragma omp master 
        {
            #pragma omp task
                res_func1 = funcao1();
            #pragma omp task
                res_func2 = funcao2();
        }
        
    }

    cout << res_func1 << " " << res_func2 << "\n";
}
