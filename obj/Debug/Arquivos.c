#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "No.h"


/**Monique: Passado como parâmetro o grafo g e o nome do arquivo de entrada, cria-se um novo arquivo texto de nome
"novo-NomeArqEntrada.txt" que contém primeiro o número de nós, em seguida o nome de cada nó e depois as arestas do grafo.

*/
void escreveGrafo(TGrafo * g, char* NomeArqEntrada){
    FILE * f;
    char nome[10] = "novo-";
    strcat(nome, NomeArqEntrada);
    f = fopen(nome, "w");
    if(!f){
        printf("Houve um erro ao criar o arquivo para escrita\n");
        return;
    }
    int num = NumeroDeNos(g);
    fprintf(f, "%d\n", num);
    TGrafo *p = g;
    for(p; p!=NULL; p=p->prox){
        fprintf(f, "%s\n", p->id);
    }

    TGrafo *v;
    p = g;

    for(p; p!=NULL; p=p->prox){
        for(v=p->prox; v!=NULL; v=v->prox){
            if(eConectado(g, p->id, v->id)){
                fprintf(f, "%s %s\n", p->id, v->id);
            }
        }
    }
    fclose(f);
}

/**Monique: Passado como parâmetro o grafo g, cria-se um novo arquivo texto de nome
"Pontes.txt" no qual primeiro é escrito o número de pontes e em seguida todas as pontes do grafo.
*/
void escrevePonte(TGrafo *g){
    FILE * f;
    f = fopen("Pontes.txt", "w");
    if(!f){
        printf("Houve um erro ao abrir o arquivo\n");
        return;
    }
    if(!eConexo(g)){
        fclose(f);
        return;
    }
    fprintf(f, "%d\n", nPontes(g));
    TGrafo *v;
    TGrafo *p = g;
    for(p; p!=NULL; p=p->prox){
      for(v=p->prox; v!=NULL; v=v->prox){
         if(eConectado(g, p->id, v->id)){
            remove_aresta(g, p->id, v->id);
            if(!(eConexo(g))){
                 fprintf(f, "%s %s\n", p->id, v->id);
            }
            ins_aresta(g, p->id, v->id);
        }
      }
    }
    fclose(f);
}

void escreveComponentes(TGrafo *g){
    FILE *f = fopen("Componentes.txt", "w");
    if(!f){
        printf("Houve um erro ao abrir o arquivo\n");
        return;
    }
    if(!g){
       fclose(f);
       return;
    }
    TGrafo *c=copia(g);
    TLista *l=getComponentes(c);
    TGrafo *q,*p;
    TViz *v;
    TLista *al=l;
    int i=0,num=0;
    for(al;al!=NULL;al=al->prox,i++){
        q=al->elem;
        fprintf(f,"Grafo %d:\n",i);
        p=q;
        num=NumeroDeNos(q);
        fprintf(f,"%d\n",num);
        for(p;p!=NULL;p=p->prox){
            fprintf(f,"%s\n",p->id);
        }
        p=al->elem;
        for(p;p!=NULL;p=p->prox){
            v=p->prim;
            for(v;v!=NULL;v=v->prox_vizinho){
                fprintf(f,"%s %s\n",p->id,v->id);
            }
        }
    }
    fclose(f);
    libera(c);
    /**LiberaLista(l)**/
}
/**Monique: Passado como parâmetro o grafo g, cria-se um novo arquivo texto de nome
"Componentes.txt" e uma lista de grafos que são os componentes do grafo g. Conta-se o número de elementos dessa lista,
que significa o numero de componentes, que é escrito no arquivo. Depois escreve os nós de cada componente

void escreveComponentes(TGrafo *g){
    FILE *f = fopen("Componentes.txt", "w");
    if(!f){
        printf("Houve um erro ao abrir o arquivo\n");
        return;
    }
    if(!g){
       fclose(f);
       return;
    }
    TLista *l = iniciaLista();
    l = getComponentes(g);
    int n = 0;
    if(l){
       TLista *p=l;
        while(p){
            n++;
            p=p->prox;
        }
    }
    fprintf(f, "%d\n", n);

    for(l;l!=NULL;l=l->prox){
      TGrafo *p = l->elem;
      for(p;p->prox!=NULL;p=p->prox){
        fprintf(f, "%s ", p->id);
      }
      fprintf(f, "%s\n", p->id);
    }
    fclose(f);
   }*/


long tamanhoArquivo(FILE *arquivo) {

    // guarda o estado ante de chamar a função fseek
    long posicaoAtual = ftell(arquivo);

    // guarda tamanho do arquivo
    long tamanho;

    // calcula o tamanho
    fseek(arquivo, 0, SEEK_END);
    tamanho = ftell(arquivo);

    // recupera o estado antigo do arquivo
    fseek(arquivo, posicaoAtual, SEEK_SET);

    return tamanho;
}

/**Monique: Passado como parâmetro o nome do arquivo que contem o grafo a ser lido,
a função abre o arquivo, cria um grafo vazio, lê o nome de cada nó, e insere esse nó no grafo criado,
depois lê as aresta e insere as mesmas no grafo que é retornado;
*/
 TGrafo* lerGrafo(char * nome){
    FILE *f;
    f = fopen(nome, "r");
    if(tamanhoArquivo(f)==0){
       printf("O arquivo esta vazio\n");
       return NULL;
    }
    if(!f){
        printf("Houve um erro ao abrir o arquivo para leitura,\nele pode nao estar na pasta corrente, verifique e tente novamente\n");
        return NULL;
    }
    printf("HERE");
    TGrafo *g = inicializa();
    int numNos, cont = 0;
    fscanf(f, "%d", &numNos);
    printf("HERE2");
    if(numNos==0) return NULL;
    fgetc(f);

    for(cont; cont<numNos;cont++){
            printf("HERE3");
        char* no = (char *) malloc(sizeof(char)*20);
        fgets(no, 20,f);
        strtok(no,"\n");
        g = ins_no(g,no);

    }
    while(!feof(f)){
        char* no1 = (char *) malloc(sizeof(char)*20);
        char* no2 = (char *) malloc(sizeof(char)*20);

        fscanf(f,"%s",no1);
        fscanf(f,"%s[^\n]",no2);
        ins_aresta(g,no1,no2);
    }

    fclose(f);
    return g;
}

