#include <iostream>

#define BRANCO 0 //Não foi visitado
#define CINZA 1     //Está dentro da fila
#define PRETO 2     //Foi visitdado e saiu da fila

using namespace std;

// CLASSES
template <typename T>
class No {
private:
    T item;
    No<T>* prox;
public:
    No() {prox = NULL;}
    No(T);
    int getItem();
    void setItem(T);
    No<T>* getProx();
    void setProx(No<T>*);
};

template <typename T>
class Lista {
private:
    No<T>* prim;
    No<T>* ult;
public:
    Lista();
    ~Lista(){}
    No<T>* getPrim();
    void insere(T);
    No<T>* buscar(T);
    void imprimirLista();
};

template <typename T>
class Fila {
private:
    No<T>* frente;
    No<T>* atras;
public:
    Fila();
    int getFrente();
    bool vazia();
    void enfileira(T);
    void desenfileira(T);
    void imprimeFila();
};

template <typename T>
class Grafo {
private:
    Lista<T>* adj;
    int n;
    int m;

    float** matriz;
    float peso = 0.0;
    int tempo;
    int* cor;
    int* tempoEntrada;
    int* tempoSaida;
    int* predecessor;
    void DFS_Visita(T);
public:
    Grafo(T);
    void inicializar(T);
    void insereAresta(T, T);
    void insereArestaPeso(T, T, T);
    void imprimeGrafo();
    float DFS();
    Lista<T> BFS(T, T, T, T[]);
};

// INICIO DA MAIN
int main() {

    string entrada, n, m, num1, num2, qtd, ini, veInicial, veFinal, ps;
    int ordem, tamanho, espaco, v1, v2, quant, inimigo, verticeInicial, verticeFinal, ordemVertice, tamanhoVertice;
    float peso, pesoTotal;
    Lista<int> caminho;

    getline	(cin, entrada);

    for(int i = 0; i < entrada.length(); i++){
        if(entrada[i] == ' ') {
            espaco = i;
            i = entrada.length();
        }
        n += entrada[i];
    }

    for(int i = espaco + 1; i < entrada.length(); i++){
        m += entrada[i];
    }

    ordem = stoi(n);
    tamanho = stoi(m);

    n.clear();
    m.clear();

    Grafo<int>* grafo = new Grafo<int>(ordem);

    for(int i = 1; i <= tamanho; i++){

        getline	(cin, entrada);

        for(int i = 0; i < entrada.length(); i++){
            if(entrada[i] == ' ') {
                espaco = i;
                i = entrada.length();
            }
            num1 += entrada[i];
        }

        for(int i = espaco + 1; i < entrada.length(); i++){
            num2 += entrada[i];
        }

        v1 = stoi(num1);
        v2 = stoi(num2);
        num1.clear();
        num2.clear();

        grafo->insereAresta(v1,v2);
    }

    getline (cin, entrada);

    for(int i = 0; i < entrada.length(); i++){
        if(entrada[i] == ' ') {
            espaco = i;
            i = entrada.length();
        }
        qtd += entrada[i];
    }

    quant = stoi(qtd);

    int* inimigos = new int[quant];

    for (int j = 0; j < quant; j++){
        for(int i = espaco + 1; i < entrada.length(); i++){
            if(entrada[i] == ' ') {
                espaco = i;
                i = entrada.length();
            }
            ini += entrada[i];
        }
        inimigo = stoi(ini);
        inimigos[j] = inimigo;
        ini.clear();
    }

    getline (cin, entrada);

    for(int i = 0; i < entrada.length(); i++){
        if(entrada[i] == ' ') {
            espaco = i;
            i = entrada.length();
        }
        veInicial += entrada[i];
    }

    for(int i = espaco + 1; i < entrada.length(); i++){
        veFinal += entrada[i];
    }

    verticeInicial = stoi(veInicial);
    verticeFinal = stoi(veFinal);

    caminho = grafo->BFS(verticeInicial,verticeFinal, quant, inimigos);

    float pesos[ordem];

    for(int i = 0; i < ordem; i++){

        getline	(cin, entrada);

        for(int i = 0; i < entrada.length(); i++){
            if(entrada[i] == ' ') {
                espaco = i;
                i = entrada.length();
            }
            n += entrada[i];
        }

        for(int i = espaco + 1; i < entrada.length(); i++){
            m += entrada[i];
        }

        ordemVertice = stoi(n);
        tamanhoVertice = stoi(m);
        n.clear();
        m.clear();

        Grafo<int>* grafo = new Grafo<int>(ordemVertice);

        for(int i = 1; i <= tamanhoVertice; i++){
            getline	(cin, entrada);

            for(int i = 0; i < entrada.length(); i++){
                if(entrada[i] == ' ') {
                    espaco = i;
                    i = entrada.length();
                }
                num1 += entrada[i];
            }

            for(int i = espaco + 1; i < entrada.length(); i++){
                if(entrada[i] == ' ') {
                    espaco = i;
                    i = entrada.length();
                }
                num2 += entrada[i];
            }

            for(int i = espaco + 1; i < entrada.length(); i++){
                ps += entrada[i];
            }

            v1 = stoi(num1);
            v2 = stoi(num2);
            peso = stoi(ps);
            num1.clear();
            num2.clear();
            ps.clear();

            grafo->insereArestaPeso(v1,v2,peso);

        }
        pesos[i+1] = grafo->DFS();
    }

    No<int>* compare;
    pesoTotal = 0.0;

    for(int i = 1; i <= ordem; i++){
        compare = caminho.getPrim()->getProx();
        while(compare != NULL){
            if(i == compare->getItem()) {
                pesoTotal = pesoTotal + pesos[i];
                compare = compare->getProx();
            }
            else{
                compare = compare->getProx();
            }
        }
    }
    cout << fixed;
    cout.precision(1);
    cout << pesoTotal << endl;
    return 0;
}

