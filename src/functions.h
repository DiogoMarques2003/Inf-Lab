/**
 * @file functions.h
 * @brief 
 * @version 0.1
 * @date 2023-12-21
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdbool.h>

#ifndef STRUCT_H
#define STRUCT_H
#include "structs.h"

/**
 * @brief Função para verificar os parâmetros passados pelo utilizador
 * 
 * @param argc * Nº de parametros passado pelo utilizador
 * @param argv * Array de parametros passado pelo utilizador
 * @return true * Se o utilizador passou o parâmetro "-ajuda"
 * @return false * Se o utilizador não passou o parâmetro "-ajuda"
 */
bool verificarParametros(int argc, char *argv[]);

/**
 * @brief Função para ler um número inteiro
 * 
 * @param n * Número inteiro
 */
void lerInteiro(int *n);

/**
 * @brief Função para criar a lista de clientes
 * 
 * @return ListaCliente* * Lista de clientes
 */
ListaCliente* criarListasClientes();

/**
 * @brief Função para criar a lista de dietas realizadas
 * 
 * @return ListaDietaRealizada* * Lista de dietas realizadas
 */
ListaDietaRealizada* criarListasDietasRealizadas();

/**
 * @brief Função para criar a lista de planos nutricionais
 * 
 * @return ListaPlanoNutricional* * Lista de planos nutricionais
 */
ListaPlanoNutricional* criarListasPlanosNutricionais();

/**
 * @brief Função para criar a lista de refeições planeadas
 * 
 * @return ListaRefeicoesPlaneadas* * Lista de refeições planeadas
 */
ListaRefeicoesPlaneadas* criarListasRefeicoesPlaneadas();

/**
 * @brief Função para criar as listas na inicialização do programa
 * 
 * @return true * Se as listas foram criadas
 * @return false * Se as listas não foram criadas
 */
bool criarListas();

/**
 * @brief Função para liberar a lista de clientes
 * 
 * @param li * Lista de clientes
 */
void liberarListaClientes(ListaCliente* li);

/**
 * @brief Função para liberar a lista de dietas realizadas
 * 
 * @param li * Lista de dietas realizadas
 */
void liberarListaDietasRealizadas(ListaDietaRealizada* li);

/**
 * @brief Função para liberar a lista de planos nutricionais
 * 
 * @param li * Lista de planos nutricionais
 */
void liberarListaPlanosNutricionais(ListaPlanoNutricional* li);

/**
 * @brief Função para liberar a lista de refeições planeadas
 * 
 * @param li * Lista de refeições planeadas
 */
void liberarListaRefeicoesPlaneadas(ListaRefeicoesPlaneadas* li);

/**
 * @brief Função para terminar o programa e apagar as listas
 * 
 */
void endProgram();

/**
 * @brief Função para verificar se o ID do cliente existe
 * 
 * @param li * Lista de clientes
 * @param id * ID do cliente
 * @return true * Se o ID do cliente existe
 * @return false * Se o ID do cliente não existe
 */
bool checkClienteID(ListaCliente* li, int id);

/**
 * @brief Função para verificar se já existe um plano nutricional para o cliente dentro do intervalo de tempo
 * 
 * @param li * Lista de planos nutricionais
 * @param idCliente * ID do cliente
 * @param data * Data
 * @param refeicao * Refeição
 * @return true * Se já existe um plano nutricional para o cliente dentro do intervalo de tempo
 * @return false * Se não existe um plano nutricional para o cliente dentro do intervalo de tempo
 */
bool checkPlanoNutricionalByClienteDataRef(ListaPlanoNutricional* li, int idCliente, Data data, int refeicao);

/**
 * @brief Função para inserir um novo cliente na lista
 * 
 * @param li * Lista de clientes
 * @param cliente * Dados do cliente
 * @return true * Se o cliente foi inserido com sucesso
 * @return false * Se o cliente não foi inserido com sucesso
 */
bool insertCliente(ListaCliente* li, Cliente cliente);

/**
 * @brief Função para inserir uma dieta realizada
 * 
 * @param li * Lista de dietas realizadas
 * @param dietaRealizada * Dados da dieta realizada
 * @return true * Se a dieta realizada foi inserida com sucesso
 * @return false * Se a dieta realizada não foi inserida com sucesso
 */
bool insertDietaRealizada(ListaDietaRealizada* li, DietaRealizada dietaRealizada);

/**
 * @brief Função para inserir um plano nutricional
 * 
 * @param li * Lista de planos nutricionais
 * @param planoNutricional * Dados do plano nutricional
 * @return true * Se o plano nutricional foi inserido com sucesso
 * @return false * Se o plano nutricional não foi inserido com sucesso
 */
bool insertPlanoNutricional(ListaPlanoNutricional* li, PlanoNutricional planoNutricional);

