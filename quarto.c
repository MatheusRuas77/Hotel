#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "quarto.h"

FILE* iniciarSistemaQuartos() {
    FILE *arquivo;
    arquivo = fopen("quarto.dat", "r+b");
    
    if (arquivo == NULL) {
        printf("Criando arquivo!\n");

        arquivo = fopen("quarto.dat", "w+b");
        if (arquivo == NULL) {
            printf("Erro na criacao do arquivo!\n");
            exit(1);
        }
    }
    return arquivo;
}

int geradorNumeroQuarto(FILE *arquivo) {
    Quarto quartoCriado;
    int numMax = 0;

    fseek(arquivo, 0, SEEK_SET);
    fread(&quartoCriado, sizeof(Quarto), 1, arquivo);

    while (!feof(arquivo)) {
        if (quartoCriado.numeroQuarto > numMax) {
            numMax = quartoCriado.numeroQuarto;
        }

        fread(&quartoCriado, sizeof(Quarto), 1, arquivo);
    }

    return numMax + 1;
}

int localizadorQuarto(FILE *arquivo, int numeroQuarto) {
    int posicao = -1;
    Quarto quartoCriado;

    fseek(arquivo, 0, SEEK_SET);
    fread(&quartoCriado, sizeof(Quarto), 1, arquivo);

    while (!feof(arquivo)) {
        posicao++;
        if (quartoCriado.numeroQuarto == numeroQuarto && strcmp(quartoCriado.statusQuarto, "excluido") != 0) {
            return posicao;
        }

        fread(&quartoCriado, sizeof(Quarto), 1, arquivo);
    }

    return -1;
}

void cadastroQuarto(FILE *arquivo) {
    Quarto quarto;
    int numQuartos;
    int posicao;

    numQuartos = geradorNumeroQuarto(arquivo); 
    printf("Numero do quarto e gerado automaticamente> %d\n", numQuartos); 
    quarto.numeroQuarto = numQuartos;

    printf("Digite a quantidade de hospedes presentes no quarto> ");
    scanf("%d", &quarto.qtdHospedesQuarto);

    printf("Digite o valor da diaria do quarto> ");
    scanf("%f", &quarto.valorDiariaQuarto);

    strcpy(quarto.statusQuarto, "desocupado");

    posicao = localizadorQuarto(arquivo, quarto.numeroQuarto);
    if (posicao == -1) {
        fseek(arquivo, 0, SEEK_END);
        fwrite(&quarto, sizeof(Quarto), 1, arquivo);
        fflush(arquivo);
        printf("Quarto cadastrado com sucesso!\n");
    } else {
        printf("Erro: Quarto com numero %d já existe!\n", quarto.numeroQuarto);
    }

    while (getchar() != '\n'); 
}

void excluirQuarto(FILE *arquivo) {
    int numeroQuarto, posicao;
    Quarto quarto;

    printf("Digite o numero do quarto para exclui-lo: ");
    scanf("%d", &numeroQuarto);

    posicao = localizadorQuarto(arquivo, numeroQuarto);
    if (posicao != -1) {
        fseek(arquivo, sizeof(Quarto) * posicao, SEEK_SET);
        fread(&quarto, sizeof(Quarto), 1, arquivo);

        strcpy(quarto.statusQuarto, "excluido");

        fseek(arquivo, sizeof(Quarto) * posicao, SEEK_SET);
        fwrite(&quarto, sizeof(Quarto), 1, arquivo);
        fflush(arquivo);

        printf("Quarto excluido com sucesso!\n");
    } else {
        printf("Quarto com numero %d nao encontrado!\n", numeroQuarto);
    }
}

void exibirQuartos(FILE *arquivo) {
    Quarto quarto;
    fseek(arquivo, 0, SEEK_SET);
    fread(&quarto, sizeof(Quarto), 1, arquivo);
    while (!feof(arquivo)) {
        printf("Numero do quarto: %d\n", quarto.numeroQuarto);
        printf("Quantidade de hospedes: %d\n", quarto.qtdHospedesQuarto);
        printf("Valor da diaria: %.2f\n", quarto.valorDiariaQuarto);
        printf("Status do quarto: %s\n", quarto.statusQuarto);
        fread(&quarto, sizeof(Quarto), 1, arquivo);
    }
}

