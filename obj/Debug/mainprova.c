#include <stdio.h>
#include <stdlib.h>
#include "No.h"
#include "Arquivos.h"

int main(int numargs, char *arg[]){


    int x = -1;


    printf("Bem vindo ao programa de grafos de Matheus Souza, Monique Moledo e Pedro Fadel! \n");
    /** Coloquei só pra poder testar, pq nao consegui passar nada pra main aqui no code blocks kkkk */
    printf("Digite o nome do arquivo texto que contem o grafo com o qual deseja comecar trabalhar\n");
    scanf("%s",arg[1]);
    TGrafo * g = inicializa();
    g = lerGrafo(arg[1]);
    /** Se o grafo nao for lido, nao tem sentido  perguntar o que quer fazer, né? */

    printf("O que deseja fazer? \n");
    printf("\n");
    printf("1 - Imprimir o grafo: \n");
    printf("2 - Inserir No: \n");
    printf("3 - Inserir Aresta: \n");
    printf("4 - Remover No: \n");
    printf("5 - Remover Aresta: \n");
    printf("6 - Verificar se o grafo eh conexo: \n");
    printf("7 - Salvar suas alteracoes no arquivo: \n");
    printf("8 - Alguma coisa super duper legal que ainda faremos! \n");
    printf("0 - Sair do programa: \n");
    scanf("%d",&x);

    while(x != 0){
        switch(x){
            case 1:
                imprime(g);
                break;
            case 2:
                printf("Entre com o no que deseja inserir: \n");
                char* no = (char *) malloc(sizeof(char)*20);
                scanf("%s",no);
                g = ins_no(g,no);
                //free(no);
                break;
            case 3:
                printf("Entre com o primeiro no da aresta: \n");
                char* no1 = (char *) malloc(sizeof(char)*20);
                scanf("%s",no1);
                while(!busca(g,no1)){
                    printf("\t Este no nao existe no grafo, por favor tente outro nome: \n");
                    scanf("%s",no1);
                }
                printf("Entre com o segundo no da aresta: \n");
                char* no2 = (char *) malloc(sizeof(char)*20);
                scanf("%s",no2);
                while(!busca(g,no2)){
                    printf("\t Este no nao existe no grafo, por favor tente outro nome: \n");
                    scanf("%s",no2);
                }
                ins_aresta(g,no1,no2);
                //free(no1);
                //free(no2);
                break;
            case 4:
                printf("Entre com o no que deseja remover: \n");
                char* noR = (char *) malloc(sizeof(char)*20);
                scanf("%s",noR);
                g = remove_no(g,noR);
                //free(noR);
                break;
            case 5:
                printf("Entre com o primeiro no da aresta: \n");
                char* noR1 = (char *) malloc(sizeof(char)*20);
                scanf("%s",noR1);
                while(!busca(g,noR1)){
                    printf("\t Este no nao existe no grafo, por favor tente outro nome: \n");
                    scanf("%s",noR1);
                }
                printf("Entre com o segundo no da aresta: \n");
                char* noR2 = (char *) malloc(sizeof(char)*20);
                scanf("%s",noR2);
                while(!busca(g,noR2)){
                    printf("\t Este no nao existe no grafo, por favor tente outro nome: \n");
                    scanf("%s",noR2);
                }
                remove_aresta(g,noR1,noR2);
                //free(noR2);
                //free(noR1);
                break;
            case 6:
                printf("Verificar se eh conexo! \n");
                break;
            case 7:
                escreveGrafo(g,"saida.txt");
                break;
            case 8:
                printf("Algo super duper legal! \n");
                break;
            default:
                printf("Operacao invalida! \n");
                break;

        }
        printf("O que mais deseja fazer? \n");
        printf("\n");
        printf("1 - Imprimir o grafo: \n");
        printf("2 - Inserir No: \n");
        printf("3 - Inserir Aresta: \n");
        printf("4 - Remover No: \n");
        printf("5 - Remover Aresta: \n");
        printf("6 - Verificar se o grafo eh conexo: \n");
        printf("7 - Salvar suas alteracoes no arquivo: \n");
        printf("8 - Alguma coisa super duper legal que ainda faremos! \n");
        printf("0 - Sair do programa: \n");
        scanf("%d",&x);
    }


    return 0;
    }
