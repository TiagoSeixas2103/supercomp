//g++ -g mais_caro.cpp -o mais_caro
//./mais_caro
#include <iostream>
#include <algorithm>

using namespace std;

struct Item{
    int id;
    double peso;
    double valor;
};

void carregaDados(int& N, int& W, vector<Item>& itens);
bool compara_valor(const Item& a, const Item& b);
bool compara_peso(const Item& a, const Item& b);

int main() {

    int N;
    int W;
    vector<Item> itens;

    // Leitura dos Dados
    carregaDados(N, W, itens);

    // Cria e instancia vetor de indices
    vector<int> indices(N);

    for (int i = 0; i < N; i++) {
        indices[i] = i;
    }

    // Faz a coordenacao indireta
    sort(indices.begin(), indices.end(), [&itens](int a, int b) {
        return compara_valor(itens[a], itens[b]);
    });
    
    // Pega os mais caros enquanto cabe na mochila
    int T = 0;
    double valor = 0;
    double peso = 0;
    vector<int> resposta(N);
    for (int i = 0; i < N; i++) {
        if (peso + itens[indices[i]].peso <= W) {
            resposta[T] = indices[i];
            peso += itens[indices[i]].peso;
            valor += itens[indices[i]].valor;
            T++;
        }
    }

    // Simplificando vetor de resposta
    resposta.erase(resposta.begin() + T, resposta.end());

    // Ordena os indices do vetor resposta
    sort(resposta.begin(), resposta.end());

    //Imprimir resposta final
    cout << peso << " " << valor << " 0" << endl;

    for (const int& i : resposta) {
        cout << i << " ";
    }
    
    /* cout << "Itens do vetor: \n";
    for (const Item& i : itens) {
        cout << "Item ID: " << i.id << ", Peso: " << i.peso <<", Valor: " << i.valor << endl;
    }

    cout << "Itens ordenados: \n";
    for (const int& i : indices) {
        cout << i << " ";
    }

    cout << "Resposta: \n";
    for (const int& i : resposta) {
        cout << i << " ";
    } */


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

bool compara_valor(const Item& a, const Item& b) {
    if (a.valor != b.valor){
        return a.valor > b.valor;
    }
    return a.peso < b.peso;
}

bool compara_peso(const Item& a, const Item& b) {
    if (a.peso != b.peso){
        return a.peso < b.peso;
    }
    return a.valor > b.valor;
}