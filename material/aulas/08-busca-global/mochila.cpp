//g++ -g mochila.cpp -o mochila
//./mochila

#include <iostream>
#include <algorithm>

using namespace std;

struct Item{
    int id;
    double peso;
    double valor;
};

void carregaDados(int& N, int& W, vector<Item>& itens);
int mochila(int N, int W, vector<Item> itens, vector<int>& melhor_mochila);
int max(int a, int b);

int main() {

    int N;
    int W;
    vector<Item> itens;
    vector<int> melhor_mochila;

    // Leitura dos Dados
    carregaDados(N, W, itens);

    cout << "Valor: " << mochila(N, W, itens, melhor_mochila) <<endl;
    sort(melhor_mochila.begin(), melhor_mochila.end());
    melhor_mochila.erase(unique(melhor_mochila.begin(), melhor_mochila.end()), melhor_mochila.end());

    cout << "Mochila: ";
    for (const int& i : melhor_mochila) {
        cout << i << " ";
    }
    cout << endl;

    return 0;
}

int mochila(int N, int W, vector<Item> itens, vector<int>& melhor_mochila) {
    if (N==0 || W == 0) {
        return 0;
    }
    int sem_i = 0;
    int com_i = 0;
    
    if (itens[N-1].peso > W){
        melhor_mochila.erase(remove(melhor_mochila.begin(), melhor_mochila.end(), itens[N-1].id), melhor_mochila.end());
        sem_i = mochila(N-1, W, itens, melhor_mochila);
        return sem_i;
    }
    else{
        sem_i = mochila(N-1, W, itens, melhor_mochila);
        com_i = mochila(N-1, W - itens[N - 1].peso, itens, melhor_mochila);
        if (itens[N-1].valor + com_i > sem_i) {
            melhor_mochila.push_back(itens[N-1].id);
            return itens[N-1].valor + com_i;
        }
        else {
            melhor_mochila.erase(remove(melhor_mochila.begin(), melhor_mochila.end(), itens[N-1].id), melhor_mochila.end());
            return sem_i;
        }
    }

    return 0;
}

void carregaDados(int& N, int& W, vector<Item>& itens) {
    cin >> N >> W;

    double w, v;
    for (int i = 0; i < N; i++) {
        cin >> w >> v;
        Item x = {i, w, v};
        itens.push_back(x);
    }
}

