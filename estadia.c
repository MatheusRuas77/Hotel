#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estadia.h"
#include "cliente.h"
#include "quarto.h"

 

FILE* abrirSistema(const char* nomeArquivo) {
    FILE *fp = fopen(nomeArquivo, "r+b");
    if (fp == NULL) {
        printf("Criando arquivo %s!\n", nomeArquivo);
        fp = fopen(nomeArquivo, "w+b");
        if (fp == NULL) {
            printf("Erro ao criar arquivo %s!\n", nomeArquivo);
            exit(1);
        }
    }
    return fp;
}

int localizadorQuartoaq(FILE *arquivo, int numeroQuarto) {
    int posicao = -1;
    Quarto quartoCriado;

    fseek(arquivo, 0, SEEK_SET);
    while (fread(&quartoCriado, sizeof(Quarto), 1, arquivo) == 1) {
        posicao++;
        if (quartoCriado.numeroQuarto == numeroQuarto && strcmp(quartoCriado.statusQuarto, "excluido") != 0) {
            return posicao;
        }
    }

    return -1;
}

int localizadorClienteaq(FILE *arquivo, int codigoCliente) {
    int posicaoCli = -1;
    Cliente c;

    fseek(arquivo, 0, SEEK_SET);
    while (fread(&c, sizeof(c), 1, arquivo) == 1) {
        posicaoCli++;
        if (c.codigoCliente == codigoCliente && c.excluido == 0) {
            return posicaoCli;
        }
    }
    return -1;
}

int gerarCodigoEstadia(FILE *fp) {
    Estadia est;
    int maiorCodigo = 0;

    fseek(fp, 0, SEEK_SET);
    while (fread(&est, sizeof(Estadia), 1, fp) == 1) {
        if (est.codigoEstadia > maiorCodigo) {
            maiorCodigo = est.codigoEstadia;
        }
    }

    return maiorCodigo + 1;
}


int checarDisponibilidadeQuarto(FILE *fp, int numQua, char *dtEnt, char *dtSai){
    Estadia est;

    fseek(fp, 0, SEEK_SET);
    while (fread(&est, sizeof(Estadia), 1, fp) == 1) {
        if (est.numeroQuartoEstadia == numQua) {
            if (strcmp(est.dtSaidaEstadia, dtEnt) > 0 && strcmp(est.dtEntradaEstadia, dtSai) < 0) {
                return 0;
            }
        }
    }
    return 1;
}

void registrarEstadia(FILE *arquivoEstadia, FILE *arquivoCliente, FILE *arquivoQuarto) {
    Estadia estadia;
    Cliente cliente;
    Quarto quarto;
    int codigoCliente, numeroHospedes, numeroQuarto;
    char dataEntrada[11], dataSaida[11];
    int disponivel = 0;
    int quantidadeDias;

    printf("Digite o codigo do cliente: ");
    scanf("%d", &codigoCliente);

    // Verificar se o cliente existe
    int posicaoCliente = localizadorClienteaq(arquivoCliente, codigoCliente);
    if (posicaoCliente == -1) {
        printf("Cliente com codigo %d nao encontrado!\n", codigoCliente);
        return;
    }

    // Ler informações do cliente
    fseek(arquivoCliente, sizeof(Cliente) * posicaoCliente, SEEK_SET);
    fread(&cliente, sizeof(Cliente), 1, arquivoCliente);

    // Verificar se o cliente está excluído
    if (cliente.excluido == 1) {
        printf("Cliente com codigo %d excluido!\n", codigoCliente);
        return;
    }

    // Ler datas de entrada e saída
    printf("Digite a data de entrada (dd/mm/aaaa): ");
    scanf("%s", dataEntrada);

    printf("Digite a data de saida (dd/mm/aaaa): ");
    scanf("%s", dataSaida);

    // Loop para encontrar um quarto disponível
    while (!disponivel) {
        printf("Digite o numero de hospedes: ");
        scanf("%d", &numeroHospedes);

        // Reiniciar a leitura dos quartos
        fseek(arquivoQuarto, 0, SEEK_SET);
        while (fread(&quarto, sizeof(Quarto), 1, arquivoQuarto) == 1) {//nao esta entrando aqui
            if (strcmp(quarto.statusQuarto, "desocupado") == 0 && quarto.qtdHospedesQuarto >= numeroHospedes) {
                // Verificar disponibilidade do quarto para as datas
                if (checarDisponibilidadeQuarto(arquivoEstadia, quarto.numeroQuarto, dataEntrada, dataSaida)) {
                    disponivel = 1;
                    numeroQuarto = quarto.numeroQuarto;

                    // Atualizar status do quarto para ocupado
                    strcpy(quarto.statusQuarto, "ocupado");
                    fseek(arquivoQuarto, sizeof(Quarto) * localizadorQuartoaq(arquivoQuarto, numeroQuarto), SEEK_SET);
                    fwrite(&quarto, sizeof(Quarto), 1, arquivoQuarto);
                    fflush(arquivoQuarto);

                    break;
                }
            }
        }

        if (!disponivel) {
            printf("Nenhum quarto disponivel para %d hospede(s) no periodo de %s a %s.\n", numeroHospedes, dataEntrada, dataSaida);
        }
    }

    // Calcular quantidade de dias da estadia
    quantidadeDias = calcularDias(dataEntrada, dataSaida);

    // Preencher dados da estadia
    estadia.codigoEstadia = gerarCodigoEstadia(arquivoEstadia);
    strcpy(estadia.dtEntradaEstadia, dataEntrada);
    strcpy(estadia.dtSaidaEstadia, dataSaida);
    estadia.qtdDiariasEstadia = quantidadeDias;
    estadia.codigoClienteEstadia = codigoCliente;
    estadia.numeroQuartoEstadia = numeroQuarto;

    // Escrever estadia no arquivo de estadias
    fseek(arquivoEstadia, 0, SEEK_END);
    fwrite(&estadia, sizeof(Estadia), 1, arquivoEstadia);
    fflush(arquivoEstadia);

    printf("Estadia cadastrada com sucesso!\n");
    printf("Numero do quarto utilizado: %d\n", numeroQuarto);
}





