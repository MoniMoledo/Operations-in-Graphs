#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
Fadel:
    Tipo vizinho
    **/
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
/**
Fadel:
    busca o elemento passado como parametro no grafo passado como parametro
    **/
TGrafo* busca(TGrafo *g, char* elem){

    TGrafo *p=g;
    while((p) && (strcmp(p->id, elem)!=0))
        p=p->prox;
    return p;
}
/**
Fadel:
    inicializa um grafo vazio
    **/
TGrafo *inicializa(void){
    return NULL;
}
/**
Fadel:
    insere o no com id "no" no grafo g
    **/
TGrafo* ins_no(TGrafo *g,char* no){
    TGrafo *p=busca(g,no);
    if(p) return g;
    TGrafo* novo = (TGrafo *) malloc(sizeof(TGrafo));
    novo->id=no;
    novo->prim=NULL;
    novo->prox=g;
    return novo;
}

/**
Monique:
    remove a aresta no grafo g entre os dois nós que tem as ids passados como parametro(id1,id2).
    **/
void remove_aresta(TGrafo *g,char* id1,char* id2){
    TGrafo * p = busca(g, id1), *q = busca(g, id2);
    if((!p)||(!q)) return;
    TViz * viz = p->prim, * ant = NULL;
    while((viz)&&(strcmp(viz->id, id2))){
        ant=viz;
        viz = viz->prox_vizinho;
    }
    if(!viz) return;
    if(!ant)
        p->prim = p->prim->prox_vizinho;
    else
        ant->prox_vizinho= viz->prox_vizinho;
    free(viz);
    viz= q->prim;
    ant = NULL;
    while((viz)&&(strcmp(viz->id, id1))){
            ant = viz;
            viz= viz->prox_vizinho;
    }
    if(!viz) return;
    if(!ant)
            q->prim=q->prim->prox_vizinho;
    else
        ant->prox_vizinho=viz->prox_vizinho;
    free(viz);
}

/**
Fadel:
    remove o no identificado com a id passada como parametro do grafo g
    **/
TGrafo *remove_no(TGrafo *g,char* no){
    TGrafo* p = busca(g,no);
    if(!p)
        return g;
    TViz *v=p->prim;
    TViz *antV;
    //Removendo todas as arestas do nó
    while(v){
        antV=v;
        v=v->prox_vizinho;
        //printf("Removendo aresta entre: %s & %s\n",p->id,antV->id);
        remove_aresta(g,p->id,antV->id);
    }

    //compara se p é a cabeça do grafo
    TGrafo *q =g;
    if(strcmp(p->id,q->id)==0){
        g=p->prox;
        free(p);
        return g;
    }
    //Andando com o ponteiro q do inicio do grafo ate o nó anterior ao removido
    while(q->prox!=p) q=q->prox;
    //Removendo nó
    q->prox=p->prox;
    free(p);
    return g;
}
/**
Monique:
    insere uma aresta entre os nós que tem as id passadas como parametro(no1,no2)**/
void ins_aresta(TGrafo *g, char* no1, char* no2){
    if(strcmp(no1,no2)==0) return;
    if(eConectado(g, no1,no2)) return;
    TGrafo *p = busca(g,no1);
    TGrafo *q = busca(g,no2);
    if((!p) || (!q))
        return;
    TViz *novo = (TViz *) malloc((sizeof(TViz)));
    novo->id = no2;
    novo->prox_vizinho=p->prim;
    p->prim=novo;
    novo=(TViz *) malloc((sizeof(TViz)));
    novo->id=no1;
    novo->prox_vizinho=q->prim;
    q->prim=novo;
}
/**
Monique:
    libera o grafo**/
void libera(TGrafo *g){

    TGrafo *p=g;
    while(p){
        TViz*v = p->prim;
        while(v){
            TViz* q=v;
            v=v->prox_vizinho;
            free(q);
        }
        TGrafo *r = p;
        p=p->prox;
        free(r);
    }
}
/**
Monique:
    imprime o grafo.
    **/
void imprime(TGrafo *g){
    TGrafo *p = g;
    while(p){
        printf("No: %s\n Vizinhos: \n",p->id);
        TViz *q = p->prim;
        while(q){
            printf("        %s \t\n",q->id);
            q=q->prox_vizinho;
        }
        p=p->prox;
    }
}
/**
Matheus:
    dado dois nós identificados por no1 e no2, essa funçao verifica se há uma aresta entre eles
    **/
