/* --------------------------------------------------
PROJETO 2 - ALG. EM GRAFOS - 2018
Prof. Candida Nunes
ALuno: Bruno Morii Borges - 726500
-------------------------------------------------- */

/*--------- MUDANCAS DO ANTERIOR ---------
	-Comentarios
	- Busca em largura adaptada para verificar distancias
	-Adaptacao para o t2
----------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

/*-----------------------------------
	ESTRUTURAS A SEREM UTILIZADAS 
-----------------------------------*/

//FILA DE VERIFICAÇÕES

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

/* O problema envolve uma busca em largura, ou seja, verifica se
um vértice é alcancavel a partir da raiz. Para esse caso, a raiz
e sempre 0 e queremos a maior distancia.*/

//A funcao retorna a maior distancia ou -1 em caso de infinito
int dist_autores(Lista *lista, int n);


/*----------------------------------
	IMPLEMENTACAO DA FUNCAO MAIN 
----------------------------------*/

int main(){
	int m, n, i, u, v, resultado;
	Fila *fila;
	Lista *lista;

	scanf("%d %d", &n, &m); //entra com vertices e arestas iniciais

	//roda enquanto não receber dois zeros
	do{
		//cria e incializa lista de adjacencias
		lista = (Lista *) malloc (n * sizeof(Lista));
		inicializar_lista(lista, n);

		//recebe as arestas e adiciona na lista de adjacencias
		for(i = 0; i < m; i++){
			scanf("%d %d", &u, &v);
			incluir(lista, u, v);
			incluir(lista, v, u);
		}

		//testando se a lista esta certa
		//imprimir_lista(lista, n);

		//calcula as distancias
		resultado = dist_autores(lista, n);

		//imprime o resultado de acordo com retorno da funcao
		if(resultado == -1){
			printf("infinito\n");
		}else{
			printf("%d\n", resultado);
		}

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
}


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

/* O problema envolve uma busca em largura, ou seja, verifica se
um vértice é alcancavel a partir da raiz. Para esse caso, a raiz
e sempre 0 e queremos a maior distancia.*/

//A funcao retorna a maior distancia ou -1 em caso de infinito

int dist_autores(Lista *lista, int n){
	int i, visitados, v, dist_max = -1, dist_atual;
	char dist[1000]; //no maximo 1000 vertices
	Fila *fila = (Fila *) malloc (sizeof (Fila)); //criando a Fila
	Lista *aux; //auxiliar de vizinhanca

	inicializar_fila(fila); //inicializa valores na fila
	visitados = 1; //inicializa contador de visitas com 1, pois visitamos a raiz
	dist[0] = 0; //dist da raiz e sempre 0

	//inicializa vetor de distancia com -1, infinito
	for(i = 1; i < n; i++){
		dist[i] = -1;
	}

	//execucao do algoritmos de busca adaptado
	inserir(fila, 0); //insere a raiz

	/*inicia busca em largura, visita todos vertice conectados ao
	grafo com raiz em 0*/
	while(!fila_vazia(fila)){
		//imprimir_fila(fila);
		v = remover(fila); //retira vertice da fila
		visitados++; //aumenta contador de visitados

		//recebe distancia atual para calcular
		dist_atual = dist[v];
		//atualiza a distancia maxima se necessario
		if(dist_max < dist_atual){
			dist_max = dist_atual;
		}

		aux = lista[v].prox; //pega adjacencias
		
		//calcula as distancias
		while(aux != NULL){
			if(dist[aux->num] == -1){
				dist[aux->num] = dist_atual + 1;
				inserir(fila, aux->num);
			}
			aux = aux->prox;
		}
	}

	//limpa lila e libera memoria
	limpar_fila(fila);
	free(fila);

	//retorno baseado em visitas
	if(visitados < n){
		return -1;
	}else{
		return dist_max;
	}
}