// METODOS DO NO
template <typename T>
No<T>::No(T item) {
    this->item = item;
    this->prox = NULL;
}

template <typename T>
int No<T>::getItem() {
    return item;
}

template <typename T>
void No<T>::setItem(T item) {
    this->item = item;
}

template <typename T>
No<T>* No<T>::getProx() {
    return prox;
}

template <typename T>
void No<T>::setProx(No<T>* prox) {
    this->prox = prox;
}

//METODOS DA LISTA
template <typename T>
Lista<T>::Lista() {
    prim = new No<T>();
    prim->setProx(NULL);
    ult = prim;
}

template <typename T>
No<T>* Lista<T>::getPrim() {
    return this->prim;
}

template <typename T>
void Lista<T>::insere(T item){
    ult->setProx(new No<T>);
    ult = ult->getProx();
    ult->setProx(NULL);
    ult->setItem(item);
}

template <typename T>
No<T>* Lista<T>::buscar(T item) {
    No<T>* p = prim->getProx();
    while (p != NULL && p->getItem() != item) {
        p = p->getProx();
    }
    if (p == NULL) {
        //cout << "Não existe!" << endl;
        return NULL;
    }
    else {
        //cout << p->getItem() << endl;
        return p;
    }
}

template <typename T>
void Lista<T>::imprimirLista() {
    No<T>* p = prim->getProx();
    while(p != NULL){
        cout << p->getItem() << " ";
        p = p->getProx();
    }
    cout << endl;
}

// METODOS DA FILA
template <typename T>
Fila<T>::Fila() {
    frente = new No<T>();
    frente->setProx(NULL);
    atras = frente;
}

template <typename T>
bool Fila<T>::vazia() {
    return atras == frente;
}

template <typename T>
int Fila<T>::getFrente() {
    return frente->getProx()->getItem();
}

template <typename T>
void Fila<T>::enfileira(T item) {
    atras->setProx(new No<T>());
    atras = atras->getProx();
    atras->setItem(item);
    atras->setProx(NULL);
}

template <typename T>
void Fila<T>::desenfileira(T item) {
    //cout << "frente = " << frente->getItem() << endl;
    No<T>* aux = new No<T>();
    aux = frente;
    frente = frente->getProx();
    item = frente->getItem();
    delete aux;
}

template <typename T>
void Fila<T>::imprimeFila() {
    frente = frente->getProx();
    while(frente != NULL){
        cout << frente->getItem() << endl;
        frente = frente->getProx();
    }
}

