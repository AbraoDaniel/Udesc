#include <stdio.h>
#include <stdlib.h>
#include "Pilha.h"

int precedencia (char *s);

int main(int argc, char *argv[])
{
    char entrada[30];
    char saida [30];
    int deu_erro = 0;
    
    printf("Informe a conta que deseja realizar: ");
    
    int w;
    for(w = 0; w < strlen(entrada); w++) {
          scanf("%s", &entrada[w]);
    } 
    
    Pilha p;
    inicializa_pilha( &p, strlen(entrada));
    
    int i, j, aux;
    for( i = 0; entrada[i] != 0; i++) {
         for (j = 0; j < i; j++) {
          while (entrada[i] != 0 && deu_erro == 0){
          
              char caractere_atual;
              for(i = 0; i < strlen(entrada); i++) {
                    caractere_atual = entrada[i];
              }
                     
              switch(caractere_atual) {
                 case 48 ... 57: 
                      for (j = 0; j < i; j++){
                          saida[j] = caractere_atual; 
                      }
                 break;
                 case 40:
                      empilha(&p, caractere_atual);
                 break;
                 case 41:
                      while (le_topo(p, &aux) != ERRO_PILHA_VAZIA && aux != 40) {
                                desempilha(&p, &aux);
                                saida[j] = aux;
                      }
                      if( pilha_vazia(p)) {
                          printf("Erro: ')' sem '('!");
                          deu_erro = 1;
                      } else {
                          desempilha(&p, &aux);
                      }
                 break;
                 case 43 ... 47: 
                      le_topo(p, &aux);
                      if (pilha_vazia(p) || aux == 40) {
                         empilha(&p, caractere_atual);
                      } else {
                         while ( le_topo(p, &aux) != ERRO_PILHA_VAZIA){  //  while ( le_topo(p, &aux) != ERRO_PILHA_VAZIA && precedencia(&aux) >= precedencia (&caractere_atual)) REVER A FUNÇÃO PRECEDÊNCIA PARA FUNCIONAR
                                desempilha(&p, &aux);
                                saida[j] = aux;
                         }
                         empilha(&p, caractere_atual);
                      }
                 break;
                 default:
                     printf("Erro: caractere inválido: %c!", caractere_atual); 
              }
          }
          if(deu_erro == 0) {
            while(le_topo(p, &aux) != ERRO_PILHA_VAZIA && aux != 40) {
                desempilha(&p, &aux);
                saida[j] = aux;
            }
            if (pilha_vazia(p)) {
               saida[j] = 0;
               for (j = 0; j < strlen(saida); i++) {
                   printf("%c", saida[j]);   
               }
            } else {
              printf(" Erro: '(' não foi fechado!");
            }
          }
         }
    
    }
    
    
   
    return 0;
}

int precedencia (char *s) {
   switch(*s) {
       case 40:
            return 0;
       break;
       case 43:
       case 45:
            return 1;
       break;
       case 42:
       case 47:
            return 2;
   }
    
}



























