#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"
#include "estadia.h"




// guardar o ultimo gerado
int ultimoCodigoGerado = 0;


FILE* iniciarSistemaCliente() {
    FILE *arquivo;
    if ((arquivo = fopen("clientes.dat", "r+b")) == NULL) {
        printf("Criando arquivo!\n");
        if ((arquivo = fopen("clientes.dat", "w+b")) == NULL) {
            printf("Erro ao criar arquivo!\n");
            exit(1);
        }
    } 
    else {
        Cliente c;
        fseek(arquivo, 0, SEEK_SET);
        while(fread(&c, sizeof(c), 1, arquivo) == 1){
            if (c.codigoCliente > ultimoCodigoGerado) {
                ultimoCodigoGerado = c.codigoCliente;
            }
        }
    }

    return arquivo;
}

int geradorCodigoCliente(FILE *arquivo) {
    Cliente c;
    int codigoMax = 0;

    fseek(arquivo, 0, SEEK_SET);
    while (fread(&c, sizeof(c), 1, arquivo) == 1) {
        if (c.codigoCliente > codigoMax) {
            codigoMax = c.codigoCliente;
        }
    }

    return codigoMax + 1;


}

void cadastrarCliente(FILE *arquivo) {
    Cliente c;
    int codigo;

    codigo = geradorCodigoCliente(arquivo);

    while (1) {
        int posicao = localizadorCliente(arquivo, codigo);
        if (posicao == -1) {
            break;
        }
        codigo++;
    }

    c.codigoCliente = codigo;
    printf("Codigo gerado: %d\n", c.codigoCliente);

    printf("Digite o nome do Cliente> ");
    fgets(c.nomeCliente, sizeof(c.nomeCliente), stdin);
    c.nomeCliente[strcspn(c.nomeCliente, "\n")] = '\0';

    printf("Digite o endereco do Cliente> ");
    fgets(c.enderecoCliente, sizeof(c.enderecoCliente), stdin);
    c.enderecoCliente[strcspn(c.enderecoCliente, "\n")] = '\0';

    printf("Digite o telefone do Cliente> ");
    fgets(c.telefoneCliente, sizeof(c.telefoneCliente), stdin);
    c.telefoneCliente[strcspn(c.telefoneCliente, "\n")] = '\0';

    c.excluido = 0;

    fseek(arquivo, 0, SEEK_END);
    fwrite(&c, sizeof(c), 1, arquivo);
    fflush(arquivo);
    printf("Cliente cadastrado!\n");
}


int localizadorCliente(FILE *arquivo, int codigoCliente) {
    int posicaoCli = -1;
    Cliente c;
    fseek(arquivo, 0, SEEK_SET);
    while (fread(&c, sizeof(c), 1, arquivo) == 1) {
        posicaoCli++;// aq
        if (c.codigoCliente == codigoCliente && c.excluido == 0) {
            printf("Cliente encontrado:\n");
            printf("Codigo: %d\n", c.codigoCliente);
            printf("Nome: %s\n", c.nomeCliente);
            printf("Endereco: %s\n", c.enderecoCliente);
            printf("Telefone: %s\n", c.telefoneCliente);
            return posicaoCli;
        }
    }
    printf("Cliente com codigo %d nao encontrado!\n", codigoCliente);
    return -1;
}

int CalcularPontosFidelidade(FILE *fpEstadia, int codCliente) {
    Estadia estadia;
    int pontos_fidelidade = 0;
    int total_diarias = 0;

    
    fseek(fpEstadia, 0, SEEK_SET);
    while (fread(&estadia, sizeof(estadia), 1, fpEstadia) == 1) {
        if (estadia.codigoClienteEstadia == codCliente) {
            total_diarias += estadia.qtdDiariasEstadia;
        }
    }


    pontos_fidelidade = total_diarias * 10;

    printf("%d", pontos_fidelidade);
}



void localizarCliente(FILE *arquivo) {
    int codigoCliente;
    printf("Digite o codigo do cliente para localizar> ");
    scanf("%d", &codigoCliente);
    getchar(); // Limpar o caractere de nova linha deixado pelo scanf
   localizadorCliente(arquivo, codigoCliente);
}




    



void excluirCliente(FILE *arquivo) {
    int cod_cliente, posicao;
    Cliente c;
    printf("Digite o codigo do cliente para excluir: ");
    scanf("%d", &cod_cliente);
    getchar(); // Clear newline character left by scanf

    posicao = localizadorCliente(arquivo, cod_cliente);
    if (posicao != -1) {
        fseek(arquivo, sizeof(c) * posicao, SEEK_SET);
        if (fread(&c, sizeof(c), 1, arquivo) != 1) {
            printf("Erro ao ler o cliente!\n");
            return;
        }

        c.excluido = 1;
        fseek(arquivo, sizeof(c) * posicao, SEEK_SET);
        fwrite(&c, sizeof(c), 1, arquivo);
        fflush(arquivo);
        printf("Cliente com codigo %d foi excluido.\n", cod_cliente);

        if(cod_cliente == ultimoCodigoGerado){
            ultimoCodigoGerado --;
        }


    }else if(posicao == -1){
        printf("Cliente com codigo %d nao encontrado!\n", cod_cliente);
    }

}
