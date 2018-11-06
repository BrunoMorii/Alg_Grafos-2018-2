/* --------------------------------------------------
PROJETO 4 - ALG. EM GRAFOS - 2018
Prof. Candida Nunes
ALuno: Bruno Morii Borges - 726500
-------------------------------------------------- */

/*--------- MUDANCAS DO ANTERIOR ---------
	-Busca comeentada
	-Vetor para atualizacao dos maiores tmepos de projeto
	-Adapatacao da busca para t4
----------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

/*-----------------------------------
	ESTRUTURAS A SEREM UTILIZADAS 
-----------------------------------*/

/*
//FILA DE VERIFICAÇÕES - nao precisa

//ED para fila de nos a serem verificados
typedef struct fila_nos{
	int indice; //representa o vertice
	struct fila_nos *prox; //proximo da fila
}Fila_no;

//facilitar visualizacao da fila
typedef struct fila_F{
	Fila_no *inicio;
	Fila_no *fim;
}Fila;

//fila vazia, retorna 1 se vazia, 0 senão
int fila_vazia(Fila* fila);
//inicializa a fila
void inicializar_fila(Fila *fila);
//insere na fila
void inserir(Fila *fila, int vertice);
//remove da fila
int remover(Fila *fila);
//imprime a fila
void imprimir_fila(Fila *fila);
//limpa fila se sobrar lixo
void limpar_fila(Fila *fila);

*/
//LISTA DE ADJACENCIAS

//ED para lista de adjacencias (apos vetor com vertices)
typedef struct lista_A{
	int num;
	struct lista_A *prox;
}Lista;

//inicializa ponteiro "prox" como NULL
void inicializar_lista(Lista *lista, int n);
//inclui um vizinho adjacente de forma ordenada
void incluir(Lista *lista, int u, int v);
//limpa a estrutura da lista;
void limpar_lista(Lista *lista, int n);
//imprime a lista de adjacência
void imprimir_lista(Lista *lista, int n);

/* Visita e calcula o maior tempo das dependencias pelo pred
Retorna o o tempo para conclusao*/

int tempo_projeto(Lista *lista, int *tempo, int n);
void busca_largura(Lista *lista, int *tempo, char *visit, int v, int *t);


/*----------------------------------
	IMPLEMENTACAO DA FUNCAO MAIN 
----------------------------------*/

int main(){
	int m, n, i, u, v, *tempo;
	Lista *lista;

	scanf("%d %d", &n, &m); //entra com vertices e arestas iniciais

	//roda enquanto não receber dois zeros
	do{
		//fazendo lista a mais por começar em 1
		//n++;

		//cria e incializa lista de adjacencias
		lista = (Lista *) calloc (n, sizeof(Lista));
		inicializar_lista(lista, n);
		//cria vetor com tempos de projeto
		tempo = (int *) calloc (n, sizeof(int));

		//recebe o tempo de cada projeto
		for(i = 0; i < n; i++){
			scanf("%d", &tempo[i]);
		}

		//recebe as arestas e adiciona na lista de adjacencias
		for(i = 0; i < m; i++){
			scanf("%d %d", &u, &v);
			incluir(lista, u, v); //insere a adjacencia de mao unica 
		}

		//testando se a lista esta certa
		//imprimir_lista(lista, n);

		//verifica o quesito de conexidade
		printf("%d\n", tempo_projeto(lista, tempo, n));

		//limpa a lista atual
		limpar_lista(lista, n);
		free(lista);
		free(tempo);

		scanf("%d %d", &n, &m); //entradas novas com vertices e arestas
	}while(n != 0 || m != 0);

	return 0;
}

/*-----------------------------------------
	IMPLEMENTACAO DE FUNCOES AUXILIARES
-----------------------------------------*/

