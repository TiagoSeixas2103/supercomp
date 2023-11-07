// g++ -g projeto1.cpp -o projeto1
// ./projeto1

#include <iostream>
#include <algorithm>
#include <list>
#include <fstream>
#include <vector>

using namespace std;

void Recursao(vector<vector<int>>& grafo, list<int>& clique, list<int>& candidatos, list<int>& cliqueMaxima);
list<int> EncontrarCliqueMaxima(vector<vector<int>>& grafo, int numVertices);
vector<vector<int>> LerGrafo(int& numVertices);

int main() {
    int numVertices;
    vector<vector<int>> grafo;
    list<int> cliqueMaxima;

    // Leitura dos Dados
    grafo = LerGrafo(numVertices);

    cliqueMaxima = EncontrarCliqueMaxima(grafo, numVertices);

    cout << "Clique máxima encontrada: [";

    int i = 0;
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

void Recursao(vector<vector<int>>& grafo, list<int>& clique, list<int>& candidatos, list<int>& cliqueMaxima) {
    if (candidatos.empty() && cliqueMaxima.size() < clique.size()) {
        cliqueMaxima = clique;
        return;
    }

    list<int> candidatosCopia = candidatos;
    for (int u : candidatosCopia) {
        list<int> novos_candidatos;

        for (int c : candidatos) {
            if (grafo[u][c] == 1) {
                novos_candidatos.push_back(c);
            }
        }

        clique.push_back(u);
        Recursao(grafo, clique, novos_candidatos, cliqueMaxima);
        clique.pop_back();

        candidatos.remove(u);
    }

}

list<int> EncontrarCliqueMaxima(vector<vector<int>>& grafo, int numVertices) {
    list<int> clique;
    list<int> candidatos;
    list<int> cliqueMaxima; 

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