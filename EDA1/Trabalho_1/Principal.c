#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Pilha.h"

char entrada[30];
char saida [30];
Pilha p;

void posfixada();
void print_saida();
int precedencia (char *s);
int solucao();

int main(int argc, char *argv[]){    
    // Entrada de dados
    printf("Informe a conta que deseja realizar:\n");
    fgets(entrada, 30, stdin);

    entrada[strcspn(entrada, "\n")] = 0;

    inicializa_pilha( &p, strlen(entrada));
    
    posfixada(); 
    printf("Nosso resultado é esse:");
    print_saida();
    int solu = solucao();
    printf("O valor final é = '%d'\n", solu);

    return 0;
}

void posfixada(){
    int i = 0, j = 0, aux, deu_erro = 0;
    char caractere_atual;

    while ( i < strlen(entrada) && entrada[i] != 0 && deu_erro == 0) {
        caractere_atual = entrada[i++];
        printf("%c\n", caractere_atual);

        // Analise do digito    
        switch(caractere_atual) {
            //espaço
            case ' ':
                break;
            // (
            case '(':
                empilha(&p, caractere_atual);
            break;
            // )
            case ')':
                while (le_topo(p, &aux) != ERRO_PILHA_VAZIA && aux != '(') { //OLHA O PROBLEMA AQUI!
                    desempilha(&p, &aux);
                    saida[j++] = aux;
                }    
                if(pilha_vazia(p)) {
                    printf("Erro: ')' sem '('! \n");
                    deu_erro = 1;
                } else {
                    desempilha(&p, &aux);
                }
            break;
            // + - / *
            case '+':
            case '-':
            case '/':
            case '*': 
                le_topo(p, &aux);
                if (pilha_vazia(p) || aux == '(') {
                    empilha(&p, caractere_atual);
                } else {
                    aux = caractere_atual + 48;
                    while (le_topo(p, &aux) != ERRO_PILHA_VAZIA && precedencia(aux) >= precedencia(caractere_atual)){ //ADICIONAR A FUNÇÃO PRECEDÊNCIA
                        desempilha(&p, &aux);
                        saida[j++] = aux;
                    }  
                    empilha(&p, caractere_atual);
                } 
                break;

                /*le_topo( P, &x );
                24. SE ( P ESTÁ VAZIA ) OU ( x == '(' ) ENTÃO
                25. EMPILHE c EM P;
                26. SENÃO
                27. ENQUANTO ( le_topo( P , &x ) != ERRO_VAZIA ) E
                ( precedencia( x ) >= precedência( c ) ) FAÇA
                28. DESEMPILHE de P para x;
                29. Coloque x na string S;
                30. FIMENQUANTO
                31. EMPILHE c EM P;
                32. FIMSE*/

            // 0-9
            case '0' ... '9': 
                saida[j++] = caractere_atual; 
            break;
            default:
                printf("Erro: caractere invalido: %c!", caractere_atual); 
                deu_erro = 1;  
            break;
        }            
        
        if(deu_erro == 0) {
            while(le_topo(p, &aux) != ERRO_PILHA_VAZIA && aux != 40) {
                desempilha(&p, &aux);
                saida[j] = aux;
            }
            
        }  
    }      
}
  
void print_saida(){
    int i = 0;
    while(saida[i]){
        printf(" %c", saida[i++]);
    }
    printf("\n");
}

int precedencia (char *s) {
   switch(*s) {
       case 40:
            return '0';
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

int solucao(){
    int aux1, aux2, result = 0;
    inicializa_pilha( &p, strlen(saida));
    for(int i = 0; saida[i] != 0; i++){ 
        char caractere_atual = saida[i];
        if(caractere_atual >= 48 && caractere_atual <= 57){//Perguntar para o professor se essa verificação comprova que o caractere é um digito
            // convertendo para um tipo inteiro
            int numero = caractere_atual - 48;
            result = numero;
            empilha(&p, numero);
        }else{ // operador
            desempilha(&p, &aux2);
            desempilha(&p, &aux1);
            switch (caractere_atual){
            case '+':
                result = aux1 + aux2;
                break;
            case '-':
                result = aux1 - aux2;
                break;
            case '*':
                result = aux1 * aux2;
                break;
            case '/':
                result = aux1 / aux2;
                break;
            }
        empilha(&p, result);
        }
    }
    return result;
}