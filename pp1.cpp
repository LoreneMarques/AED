#include <iostream>

#define BRANCO 0 //Não foi visitado
#define CINZA 1     //Está dentro da fila 
#define PRETO 2     //Foi visitdado e saiu da fila

using namespace std;

template <class T>
// CLASSES
class No {
private:
	int item;
	No<T>* prox;
public:
	No() {prox = NULL;}
	No(int);
	int getItem();
	void setItem(int);
	No<T>* getProx();
	void setProx(No*);
};

template <class T>
class Lista {
private:
	No<T>* prim;
	No<T>* ult;
public:
	Lista();
	~Lista(){}
	No<T>* getPrim();
	void insere(int);
	No<T>* buscar(int);
	void imprimirLista();
};

template <class T>
class Fila {
private:
	No<T>* frente;
	No<T>* atras;
public:
	Fila();
	int getFrente();
	bool vazia();
	void enfileira(int);
	void desenfileira(int);
	void imprimeFila();
};

template <class T>
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
    void DFS_Visita(int);
public:
	Grafo(int);
	void inicializar(int);
	void insereAresta(int, int);
	void insereArestaPeso(int, int, float);
	void imprimeGrafo();
	void DFS();
	int BFS(int, int, int, int[]);
};

// INICIO DA MAIN
int main() {

	string entrada, n, m, num1, num2, qtd, ini, veInicial, veFinal;
	int ordem, tamanho, espaco, v1, v2, quant, inimigo, verticeInicial, verticeFinal;
	//int* inimigos;
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

    Grafo<int>* grafo = new Grafo<int>(ordem);

    for(int i = 0; i < tamanho; i++){
    	
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
	//cout << "quant: " << quant << endl;

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
	    //cout << "inimigos["<< j <<"]: " << inimigos[j] << endl;
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

	grafo->BFS(verticeInicial,verticeFinal, quant, inimigos);

	//grafo->DFS();
    //grafo->BFS(2,8);*/
	return 0;
}

template <class T>
// METODOS DO NO
No<T>::No(int item) {
	this->item = item;
	this->prox = NULL;
}

template <class T>
int No<T>::getItem() {
	return item;
}

template <class T>
void No<T>::setItem(int item) {
	this->item = item;
}

template <class T>
No<T>* No<T>::getProx() {
	return prox;
}

template <class T>
void No<T>::setProx(No* prox) {
	this->prox = prox;
}

template <class T>
//METODOS DA LISTA
Lista<T>::Lista() {
	prim = new No<T>();
    prim->setProx(NULL);
    ult = prim;
}

template <class T>
No<T>* Lista<T>::getPrim() {
	return this->prim;
}

template <class T>
void Lista<T>::insere(int item){
   ult->setProx(new No<T>);
   ult = ult->getProx();
   ult->setProx(NULL);
   ult->setItem(item);
}

template <class T>
No<T>* Lista<T>::buscar(int item) {
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

template <class T>
void Lista<T>::imprimirLista() {
    No<T>* p = prim->getProx();
    while(p != NULL){
        cout << p->getItem() << " ";
        p = p->getProx();
    }
    cout << endl;
}

template <class T>
// METODOS DA FILA
Fila<T>::Fila() {
    frente = new No<T>();
    frente->setProx(NULL);
    atras = frente;
}

template <class T>
bool Fila<T>::vazia() { 
	return atras == frente; 
}

template <class T>

int Fila<T>::getFrente() { 
	return frente->getProx()->getItem();
}
template <class T>
void Fila<T>::enfileira(int item) {
    atras->setProx(new No<T>());
    atras = atras->getProx();
    atras->setItem(item);
    atras->setProx(NULL);
}
template <class T>
void Fila<T>::desenfileira(int item) {
    //cout << "frente = " << frente->getItem() << endl;
    No<T>* aux = new No<T>();
    aux = frente;
    frente = frente->getProx();
    item = frente->getItem();
    delete aux;
}

template <class T>
void Fila<T>::imprimeFila() {
    frente = frente->getProx();
    while(frente != NULL){
        cout << frente->getItem() << endl;
        frente = frente->getProx();
    }
}

//METODOS DO GRAFO
template <class T>
Grafo<T>::Grafo(int n) {
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

template <class T>
void Grafo<T>::inicializar(int n) {
	for(int i = 1;i <= n; i++){
        for(int j = 1; j <= n; j++){
            matriz[i][j] = 0;
        }
    }
}

template <class T>
void Grafo<T>::insereAresta(int u, int v) {
	adj[u].insere(v);
	adj[v].insere(u);
	m++;
}
template <class T>
void Grafo<T>::insereArestaPeso(int u, int v, float peso){
    matriz[u][v] = peso;
    matriz[v][u] = peso;
	insereAresta(u, v);
    m++;
}

template <class T>
void Grafo<T>::imprimeGrafo() {
	for(int i = 1; i <= n; i++) {
		cout << "v[" << i << "] = ";
		adj[i].imprimirLista();
	}
}

template <class T>
void Grafo<T>::DFS() {
    
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
    cout<< "peso: " << peso << endl;
    //return peso;
}

template <class T>
void Grafo<T>::DFS_Visita(int u) {
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

template <class T>
int Grafo<T>::BFS (int inicioVertice, int fimVertice, int qtd, int enemies[]){
    int vertice = inicioVertice; 
    bool found = false;
    int* cor = new int[n + 1];
    int* distancia = new int[n + 1];
    int* predecessor = new int[n + 1];
    string vertices;

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
                
                vertices += (posicao->getItem());
                i++;

                cout << "i: " << i << endl;
                cout << "vertices= " << vertices << endl;
                cout << "vertice = " << posicao->getItem() << endl;
            }

            if(posicao->getItem() == fimVertice){
                found = true;
            }

            posicao = posicao->getProx();
        }
        cor[vertice] = PRETO;
    }

    //cout << "tamanho do vetor: " << sizeof(vertices) << endl;
    /*for(int i = 0; i < sizeof(vertices); i++){
    	cout << "vertices["<< i <<"]: " << vertices[i] << endl;
    }*/
    cout << "menor distancia para se alcançar o vertice foi de: " << distancia[fimVertice] + 1 << endl;
    return distancia[fimVertice];
}