//nao precisa de fila
/*
//fila vazia, retorna 1 se vazia, 0 senão
int fila_vazia(Fila* fila){
	if(fila->inicio == NULL){
		return 1;
	}

	return 0;
}

//inicializa a fila
void inicializar_fila(Fila *fila){
	fila->inicio = NULL;
	fila->fim = NULL;
}

//insere na fila
void inserir(Fila *fila, int vertice){
	Fila_no *no_novo; //variavel para criar um novo no

	//cria um novo no, com "nome" do vertice que sera o ultima da fila
	no_novo = (Fila_no *) malloc(sizeof(Fila_no));
	no_novo->indice = vertice;
	no_novo->prox = NULL;

	//verifica caso a fila esteja vazia
	if(fila_vazia(fila)){
		//insere como primeiro e ultimo
		fila->inicio = no_novo;
		fila->fim = no_novo;
	}else{
		//senao insere e atualiza como ultimo
		fila->fim->prox = no_novo;
		fila->fim = no_novo;
	}
}

//remove da fila
int remover(Fila *fila){
	int num; //indice do vertice removido
	Fila_no *remov_no; //auxiliar de remocao

	if(fila_vazia(fila)){ //se fila vazia, nao tem o que remover
		return -1;
	}

	remov_no = fila->inicio; //pega par armeocao

	fila->inicio = fila->inicio->prox; //atualiza a fila
	if(fila->inicio == NULL){ //nao e tao necessario, mas emlhor evitar problemas
		fila->fim = fila->inicio;
	}

	num = remov_no->indice;
	free(remov_no); //libera memoria

	return(num);
}

//imprime a fila
void imprimir_fila(Fila *fila){
	Fila_no *aux;

	aux = fila->inicio;

	printf("Fila: ");
	if(aux == NULL){
		printf("VAZIA!");
	}

	while(aux != NULL){
		printf("%d ", aux->indice);
		aux = aux->prox;
	}

	printf("\n");
}

//limpa fila se sobrar lixo
void limpar_fila(Fila *fila){
	Fila_no *aux, *limpa;

	if(fila_vazia(fila)){
		return;
	}
	
	aux = fila->inicio;

	while(aux != NULL){
		limpa = aux;
		aux = aux->prox;
		free(limpa);
	}
}*/


//inicializa ponteiro "prox" como NULL
void inicializar_lista(Lista *lista, int n){
	int i;

	//valor do no vizinho apenas para nao ter lixo, indice 0 nao e util
	for(i = 0; i < n; i++){
		lista[i].num = i;
		lista[i].prox = NULL;
	}

}

//inclui um vizinho adjacente de forma ordenada
void incluir(Lista *lista, int u, int v){
	Lista *no_novo, *i;

	//cria novo no adjacente
	no_novo = (Lista *) malloc (sizeof(Lista));
	no_novo->num = v;

	//comeca iteracao para insercao ordenada na lista
	i = &lista[u];

	//percorre para encontrar onde inserir
	while(i->prox != NULL && i->prox->num < v){
		i = i->prox;
	}

	//insere na lista
	no_novo->prox = i->prox;
	i->prox = no_novo;
}

//limpa a estrutura da lista
void limpar_lista(Lista *lista, int n){
	int i;
	Lista *aux_limpeza, *j;

	//percorre o vetor liberando adjacencias
	for(i = 0; i < n; i++){
		j = lista[i].prox; //pega o indice do vetor e sua primeira adjacencia

		//limpa cada vertice adjacente
		while(j != NULL){
			aux_limpeza = j;
			j = j->prox;
			free(aux_limpeza);
		}
	}
}

//imprime a lista de adjacência
void imprimir_lista(Lista *lista, int n){
	int i;
	Lista *j;

	printf("[v] -> u's\n\n");
	for(i = 1; i < n; i++){
		printf("[%d] -> ", i);
		j = lista[i].prox;
		while(j != NULL){
			printf("%d ", j->num);
			j = j->prox;
		}
		printf("\n");
	}
}

/* Visita e calcula o maior tempo das dependencias pelo pred
Retorna o tempo para conclusao*/

int tempo_projeto(Lista *lista, int *tempo, int n){
	int i, j, k, soma_tempo = 0;
	char *visitados; 

	visitados = (char*) calloc (6000, sizeof(char)); //no maximo 6000 vertices

	//inicializa vetor de visitas com branco, infinito
	for(j = 0; j < n; j++){
		visitados[j] = 'b';
	}

	//passa em todos os vértices e inicia a busca a partir de um vertice nao visitado
	for(i = 0; i < n; i++){
		if(visitados[i] == 'b'){
			busca_largura(lista, tempo, visitados, i, &soma_tempo);
		}
	}

	for(i = 0; i < n; i++){ //verifica qual foi o maior tempo de projetos
		if(soma_tempo < tempo[i]){
			soma_tempo = tempo[i];
		}
	}

	free(visitados);
	return soma_tempo;
}

void busca_largura(Lista *lista, int *tempo, char *visit, int v, int *t){
	Lista *aux;
	int max_tempo = tempo[v]; //maior tempo atual e o sue proprio inicialmente

	visit[v] = 'c'; //vertice visitado, inicia busca em vizinhanca

	aux = lista[v].prox;

	while(aux != NULL){
		if(visit[aux->num] == 'b'){
			busca_largura(lista, tempo, visit, aux->num, t);
		}
		//para cada vizinho verifica qual adjacencia e possivel o maior tempo
		if(max_tempo < tempo[v] + tempo[aux->num]){
			max_tempo = tempo[v] + tempo[aux->num];
		}
		aux = aux->prox;
	}

	visit[v] = 'p';
	tempo[v] = max_tempo; //atualiza o tempo do projeto com a soma de suas "maiores" dependencias
}