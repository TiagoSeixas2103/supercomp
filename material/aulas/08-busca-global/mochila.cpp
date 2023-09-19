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
int mochila(int W, vector<Item> itens,vector<Item>& usados, vector<Item>& melhor_mochila);

int main() {

    int N;
    int W;
    vector<Item> itens;
    vector<Item> melhor_mochila;
    vector<Item> usados;

    // Leitura dos Dados
    carregaDados(N, W, itens);

    cout << "Valor: " << mochila(W, itens, usados, melhor_mochila) <<endl;
    //sort(melhor_mochila.begin(), melhor_mochila.end());
    //.erase(unique(melhor_mochila.begin(), melhor_mochila.end()), melhor_mochila.end());

    cout << "Mochila: ";
    for (const Item& i : melhor_mochila) {
        cout << i.id << " ";
    }
    cout << endl;

    return 0;
}

int mochila(int W, vector<Item> itens, vector<Item>& usados, vector<Item>& melhor_mochila) {
    double sem_i = 0.0;
    double com_i = 0.0;
    double v = 0.0;
    double p = 0.0;

    vector<Item> itens2 = itens;

    if (itens.size()==0 || W == 0) {
        return 0;
    }

    if (itens[0].peso <= W) {
        usados.push_back(itens[0]);
        v = itens[0].valor;
        p = itens[0].peso;
        itens.erase(itens.begin());
        com_i = mochila(W-p, itens, usados, melhor_mochila);
    }

    itens2.erase(itens2.begin());
    sem_i = mochila(W, itens2, usados, melhor_mochila);

    double valor_atual = 0.0;
    for (auto& elemento_atual : usados) {
        valor_atual += elemento_atual.valor;
    }

    double melhor_valor = 0.0;
    for (auto& elemento_atual : melhor_mochila) {
        melhor_valor += elemento_atual.valor;
    }

    if (valor_atual > melhor_valor) {
        melhor_mochila = usados;
    }

    usados.clear();
    return max(sem_i, v+com_i);
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

