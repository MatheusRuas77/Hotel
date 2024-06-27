#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcionario.h"


// guardar o ultimo gerado
int ultimoCodigoGeradoaq = 0;


FILE* iniciarSistemaFuncionario() {
    FILE *arquivo;
    if ((arquivo = fopen("funcionarios.dat", "r+b")) == NULL) {
        printf("Criando arquivo!\n");
        if ((arquivo = fopen("funcionarios.dat", "w+b")) == NULL) {
            printf("Erro ao criar arquivo!\n");
            exit(1);
        }
    } 
    else {
        Funcionario c;
        fseek(arquivo, 0, SEEK_SET);
        while(fread(&c, sizeof(c), 1, arquivo) == 1){
            if (c.codigoFuncionario > ultimoCodigoGeradoaq) {
                ultimoCodigoGeradoaq = c.codigoFuncionario;
            }
        }
    }

    return arquivo;
}

int geradorCodigoFuncionario(FILE *arquivo) {
    Funcionario c;
    int codigoMax = 0;

    fseek(arquivo, 0, SEEK_SET);
    while (fread(&c, sizeof(c), 1, arquivo) == 1) {
        if (c.codigoFuncionario > codigoMax) {
            codigoMax = c.codigoFuncionario;
        }
    }

    return codigoMax + 1;

}

void cadastrarFuncionario(FILE *arquivo) {
    Funcionario c;
    int codigo;

    codigo = geradorCodigoFuncionario(arquivo);

    while (1) {
        int posicao = localizadorFuncionario(arquivo, codigo);
        if (posicao == -1) {
            break;
        }
        codigo++;
    }

    c.codigoFuncionario = codigo;
    printf("Codigo gerado: %d\n", c.codigoFuncionario);

    printf("Digite o nome do Funcionario> ");
    fgets(c.nomeFuncionario, sizeof(c.nomeFuncionario), stdin);
    c.nomeFuncionario[strcspn(c.nomeFuncionario, "\n")] = '\0';

    printf("Digite o cargo do Funcionario> ");
    fgets(c.cargoFuncionario, sizeof(c.cargoFuncionario), stdin);
    c.cargoFuncionario[strcspn(c.cargoFuncionario, "\n")] = '\0';

    printf("Digite o salario do Funcionario: ");
    scanf("%f", &c.salarioFuncionario);


    printf("Digite o telefone do Funcionario> ");
    fgets(c.telFuncionario, sizeof(c.telFuncionario), stdin);
    c.telFuncionario[strcspn(c.telFuncionario, "\n")] = '\0';

    c.excluido = 0;

    fseek(arquivo, 0, SEEK_END);
    fwrite(&c, sizeof(c), 1, arquivo);
    fflush(arquivo);
    printf("Funcionario cadastrado!\n");
}


int localizadorFuncionario(FILE *arquivo, int codigoFuncionario) {
    int posicaoCli = -1;
    Funcionario c;
    fseek(arquivo, 0, SEEK_SET);
    while (fread(&c, sizeof(c), 1, arquivo) == 1) {
        posicaoCli++;
        if (c.codigoFuncionario == codigoFuncionario && c.excluido == 0) {
            printf("Funcionario encontrado:\n");
            printf("Codigo: %d\n", c.codigoFuncionario);
            printf("Nome: %s\n", c.nomeFuncionario);
            printf("Cargo: %s\n", c.cargoFuncionario);
            printf("Cargo: %.2f\n", c.salarioFuncionario);
            printf("Telefone: %s\n", c.telFuncionario);
            return posicaoCli;
        }
    }
    printf("Funcionario com codigo %d nao encontrado!\n", codigoFuncionario);
    return -1;
}



void localizarFuncionario(FILE *arquivo) {
    int codigoFuncionario;
    printf("Digite o codigo do funcionario para Funcionario> ");
    scanf("%d", &codigoFuncionario);
    getchar(); 
   localizadorFuncionario(arquivo, codigoFuncionario);
}




    



void excluirFuncionario(FILE *arquivo) {
    int codigoFuncionario, posicao;
    Funcionario c;
    printf("Digite o codigo do funcionario para excluir> ");
    scanf("%d", &codigoFuncionario);
    getchar(); 

    posicao = localizadorFuncionario(arquivo, codigoFuncionario);
    if (posicao != -1) {
        fseek(arquivo, sizeof(c) * posicao, SEEK_SET);
        if (fread(&c, sizeof(c), 1, arquivo) != 1) {
            printf("Erro ao ler o Funcionario!\n");
            return;
        }

        c.excluido = 1;
        fseek(arquivo, sizeof(c) * posicao, SEEK_SET);
        fwrite(&c, sizeof(c), 1, arquivo);
        fflush(arquivo);
        printf("Funcionario com codigo %d foi excluido.\n", codigoFuncionario);

        if(codigoFuncionario == ultimoCodigoGeradoaq){
            ultimoCodigoGeradoaq --;
        }


    }else if(posicao == -1){
        printf("Funcionario com codigo %d nao encontrado!\n", codigoFuncionario);
    }
}
