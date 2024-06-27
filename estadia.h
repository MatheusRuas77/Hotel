#ifndef ESTADIA_H_INCLUDED
#define ESTADIA_H_INCLUDED

typedef struct {
    int codigoEstadia;
    char dtEntradaEstadia[11];
    char dtSaidaEstadia[11];
    int qtdDiariasEstadia;
    int codigoClienteEstadia;
    int numeroQuartoEstadia;
    int excluido;
} Estadia;

FILE* abrirSistema(const char* nomeArquivo);
int checarDisponibilidadeQuarto(FILE *fp, int numQua, char *dtEnt, char *dtSai);
int localizadorQuartoaq(FILE *fp, int numQua);
int calcularDias(char *dtEnt, char *dtSai);
void registrarEstadia(FILE *arquivo, FILE *fpCliente, FILE *fpQuarto);
void finalizarEstadia(FILE *fpEstadia, FILE *fpQuarto, FILE *fpCliente, int codEst);
void exibirEstadias(FILE *fpEstadia, FILE *fpCliente, FILE *fpQuarto) ;
int localizadorClienteaq(FILE *arquivo, int codigoCliente);


#endif
