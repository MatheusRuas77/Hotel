#ifndef FUNCIONARIO_H_INCLUDED
#define FUNCIONARIO_H_INCLUDED

typedef struct {
    int codigoFuncionario;
    char nomeFuncionario[100];
    char telFuncionario[15];
    char cargoFuncionario[50];
    float salarioFuncionario;
    int excluido;
} Funcionario;

FILE* iniciarSistemaFuncionario();
int geradorCodigoFuncionario(FILE *arquivo);
void cadastrarFuncionario(FILE *arquivo);
int localizadorFuncionario(FILE *arquivo, int codigoFuncionario);
void excluirFuncionario(FILE *arquivo);
void localizarFuncionario(FILE *arquivo);



#endif
