//Eduardo Maia Freire - 1615310003
//Lorene da Silva Marques - 1615310013

#include <iostream>

using namespace std;

#define BRANCO 0
#define CINZA 1
#define PRETO 2

template<typename T>
class No {
private:
	T item;
	No<T>* prox;
public:
	No() {prox = NULL;}
	No(T);
	T getItem();
	void setItem(T);
	No<T>* getProx();
	void setProx(No<T>*);
};

template<typename T>
class Lista {
private:
	No<T>* prim;
	No<T>* ult;
public:
	Lista();
	No<T>* getPrim();
	void insere(T);
	No<T>* buscar(T);
	void imprimirLista();
};

template<typename T>
class Fila {
private:
	No<T>* frente;
	No<T>* atras;
public:
	Fila();
	T getFrente();
	bool vazia();
	void enfileira(T);
	void desenfileira(T);
	void imprimeFila();
};

template<typename T>
class Grafo {
private:
	Lista<T>* adj;
	float** matrizPesos;
	int n;
	int m;
	int* cor;
    T* predecessor;
	float pesoDFS = 0.0;
	int tempoDFS;
    int* tempoEntradaDFS;
    int* tempoSaidaDFS;
    void DFS_Visita(T);
public:
	Grafo(T);
	void inicializar(T);
	void insereAresta(T, T);
	void insereArestaPeso(T, T, float);
	float DFS();
	Lista<T> BFS(T, T, T, T[]);
	void imprimeGrafo();
};

float inicializarEnterprise();

int main() {

	float pesoTotal = inicializarEnterprise();

	cout << fixed;
	cout.precision(1);
    cout << pesoTotal << endl;
	
	return 0;
}


