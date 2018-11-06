/* --------------------------------------------------
PROJETO 3 - ALG. EM GRAFOS - 2018
Prof. Candida Nunes
ALuno: Bruno Morii Borges - 726500
-------------------------------------------------- */

/*--------- MUDANCAS DO ANTERIOR ---------
	-Busca em Profundidade
	-Rotinas extras foram comentadas
	-Adaptacao da em profundidade
		-apenas ve se todos foram alcancados
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

/* Tenta visitar todos os vertice a partir da raiz que sera o vertice 1
Se houver algum vertice nao visitado, retorna 0, caso contrario, retorna 1*/

int ver_conexidade(Lista *lista, int n);
void busca_largura(Lista *lista, char *visit, int v);


/*----------------------------------
	IMPLEMENTACAO DA FUNCAO MAIN 
----------------------------------*/

int main(){
	int m, n, i, v, p, w, resultado;
	Lista *lista;

	scanf("%d %d", &n, &m); //entra com vertices e arestas iniciais

	//roda enquanto não receber dois zeros
	do{
		//fazendo lista a mais por começar em 1
		n++;
		//cria e incializa lista de adjacencias
		lista = (Lista *) malloc (n * sizeof(Lista));
		inicializar_lista(lista, n);

		//recebe as arestas e adiciona na lista de adjacencias
		for(i = 0; i < m; i++){
			scanf("%d %d %d", &v, &w, &p);
			incluir(lista, v, w); //insere a adjacencia de mao unica 

			if(p == 2){ //se mao dupla
				incluir(lista, w, v);
			}
		}

		//testando se a lista esta certa
		//imprimir_lista(lista, n);

		//verifica o quesito de conexidade
		printf("%d\n", ver_conexidade(lista, n));

		//limpa a lista atual
		limpar_lista(lista, n);
		free(lista);

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

/* Tenta visitar todos os vertice a partir da raiz que sera o vertice 1
Se houver algum vertice nao visitado, retorna 0, caso contrario, retorna 1*/

int ver_conexidade(Lista *lista, int n){
	int i, j;
	char *visitados; 

	visitados = (char*) malloc (2001 * sizeof(char)); //no maximo 2000 vertices

	//passa em todos os vértices
	for(i = 1; i < n; i++){
		//inicializa vetor de visitas com branco, infinito
		for(j = 1; j < n; j++){
			visitados[j] = 'b';
		}

		//primeiro vertice é 1
		busca_largura(lista, visitados, i);

		//for comecando em 1, pois primeiro valor e 1 e nao 0
		for(j = 1; j < n; j++){
			if(visitados[j] != 'p'){
				free(visitados);
				return 0;
			}
		}
	}

	free(visitados);
	return 1;
}

void busca_largura(Lista *lista, char *visit, int v){
	Lista *aux;

	visit[v] = 'c';

	aux = lista[v].prox;

	while(aux != NULL){
		if(visit[aux->num] == 'b'){
			busca_largura(lista, visit, aux->num);
		}
		aux = aux->prox;
	}

	visit[v] = 'p';
}