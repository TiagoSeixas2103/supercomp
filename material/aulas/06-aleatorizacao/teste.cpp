//g++ -g teste.cpp -o teste
//./teste
#include <iostream>
#include <algorithm>
#include <random>
#include <list>

using namespace std;

int main() {
    int i, N;
    i = 2;
    N = 6;
    default_random_engine gerador2(25);
    uniform_int_distribution<int> distribution(i, N);
    for (int i=0; i<20; i++) {
        int val = distribution(gerador2);
        cout << val << endl;
    } 
    
    cout << gerador2 << endl;

    return 0;
}