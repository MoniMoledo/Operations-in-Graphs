#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct vizinho{ // tipo vizinho
    char* id; // nome do vizinho
    struct vizinho *prox_vizinho; // ponteiro para o próximo vizinho
}TViz;
/**
Fadel:
    Tipo grafo
    **/
typedef struct grafo{ // tipo nó
    char* id; // nome do nó
    TViz* prim; // ponteiro para o primeiro vizinho
    struct grafo* prox; //ponteiro para o próximo nó
}TGrafo;
/**
Matheus:
    tipo lista
    **/
typedef struct lista{
    TGrafo *elem;
    struct lista *prox;
}TLista;

TGrafo* busca(TGrafo *g, char* elem);

TGrafo *inicializa(void);

TGrafo* ins_no(TGrafo *g,char* no);

void remove_aresta(TGrafo *g,char* id1,char* id2);

TGrafo *remove_no(TGrafo *g,char* no);

void ins_aresta(TGrafo *g, char* no1, char* no2);

void libera(TGrafo *g);

void imprime(TGrafo *g);

int eConectado(TGrafo *g,char* no1,char* no2);

//int daPraChegar(TGrafo *g,char* no1,char* no2,TGrafo *aux);

int eConexo(TGrafo *g);

//int ePonte(TGrafo *g,char* no1,char* no2);

int nPontes(TGrafo *g);

int NumeroDeNos(TGrafo *g);

TLista *iniciaLista(void);

TLista *insereNaLista(TLista *l,TGrafo *elem);

TLista *getComponentes(TGrafo *g);

void imprimeLista(TLista *l);

TGrafo *copia(TGrafo *g);

/**
    Let the fun begin
    **/

int estaoTodosAUmaDistanciaN(TGrafo *g,int n);

int numeroMinDeDistancia(TGrafo *g);