/**
 * @brief Função para inserir uma refeição planeada
 * 
 * @param li * Lista de refeições planeadas
 * @param refeicoesPlaneadas * Dados da refeição planeada
 * @return true * Se a refeição planeada foi inserida com sucesso
 * @return false * Se a refeição planeada não foi inserida com sucesso
 */
bool insertRefeicaoPlaneada(ListaRefeicoesPlaneadas* li, RefeicoesPlaneadas refeicoesPlaneadas);

/**
 * @brief Função para converter a string de uma refeição para número
 * 
 * @param refeicao * String da refeição
 * @return int * Número da refeição
 */
int convertRefeicao(char *refeicao);

/**
 * @brief Função para converter o número da refeição para a sua string
 * 
 * @param refeicao * Número da refeição
 * @return char* * String da refeição
 */
char* convertRefeicaoString(int refeicao);

/**
 * @brief Função para verificar se o arquivo existe
 * 
 * @param fileName * Nome/Caminho do arquivo
 * @return true * Se o arquivo existir
 * @return false * Se o arquivo não existir
 */
bool fileExists(char *fileName);

/**
 * @brief Função para carregar os clientes
 * 
 * @return true * Se os clientes foram carregados com sucesso
 * @return false * Se os clientes não foram carregados com sucesso
 */
bool carregarClientes();

/**
 * @brief Função para carregar as dietas realizadas
 * 
 * @return true * Se as dietas realizadas foram carregadas com sucesso
 * @return false * Se as dietas realizadas não foram carregadas com sucesso
 */
bool carregarDietasRealizadas();

/**
 * @brief Função para carregar os planos nutricionais
 * 
 * @return true * Se os planos nutricionais foram carregados com sucesso
 * @return false * Se os planos nutricionais não foram carregados com sucesso
 */
bool carregarPlanosNutricionais();

/**
 * @brief Função para fazer display dos clientes inseridos na lista
 * 
 */
void displayClientes();

/**
 * @brief Função para fazer display das dietas realizadas inseridas na lista
 * 
 */
void displayDietasRealizadas();

/**
 * @brief Função para fazer display dos planos nutricionais inseridos na lista
 * 
 */
void displayPlanosNutricionais();

/**
 * @brief Função para verificar se um ano é bissexto
 * 
 * @param ano * Ano
 * @return true * Se o ano for bissexto
 * @return false * Se o ano não for bissexto
 */
bool isAnoBissexto(int ano);

/**
 * @brief Função para perguntar a data ao utilizador
 * 
 * @return Data * Data inserida pelo utilizador
 */
Data perguntarData();

/**
 * @brief Função para verificar se as datas fornecidas formam um range válido
 * 
 * @param dataInicio * Data de início
 * @param dataFim * Data de fim
 * @return true * Se o range for válido
 * @return false * Se o range não for válido
 */
bool isValidDataRange(Data dataInicio, Data dataFim);

/**
 * @brief Função para verificar se a data está dentro do intervalo de datas
 * 
 * @param data * Data para verificar
 * @param dataInicio * Data de início
 * @param dataFim * Data de fim
 * @return true * Se a data estiver dentro do intervalo
 * @return false * Se a data não estiver dentro do intervalo
 */
bool isInDataRange(Data data, Data dataInicio, Data dataFim);

/**
 * @brief Função para verificar se um range de datas está dentro do outro
 * 
 * @param dataInicio * Data de início do 1º range
 * @param dataFim * Data de fim do 1º range
 * @param dataInicio2 * Data de início do 2º range
 * @param dataFim2 * Data de fim do 2º range
 * @return true * Se o 1º range estiver dentro do 2º range
 * @return false * Se o 1º range não estiver dentro do 2º range
 */
bool iSDateRangeInsideOther(Data dataInicio, Data dataFim, Data dataInicio2, Data dataFim2);

/**
 * @brief Função para obter os dias do mês
 * 
 * @param mes * Mês 
 * @param ano * Ano
 * @return int * Número de dias do mês
 */
int diaMes(int mes, int ano);

/**
 * @brief Função para ordenar os clientes de forma decrescente 
 * 
 * @param li * Lista de clientes para ordenar
 */
void ordenarClientesDecrescente(ListaCliente* li);

/**
 * @brief Função para o ponto 2 do trabalho
 * 
 */
void clientesPassaramCaloriasPeriodoTempo();

/**
 * @brief Função para o ponto 3 do trabalho
 * 
 */
void clientesPassaramPlanoNutricionalPeriodoTempoDecrescente();

/**
 * @brief Função para o ponto 4 do trabalho
 * 
 */
void listarPlanoNutricionalPacienteRefeicaoPeriodoTempo();

/**
 * @brief Função para o ponto 5 do trabalho
 * 
 */
void calcularMediaCalRefeicaoPassadoPeriodoTempo();

/**
 * @brief Função para o ponto 6 do trabalho
 * 
 */
void gerarTabelaRefeicoesPlaneadas();

#endif