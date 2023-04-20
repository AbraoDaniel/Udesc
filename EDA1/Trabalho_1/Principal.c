#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Pilha.h"

char entrada[100];
char saida[100];
Pilha p;

void posfixada();
void print_saida();
int precedencia(char s);
int solucao();

int main()
{
    // Entrada de dados
    printf("Informe a conta que deseja realizar:\n");
    fgets(entrada, 100, stdin);

    entrada[strcspn(entrada, "\n")] = 0;

    inicializa_pilha(&p, strlen(entrada));

    posfixada();
    printf("Nossa equação posfixada é essa: ");
    print_saida();
    int solu = solucao();
    printf("Nosso Resultado final é: '%d'\n", solu);

    return 0;
}

void posfixada()
{
    int j = 0;
    int aux, deu_erro = 0;
    char caractere_atual;

    for (int i = 0; i < strlen(entrada); i++)
    {
        caractere_atual = entrada[i];

        switch (caractere_atual)
        {
        case '0' ... '9':
            saida[j++] = caractere_atual;
            break;
        case '(':
            empilha(&p, caractere_atual);
            break;
        case ')':
            while (le_topo(p, &aux) != ERRO_PILHA_VAZIA && aux != '(')
            {
                desempilha(&p, &aux);
                saida[j++] = aux;
            }
            if (pilha_vazia(p))
            {
                printf("Erro: ')' sem '('! \n");
                deu_erro = 1;
            }
            else
            {
                desempilha(&p, &aux);
            }
            break;

        case '+':
        case '-':
        case '/':
        case '*':
            while (!pilha_vazia(p) && precedencia(le_topo(p, &aux)) >= precedencia(caractere_atual))
            {
                desempilha(&p, &aux);
                saida[j++] = aux;
            }

            empilha(&p, caractere_atual);
            break;

        default:
            printf("Erro: caractere invalido: %c!\n", caractere_atual);
            deu_erro = 1;
            break;
        }
        if (deu_erro)
            break;
    }

    while (le_topo(p, &aux) != ERRO_PILHA_VAZIA)
    {
        desempilha(&p, &aux);
        if (aux == '(')
        {
            printf("Erro: '(' sem ')'!\n");
            deu_erro = 1;
            break;
        }
        saida[j++] = aux;
    }
}

void print_saida()
{
    int i = 0;
    while (saida[i])
    {
        printf("%c", saida[i++]);
    }
    printf("\n");
}

int precedencia(char s)
{
    switch (s)
    {
    case '(':
        return 0;
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    }
}

int solucao()
{

    int aux1, aux2, result = 0;
    inicializa_pilha(&p, strlen(saida));
    for (int i = 0; saida[i] != 0; i++)
    {
        char caractere_atual = saida[i];
        if (caractere_atual >= 48 && caractere_atual <= 57)
        {
            int numero = caractere_atual - 48;
            result = numero;
            empilha(&p, numero);
        }
        else
        { // operador
            desempilha(&p, &aux2);
            desempilha(&p, &aux1);
            switch (caractere_atual)
            {
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