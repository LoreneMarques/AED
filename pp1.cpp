#include <iostream>

#define BRANCO 0 //Não foi visitado
#define CINZA 1     //Está dentro da fila 
#define PRETO 2     //Foi visitdado e saiu da fila

using namespace std;

// CLASSES
class No {
private:
	int item;
	No* prox;
public:
	No() {prox = NULL;}
	No(int);
	int getItem();
	void setItem(int);
	No* getProx();
	void setProx(No*);
};

class Lista {
private:
	No* prim;
	No* ult;
public:
	Lista();
	~Lista(){}
	No* getPrim();
	void insere(int);
	No* buscar(int);
	void imprimirLista();
};

class Fila {
private:
	No* frente;
	No* atras;
public:
	Fila();
	int getFrente();
	bool vazia();
	void enfileira(int);
	void desenfileira(int);
	void imprimeFila();
};

class Grafo {
private:
	Lista* adj;
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
	int BFS(int, int);
};

// INICIO DA MAIN
int main() {

/*	No* teste = new No(2);
	cout << teste->getItem() << endl;

	Lista* teste = new Lista();
	teste->insere(2);
	teste->insere(3);
	teste->insere(4);
	
	teste->buscar(4);
	teste->buscar(3);
	teste->buscar(2);
	teste->buscar(1);

	teste->imprimirLista();

	Fila* teste = new Fila();
	teste->enfileira(2);
	teste->enfileira(3);
	teste->enfileira(4);
	teste->desenfileira(2);
	teste->imprimeFila();*/

/*	Grafo* teste = new Grafo(7);
	teste->insereAresta(1,2);
	teste->insereAresta(1,4);
	teste->insereAresta(1,7);
	teste->insereAresta(2,3);
	teste->insereAresta(2,4);
	teste->insereAresta(2,7);
	teste->insereAresta(4,5);
	teste->insereAresta(4,7);
	teste->insereAresta(5,6);
	teste->insereAresta(5,7);
	//teste->imprimeGrafo();

	//teste->DFS();

	teste->BFS(3,5);*/

/*	Grafo* teste = new Grafo(9);
	teste->insereAresta(1,2);
	teste->insereAresta(1,7);
	teste->insereAresta(1,8);
	teste->insereAresta(2,3);
	teste->insereAresta(3,4);
	teste->insereAresta(3,5);
	teste->insereAresta(3,7);
	teste->insereAresta(4,5);
	teste->insereAresta(4,6);
	teste->insereAresta(6,7);
	teste->insereAresta(7,8);
	teste->insereAresta(7,9);

	//teste->imprimeGrafo();

	//teste->DFS();
	teste->BFS(8,5);*/

	Grafo* teste = new Grafo(8);
	teste->insereArestaPeso(1,2,1);
	teste->insereArestaPeso(1,5,1);
	teste->insereArestaPeso(2,6,1);
	teste->insereArestaPeso(3,4,2);
	teste->insereArestaPeso(3,6,2);
	teste->insereArestaPeso(3,7,1);
	teste->insereArestaPeso(4,7,5);
	teste->insereArestaPeso(4,8,1);
	teste->insereArestaPeso(6,7,1);
	teste->insereArestaPeso(7,8,2);
	//teste->imprimeGrafo();

	teste->DFS();

	//teste->BFS(2,6);

	/*Grafo* teste = new Grafo(25);
	teste->insereAresta(1,2);
	teste->insereAresta(1,4);
	teste->insereAresta(1,7);
	teste->insereAresta(1,13);

	teste->insereAresta(2,3);
	teste->insereAresta(2,7);
	teste->insereAresta(2,8);

	teste->insereAresta(3,4);
	teste->insereAresta(3,8);

	teste->insereAresta(4,8);
	teste->insereAresta(4,9);
	teste->insereAresta(4,10);
	teste->insereAresta(4,5);

	teste->insereAresta(5,8);
	teste->insereAresta(5,10);
	teste->insereAresta(5,11);

	teste->insereAresta(6,7);
	teste->insereAresta(6,12);

	teste->insereAresta(7,8);
	teste->insereAresta(7,12);
	teste->insereAresta(7,13);

	teste->insereAresta(8,12);
	teste->insereAresta(8,13);
	teste->insereAresta(8,14);
	teste->insereAresta(8,9);
	teste->insereAresta(8,10);

	teste->insereAresta(9,10);
	teste->insereAresta(9,11);
	teste->insereAresta(9,14);
	teste->insereAresta(9,16);

	teste->insereAresta(10,11);
	teste->insereAresta(10,15);

	teste->insereAresta(11,15);
	teste->insereAresta(11,16);

	teste->insereAresta(12,13);
	teste->insereAresta(12,17);

	teste->insereAresta(13,14);
	teste->insereAresta(13,17);
	teste->insereAresta(13,18);
	teste->insereAresta(13,19);
	teste->insereAresta(13,15);

	teste->insereAresta(14,15);
	teste->insereAresta(14,19);
	teste->insereAresta(14,20);

	teste->insereAresta(15,18);
	teste->insereAresta(15,19);
	teste->insereAresta(15,20);
	teste->insereAresta(15,21);
	teste->insereAresta(15,16);

	teste->insereAresta(16,21);
	teste->insereAresta(16,25);

	teste->insereAresta(17,18);
	teste->insereAresta(17,22);

	teste->insereAresta(18,22);
	teste->insereAresta(18,23);
	teste->insereAresta(18,24);

	teste->insereAresta(19,20);
	teste->insereAresta(19,23);
	teste->insereAresta(19,24);

	teste->insereAresta(20,21);
	teste->insereAresta(20,24);
	teste->insereAresta(20,25);

	teste->insereAresta(21,24);
	teste->insereAresta(21,25);

	teste->insereAresta(22,23);
	teste->insereAresta(24,25);

	teste->BFS(5,23);*/

	return 0;
}