int eConectado(TGrafo *g,char* no1,char* no2){
    TGrafo *p=busca(g,no1);
    TGrafo *q=busca(g,no2);
    if(!p||!q) return 0;
    TViz *v;
    for(v=p->prim;v!=NULL;v=v->prox_vizinho){
        if(strcmp(v->id,q->id)==0){
            return 1;
        }
    }
    return 0;
}
/**
Matheus:
    Passados dois nós identificados por no1 e no2, a funçao verifica usando backtracking se é possivel, "andando" pelas arestas
    do grafo, chegar de no1 à no2(O grafo aux é para impedir que o algoritimo repita o caminho já feito)
    **/
int daPraChegar(TGrafo *g,char* no1,char* no2,TGrafo *aux){
    if(eConectado(g,no1,no2)) return 1;
    TGrafo *p=busca(g,no1);
    aux=ins_no(aux,no1);
    TViz *v;
    for(v=p->prim;v!=NULL;v=v->prox_vizinho){
        if(!busca(aux,v->id)){
            if(daPraChegar(g,v->id,no2,aux)) return 1;
        }
    }
    return 0;
}
/**
Matheus:
    Para verificar se o grafo é conexo usamos o conceito visto em aula que um grafo só é conexo se, partindo de qualquer nó é possivel
    chegar a qualquer outro nó no grafo.
    Para isso usamos a funçao daPraChegar, se o numeros de nós que da pra chegar partindo da cabeça do grafo for menor que o numeros de nós no grafo
    podemos afirmar que o grafo é desconexo.
    **/
int eConexo(TGrafo *g){
    if(!g) return 0;
    if(!g->prox) return 1;
    TGrafo *p=g;
    TGrafo *q;
    TGrafo *aux=inicializa();
    if(!g) return -1;
    int resposta=0;
    int no_nos=0;
    for(q=p->prox;q!=NULL;q=q->prox){
        resposta=resposta+daPraChegar(g,p->id,q->id,aux);
        no_nos++;
    }
    libera(aux);
    return (resposta>=no_nos);
}
/**
Matheus:
    Dado dois nós identificados pelos parametros passados, verifica se a aresta entre eles é uma ponte.
    (Funçao não utilizada no trabalho).
    **/
int ePonte(TGrafo *g,char* no1,char* no2){
    if(!eConexo(g)){
        printf("Esse grafo nao e conexo");
        return -1;
    }
    int resposta=0;
    if(eConectado(g,no1,no2)){
        remove_aresta(g,no1,no2);
        if(!eConexo(g)) resposta =1;
        ins_aresta(g,no1,no2);
    }
    return resposta;
}
/**
Monique:Percorre todas as arestas de um grafo conexo, retirando cada uma e
    verificando se depois dessa retirada o grafo deixou de ser conexo, caracterizando assim
    esta aresta como uma ponte. Insere a aresta de volta e retorna o numero total de pontes.
    Se retornar -1 é devido ao grafo passado nao ser conexo.

    **/
int nPontes(TGrafo *g){
    int resp = 0;
   if(!eConexo(g))return -1;
       TGrafo *v;
       TGrafo *p = g;
       for(p; p!=NULL; p=p->prox){
        for(v=p->prox; v!=NULL; v=v->prox){
            if(eConectado(g, p->id, v->id)){
              remove_aresta(g, p->id, v->id);
              if(!(eConexo(g))){
                resp++;
              }
              ins_aresta(g, p->id, v->id);
            }
        }
      }
    return resp;
}
/**
Monique: Percorre o grafo g e retorna o número de nós existentes;
         Função auxiliar para escrever o grafo no arquivo.

    **/
int NumeroDeNos(TGrafo *g){
    TGrafo*p = g;
    int resp = 0;
    for(p; p!=NULL; p=p->prox){
        resp++;
    }
    return resp;
}
/**
Matheus:
    (Funçao "privada")
    sabendo que o grafo g não é conexo copiamos para o grafo ng o no identificado por no1 e todos os seus vizinhos
    (Não inserimos as arestas aqui)
    **/
TGrafo *getNos(TGrafo *g,char* no1, TGrafo *ng){
    TGrafo *p=busca(g,no1);
    ng=ins_no(ng,no1);
    TViz *v=p->prim;
    for(v;v!=NULL;v=v->prox_vizinho){
        if(!busca(ng,v->id)){
           ng=getNos(g,v->id,ng);
        }
    }
    return ng;
}
/**
Matheus:
    (Função "Privada")
    Passados os grafos g e ng, para cada nó em ng copiamos suas respectivas arestas em g
    **/
