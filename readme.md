1. Introdução
Este projeto foi desenvolvido para a disciplina de Algoritmos e Estruturas de Dados I do curso de Engenharia de Software da Pontifícia Universidade Católica de Minas Gerais. O objetivo é criar um sistema de gerenciamento para o Hotel Descanso Garantido, localizado em Itacaré - BA. O sistema visa substituir o controle manual de estadias, clientes e funcionários por um sistema automatizado e eficiente.

2. Funcionalidades do Sistema
O sistema desenvolvido possui as seguintes funcionalidades:

Cadastro de clientes
Cadastro de funcionários
Cadastro de estadias
Baixa de estadias e cálculo do valor total a ser pago
Pesquisa de clientes e funcionários
Listagem de estadias de um cliente específico
Cálculo de pontos de fidelidade para clientes
3. Estrutura de Dados
Cliente
Código: Identificador único do cliente
Nome: Nome completo do cliente
Endereço: Endereço residencial do cliente
Telefone: Número de telefone do cliente

Funcionário
Código: Identificador único do funcionário
Nome: Nome completo do funcionário
Telefone: Número de telefone do funcionário
Cargo: Cargo do funcionário (recepcionista, auxiliar de limpeza, garçom, gerente)
Salário: Salário do funcionário

Estadia
Código da estadia: Identificador único da estadia
Data de entrada: Data de início da estadia
Data de saída: Data de término da estadia
Quantidade de diárias: Calculada com base na data de entrada e saída
Código do cliente: Referência ao cliente hospedado
Número do quarto: Quarto onde o cliente está hospedado

Quarto
Número do quarto: Identificador único do quarto
Quantidade de hóspedes: Capacidade máxima de hóspedes no quarto
Valor da diária: Preço por diária do quarto
Status: Ocupado ou desocupado

4. Funções Implementadas
4.1 Cadastro de Cliente
Essa função permite cadastrar um novo cliente, garantindo que não haja duplicidade de códigos.

4.2 Cadastro de Funcionário
Essa função permite cadastrar um novo funcionário, garantindo que não haja duplicidade de códigos.

4.3 Cadastro de Estadia
Essa função permite cadastrar uma nova estadia, verificando a disponibilidade dos quartos e calculando a quantidade de diárias.

4.4 Baixa de Estadia e Cálculo do Valor Total
Essa função realiza a baixa de uma estadia e calcula o valor total a ser pago pelo cliente, além de atualizar o status do quarto.

4.5 Pesquisa de Clientes e Funcionários
Essas funções permitem a pesquisa de clientes e funcionários pelo nome ou código, exibindo todas as informações cadastradas.

4.6 Listagem de Estadias de um Cliente
Essa função lista todas as estadias de um determinado cliente.

4.7 Cálculo de Pontos de Fidelidade
Essa função calcula a quantidade de pontos de fidelidade de um cliente, com base na quantidade de diárias.

5. Estrutura de Arquivos
As informações são armazenadas em arquivos binários, sendo:

clientes.dat: Armazena os dados dos clientes
funcionarios.dat: Armazena os dados dos funcionários
estadias.dat: Armazena os dados das estadias
quartos.dat: Armazena os dados dos quartos
6. Menu Principal
A função main() apresenta um menu principal com as opções de cadastro, pesquisa e saída. O menu fica em loop até o usuário selecionar a opção de sair.


7. Testes Realizados
Os arquivos de testes realizados estão incluídos no pacote de entrega, demonstrando a criação, pesquisa e manipulação de dados no sistema.

8. Apresentação
A apresentação gravada pelos membros do grupo está disponível no Canvas, conforme as diretrizes fornecidas.

9. Conclusão
O sistema desenvolvido atende às necessidades do Hotel Descanso Garantido, substituindo o controle manual por um sistema informatizado, garantindo eficiência e redução de erros. A documentação e os testes realizados comprovam o correto funcionamento das funcionalidades implementadas.