// METODOS DO NO
No::No(int item) {
	this->item = item;
	this->prox = NULL;
}

int No::getItem() {
	return item;
}

void No::setItem(int item) {
	this->item = item;
}

No* No::getProx() {
	return prox;
}

void No::setProx(No* prox) {
	this->prox = prox;
}

//METODOS DA LISTA
Lista::Lista() {
	prim = new No();
    prim->setProx(NULL);
    ult = prim;
}

No* Lista::getPrim() {
	return this->prim;
}

void Lista::insere(int item){
   ult->setProx(new No);
   ult = ult->getProx();
   ult->setProx(NULL);
   ult->setItem(item);
}

No* Lista::buscar(int item) {
	No* p = prim->getProx();
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

void Lista::imprimirLista() {
    No* p = prim->getProx();
    while(p != NULL){
        cout << p->getItem() << " ";
        p = p->getProx();
    }
    cout << endl;
}

// METODOS DA FILA
//template<typename T>
Fila::Fila() {
    frente = new No();
    frente->setProx(NULL);
    atras = frente;
}

//template<typename T>
bool Fila::vazia() { 
	return atras == frente; 
}

//template<typename T>
int Fila::getFrente() { 
	return frente->getProx()->getItem();
}

//template<typename T>
void Fila::enfileira(int item) {
    atras->setProx(new No());
    atras = atras->getProx();
    atras->setItem(item);
    atras->setProx(NULL);
}

//template<typename T>
void Fila::desenfileira(int item) {
    //cout << "frente = " << frente->getItem() << endl;
    No* aux = new No();
    aux = frente;
    frente = frente->getProx();
    item = frente->getItem();
    delete aux;
}

//template<typename T>
void Fila::imprimeFila() {
    frente = frente->getProx();
    while(frente != NULL){
        cout << frente->getItem() << endl;
        frente = frente->getProx();
    }
}

//METODOS DO GRAFO
Grafo::Grafo(int n) {
	this->n = n;
	adj = new Lista[n + 1];
	cor = new int[n + 1];
    tempoEntrada = new int[n + 1];
    tempoSaida = new int[n + 1];
    predecessor = new int[n + 1];
    matriz = new float*[n + 1];
	for(int i = 1; i <= n; i++){ matriz[i] = new float[n + 1]; }
	inicializar(n);
}

void Grafo::inicializar(int n) {
	for(int i = 1;i <= n; i++){
        for(int j = 1; j <= n; j++){
            matriz[i][j] = 0;
        }
    }
}

void Grafo::insereAresta(int u, int v) {
	adj[u].insere(v);
	adj[v].insere(u);
	m++;
}

void Grafo::insereArestaPeso(int u, int v, float peso){
    matriz[u][v] = peso;
    matriz[v][u] = peso;
	insereAresta(u, v);
    m++;
}

void Grafo::imprimeGrafo() {
	for(int i = 1; i <= n; i++) {
		cout << "v[" << i << "] = ";
		adj[i].imprimirLista();
	}
}

//template<typename T>
void Grafo::DFS() {
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

void Grafo::DFS_Visita(int u) {
	tempo++;
	tempoEntrada[u] = tempo;
	cor[u] = CINZA;

	No* p = adj[u].getPrim()->getProx();
	//cout << p->getItem() << endl;
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
    cout << "tempo = " << tempo << endl;
    tempoSaida[u] = tempo;
	
	/*for(int i = 1;i <= n; i++){
        cout << endl;
        for(int j = 1; j <= n; j++){
            cout << " " << matriz[i][j];
        }

    }
    cout << endl;*/
    //cout << "peso: " << peso << endl;

}

//template<typename T>
int Grafo::BFS (int inicioVertice, int fimVertice){
    int vertice = inicioVertice; 
    bool found = false;
    int* cor = new int[n + 1];
    int* distancia = new int[n + 1];
    int* predecessor = new int[n + 1];
    
    for(int i = 0; i < n + 1; i++){
        cor[i] = BRANCO;
        distancia[i] = 1000;
        predecessor[i] = -1; 
    }

    cor[vertice] = CINZA;
    distancia[vertice] = -1;
    predecessor[vertice] = -1;

    Fila fila;
    fila.enfileira(vertice);
    
    while(!fila.vazia() && !found){
        vertice = fila.getFrente();
        fila.desenfileira(vertice);
        No* posicao = adj[vertice].getPrim()->getProx();

        while(posicao != NULL){
            if(cor[posicao->getItem()] == BRANCO){
                cor[posicao->getItem()] = CINZA;
                distancia[posicao->getItem()] = distancia[vertice] + 1;
                predecessor[posicao->getItem()] = vertice;
                fila.enfileira(posicao->getItem());
            }

            if(posicao->getItem() == fimVertice){
                found = true;
            }

            posicao = posicao->getProx();
        }
        cor[vertice] = PRETO;
    }
    
    cout << "menor distancia para se alcançar o vertice foi de: " << distancia[fimVertice] + 1 << endl;
    return distancia[fimVertice];
}