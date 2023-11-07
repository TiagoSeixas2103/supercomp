// g++ -g -Wall -fopenmp projeto1parallel.cpp -o projeto1parallel
// ./projeto1parallel < grafo.txt

#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <omp.h>
#include <unistd.h>

using namespace std;

void Recursao(vector<vector<int>>& grafo, vector<int>& clique, vector<int>& candidatos, vector<int>& cliqueMaxima);
vector<int> EncontrarCliqueMaxima(vector<vector<int>>& grafo, int numVertices);
vector<vector<int>> LerGrafo(int& numVertices);

int main() {
    int numVertices;
    vector<vector<int>> grafo;
    vector<int> cliqueMaxima;

    // Leitura dos Dados
    grafo = LerGrafo(numVertices);

    float time = omp_get_wtime();
    cliqueMaxima = EncontrarCliqueMaxima(grafo, numVertices);
    time = omp_get_wtime() - time;
    cout << "Tempo: " << time << "\n";

    cout << "Clique máxima encontrada: [";

    long unsigned int i = 0;
    for (const int& element : cliqueMaxima) {
        cout << "'" << element + 1 << "'";
        if (i < cliqueMaxima.size() - 1) {
            cout << ", ";
            i++;
        }
    }

    cout << "]" << endl;

    return 0;
}

void Recursao(vector<vector<int>>& grafo, vector<int>& clique, vector<int>& candidatos, vector<int>& cliqueMaxima) {
    if (candidatos.empty() && cliqueMaxima.size() < clique.size()) {
        cliqueMaxima = clique;
        return;
    }

    vector<int> candidatosCopia = candidatos;

    for (long unsigned int i = 0; i < candidatosCopia.size(); i++) {
        int u = candidatosCopia[i];
        vector<int> novos_candidatos;

        for (long unsigned int j = 0; j < candidatos.size(); j++) {
            int c = candidatos[j];
            if (grafo[u][c] == 1) {
                novos_candidatos.push_back(c);
            }
        }

        clique.push_back(u);
        Recursao(grafo, clique, novos_candidatos, cliqueMaxima);
        clique.pop_back();

        candidatos.erase(remove(candidatos.begin(), candidatos.end(), u), candidatos.end());
    }
}

vector<int> EncontrarCliqueMaxima(vector<vector<int>>& grafo, int numVertices) {
    vector<int> clique;
    vector<int> candidatos;
    vector<int> cliqueMaxima; 

    for (int i = 0; i < numVertices; i++) {
        candidatos.push_back(i);
    }

    Recursao(grafo, clique, candidatos, cliqueMaxima);
    return cliqueMaxima;
}

// Função para ler o grafo a partir do arquivo de entrada
vector<vector<int>> LerGrafo(int& numVertices) {
    int numArestas;
    cin >> numVertices >> numArestas;

    vector<vector<int>> grafo(numVertices, vector<int>(numVertices, 0));

    for (int i = 0; i < numArestas; ++i) {
        int u, v;
        cin >> u >> v;
        grafo[u - 1][v - 1] = 1;
        grafo[v - 1][u - 1] = 1;  // O grafo é não direcionado
    }

    return grafo;
}