//METODOS DO GRAFO
template <typename T>
Grafo<T>::Grafo(T n) {
    this->n = n;
    adj = new Lista<T>[n + 1];
    cor = new int[n + 1];
    tempoEntrada = new int[n + 1];
    tempoSaida = new int[n + 1];
    predecessor = new int[n + 1];
    matriz = new float*[n + 1];
    for(int i = 1; i <= n; i++){ matriz[i] = new float[n + 1]; }
    inicializar(n);
}

template <typename T>
void Grafo<T>::inicializar(T n) {
    for(int i = 1;i <= n; i++){
        for(int j = 1; j <= n; j++){
            matriz[i][j] = 0;
        }
    }
}

template <typename T>
void Grafo<T>::insereAresta(T u, T v) {
    adj[u].insere(v);
    adj[v].insere(u);
    m++;
}

template <typename T>
void Grafo<T>::insereArestaPeso(T u, T v, T peso){
    matriz[u][v] = peso;
    matriz[v][u] = peso;
    insereAresta(u, v);
    m++;
}

template <typename T>
void Grafo<T>::imprimeGrafo() {
    for(int i = 1; i <= n; i++) {
        cout << "v[" << i << "] = ";
        adj[i].imprimirLista();
    }
}

template <typename T>
float Grafo<T>::DFS() {

    for(int i = 0; i < n + 1; i++){
        cor[i] = BRANCO;
        predecessor[i] = -1;
    }

    tempo = 0;
    for(int u = 1; u < n + 1; u++){
        if(cor[u] == BRANCO) {
            DFS_Visita(u);
        }
    }
    return peso;
}

template <typename T>
void Grafo<T>::DFS_Visita(T u) {
    tempo++;
    tempoEntrada[u] = tempo;
    cor[u] = CINZA;

    No<T>* p = adj[u].getPrim()->getProx();
    while(p != NULL){
        if(cor[p->getItem()] == BRANCO){
            peso += matriz[u][p->getItem()];
            predecessor[p->getItem()] = u;
            DFS_Visita(p->getItem());
        }
        p = p->getProx();
    }

    cor[u] = PRETO;
    tempo++;
    //cout << "tempo = " << tempo << endl;
    tempoSaida[u] = tempo;
}

template <typename T>
Lista<T> Grafo<T>::BFS (T inicioVertice, T fimVertice, T qtd, T enemies[]){
    int vertice = inicioVertice;
    bool found = false;
    int* cor = new int[n + 1];
    int* distancia = new int[n + 1];
    int* predecessor = new int[n + 1];

    int p;

    for(int i = 0; i < n + 1; i++){
        cor[i] = BRANCO;
        distancia[i] = 1000;
        predecessor[i] = -1;
    }

    for(int i = 0;i < qtd; i++){
        cor[enemies[i]] = PRETO;
    }

    cor[vertice] = CINZA;
    distancia[vertice] = -1;
    predecessor[vertice] = -1;

    Lista<T> prev;

    Fila<T> fila;
    fila.enfileira(vertice);

    int i = 0;
    while(!fila.vazia() && !found){

        vertice = fila.getFrente();
        fila.desenfileira(vertice);
        No<T>* posicao = adj[vertice].getPrim()->getProx();

        while(posicao != NULL){

            if(cor[posicao->getItem()] == BRANCO){
                cor[posicao->getItem()] = CINZA;
                distancia[posicao->getItem()] = distancia[vertice] + 1;
                predecessor[posicao->getItem()] = vertice;
                fila.enfileira(posicao->getItem());
            }

            if(posicao->getItem() == fimVertice){
                found = true;
                int p = posicao->getItem();
                prev.insere(p);

                while(predecessor[p] > 0){
                    prev.insere(predecessor[p]);
                    p = predecessor[p];
                }
            }

            posicao = posicao->getProx();
        }
        cor[vertice] = PRETO;
    }

    //cout << "menor distancia para se alcançar o vertice foi de: " << distancia[fimVertice] + 1 << endl;
    //return distancia[fimVertice];
    return prev;
}
