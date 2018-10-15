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

    Grafo* grafo = new Grafo(ordem);

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

//template<typename T>
int Grafo::BFS (int inicioVertice, int fimVertice, int qtd, int enemies[]){
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

    Fila fila;
    fila.enfileira(vertice);
    
    int i = 0;
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