void getArestas(TGrafo *g,TGrafo *ng){
    TGrafo *p=ng;
    TGrafo *q;
    TViz *v;
    for(p;p!=NULL;p=p->prox){
        q=busca(g,p->id);
        v=q->prim;
        for(v;v!=NULL;v=v->prox_vizinho){
            ins_aresta(ng,p->id,v->id);
        }
    }
}
/**
Matheus:
    (Função "Privada")
    Sabendo que o grafo g é desconexo removemos todos os nos pertencentes a ng de g
    (ng deve ser obtido usando as funçoes getNos e getArestas, remover ng de g de outra forma pode não ser seguro)
    **/
TGrafo *removeComponente(TGrafo *g,TGrafo *ng){
    TGrafo *p=ng;
    for(p;p!=NULL;p=p->prox){
        g=remove_no(g,p->id);
    }
    return g;
}
/**
Matheus:
    (Função "Privada")
    Sabendo que o grafo g é desconexo devolvemos o outro grafo onde a cabeça é o nó desconexo
    identificado por no (ng) e remove ng de g
     **/
TGrafo *getGrafo(TGrafo *g,char *no){
    TGrafo *ng=inicializa();
    ng=getNos(g,no,ng);
    getArestas(g,ng);
    g=removeComponente(g,ng);
    return ng;
}
/**
Matheus:
    Inicia uma lista vazia onde os dados são grafos
    **/
TLista *iniciaLista(void){
    return NULL;
}
/**
Matheus:
    insere um grafo(elem) na lista(l).
    **/
TLista *insereNaLista(TLista *l,TGrafo *elem){
    TLista *novo=(TLista*)malloc(sizeof(TLista));
    novo->elem=elem;
    novo->prox=l;
    return novo;
}
/**
Matheus:
    Passado um grafo (CopiaDeG) devolve uma lista de grafos com seus componentes
    (é recomendado usar uma copia do seu grafo original como parametro para não perder sua estrutura original.)
    Lembrar de dar libera na copia apos usar os componentes.
    **/
TLista *getComponentes(TGrafo *CopiaDeG){
    TLista *l=iniciaLista();
    TGrafo *p=CopiaDeG;
    TGrafo *q=p->prox;
    TGrafo *componente;
    TGrafo *aux;
    for(q;q!=NULL;q=q->prox){
        aux=inicializa();
        if(!daPraChegar(CopiaDeG,p->id,q->id,aux)){
            componente=inicializa();
            componente=getGrafo(CopiaDeG,q->id);
            l=insereNaLista(l,componente);
        }
        libera(aux);
    }
    l=insereNaLista(l,p);
    return l;
}
/**
Matheus:
    Dado uma lista l imprime todos os seus elementos separados por um identificador
    **/
void imprimeLista(TLista *l){
    for(l;l!=NULL;l=l->prox){
        imprime(l->elem);
        printf("|_______________|\n");
        printf("\n");

     }
}
/**
Fadel:
    Cria uma copia idêntica ao grafo passado como parametro
    **/
TGrafo *copia(TGrafo* g){

    if(!g)return g;
    TGrafo *p = g;
    TGrafo *resp = inicializa();
    for(p;p!=NULL;p=p->prox){
        resp = ins_no(resp,p->id);
    }
    getArestas(g,resp);
    return resp;
}

/**
    Let the fun begin
    **/
int estaAUmaDistanciaNDeArestas(TGrafo *g,int n,char* no1,char*no2,TGrafo *aux){
    if (strcmp(no1,no2)==0)return 1;
    TGrafo *p=busca(g,no1);
    aux=ins_no(aux,no1);
    TViz *v;
    if(n>0){
        if (eConectado(p,no1,no2)) return 1;
        for(v=p->prim;v!=NULL;v=v->prox_vizinho){
            if ((!busca(aux,v->id))&&(estaAUmaDistanciaNDeArestas(g,(n-1),v->id,no2,aux))) return 1;
        }
    }
    return 0;
}

int estaoTodosAUmaDistanciaN(TGrafo *g,int n){
    TGrafo *p=g;
    TGrafo *q;
    TGrafo *aux;
    for (p;p!=NULL;p=p->prox){
        q=p->prox;
        for (q;q!=NULL;q=q->prox){
            aux=inicializa();
            if(!estaAUmaDistanciaNDeArestas(g,n,p->id,q->id,aux)) return 0;
            libera(aux);
        }
    }
    return 1;
}

int numeroMinDeDistancia(TGrafo *g){
    int n=0;
    while(!estaoTodosAUmaDistanciaN(g,n)) n++;
    return n;
}
