/* --------------------------------------------------
PROJETO 1 - ALG. EM GRAFOS - 2018
Prof. Candida Nunes
ALuno: Bruno Morii Borges - 726500
-------------------------------------------------- */

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


//TESTE DA BICOLORACAO

/* Como o problema de bicoloracao pode ser usado para o problema de biparticao
usaremos isto para reduzir o numero de vetores utilizados numa busca, restan-
do apenas o vetor de cores.*/
int bicoloracao(Lista *lista, int n);


/*----------------------------------
	IMPLEMENTACAO DA FUNCAO MAIN 
----------------------------------*/

int main(){
	int m, n, i, u, v;
	Fila *fila;
	Lista *lista;

	scanf("%d %d", &n, &m); //entra com vertices e arestas iniciais

	//roda enquanto não receber dois zeros
	do{
		//incrementa n, pois numeracao do vertice comeca em 1
		n++; //espaco inutil no vetor de tamanho int + *Lista

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

		//realiza teste de bipartiao (bicoloracao)
		if(bicoloracao(lista, n)){
			printf("SIM\n");
		}else{
			printf("NAO\n");
		}

		//limpa a lista atual
		limpar_lista(lista, n);
		free(lista);

		scanf("%d %d", &n, &m); //entradas novas com vertices e arestas
	}while(n != 0 && m != 0);

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

/* 
	Como o problema de bicoloracao pode ser usado para o problema de biparticao
usaremos isto para reduzir o numero de vetores utilizados numa busca, restan-
do apenas o vetor de cores.
	Prop.: Um grafo G é bípartido se e somente se não possuir ciclo ímpar
*/

int bicoloracao(Lista *lista, int n){
	int i, visitados, raiz, v;
	char cor[2001], cor_atual, pintor; //no maximo 2000 vertices, lembrando do tratamento do 0, por isso 2001
	Fila *fila = (Fila *) malloc (sizeof (Fila)); //criando a Fila
	Lista *aux; //auxiliar de vizinhanca

	inicializar_fila(fila); //inicializa valores na fila
	visitados = 0; //inicializa contador de visitas

	//inicializa o vetor de cores com branco, a cor neutra
	for(i = 0; i < n; i++){
		cor[i] = 'b';
	}

	/*Para esse problema, as duas cores de bicoloracao serão azul ('a') e vermelho ('v')*/

	//while para verificar se todos os vértices foram visitados, grafos desconexos
	while(visitados < (n - 1)){
		//execucao do algoritmos de busca adaptado
		for(i = 1; i < n; i++){
			//escolhe raiz no primeiro branco
			if(cor[i] == 'b'){
				raiz = i;
				break;
			}
			//Obs.: aumenta a complexidade D: ;-;
			/*Obs2.: assumindo os casos de teste abertos, sem isso é ok.
			No entanto, ele só consideraria o primeiro grafo encontrado,
			mas e se esistirem grafos desconexos? Esse for serve para 
			tentar resolver*/
		}
		raiz = i;
		inserir(fila, raiz); //insere a raiz
		cor[raiz] = 'a'; //comeca com a cor azul

		//inicia busca
		while(!fila_vazia(fila)){
			//imprimir_fila(fila);
			v = remover(fila); //retira vertice da fila
			visitados++;

			//escolhe para pintor de acordo com a cor do v atual
			cor_atual = cor[v];
			if(cor_atual == 'a'){
				pintor = 'v';
			}else if(cor_atual == 'v'){
				pintor = 'a';
			}else{
				//caso de erro. Não deve acontecer D: mas está aqui por debug
				printf("Ih rapaz! Algo errado aí!\n");
				limpar_fila(fila);
				free(fila);
				return 0;
			}

			aux = lista[v].prox; //pega adjacencias
			
			//pinta ou verifica ocorrencia de ciclo impar pela cor
			while(aux != NULL){
				if(cor[aux->num] == 'b'){
					//caso branco, apenas pinta
					cor[aux->num] = pintor;
					inserir(fila, aux->num);
				}else if(cor[aux->num] == cor_atual){
					//caso em que vizinho tem a mesma cor que v
					//ciclo impar detectado
					limpar_fila(fila);
					free(fila);
					return 0;
				}
				aux = aux->prox;
			}
		}

	}

	limpar_fila(fila);
	free(fila);
	return 1; //se nao encontrou problemas e possivel separar em dois grupos
}