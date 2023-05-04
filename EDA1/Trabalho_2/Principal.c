#include <stdlib.h>
#include <stdio.h>
#include "Fila.h"
#include "Pilha.h"

int main()
{
  FILE *arquivo;

  arquivo = fopen("arquivo.txt", "r");
  if (arquivo == NULL)
  {
    printf("Erro ao abrir o arquivo");
    return 1;
  }

  // DEFININDO TAMANHO DA MATRIZ E ALOCANDO OS VALORES

  int n;
  printf("Defina o tamanho da matriz desejada: ");
  scanf("%d", &n);

  int matriz[n][n];

  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      fscanf(arquivo, "%d", &matriz[i][j]);
    }
  }

  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      int valor;
      printf("%4d", matriz[i][j]);
    }
    printf("\n");
  }

  // INFORMANDO VERTICE INICIAL E FINAL

  int vertice_inicial, vertice_final;
  printf("Informe o vértice inicial: ");
  scanf("%d", &vertice_inicial);

  printf("Informe o vértice final: ");
  scanf("%d", &vertice_final);

  // INICIALIZA VETOR DE STATUS (VS) e VETOR DE ANTECESSORES (VA)

  int vs[n];
  int va[n];
  for (int i = 0; i < n; i++)
  {
    vs[i] = 0;
    va[i] = 0;
  }

  // INICIALIZANDO FILA

  Fila f;
  inicializa_fila(&f, n);

  // DEFININDO V[A] COMO DEFINIDO

  vs[vertice_inicial] = 1;
  inserir(&f, vertice_inicial);

  int achou = 0;
  int aux;
  while (!fila_vazia(f) && !achou)
  {
    remover(&f, &aux);
    if (aux == vertice_final)
    {
      achou = 1;
    }
    else
    {
      for (int j = 0; j < n; j++)
      {
        if (matriz[aux][j] == 1)
        {
          if (vs[j] == 0)
          {
            vs[j] = 1;
            va[j] = aux;
            inserir(&f, j);
          }
        }
      }
    }
  }

  if (achou)
  {
    Pilha p;
    inicializa_pilha(&p, n);
    while (aux != 0)
    {
      empilha(&p, aux);
      aux = va[aux];
    }
    while (!pilha_vazia(p))
    {
      desempilha(&p, &aux);
      printf("%d \n", aux);
    }
  }
  else
  {
    printf("B não é alcançável a partir de A!");
  }

  return 0;
}
