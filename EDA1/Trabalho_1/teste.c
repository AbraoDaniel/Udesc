#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Pilha.h"

char entrada[30];
char saida [30];

int main(int argc, char *argv[])
{    
   int result;
    printf("Informe a conta que deseja realizar: ");
    
    fgets(entrada, 30, stdin);
     for(int i = 0; entrada[i] != 0; i++){ 
        char caractere_atual = entrada[i];
        if(caractere_atual >= 48 && caractere_atual <= 57){
            int numero = caractere_atual - 48;
            result = numero;
        }
        
    }
    printf("%d\n", result);
    return EXIT_SUCCESS;
}