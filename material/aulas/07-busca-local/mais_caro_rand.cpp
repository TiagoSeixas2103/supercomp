//g++ -g mais_caro.cpp -o mais_caro
//./mais_caro
#include <iostream>
#include <algorithm>
#include <random>
#include <list>

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
    
    // Pega os mais caros enquanto cabe na mochila
    int T = 0;
    double valor = 0;
    double peso = 0;
    vector<int> resposta(N);
    list<int> indicesChecados;
    for (int i = 0; i < N; i++) {
        indicesChecados.push_back(i);
    }

    default_random_engine gerador(10);
    for (int i = 0; i < N; i++) {
        uniform_real_distribution<double> distribution(0.0, 1.0);
        double valorGerado = distribution(gerador); // gera número
        int v = i;
        bool iNaLista = (find(indicesChecados.begin(), indicesChecados.end(), i) != indicesChecados.end());
        if (valorGerado <= 0.5 && iNaLista == true) {
            if (peso + itens[indices[i]].peso < W) {
                resposta[T] = indices[i];
                peso += itens[indices[i]].peso;
                valor += itens[indices[i]].valor;
                T++;
            }
            indicesChecados.remove(i);
        }
        i = v;
    }

    int iTira = 0;
    int iCompara = 0;
    double pesoCompara = -1;
    for (int i = 0; i < resposta.size(); i++) {
        iCompara = resposta[i];
        if (itens[indices[iCompara]].peso > pesoCompara) {
            pesoCompara =  itens[indices[iCompara]].peso;
            iTira = iCompara;
        }
    }

    vector<int> novaResposta(N);
    novaResposta = resposta;
    novaResposta.erase(remove(novaResposta.begin(), novaResposta.end(), iTira), novaResposta.end());
    double novoValor = valor - itens[indices[iTira]].valor;
    double novoPeso = peso -  - itens[indices[iTira]].peso;
    int T2 = novaResposta.size();

    for (int i = 0; i < N; i++) {
        bool iNaLista = (find(novaResposta.begin(), novaResposta.end(), i) != novaResposta.end());
        if (i != iTira && iNaLista == false) {
            if (novoPeso + itens[indices[i]].peso < W) {
                novaResposta[T] = indices[i];
                novoPeso += itens[indices[i]].peso;
                novoValor += itens[indices[i]].valor;
                T2++;
            }
        }
    }

    if (novoValor > valor) {
        resposta = novaResposta;
        valor = novoValor;
        peso = novoPeso;
        T = T2;
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
    cout << endl;

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
    /* if (a.valor != b.valor){
        return a.valor > b.valor;
    }
    return a.peso < b.peso; */
    return a.valor > b.valor;
}

bool compara_peso(const Item& a, const Item& b) {
    if (a.peso != b.peso){
        return a.peso < b.peso;
    }
    return a.valor > b.valor;
}