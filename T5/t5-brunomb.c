/* --------------------------------------------------
PROJETO 5 - ALG. EM GRAFOS - 2018
Prof. Candida Nunes
ALuno: Bruno Morii Borges - 726500
-------------------------------------------------- */

/*--------- MUDANCAS DO ANTERIOR ---------
	-Implementação de Dijkstra
	-Implementação da fila usada para implementar lista rodenada
	-Vetor dist adaptado para resolver menor índice quando custos iguais
	-Adapatacao da busca para t5
----------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

/*-----------------------------------
	ESTRUTURAS A SEREM UTILIZADAS 
-----------------------------------*/


//FILA DE VERIFICAÇÕES - nao precisa

//ED para fila de nos a serem verificados
typedef struct fila_nos{
	int indice; //representa o vertice
	int custo;
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
void inserir(Fila *fila, int vertice, int custo);
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
	int custo;
	struct lista_A *prox;
}Lista;

//inicializa ponteiro "prox" como NULL
void inicializar_lista(Lista *lista, int n);
//inclui um vizinho adjacente de forma ordenada
void incluir(Lista *lista, int u, int v, int c);
//limpa a estrutura da lista;
void limpar_lista(Lista *lista, int n);
//imprime a lista de adjacência
void imprimir_lista(Lista *lista, int n);

/* Visita e calcula o maior tempo das dependencias pelo pred
Retorna o o tempo para conclusao*/

void dijkstra(Lista *lista, int n, int k);


/*----------------------------------
	IMPLEMENTACAO DA FUNCAO MAIN 
----------------------------------*/

int main(){
	int m, n, k, i, u, v, c;
	Lista *lista;

	scanf("%d %d %d", &n, &m, &k); //entra com vertices e arestas iniciais

	//fazendo lista a mais por começar em 1
	//n++;

	//cria e incializa lista de adjacencias
	lista = (Lista *) calloc (n, sizeof(Lista));
	inicializar_lista(lista, n);


	//recebe as arestas e adiciona na lista de adjacencias
	for(i = 0; i < m; i++){
		scanf("%d %d %d", &u, &v, &c);
		incluir(lista, u, v, c); 
		incluir(lista, v, u, c); 
	}

	//testando se a lista esta certa
	//imprimir_lista(lista, n);

	dijkstra(lista, n, k);

	//limpa a lista atual
	limpar_lista(lista, n);
	free(lista);

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
void inserir(Fila *fila, int vertice, int custo){
	Fila_no *no_novo, *aux, *remov; //variavel para criar um novo no

	//cria um novo no, com "nome" do vertice que sera o ultima da fila
	no_novo = (Fila_no *) malloc(sizeof(Fila_no));
	no_novo->indice = vertice;
	no_novo->custo = custo;
	no_novo->prox = NULL;

	//senao insere ordenado
	aux = fila->inicio;

	//busca se ja existe
	while(aux != NULL){
		//se existe remove para inserir de novo de forma ordenada com novo custo
		if(aux->indice == vertice){
			aux = fila->inicio;
			//caso é o primeiro da fila
			if(fila->inicio->indice == vertice){
				remov = fila->inicio;
				fila->inicio = fila->inicio->prox;
				free(remov);
				break;
			}else{
				//nao e primeiro da fila
				while(aux->prox->indice != vertice){
					aux = aux->prox;
				}
				remov = aux->prox;
				aux->prox = aux->prox->prox;
				free(remov);
				break;
			}
		}
		aux = aux->prox;
	}

	//verifica caso a fila esteja vazia
	if(fila_vazia(fila)){
		//insere como primeiro e ultimo
		fila->inicio = no_novo;
		fila->fim = no_novo;
	}else{
		//senao insere ordenado
		aux = fila->inicio;

		//caso primeiro
		if(aux->custo > no_novo->custo){
			no_novo->prox = fila->inicio;
			fila->inicio = no_novo;
			return;
		}

		//outro caso
		while( (aux->prox != NULL) && (aux->prox->custo <= no_novo->custo && aux->prox->indice < no_novo->indice) ){
			aux = aux->prox;
		}

		no_novo->prox = aux->prox;
		aux->prox = no_novo;
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
		printf("%d [%d]", aux->indice, aux->custo);
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
		lista[i].custo = -1;
		lista[i].prox = NULL;
	}

}

//inclui um vizinho adjacente de forma ordenada
void incluir(Lista *lista, int u, int v, int custo){
	Lista *no_novo, *i;

	//cria novo no adjacente
	no_novo = (Lista *) malloc (sizeof(Lista));
	no_novo->num = v;
	no_novo->custo = custo;

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

void dijkstra(Lista *lista, int n, int k){
	Fila *fila;
	Lista *aux;
	int dist[10001][2], testes, i, ind, menor_dist[1][2];

	//roda para cada distrbibuidor de k a n
	for(testes = k; testes < n; testes++){
		//cria e inicializa a fila
		fila = (Fila*) calloc (1, sizeof(Fila));
		inicializar_fila(fila);

		//inicializa menor_dist
		menor_dist[0][0] = -1;
		menor_dist[0][1] = 10002;

		//inicializa dst com infinito e estado de visita
		for(i = 0; i < n; i++){
			dist[i][0] = -1;
			dist[i][1] = 0;
		}

		//inicializa raiz
		dist[testes][0] = 0;
		dist[testes][1] = 1;

		//insere raiz
		inserir(fila, testes, 0);

		//executa dijkstra para caminhos mínimos
		while(!fila_vazia(fila)){
			//teste da fila
			//imprimir_fila(fila);
			ind = remover(fila); //remove o de menor custo

			aux = lista[ind].prox; //pega adjacencias
			dist[ind][1] = 1; //visita

			//executa dijkstra para pegas as distancias
			while(aux != NULL){
				if(dist[aux->num][1] == 0){ //nao visitado
					//pega o valor menor, se for o caso, atuliza
					if( (dist[aux->num][0] == -1) || (dist[aux->num][0] > aux->custo + dist[ind][0]) ){
						//atualiza e insere na fila
						dist[aux->num][0] = aux->custo + dist[ind][0];
						inserir(fila, aux->num, dist[aux->num][0]);

						//já prevê se essa é a melhor estufa para este distribuidor
						if((menor_dist[0][0] == -1) || (menor_dist[0][0] >= dist[aux->num][0])){

							//se forem iguais, verifica índice, senão só verificar se é estufa
							if(menor_dist[0][0] == dist[aux->num][0] && menor_dist[0][1] > aux->num){
								if(aux->num < k){ //se é estufa
									menor_dist[0][0] = dist[aux->num][0];
									menor_dist[0][1] = aux->num;
								}
							}else if(menor_dist[0][0] != dist[aux->num][0]){
								if(aux->num < k){ //se é estufa
									menor_dist[0][0] = dist[aux->num][0];
									menor_dist[0][1] = aux->num;
								}
							}
						}
					}
				}
				aux = aux->prox;
			}
		}

		//para testes
		//printf("%d [", menor_dist[0][1]);
		//printf("%d]\n", menor_dist[0][0]);

		//imprime melhor estufa para cada distribuidor

		//trata de ser o ultimo, aí é \n ao invés de espaço
		if(testes ==  n -1){
			printf("%d\n", menor_dist[0][1]);
		}else{
			printf("%d ", menor_dist[0][1]);
		}

		//limpa fila e libera fila
		limpar_fila(fila);
		free(fila);
	}
}