void finalizarEstadia(FILE *fpEstadia, FILE *fpQuarto, FILE *fpCliente, int codEst) {
    Estadia est;
    Quarto qua;
    Cliente cli;
    int encontrada = 0;

    fseek(fpEstadia, 0, SEEK_SET);
    while (fread(&est, sizeof(Estadia), 1, fpEstadia) == 1) {
        if (est.codigoEstadia == codEst) {
            encontrada = 1;

            int posCli = localizadorClienteaq(fpCliente, est.codigoClienteEstadia);
            fseek(fpCliente, sizeof(Cliente) * posCli, SEEK_SET);
            fread(&cli, sizeof(Cliente), 1, fpCliente);

            int posQua = localizadorQuartoaq(fpQuarto, est.numeroQuartoEstadia);
            fseek(fpQuarto, sizeof(Quarto) * posQua, SEEK_SET);
            fread(&qua, sizeof(Quarto), 1, fpQuarto);

            float valorTotal = est.qtdDiariasEstadia * qua.valorDiariaQuarto;
            strcpy(qua.statusQuarto, "desocupado");
            fseek(fpQuarto, sizeof(Quarto) * posQua, SEEK_SET);
            fwrite(&qua, sizeof(Quarto), 1, fpQuarto);
            fflush(fpQuarto);

            printf("Estadia do cliente> %s\n", cli.nomeCliente);
            printf("Codigo da Estadia> %d\n", est.codigoEstadia);
            printf("Data de Entrada> %s\n", est.dtEntradaEstadia);
            printf("Data de Saida> %s\n", est.dtSaidaEstadia);
            printf("Quantidade de Diarias> %d\n", est.qtdDiariasEstadia);
            printf("Valor Total a ser pago> R$ %.2f\n", valorTotal);
            break;
        }
    }

    if (!encontrada) {
        printf("Estadia com codigo %d não encontrada.\n", codEst);
    }
}

int calcularDias(char *dtEnt, char *dtSai) {
    int diaE, mesE, anoE;
    int diaS, mesS, anoS;
    sscanf(dtEnt, "%d/%d/%d", &diaE, &mesE, &anoE);
    sscanf(dtSai, "%d/%d/%d", &diaS, &mesS, &anoS);

    return ((anoS - anoE) * 365 + (mesS - mesE) * 30 + (diaS - diaE));
}

void exibirEstadias(FILE *fpEstadia, FILE *fpCliente, FILE *fpQuarto) {
    Estadia est;
    Cliente cli;
    Quarto qua;

    fseek(fpEstadia, 0, SEEK_SET);
    while (fread(&est, sizeof(Estadia), 1, fpEstadia) == 1) {
        int posCli = localizadorClienteaq(fpCliente, est.codigoClienteEstadia);
        fseek(fpCliente, sizeof(Cliente) * posCli, SEEK_SET);
        fread(&cli, sizeof(Cliente), 1, fpCliente);

        int posQua = localizadorQuartoaq(fpQuarto, est.numeroQuartoEstadia);
        fseek(fpQuarto, sizeof(Quarto) * posQua, SEEK_SET);
        fread(&qua, sizeof(Quarto), 1, fpQuarto);

        printf("Estadia Codigo: %d\n", est.codigoEstadia);
        printf("Cliente: %s\n", cli.nomeCliente);
        printf("Quarto: %d\n", qua.numeroQuarto);
        printf("Data de Entrada: %s\n", est.dtEntradaEstadia);
        printf("Data de Saida: %s\n", est.dtSaidaEstadia);
        printf("Quantidade de Diárias: %d\n", est.qtdDiariasEstadia);

    }
}

// int main() {
//     FILE *fpEstadia = abrirSistema("estadias.dat");
//     FILE *fpCliente = abrirSistema("clientes.dat");
//     FILE *fpQuarto = abrirSistema("quartos.dat");

//     int opcao;

//     do {
//         printf("Menu:\n");
//         printf("1. Registrar estadia\n");
//         printf("2. Finalizar estadia\n");
//         printf("3. Exibir estadias\n");
//         printf("4. Sair\n");
//         printf("Escolha uma opção: ");
//         scanf("%d", &opcao);

//         switch (opcao) {
//             case 1:
//                 registrarEstadia(fpEstadia, fpCliente, fpQuarto);
//                 break;
//             case 2: {
//                 int codEst;
//                 printf("Digite o código da estadia a ser finalizada: ");
//                 scanf("%d", &codEst);
//                 finalizarEstadia(fpEstadia, fpQuarto, fpCliente, codEst);
//                 break;
//             }
//             case 3:
//                 exibirEstadias(fpEstadia, fpCliente, fpQuarto);
//                 break;
//             case 4:
//                 printf("Saindo...\n");
//                 break;
//             default:
//                 printf("Opção inválida!\n");
//                 break;
//         }
//     } while (opcao != 4);

//     fclose(fpEstadia);
//     fclose(fpCliente);
//     fclose(fpQuarto);

//     return 0;
// }
