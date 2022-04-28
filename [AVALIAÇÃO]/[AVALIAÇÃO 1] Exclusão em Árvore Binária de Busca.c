#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct sNoA {
    int chave;
    struct sNoA *esq;
    struct sNoA *dir;
} TNoA;

TNoA *exclui(TNoA *raiz, int chave) {
    //Se a árvore estiver vazia, retorna NULL;
    if(!raiz) return NULL;
    else {
        //Procura o nó a remover
        if(raiz->chave == chave){
            //Remove nó folha
            if(!raiz->esq && !raiz->dir){
                free(raiz);
                return NULL;}
            else{
                //Remove nó com 1 filho
                TNoA *aux;
                //Filho à esquerda
                if(raiz->esq && !raiz->dir){
                    aux = raiz->esq;
                    free(raiz);
                    return aux;
                }
                //Filho à direita
                else if(raiz->dir && !raiz->esq){
                    aux = raiz->dir;
                    free(raiz);
                    return aux;
                }
                //Remove nó com dois filhos
                else{
                    //Caminha para o subárvore à esquerda
                    aux = raiz->esq;
                    //Procura o elemento mais à direita da subárvore à esquerda
                    while(aux->dir)
                        aux = aux->dir;
                    //Realiza a troca de conteúdo entre os nós
                    raiz->chave = aux->chave;
                    aux->chave = chave;
                    //Remove o nó trocado (que pode ser um nó folha ou nó com 1 filho)
                    raiz->esq = exclui(raiz->esq, chave);
                    return raiz;
                }
            }
        }
        //Percorre a árvore até achar o nó desejado OU
        //Retorna NULL se não estiver presente na árvore
        else{
            if(chave < raiz->chave)
                raiz->esq = exclui(raiz->esq, chave);
            else
                raiz->dir = exclui(raiz->dir, chave);
            return raiz;
        }
    }
}

void imprime(TNoA *nodo, int tab) {
    for (int i = 0; i < tab; i++) {
        printf("-");
    }
    if (nodo != NULL) {
        printf("%d\n", nodo->chave);
        imprime(nodo->esq, tab + 2);
        printf("\n");
        imprime(nodo->dir, tab + 2);
    } else printf("vazio");
}

TNoA *insere(TNoA *no, int chave) {
    if (no == NULL) {
        no = (TNoA *) malloc(sizeof(TNoA));
        no->chave = chave;
        no->esq = NULL;
        no->dir = NULL;
    } else if (chave < (no->chave))
        no->esq = insere(no->esq, chave);
    else if (chave > (no->chave)) {
        no->dir = insere(no->dir, chave);
    } else {
        printf("Inserção inválida! ");
        exit(1);
    }
    return no;
}

int main(void) {

    /* A função main lê os dados de entrada, cria a árvore e chama a função solicitada no problema
     * depois imprime o resultado solicitado
     * ELA NÃO DEVE SER MODIFICADA
     * */
    TNoA *raiz;
    raiz = NULL;

    char l[100];
    char delimitador[] = "-";
    char *ptr;
    int valor;

    /* lê valores para criar a arvore
     * valores devem ser informados separados por traço
     * exemplo: 1-3-5-2-7-9-21-6 */
    scanf("%s", l);
    //quebra a string de entrada
    ptr = strtok(l, delimitador);
    while(ptr != NULL) {
        valor = atoi(ptr);
        raiz = insere(raiz, valor);
        ptr = strtok(NULL, delimitador);
    }

    //le valor a ser excluido
    scanf("%d", &valor);
    //Chama função
    raiz = exclui(raiz, valor);
    imprime(raiz, 0);
};