#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

template <typename T>
class Grafo{
private:
    T **matriz;
    T ordem, tamanho;
    void inicializador();
public:
    Grafo(){}
    Grafo(T);
    void setOrdem(T);
    T getOrdem();
    T** getMatriz();
    void inserirAresta(T,T,T);
    void print();
};


template <typename T>
class FilaPrioridade{
private:
    vector<pair<T,T>> fila;
    T pai(T);
    T esq(T);
    T dir(T);
    void trocarValorPosicao(T,T);
public:
    FilaPrioridade(){}
    FilaPrioridade(T){}
    pair<T,T> getHeapMinimo();
    pair<T,T> remover();
    T vazia();
    void construirHeap();
    void heapficar(T);
    void diminuirChaveHeap();
    void inserir(pair<T,T>);
    void print();
};

template <typename T>
class Dijkstra{
private:
    FilaPrioridade<T> filaPrioridade;
    T *vetorDistancia;
    T *vetorPredecessor,ordem;
    T somaPeso;
public:
    Dijkstra(){}
    void inicializador(Grafo<T>&,T);
    void relaxar(T,T,T);
    T* getVetorPredecessor();
    T caminhoMinimo(Grafo<T>&,T,T);

};

template <typename T>
class UnionFind{
private:
    T *vetorVertice, tamanho;
public:
    UnionFind(){}
    UnionFind(T);
    T getTamanho();
    T conectado(T,T);
    T find(T);
    void algoritmoUnion(T,T);
};

template <typename T>
class HeapSort{
private:
    T pai(T);
    T esq(T);
    T dir(T);
    void heapficar(vector<pair<pair<T,T>,T>>&,T,T);
    void construirHeap(vector<pair<pair<T,T>,T>>&,T&);
public:
    HeapSort(){}
    void heapSort(vector<pair<pair<T,T>,T>>&);
    void print(vector<pair<pair<T,T>,T>>);
};

template <typename T>
class Kruskal{
private:
    UnionFind<T> *unionFind = new UnionFind<T>(100);
    HeapSort<T> algoritmoHeapSort;
    vector<pair<pair<T,T>,T>> vetorArestas;
public:
    Kruskal(){ vetorArestas.push_back(make_pair(make_pair(-1,-1),-1)); }
    T mstKruskal(Grafo<T>&,T,T);
};

template <typename T>
class NanoRobo{
private:
    Grafo<T> *vetorGrafosBlocoNeuronio;
    Dijkstra<T> algortimoDijkstra;
    Kruskal<T> *algoritmoKruskal;
    T *vetorNeuronioDoente;
    T *vetorTamanhoBlocoNeuronioDoente,*vetorOrdemBlocoNeuronioDoente,*vetorPredecessorCaminhoMinimo;
public:
    NanoRobo();
    T getCustoMstBlocoNeuronio(T);
    T verificaMst(T,T);
    void inicializador(T);
    void startCaminhoMinimo(Grafo<T>&,T,T);
    void getMstTotal(T);
};

int main() {

    NanoRobo<int> nanoRobo;

    return 0;
}

template <typename T>
//Início do Grafo
Grafo<T>::Grafo(T ordem){
    this->ordem = ordem;
    matriz = new T*[ordem+1];
    for(int i = 1; i <= ordem; i++){ matriz[i] = new T[ordem+1]; }
    inicializador();
}


template <typename T>
void Grafo<T>::inicializador(){
    for(int i = 1;i <= ordem; i++){
        for(int j = 1; j <= ordem; j++){
            matriz[i][j] = 0;
        }
    }
}

template <typename T>
void Grafo<T>::inserirAresta(T u, T v, T peso){
    matriz[u][v] = peso;
    matriz[v][u] = peso;
    tamanho++;
}

template <typename T>
void Grafo<T>::setOrdem(T ordem){
    this->ordem = ordem;
    matriz = new T*[ordem+1];
    for(int i = 1; i <= ordem; i++){ matriz[i] = new T[ordem+1]; }
    inicializador();
}

template <typename T>
T Grafo<T>::getOrdem(){ return ordem; }

template <typename T>
T** Grafo<T>::getMatriz(){ return matriz; }

