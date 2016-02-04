#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Arquivos.c"
#include "No.h"

int main()
{

   TGrafo* g = inicializa();
     g = lerGrafo("Exemplo.txt");
     imprime(g);
     escreveGrafo(g, "Exemplo.txt");
     escrevePonte(g);
     escreveComponentes(g);
     return 0;
    }