float inicializarEnterprise(){
	string entrada, n, m, num1, num2, qtd, ini, veInicial, veFinal, pesoTexto;
	int ordem, tamanho, espaco, v1, v2, quant, inimigo, verticeInicial, verticeFinal, ordemVertice, tamanhoVertice;
	float peso, pesoTotal;
	Lista<int> caminho;

	getline	(cin, entrada);

	for(unsigned int i = 0; i < entrada.length(); i++){
        if(entrada[i] == ' ') {
        	espaco = i;
        	i = entrada.length();
        }
        n += entrada[i];
    }

    for(unsigned int i = espaco + 1; i < entrada.length(); i++){
        m += entrada[i];
    }

    ordem = stoi(n);
    tamanho = stoi(m);

    n.clear();
    m.clear();

    Grafo<int>* grafoExterno = new Grafo<int>(ordem);

    for(int i = 1; i <= tamanho; i++){
    	
    	getline	(cin, entrada);
    	
		for(unsigned int i = 0; i < entrada.length(); i++){
	        if(entrada[i] == ' ') {
	        	espaco = i;
	        	i = entrada.length();
	        }
	        num1 += entrada[i];
	    }

	    for(unsigned int i = espaco + 1; i < entrada.length(); i++){
	        num2 += entrada[i];
	    }

	    v1 = stoi(num1);
	    v2 = stoi(num2);
	    num1.clear();
	    num2.clear();
	    
    	grafoExterno->insereAresta(v1,v2);
    }

    getline (cin, entrada);

    for(unsigned int i = 0; i < entrada.length(); i++){
	    if(entrada[i] == ' ') {
	       	espaco = i;
	       	i = entrada.length();
	    }
	    qtd += entrada[i];
	}
	
	quant = stoi(qtd);

	int* inimigos = new int[quant];
	    
	for (int j = 0; j < quant; j++){
	    for(unsigned int i = espaco + 1; i < entrada.length(); i++){
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
	
	for(unsigned int i = 0; i < entrada.length(); i++){
        if(entrada[i] == ' ') {
        	espaco = i;
        	i = entrada.length();
        }
        veInicial += entrada[i];
    }

    for(unsigned int i = espaco + 1; i < entrada.length(); i++){
        veFinal += entrada[i];
    }

    verticeInicial = stoi(veInicial);
    verticeFinal = stoi(veFinal);

	caminho = grafoExterno->BFS(verticeInicial,verticeFinal, quant, inimigos);
	
	float *pesos = new float[ordem];

	for(int i = 0; i < ordem; i++){
    	
		getline	(cin, entrada);

		for(unsigned int i = 0; i < entrada.length(); i++){
	        if(entrada[i] == ' ') {
	        	espaco = i;
	        	i = entrada.length();
	        }
	        n += entrada[i];
	    }

	    for(unsigned int i = espaco + 1; i < entrada.length(); i++){
	        m += entrada[i];
	    }

	    ordemVertice = stoi(n);
	    tamanhoVertice = stoi(m);
	    n.clear();
	    m.clear();

	    Grafo<int>* grafoInterno = new Grafo<int>(ordemVertice);

	    for(int i = 1; i <= tamanhoVertice; i++){
	    	getline	(cin, entrada);
	    	
			for(unsigned int i = 0; i < entrada.length(); i++){
		        if(entrada[i] == ' ') {
		        	espaco = i;
		        	i = entrada.length();
		        }
		        num1 += entrada[i];
		    }

		    for(unsigned int i = espaco + 1; i < entrada.length(); i++){
		    	if(entrada[i] == ' ') {
		        	espaco = i;
		        	i = entrada.length();
		        }
		        num2 += entrada[i];
		    }

		    for(unsigned int i = espaco + 1; i < entrada.length(); i++){
		    	pesoTexto += entrada[i];
		    }

		    v1 = stoi(num1);
		    v2 = stoi(num2);
		    peso = stoi(pesoTexto);
		    num1.clear();
		    num2.clear();
		    pesoTexto.clear();
		    
	    	grafoInterno->insereArestaPeso(v1,v2,peso);
	    	
    	}
    	pesos[i+1] = grafoInterno->DFS();
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

    return pesoTotal;
}

template<typename T>
No<T>::No(T item) {
	this->item = item;
	this->prox = NULL;
}

template<typename T>
T No<T>::getItem() {
	return item;
}

template<typename T>
void No<T>::setItem(T item) {
	this->item = item;
}

template<typename T>
No<T>* No<T>::getProx() {
	return prox;
}

template<typename T>
void No<T>::setProx(No<T>* prox) {
	this->prox = prox;
}


template<typename T>
Lista<T>::Lista() {
	prim = new No<T>();
    prim->setProx(NULL);
    ult = prim;
}

template<typename T>
No<T>* Lista<T>::getPrim() {
	return this->prim;
}

template<typename T>
void Lista<T>::insere(T item){
   ult->setProx(new No<T>);
   ult = ult->getProx();
   ult->setProx(NULL);
   ult->setItem(item);
}

template<typename T>
No<T>* Lista<T>::buscar(T item) {
	No<T>* p = prim->getProx();
	while (p != NULL && p->getItem() != item) {
		p = p->getProx();
	}
	return p == NULL ? NULL : p;
}

template<typename T>
void Lista<T>::imprimirLista() {
    No<T>* p = prim->getProx();
    while(p != NULL){
        cout << p->getItem() << " ";
        p = p->getProx();
    }
    cout << endl;
}


template<typename T>
Fila<T>::Fila() {
    frente = new No<T>();
    frente->setProx(NULL);
    atras = frente;
}

template<typename T>
bool Fila<T>::vazia() { 
	return atras == frente; 
}

template<typename T>
T Fila<T>::getFrente() { 
	return frente->getProx()->getItem();
}

template<typename T>
void Fila<T>::enfileira(T item) {
    atras->setProx(new No<T>());
    atras = atras->getProx();
    atras->setItem(item);
    atras->setProx(NULL);
}

template<typename T>
void Fila<T>::desenfileira(T item) {
    No<T>* aux = new No<T>();
    aux = frente;
    frente = frente->getProx();
    item = frente->getItem();
    delete aux;
}

template<typename T>
void Fila<T>::imprimeFila() {
    frente = frente->getProx();
    while(frente != NULL){
        cout << frente->getItem() << endl;
        frente = frente->getProx();
    }
}


template<typename T>
Grafo<T>::Grafo(T n) {
	this->n = n;
	adj = new Lista<T>[n + 1];
	cor = new T[n + 1];
    tempoEntradaDFS = new T[n + 1];
    tempoSaidaDFS = new T[n + 1];
    predecessor = new T[n + 1];
    matrizPesos = new float*[n + 1];
	for(int i = 1; i <= n; i++){ matrizPesos[i] = new float[n + 1]; }
	inicializar(n);
}

template<typename T>
void Grafo<T>::inicializar(T n) {
	for(int i = 1;i <= n; i++){
        for(int j = 1; j <= n; j++){
            matrizPesos[i][j] = 0;
        }
    }
}

template<typename T>
void Grafo<T>::insereAresta(T u, T v) {
	adj[u].insere(v);
	adj[v].insere(u);
	m++;
}

template<typename T>
void Grafo<T>::insereArestaPeso(T u, T v, float peso){
    matrizPesos[u][v] = peso;
    matrizPesos[v][u] = peso;
	insereAresta(u, v);
    m++;
}

template<typename T>
void Grafo<T>::imprimeGrafo() {
	for(int i = 1; i <= n; i++) {
		cout << "v[" << i << "] = ";
		adj[i].imprimirLista();
	}
}

template<typename T>
float Grafo<T>::DFS() {
    for(int i = 0; i < n + 1; i++){
        cor[i] = BRANCO;
        predecessor[i] = -1; 
    }

    tempoDFS = 0;
    for(int u = 1; u < n + 1; u++){
    	if(cor[u] == BRANCO) {
    		DFS_Visita(u);
    	}
    }
    return pesoDFS;
}

template<typename T>
void Grafo<T>::DFS_Visita(T u) {
	tempoDFS++;
	tempoEntradaDFS[u] = tempoDFS;
	cor[u] = CINZA;

	No<T>* p = adj[u].getPrim()->getProx();
	while(p != NULL){
    	if(cor[p->getItem()] == BRANCO){
    		pesoDFS += matrizPesos[u][p->getItem()];
    		predecessor[p->getItem()] = u;
    		DFS_Visita(p->getItem());
    	}
        p = p->getProx();
    }

    cor[u] = PRETO;
    tempoDFS++;
    tempoSaidaDFS[u] = tempoDFS;
}


template<typename T>
Lista<T> Grafo<T>::BFS (T inicioVertice, T fimVertice, T qtd, T enemies[]){
    T vertice = inicioVertice; 
    bool found = false;
    int* cor = new int[n + 1];
    int* distancia = new int[n + 1];
    T* predecessor = new T[n + 1];

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

    return prev;
}