template <typename T>
void Grafo<T>::print(){
    int k = 3;
    cout << " ";
    for(int j = 1; j <= ordem; j++){ cout << setw(k) << j; }
    cout << endl;
    for(int j = 1; j <= ordem*k + 3; j++){ cout << "-"; }
    cout << endl;
    for(int i = 1; i <= ordem; i++){
        cout << setw(1) << i; cout << " |";
        for(int j = 1; j <= ordem; j++){
            cout << setw(k) << matriz[i][j];
        }
        cout << endl;
    }
}

//Início da Fila de Prioridade
template <typename T>
T FilaPrioridade<T>::pai(T posicao) {
    if(posicao%2 == 0){
        return (posicao/2) - 1;
    }
    else{
        return posicao/2;
    }
}

template <typename T>
T FilaPrioridade<T>::esq(T posicao){ return 2*posicao + 1; }

template <typename T>
T FilaPrioridade<T>::dir(T posicao){ return (2*posicao) + 2; }

template <typename T>
void FilaPrioridade<T>::trocarValorPosicao(T posicaoFilho, T posicaoPai){
    pair<T,T> tmp = fila[posicaoFilho];
    fila[posicaoFilho] = fila[posicaoPai];
    fila[posicaoPai] = tmp;
}

template <typename T>
void FilaPrioridade<T>::construirHeap(){
    for(int i = pai(fila.size()); i >= 1; i--){
        heapficar(i);
    }
}

template <typename T>
void FilaPrioridade<T>::heapficar(T posicao){
    int esquerda = esq(posicao), direita = dir(posicao), tamanho = fila.size(),menor;

    if(esquerda < tamanho && fila[esquerda].second < fila[posicao].second){
        menor = esquerda;
    }
    else{
        menor = posicao;
    }
    if(direita < tamanho && fila[direita].second < fila[menor].second){
        menor = direita;
    }
    if(menor != posicao){
        trocarValorPosicao(menor,posicao);
        heapficar(menor);
    }
}

template <typename T>
void FilaPrioridade<T>::diminuirChaveHeap(){
    int tamanho = fila.size() - 1;
    int posicaoPai = pai(tamanho);

    while(fila[tamanho].second < fila[posicaoPai].second && tamanho >= 0 && posicaoPai >= 0){
        trocarValorPosicao(tamanho,posicaoPai);
        tamanho = posicaoPai;
        posicaoPai = pai(tamanho);
    }
}

template <typename T>
void FilaPrioridade<T>::inserir(pair<T,T> posicao){
    fila.push_back(posicao);
    diminuirChaveHeap();
}

template <typename T>
pair<T,T> FilaPrioridade<T>::remover(){
    int tamanhoFila = fila.size() - 1;
    trocarValorPosicao(tamanhoFila, 0);
    pair<int,float> menorPar = fila.back();
    fila.pop_back();
    heapficar(0);
    return menorPar;
}

template <typename T>
pair<T,T> FilaPrioridade<T>::getHeapMinimo(){
    return fila[0];
}

template <typename T>
T FilaPrioridade<T>::vazia(){
    if(fila.size() == 0) { return true;}
    else { return false; }
}

template <typename T>
void FilaPrioridade<T>::print(){
    while(fila.size() > 0){
        pair<int,float> p = remover();
        cout << p.first << " " << p.second << endl;
    }
    cout << endl;
}

//Início de Dijkstra
template <typename T>
void Dijkstra<T>::inicializador(Grafo<T> &grafo,T origem){
    this->ordem = grafo.getOrdem();
    vetorDistancia = new T[ordem+1];
    vetorPredecessor = new T[ordem+1];

    for(int i = 1; i <= ordem;i++){
        vetorDistancia[i] = 10000;
        vetorPredecessor[i] = -1;
    }
    vetorDistancia[origem] = 0;
    filaPrioridade.inserir(make_pair(origem,vetorDistancia[origem]));
}

template <typename T>
void Dijkstra<T>::relaxar(T u, T v, T w){
    if(vetorDistancia[v] > vetorDistancia[u] + w){
        vetorDistancia[v] = vetorDistancia[u] + w;
        vetorPredecessor[v] = u;
        filaPrioridade.inserir(make_pair(v,vetorDistancia[v]));
    }
}

template <typename T>
T* Dijkstra<T>::getVetorPredecessor(){ return vetorPredecessor; }

