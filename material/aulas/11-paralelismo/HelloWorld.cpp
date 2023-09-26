//g++ -g -Wall -fopenmp -o HelloWorld HelloWorld.cpp
// ./HelloWorld
#include <iostream>
#include <unistd.h>
#include <omp.h>
using namespace std;

int main() {

    #pragma omp parallel
    {
        cout << "Hello World" << "\n";
    }
}
