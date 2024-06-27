#ifndef QUARTO_H_INCLUDED
#define QUARTO_H_INCLUDED

typedef struct {
    int numeroQuarto;
    int qtdHospedesQuarto;
    float valorDiariaQuarto;
    char statusQuarto[15];
   
} Quarto;

FILE* iniciarSistemaQuartos();
void cadastroQuarto(FILE *arquivo);
void excluirQuarto(FILE *arquivo);
void exibirQuartos(FILE *arquivo );
int geradorNumeroQuarto(FILE *arquivo);
int localizadorQuarto(FILE *arquivo, int numeroQuarto);



#endif
