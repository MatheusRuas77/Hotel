#ifndef CLIENTE_H_INCLUDED
#define CLIENTE_H_INCLUDED

typedef struct {
    int codigoCliente;
    char nomeCliente[100];
    char enderecoCliente[150];
    char telefoneCliente[15];
    int excluido; 
} Cliente;

FILE* iniciarSistemaCliente();
int geradorCodigoCliente(FILE *arquivo);
void cadastrarCliente(FILE *arquivo);
int localizadorCliente(FILE *arquivo, int codigoCliente);
void localizarCliente(FILE *arquivo);
void excluirCliente(FILE *arquivo);
void exibirEstadias(FILE *fpEstadia, FILE *fpCliente, FILE *fpQuarto) ;
int CalcularPontosFidelidade(FILE *fpEstadia, int codCliente);


#endif