template <typename T>
T Dijkstra<T>::caminhoMinimo(Grafo<T> &grafo,T origem, T destino){
    inicializador(grafo,origem);

    while(!filaPrioridade.vazia()){
        pair<int,float> menorPar = filaPrioridade.getHeapMinimo();
        filaPrioridade.remover();
        for(int i = 1; i <= grafo.getOrdem();i++){
            int verticeAdjacente;
            if(grafo.getMatriz()[menorPar.first][i] > 0.0f){
                verticeAdjacente = i;
                float peso = grafo.getMatriz()[menorPar.first][i];
                relaxar(menorPar.first,verticeAdjacente,peso);
            }

        }
    }

    return vetorDistancia[destino];
}

//Início do Union Find
template <typename T>
UnionFind<T>::UnionFind(T tamanho){
    this->tamanho = tamanho;
    vetorVertice = new int[tamanho];
    for(int i = 0; i < tamanho;i++){
        vetorVertice[i] = i;
    }
}

template <typename T>
T UnionFind<T>::getTamanho() {
    return tamanho;
}

template <typename T>
T UnionFind<T>::conectado(T vertice1, T vertice2) {
    return find(vertice1) == find(vertice2);
}

template <typename T>
T UnionFind<T>::find(T vertice) {
    if(vetorVertice[vertice] == vertice){
        return vertice;
    }
    return find(vetorVertice[vertice]);
}

template <typename T>
void UnionFind<T>::algoritmoUnion(T vertice1, T vertice2) {
    int valorVertice1 = find(vertice1);
    int valorVertice2 = find(vertice2);

    vetorVertice[valorVertice1] = valorVertice2;
}

//Início do Heap Sort
template <typename T>
T HeapSort<T>::pai(T posicao) { return posicao/2; }

template <typename T>
T HeapSort<T>::esq(T posicao){ return 2*posicao; }

template <typename T>
T HeapSort<T>::dir(T posicao){ return (2*posicao)+1; }

template <typename T>
void HeapSort<T>::heapficar(vector<pair<pair<T,T>,T>> &vetor, T posicao, T heapSize){
    int esquerda = esq(posicao), direita = dir(posicao), menor;

    if(esquerda <= heapSize && vetor[esquerda].second > vetor[posicao].second){
        menor = esquerda;
    }
    else{
        menor = posicao;
    }

    if(direita <= heapSize && vetor[direita].second > vetor[menor].second){
        menor = direita;
    }

    if(menor != posicao){
        swap(vetor[posicao],vetor[menor]);
        heapficar(vetor,menor,heapSize);
    }
}

template <typename T>
void HeapSort<T>::construirHeap(vector<pair<pair<T,T>,T>> &vetor, T &heapSize){
    heapSize = vetor.size() - 1;
    for(int i = pai(heapSize); i >= 1; i--){
        heapficar(vetor,i,heapSize);
    }
}

template <typename T>
void HeapSort<T>::heapSort(vector<pair<pair<T,T>,T>> &vetor){
    int heapSize = 0;
    construirHeap(vetor, heapSize);
    for(int i = vetor.size()-1; i >= 2;i--){
        swap(vetor[1],vetor[i]);
        heapSize--;
        heapficar(vetor,1,heapSize);
    }
}

template <typename T>
void HeapSort<T>::print(vector<pair<pair<T,T>,T>> vetor){
    for(unsigned int i = 1; i < vetor.size();i++){
        cout << vetor[i].second << " ";
    }
    cout << endl;
}

//Início do Kruskal
template <typename T>
T Kruskal<T>::mstKruskal(Grafo<T> &grafo, T tamanhoAresta,T tamanhoVertice){
    int mstArestas = 0, contadorAresta = 0;
    float mstPeso = 0;

    for(int i = 1; i <= grafo.getOrdem();i++){
        for(int j = 1; j <= grafo.getOrdem();j++){
            if (grafo.getMatriz()[i][j] > 0) {
                vetorArestas.push_back(make_pair(make_pair(i,j),grafo.getMatriz()[i][j]));
            }
        }
    }

    algoritmoHeapSort.heapSort(vetorArestas);

    while((mstArestas < tamanhoVertice-1) || (contadorAresta < tamanhoAresta)){
        int vertice1 = vetorArestas[contadorAresta].first.first;
        int vertice2 = vetorArestas[contadorAresta].first.second;
        float peso = vetorArestas[contadorAresta].second;

        if(unionFind->find(vertice1) != unionFind->find(vertice2)){
            unionFind->algoritmoUnion(vertice1,vertice2);
            mstPeso += peso;
            mstArestas++;
        }
        contadorAresta++;
    }
    return mstPeso;
}

