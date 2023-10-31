// g++ -g projeto1.cpp -o projeto1
// ./projeto1 < grafo.txt

#include <iostream>
#include <algorithm>
#include <list>
#include <fstream>

using namespace std;

list<int> EncontrarCliqueMaxima(vector<vector<int>> grafo, int numVertices);
//vector<vector<int>> LerGrafo(const string& nomeArquivo, int& numVertices);
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

list<int> EncontrarCliqueMaxima(vector<vector<int>> grafo, int numVertices) {
    list<int> cliqueMaxima;
    list<int> candidatos;

    for (int i = 0; i < numVertices; i++) {
        candidatos.push_back(i);  

    }

    while (candidatos.size() > 0) {
        int v = candidatos.back();
        candidatos.pop_back();

        bool podeAdicionar = true;

        for (const int& u : cliqueMaxima) {
            if (grafo[u][v] == 0) {
                podeAdicionar = false;
                break;
            }
        }

        if (podeAdicionar) {
            cliqueMaxima.push_back(v);
            list<int> novosCandidatos;

            for (const int& u : candidatos) {
                bool adjacenteATodos = true;

                for (const int& c : cliqueMaxima) {
                    if (grafo[u][c] == 0) {
                        adjacenteATodos = false;
                        break;
                    }
                }

                if (adjacenteATodos) {
                    novosCandidatos.push_back(u);
                }
            } 

            candidatos = novosCandidatos;

        }
    }

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