#include <stdio.h>
#include <stdlib.h>
#include "cliente.h"
#include "funcionario.h"
#include "quarto.h"
#include "estadia.h"

void menuPrincipal();
void menuClientes();
void menuFuncionarios();
void menuQuartos();
void menuEstadias();

int main() {
    int opcao;
    
    while (1) {
        menuPrincipal();
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                menuClientes();
                break;
            case 2:
                menuFuncionarios();
                break;
            case 3:
                menuQuartos();
                break;
            case 4:
                menuEstadias();
                break;
            case 5:
                printf("Saindo...\n");
                return 0;
            default:
                printf("Opcao invalida!\n");
                break;
        }
    }

    return 0;
}

void menuPrincipal() {
    printf("\n==== Sistema de Gestao de Hotel ====\n");
    printf("1. Gerenciar Clientes\n");
    printf("2. Gerenciar Funcionarios\n");
    printf("3. Gerenciar Quartos\n");
    printf("4. Gerenciar Estadias\n");
    printf("5. Sair\n");
    printf("Escolha uma opcao> ");
}

void menuClientes() {
    FILE *arquivo = iniciarSistemaCliente();
    int opcao;

    while (1) {
        printf("\n==== Menu Clientes ====\n");
        printf("1. Cadastrar Cliente\n");
        printf("2. Excluir Cliente\n");
        printf("3. Localizar Cliente\n");
        printf("4. Calcular Pontos de Fidalidade\n");
        printf("5. Voltar ao Menu Principal\n");
        printf("Escolha uma opcao> ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                cadastrarCliente(arquivo);
                break;
            case 2:
                excluirCliente(arquivo);
                break;
            case 3:
                localizarCliente(arquivo);
                break;
            case 4:{
                int codCliente;
                
                printf("Digite o codigo do Cliente>");
                scanf("%d", &codCliente);
                getchar();

                CalcularPontosFidelidade(arquivo, codCliente);
                break;
            }
            case 5:
                fclose(arquivo);
                return;
            default:
                printf("Opcao invalida!\n");
                break;
        }
    }
}

void menuFuncionarios() {
    FILE *arquivo = iniciarSistemaFuncionario();
    int opcao;

    while (1) {
        printf("\n==== Menu Funcionarios ====\n");
        printf("1. Cadastrar Funcionario\n");
        printf("2. Excluir Funcionario\n");
        printf("3. Localizar Funcionario\n");
        printf("4. Voltar ao Menu Principal\n");
        printf("Escolha uma opcao> ");
        scanf("%d", &opcao);
        getchar(); 

        switch (opcao) {
            case 1:
                cadastrarFuncionario(arquivo);
                break;
            case 2:
                excluirFuncionario(arquivo);
                break;
            case 3:
                localizarFuncionario(arquivo);
                break;
            case 4:
                fclose(arquivo);
                return;
            default:
                printf("Opcao invalida!\n");
                break;
        }
    }
}

void menuQuartos() {
    FILE *arquivo = iniciarSistemaQuartos();
    int opcao;

    while (1) {
        printf("\n==== Menu Quartos ====\n");
        printf("1. Cadastrar Quarto\n");
        printf("2. Excluir Quarto\n");
        printf("3. Localizar Quarto\n");
        printf("4. Voltar ao Menu Principal\n");
        printf("Escolha uma opcao> ");
        scanf("%d", &opcao);
        getchar(); 

        switch (opcao) {
            case 1:
                cadastroQuarto(arquivo);
                break;
            case 2:
                excluirQuarto(arquivo);
                break;
           case 3: {
                int numQuarto;
                printf("Digite o numero do quarto a ser localizado> ");
                scanf("%d", &numQuarto);
                getchar(); 
                exibirQuartos(arquivo);
                break;
            }
            case 4:
                fclose(arquivo);
                return;
            default:
                printf("Opcao invalida!\n");
                break;
        }
    }
}

void menuEstadias() {
    FILE *fpEstadia = abrirSistema("estadias.dat");
    FILE *fpCliente = abrirSistema("clientes.dat");
    FILE *fpQuarto = abrirSistema("quarto.dat");
    int opcao;

    while (1) {
        printf("\n==== Menu Estadias ====\n");
        printf("1. Registrar Estadia\n");
        printf("2. Finalizar Estadia\n");
        printf("3. Exibir Estadias\n");
        printf("4. Voltar ao Menu Principal\n");
        printf("Escolha uma opcao> ");
        scanf("%d", &opcao);
        getchar(); 

        switch (opcao) {
            case 1:
                registrarEstadia(fpEstadia, fpCliente, fpQuarto);
                break;
            case 2: {
                int codEst;
                printf("Digite o codigo da estadia a ser finalizada: ");
                scanf("%d", &codEst);
                finalizarEstadia(fpEstadia, fpQuarto, fpCliente, codEst);
                break;
            }
            case 3:
                exibirEstadias(fpEstadia, fpCliente, fpQuarto);
                break;
            case 4:
                fclose(fpEstadia);
                fclose(fpCliente);
                fclose(fpQuarto);
                return;
            default:
                printf("Opcao invalida!\n");
                break;
        }
    }
}