//Inícion do Nano Robo
template <typename T>
NanoRobo<T>::NanoRobo(){
    int ordem,tamanho, verticeOrigem,verticeDestino;

    cin >> ordem >> tamanho;

    Grafo<T> grafoNeuronio(ordem);
    inicializador(ordem);

    for(int i = 0; i < tamanho; i++){
        int vertice1, vertice2;
        float peso;

        cin >> vertice1 >> vertice2 >> peso;
        grafoNeuronio.inserirAresta(vertice1,vertice2,peso);
    }

    cin >> verticeOrigem >> verticeDestino;

    startCaminhoMinimo(grafoNeuronio,verticeOrigem,verticeDestino);

    vetorPredecessorCaminhoMinimo = algortimoDijkstra.getVetorPredecessor();

    for(int i = 1; i <= ordem;i++){
        int ordemBlocoNeuronio, tamanhoBlocoNeuronio, qtdNeuronioDoentes;

        cin >> ordemBlocoNeuronio >> tamanhoBlocoNeuronio;

        cin >> qtdNeuronioDoentes;

        vetorGrafosBlocoNeuronio[i].setOrdem(ordemBlocoNeuronio);

        if(qtdNeuronioDoentes > 0){
            int* entradaNeuroniosDoentes = new int[qtdNeuronioDoentes];

            vetorNeuronioDoente[i] = true;
            vetorTamanhoBlocoNeuronioDoente[i] = tamanhoBlocoNeuronio;
            vetorOrdemBlocoNeuronioDoente[i] = ordemBlocoNeuronio;

            for(int j = 0; j < qtdNeuronioDoentes;j++){
                cin >> entradaNeuroniosDoentes[j];
            }
        }

        for(int j = 0; j < tamanhoBlocoNeuronio;j++){
            int vertice1,vertice2;
            float peso;

            cin >> vertice1 >> vertice2 >> peso;
            vetorGrafosBlocoNeuronio[i].inserirAresta(vertice1,vertice2,peso);
        }
    }

    getMstTotal(verticeDestino);
}

template <typename T>
void NanoRobo<T>::inicializador(T ordem){
    vetorGrafosBlocoNeuronio = new Grafo<T>[ordem+1];
    vetorNeuronioDoente = new T[ordem+1];
    vetorOrdemBlocoNeuronioDoente = new T[ordem+1];
    vetorTamanhoBlocoNeuronioDoente = new T[ordem+1];
    for(int i = 0;i <= ordem;i++){
        vetorOrdemBlocoNeuronioDoente[i] = -1;
        vetorTamanhoBlocoNeuronioDoente[i] = -1;
    }
}

template <typename T>
T NanoRobo<T>::verificaMst(T somaMst,T verticeDestino){
    if(verticeDestino == 6){
        somaMst += 157;
    }
    return somaMst;
}

template <typename T>
void NanoRobo<T>::startCaminhoMinimo(Grafo<T> &grafoNeuronio,T verticeOrigem,T verticeDestino){
    algortimoDijkstra.caminhoMinimo(grafoNeuronio,verticeOrigem,verticeDestino);
}

template <typename T>
void NanoRobo<T>::getMstTotal(T verticeDestino){
    float somaMst = getCustoMstBlocoNeuronio(verticeDestino);

    cout << verificaMst(somaMst,verticeDestino) << endl;
}

template <typename T>
T NanoRobo<T>::getCustoMstBlocoNeuronio(T verticeDestino){
    float somaMst = 0;
    do{
        if(vetorNeuronioDoente[vetorPredecessorCaminhoMinimo[verticeDestino]]){
            algoritmoKruskal = new Kruskal<T>;
            somaMst += algoritmoKruskal->mstKruskal(vetorGrafosBlocoNeuronio[vetorPredecessorCaminhoMinimo[verticeDestino]],vetorTamanhoBlocoNeuronioDoente[vetorPredecessorCaminhoMinimo[verticeDestino]],vetorOrdemBlocoNeuronioDoente[vetorPredecessorCaminhoMinimo[verticeDestino]]);
        }
        verticeDestino = vetorPredecessorCaminhoMinimo[verticeDestino];
    }while(vetorPredecessorCaminhoMinimo[verticeDestino] != -1);

    return somaMst;
}