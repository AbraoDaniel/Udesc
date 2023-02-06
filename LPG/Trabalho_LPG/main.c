#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

typedef struct {
  char nome[50];
  int id;
} aluno;
aluno alunos[100]; // array de struct global
int buscaIndice();
void consulta() {
    int id;
    printf("qual id vc quer consultar?\n");
    scanf("%d", &id);


    int indice = buscaIndice(id);
        if (indice != -1) {
        printf("Aluno achado!\n\n");

        printf("ID do aluno: %d\nNome do aluno: %s\n\n", id, alunos[indice].nome);
        printf("voltando para o menu\n\n");
    } else {
        printf("O Aluno não foi encontrado\n");
    }

    }




int buscaIndice(int id){
    printf("buscando o aluno...\n");
    for (int i = 0; i < 25; i++) {
        if (alunos[i].id == id) {
        return i;
        } 
    }
    return -1;
}


void relatorio(){
        printf("—-------------------------------------------------------------------\n");
        printf("                        RELATÓRIO DE ALUNOS\n");
        printf("—-------------------------------------------------------------------\n");
        printf("—-------------------------------------------------------------------\n");
        printf("|        ID     |                      NOME                        |\n");
    for(int i = 0;i< 24;i++){


        printf(" %d               %s  \n",alunos[i].id,alunos[i].nome);

    }
   
}

int main(){
    int i = 0;
    FILE *ent;
    ent = fopen("alunos.txt", "r");
    if (ent == NULL) {
        printf("erro ao abrir o arquivo\n");
        return -1;
    }
    
    char linha[50], tempnome;
    int tempid;

    
    while(!feof(ent)) {
        if(i == 0) {
        fgets(linha, 50, ent);
        } else {
            fscanf(ent, "%d;", &alunos[i].id);
            fgets(alunos[i].nome, 40, ent);
            // printf("id: %d nome: %s\n", tempid, tempnome);
    }
    i++;
    }





    i = 1;
    while ( i != 0) {
        printf("[1] - Consultar por id\n"
                "[2] - Relatório\n"
                "[3] - Sair\n");
        scanf("%d", &i);
        switch (i){
        case 1:
            printf("Buscando dados!\n");
            consulta();
            break;
        case 2:
            printf("Gerando o relatório!\n");
            relatorio();
            break;        
        case 3:
            i = 0;
            printf("Saindo do programa!\n");
            break;   

        }
    }

    return EXIT_SUCCESS;
}



