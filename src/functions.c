/**
 * @file functions.c
 * @brief 
 * @version 0.1
 * @date 2023-12-21
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "functions.h"

// Variáveis globais
bool arquivoTab = false; // Variável que indica se é para trabalhar com arquivos separados por tabulação
bool arquivoBin = false; // Variável que indica se é para trabalhar com arquivos binarios

ListaCliente *listaCliente;
ListaDietaRealizada *listaDietaRealizada;
ListaPlanoNutricional *listaPlanoNutricional;
ListaRefeicoesPlaneadas *listaRefeicoesPlaneadas;
//

bool verificarParametros(int argc, char *argv[]) {
    bool ajudaParam = false;

    if (argc == 1) return false;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-tab") == 0) {
            arquivoTab = true;
        } else if (strcmp(argv[i], "-bin") == 0) {
            arquivoBin = true;
        } else if (strcmp(argv[i], "-ajuda") == 0) {
            ajudaParam = true;
            break;
        }      
    }

    return ajudaParam;
}

void lerInteiro(int *n) {
	int temp, res;

	// Verifica se o valor introduzido é um inteiro, se não for, faz loop até introduzir um inteiro
	res = scanf("%d", &temp);
	while(res != 1) {
        printf("Precisa escrever um número inteiro.\n");
		printf("Tente novamente: ");
        while (getchar() != '\n'); // Limpar o buffer de input
        res = scanf("%d", &temp);
    }

	// Manda o valor da variável temp para o ponteiro *n
	*n = temp;
}

ListaCliente* criarListasClientes() {
    ListaCliente* li = (ListaCliente*) malloc(sizeof(ListaCliente));

    if (li != NULL) *li = NULL;

    return li;
}

ListaDietaRealizada* criarListasDietasRealizadas() {
    ListaDietaRealizada* li = (ListaDietaRealizada*) malloc(sizeof(ListaDietaRealizada));

    if (li != NULL) *li = NULL;

    return li;
}

ListaPlanoNutricional* criarListasPlanosNutricionais() {
    ListaPlanoNutricional* li = (ListaPlanoNutricional*) malloc(sizeof(ListaPlanoNutricional));

    if (li != NULL) *li = NULL;

    return li;
}

ListaRefeicoesPlaneadas* criarListasRefeicoesPlaneadas() {
    ListaRefeicoesPlaneadas* li = (ListaRefeicoesPlaneadas*) malloc(sizeof(ListaRefeicoesPlaneadas));

    if (li != NULL) *li = NULL;

    return li;
}

bool criarListas() {
    // Criar as listas
    listaCliente = criarListasClientes();
    listaDietaRealizada = criarListasDietasRealizadas();
    listaPlanoNutricional = criarListasPlanosNutricionais();
    listaRefeicoesPlaneadas = criarListasRefeicoesPlaneadas();

    if (listaCliente == NULL || listaDietaRealizada == NULL || listaPlanoNutricional == NULL || listaRefeicoesPlaneadas == NULL) {
        return false;
    }

    return true;
}

void liberarListaClientes(ListaCliente* li) {
    if (li != NULL) {
        ElementoCliente* no;
        while ((*li) != NULL) {
            no = *li;
            *li = (*li)->prox;
            free(no);
        }
        free(li);
    }
}

void liberarListaDietasRealizadas(ListaDietaRealizada* li) {
    if (li != NULL) {
        ElementoDietaRealizada* no;
        while ((*li) != NULL) {
            no = *li;
            *li = (*li)->prox;
            free(no);
        }
        free(li);
    }
}

void liberarListaPlanosNutricionais(ListaPlanoNutricional* li) {
    if (li != NULL) {
        ElementoPlanoNutricional* no;
        while ((*li) != NULL) {
            no = *li;
            *li = (*li)->prox;
            free(no);
        }
        free(li);
    }
}

void liberarListaRefeicoesPlaneadas(ListaRefeicoesPlaneadas* li) {
    if (li != NULL) {
        ElementoRefeicoesPlaneadas* no;
        while ((*li) != NULL) {
            no = *li;
            *li = (*li)->prox;
            free(no);
        }
        free(li);
    }
}

void endProgram() {
    liberarListaClientes(listaCliente);
    liberarListaDietasRealizadas(listaDietaRealizada);
    liberarListaPlanosNutricionais(listaPlanoNutricional);
    liberarListaRefeicoesPlaneadas(listaRefeicoesPlaneadas);
}

bool checkClienteID(ListaCliente* li, int id) {
    if (li == NULL) return false;

    ElementoCliente* no = *li;
    while (no != NULL && no->cliente.pacienteID != id) {
        no = no->prox;
    }

    if (no == NULL) return false;

    return true;
}

bool checkPlanoNutricionalByClienteDataRef(ListaPlanoNutricional* li, int idCliente, Data data, int refeicao) {
    if (li == NULL) return false;

    ElementoPlanoNutricional* no = *li;
    // Verificar se não existe nenhuma refeição entre a data de inicio e fim para cliente e refeição
    while (no != NULL && (no->planoNutricional.pacienteID != idCliente || 
                          ( isValidDataRange(no->planoNutricional.dataInicio, data) && 
                          isValidDataRange(data, no->planoNutricional.dataFim) ) || 
                          no->planoNutricional.refeicao != refeicao)) {
        no = no->prox;
    }

    if (no == NULL) return false;

    return true;
}

bool insertCliente(ListaCliente* li, Cliente cliente) {
    if (li == NULL) return false;

    if (checkClienteID(li, cliente.pacienteID)) {
        printf("Já existe um cliente com o id %d!\n", cliente.pacienteID);
        return false;
    }

    ElementoCliente* no = (ElementoCliente*) malloc(sizeof(ElementoCliente));
    if (no == NULL) return false;

    no->cliente = cliente;
    no->prox = NULL;

    if ((*li) == NULL) {
        *li = no;
    } else {
        ElementoCliente* aux = *li;
        while (aux->prox != NULL) {
            aux = aux->prox;
        }
        aux->prox = no;
    }

    return true;
}

bool insertDietaRealizada(ListaDietaRealizada* li, DietaRealizada dietaRealizada) {
    if (li == NULL) return false;

    ElementoDietaRealizada* no = (ElementoDietaRealizada*) malloc(sizeof(ElementoDietaRealizada));
    if (no == NULL) return false;

    no->dietaRealizada = dietaRealizada;
    no->prox = NULL;

    if ((*li) == NULL) {
        *li = no;
    } else {
        ElementoDietaRealizada* aux = *li;
        while (aux->prox != NULL) {
            aux = aux->prox;
        }
        aux->prox = no;
    }

    return true;
}

bool insertPlanoNutricional(ListaPlanoNutricional* li, PlanoNutricional planoNutricional) {
    if (li == NULL) return false;

    if (checkPlanoNutricionalByClienteDataRef(li, planoNutricional.pacienteID, planoNutricional.dataInicio, planoNutricional.refeicao)) {
        printf("Já existe um plano nutricional para o cliente com o id %d entre as datas %d-%d-%d e %d-%d-%d, e para a refeição %s!\n", 
        planoNutricional.pacienteID, planoNutricional.dataInicio.dia, planoNutricional.dataInicio.mes, planoNutricional.dataInicio.ano, planoNutricional.dataFim.dia, planoNutricional.dataFim.mes, planoNutricional.dataFim.ano, convertRefeicaoString(planoNutricional.refeicao));
        return false;
    }

    ElementoPlanoNutricional* no = (ElementoPlanoNutricional*) malloc(sizeof(ElementoPlanoNutricional));
    if (no == NULL) return false;

    no->planoNutricional = planoNutricional;
    no->prox = NULL;

    if ((*li) == NULL) {
        *li = no;
    } else {
        ElementoPlanoNutricional* aux = *li;
        while (aux->prox != NULL) {
            aux = aux->prox;
        }
        aux->prox = no;
    }

    return true;
}

bool insertRefeicaoPlaneada(ListaRefeicoesPlaneadas* li, RefeicoesPlaneadas refeicoesPlaneadas) {
    if (li == NULL) return false;

    ElementoRefeicoesPlaneadas* no = (ElementoRefeicoesPlaneadas*) malloc(sizeof(ElementoRefeicoesPlaneadas));
    if (no == NULL) return false;

    // Verificar se já existe um nó com o mesmo id do paciente, data e refeição
    ElementoRefeicoesPlaneadas* aux = *li;
    while (aux != NULL && (aux->refeicoesPlaneadas.pacienteID != refeicoesPlaneadas.pacienteID || 
                           aux->refeicoesPlaneadas.dataInicio.dia != refeicoesPlaneadas.dataInicio.dia || 
                           aux->refeicoesPlaneadas.dataInicio.mes != refeicoesPlaneadas.dataInicio.mes || 
                           aux->refeicoesPlaneadas.dataInicio.ano != refeicoesPlaneadas.dataInicio.ano || 
                           aux->refeicoesPlaneadas.refeicao != refeicoesPlaneadas.refeicao)) {
        aux = aux->prox;
    }

    if (aux != NULL) {
        aux->refeicoesPlaneadas.consumo_cal += refeicoesPlaneadas.consumo_cal;
        aux->refeicoesPlaneadas.n_compridas++;
        return true;
    } else {
        no->refeicoesPlaneadas = refeicoesPlaneadas;
        no->refeicoesPlaneadas.n_compridas = 1;
        no->prox = NULL;

        if ((*li) == NULL) {
            *li = no;
        } else {
            ElementoRefeicoesPlaneadas* aux = *li;
            while (aux->prox != NULL) {
                aux = aux->prox;
            }
            aux->prox = no;
        }

        return true;
    }
}

int convertRefeicao(char *refeicao) {
    if (strcmp(refeicao, "pequeno almoço") == 0) {
        return 1;
    } else if (strcmp(refeicao, "almoço") == 0) {
        return 2;
    } else if (strcmp(refeicao, "jantar") == 0) {
        return 3;
    }

    return 0;
}

char* convertRefeicaoString(int refeicao) {
    switch (refeicao) {
        case 1:
            return "pequeno almoço";
        case 2:
            return "almoço";
        case 3:
            return "jantar";
    }

    return "";
}

bool fileExists(char *fileName) {
    FILE *fp;

    fp = fopen(fileName, "r");

    if (fp != NULL) {
        fclose(fp);
        return true;
    }

    return false;
}

bool carregarClientes() {
    char fileName[256];
    char linha[150];
    int opcao;
    FILE *fp;
    Cliente cliente;

    if ((*listaCliente) != NULL) {
        printf("Já existem clientes carregados!\n");
        printf("Quer sobrescrever os clientes carregados ou carregar novos? (1 - sobrescrever (ira apagar todos os dados) | outro número - carregar novos): ");
        lerInteiro(&opcao);
        if (opcao == 1) {
            liberarListaClientes(listaCliente);
            liberarListaDietasRealizadas(listaDietaRealizada);
            liberarListaPlanosNutricionais(listaPlanoNutricional);
            listaCliente = criarListasClientes();
            listaDietaRealizada = criarListasDietasRealizadas();
            listaPlanoNutricional = criarListasPlanosNutricionais();
        }
    }

    printf("Qual é o nome ou caminho do arquivo (escreva \"sair\" para cancelar): ");
    scanf("%s", fileName); fflush(stdin);

    if (strcmp(fileName, "sair") == 0) {
        printf("Operação cancelada!\n");
        return false;
    }

    while (!fileExists(fileName)) {
        printf("O arquivo não existe!\n");
        printf("Qual é o nome ou caminho do arquivo (escreva \"sair\" para cancelar): ");
        scanf("%s", fileName); fflush(stdin);

        if (strcmp(fileName, "sair") == 0) {
            printf("Operação cancelada!\n");
            return false;
        }
    }

    fp = fopen(fileName, arquivoBin ? "rb" : "r"); // Se o arquivo for binário, abre em modo de leitura binária, se não, abre em modo de leitura normal

    if (fp == NULL) {
        printf("Ocorreu um erro ao abrir o arquivo!\n");
        return false;
    }

    // Lê o arquivo linha por linha
    while (fgets(linha, 150, fp) != NULL) {
            if(sscanf(linha,
            arquivoTab ? "%d\t%s\t%d" : "%d;%[^;];%d",
            &cliente.pacienteID, cliente.nome, &cliente.telefone) != 3) {
                fclose(fp);
                printf("Ocorreu um erro ao ler o arquivo!\n");
                return false;
            }
        
        if (!insertCliente(listaCliente, cliente)) {
            fclose(fp);
            return false;
        }
    }

    fclose(fp);

    return true;
}

bool carregarDietasRealizadas() {
    char fileName[256];
    char linha[150];
    char refeicao[30];
    int opcao;
    FILE *fp;
    DietaRealizada dietaRealizada;

    if ((*listaDietaRealizada) != NULL) {
        printf("Já existem dietas realizadas carregadas!\n");
        printf("Quer sobrescrever as dietas realizadas carregadas ou carregar novas? (1 - sobrescrever | outro número - carregar novas): ");
        lerInteiro(&opcao);
        if (opcao == 1) {
            liberarListaDietasRealizadas(listaDietaRealizada);
            listaDietaRealizada = criarListasDietasRealizadas();
        }
    }

    if ((*listaCliente) == NULL) {
        printf("Ainda não existem clientes carregados!\n");
        return false;
    }

    printf("Qual é o nome ou caminho do arquivo (escreva \"sair\" para cancelar): ");
    scanf("%s", fileName); fflush(stdin);

    if (strcmp(fileName, "sair") == 0) {
        printf("Operação cancelada!\n");
        return false;
    }

    while (!fileExists(fileName)) {
        printf("O arquivo não existe!\n");
        printf("Qual é o nome ou caminho do arquivo (escreva \"sair\" para cancelar): ");
        scanf("%s", fileName); fflush(stdin);

        if (strcmp(fileName, "sair") == 0) {
        printf("Operação cancelada!\n");
        return false;
    }
    }

    fp = fopen(fileName, arquivoBin ? "rb" : "r"); // Se o arquivo for binário, abre em modo de leitura binária, se não, abre em modo de leitura normal

    if (fp == NULL) {
        printf("Ocorreu um erro ao abrir o arquivo!\n");
        return false;
    }

    // Lê o arquivo linha por linha
    while (fgets(linha, 150, fp) != NULL) {
        if (sscanf(linha,
        arquivoTab ? "%d\t%d-%d-%d\t%s\t%s\t%d cal" : "%d;%d-%d-%d;%[^;];%[^;];%d cal",
        &dietaRealizada.pacienteID,
        &dietaRealizada.data.dia, &dietaRealizada.data.mes, &dietaRealizada.data.ano,
        refeicao, // Colocar o valor da refeição para depois ler a mesma e converter
        dietaRealizada.alimento,
        &dietaRealizada.calorias) != 7) {
            fclose(fp);
            printf("Ocorreu um erro ao ler o arquivo!\n");
            return false;
        }

        dietaRealizada.refeicao = convertRefeicao(refeicao);
        if (dietaRealizada.refeicao == 0) {
            fclose(fp);
            printf("O tipo de refeição %s não é aceite pelo sistema!\n", refeicao);
            return false;
        }

        if (dietaRealizada.calorias <= 0) {
            fclose(fp);
            printf("O valor de calorias não pode ser menor ou igual a 0!\n");
            return false;
        }

        if (!checkClienteID(listaCliente, dietaRealizada.pacienteID)) {
            fclose(fp);
            printf("Não existe nenhum paciente com o id %d!\n", dietaRealizada.pacienteID);
            return false;
        }

        if (!insertDietaRealizada(listaDietaRealizada, dietaRealizada)) {
            fclose(fp);
            return false;
        }
    }

    fclose(fp);

    return true;
}

bool carregarPlanosNutricionais() {
    char fileName[256];
    char linha[150];
    char refeicao[30];
    int opcao;
    FILE *fp;
    PlanoNutricional planoNutricional;

    if ((*listaPlanoNutricional) != NULL) {
        printf("Já existem planos nutricionais carregados!\n");
        printf("Quer sobrescrever os planos nutricionais carregados ou carregar novos? (1 - sobrescrever | outro número - carregar novos):");
        lerInteiro(&opcao);
        if (opcao == 1) {
            liberarListaPlanosNutricionais(listaPlanoNutricional);
            listaPlanoNutricional = criarListasPlanosNutricionais();
        }
    }

    if ((*listaCliente) == NULL) {
        printf("Ainda não existem clientes carregados!\n");
        return false;
    }

    printf("Qual é o nome ou caminho do arquivo (escreva \"sair\" para cancelar): ");
    scanf("%s", fileName); fflush(stdin);

    if (strcmp(fileName, "sair") == 0) {
        printf("Operação cancelada!\n");
        return false;
    }

    while (!fileExists(fileName)) {
        printf("O arquivo não existe!\n");
        printf("Qual é o nome ou caminho do arquivo (escreva \"sair\" para cancelar): ");
        scanf("%s", fileName); fflush(stdin);

        if (strcmp(fileName, "sair") == 0) {
        printf("Operação cancelada!\n");
        return false;
    }
    }

    fp = fopen(fileName, arquivoBin ? "rb" : "r"); // Se o arquivo for binário, abre em modo de leitura binária, se não, abre em modo de leitura normal

    if (fp == NULL) {
        printf("Ocorreu um erro ao abrir o arquivo!\n");
        return false;
    }

    // Lê o arquivo linha por linha
    while (fgets(linha, 150, fp) != NULL) {
        if (sscanf(linha,
        // arquivoTab ? "%d\t%s\t%s\t%s\t%d cal\t%d cal" : "%d;%[^;];%[^;];%[^;];%d cal;%d cal",
        arquivoTab ? "%d\t%d-%d-%d\t%d-%d-%d\t%s\t%d cal\t%d cal" : "%d;%d-%d-%d;%d-%d-%d;%[^;];%d cal;%d cal",
        &planoNutricional.pacienteID,
        &planoNutricional.dataInicio.dia, &planoNutricional.dataInicio.mes, &planoNutricional.dataInicio.ano,
        &planoNutricional.dataFim.dia, &planoNutricional.dataFim.mes, &planoNutricional.dataFim.ano,
        refeicao, // Colocar o valor da refeição para depois ler a mesma e converter
        &planoNutricional.min_cal,
        &planoNutricional.max_cal) != 10) {
            fclose(fp);
            printf("Ocorreu um erro ao ler o arquivo1!\n");
            return false;
        }

        planoNutricional.refeicao = convertRefeicao(refeicao);
        if (planoNutricional.refeicao == 0) {
            fclose(fp);
            printf("O tipo de refeição %s não é aceite pelo sistema!\n", refeicao);
            return false;
        }

        if (planoNutricional.min_cal <= 0 || planoNutricional.max_cal <= 0) {
            fclose(fp);
            printf("O valor de calorias não pode ser menor ou igual a 0!\n");
            return false;
        }

        if (planoNutricional.min_cal >= planoNutricional.max_cal) {
            fclose(fp);
            printf("O valor de calorias mínimo não pode ser maior ou igual ao valor de calorias máximo!\n");
            return false;
        }

        if (!checkClienteID(listaCliente, planoNutricional.pacienteID)) {
            fclose(fp);
            printf("Não existe nenhum paciente com o id %d!\n", planoNutricional.pacienteID);
            return false;
        }

        if (!insertPlanoNutricional(listaPlanoNutricional, planoNutricional)) {
            fclose(fp);
            return false;
        }
    }

    fclose(fp);

    return true;
}

void displayClientes() {
    if ((*listaCliente) == NULL) {
        printf("Ainda não existem clientes carregados!\n");
        return;
    }

    printf("Clientes:\n");

    ElementoCliente* no = *listaCliente;
    while (no != NULL) {
        printf("ID: %d\n", no->cliente.pacienteID);
        printf("Nome: %s\n", no->cliente.nome);
        printf("Telefone: %d\n\n", no->cliente.telefone);
        no = no->prox;
    }
}  

void displayDietasRealizadas() {
    if ((*listaDietaRealizada) == NULL) {
        printf("Ainda não existem dietas realizadas carregadas!\n");
        return;
    }

    printf("Dietas Realizadas:\n");

    ElementoDietaRealizada* no = *listaDietaRealizada;
    while (no != NULL) {
        printf("ID do Paciente: %d\n", no->dietaRealizada.pacienteID);
        printf("Data: %d-%d-%d\n", no->dietaRealizada.data.dia, no->dietaRealizada.data.mes, no->dietaRealizada.data.ano);
        printf("Refeição: %s\n", convertRefeicaoString(no->dietaRealizada.refeicao));
        printf("Alimento: %s\n", no->dietaRealizada.alimento);
        printf("Calorias: %d\n\n", no->dietaRealizada.calorias);
        no = no->prox;
    }
}  
      
void displayPlanosNutricionais() {
    if ((*listaPlanoNutricional) == NULL) {
        printf("Ainda não existem planos nutricionais carregados!\n");
        return;
    }

    printf("Planos Nutricionais:\n");

    ElementoPlanoNutricional* no = *listaPlanoNutricional;
    while (no != NULL) {
        printf("ID do Paciente: %d\n", no->planoNutricional.pacienteID);
        printf("Data Inicio: %d-%d-%d\n", no->planoNutricional.dataInicio.dia, no->planoNutricional.dataInicio.mes, no->planoNutricional.dataInicio.ano);
        printf("Data fim: %d-%d-%d\n", no->planoNutricional.dataFim.dia, no->planoNutricional.dataFim.mes, no->planoNutricional.dataFim.ano);
        printf("Refeição: %s\n", convertRefeicaoString(no->planoNutricional.refeicao));
        printf("Calorias Mínimas: %d\n", no->planoNutricional.min_cal);
        printf("Calorias Máximas: %d\n\n", no->planoNutricional.max_cal);
        no = no->prox;
    }
}

bool isAnoBissexto(int ano) {
    return ((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0));
} 

int diaMes(int mes, int ano) {
    int diaMax;

    switch (mes) {
        case 1:
            diaMax = 31;
            break;
        case 2:
            diaMax = isAnoBissexto(ano) ? 29 : 28;
            break;
        case 3:
            diaMax = 31;
            break;
        case 4:
            diaMax = 30;
            break;
        case 5:
            diaMax = 31;
            break;
        case 6:
            diaMax = 30;
            break;
        case 7:
            diaMax = 31;
            break;
        case 8:
            diaMax = 31;
            break;
        case 9:
            diaMax = 30;
            break;
        case 10:
            diaMax = 31;
            break;
        case 11:
            diaMax = 30;
            break;
        case 12:
            diaMax = 31;
            break;
    }

    return diaMax;
}

void ordenarClientesDecrescente(ListaCliente* li) {
    if (li == NULL) return;

    ElementoCliente *atual, *proximo;
    Cliente temp;

    atual = *li;
    while (atual != NULL) {
        proximo = atual->prox;
        while (proximo != NULL) {
            if (atual->cliente.pacienteID < proximo->cliente.pacienteID) {
                temp = atual->cliente;
                atual->cliente = proximo->cliente;
                proximo->cliente = temp;
            }
            proximo = proximo->prox;
        }
        atual = atual->prox;
    }
}

bool isValidDataRange(Data dataInicio, Data dataFim) {
    if (dataInicio.ano > dataFim.ano) {
        return false;
    } else if (dataInicio.ano == dataFim.ano) {
        if (dataInicio.mes > dataFim.mes) {
            return false;
        } else if (dataInicio.mes == dataFim.mes) {
            if (dataInicio.dia > dataFim.dia) {
                return false;
            }
        }
    }

    return true;
}

bool isInDataRange(Data data, Data dataInicio, Data dataFim) {
    int dataInt = data.ano * 10000 + data.mes * 100 + data.dia;
    int dataInicioInt = dataInicio.ano * 10000 + dataInicio.mes * 100 + dataInicio.dia;
    int dataFimInt = dataFim.ano * 10000 + dataFim.mes * 100 + dataFim.dia;

    return (dataInicioInt <= dataInt && dataInt <= dataFimInt);
}

bool iSDateRangeInsideOther(Data dataInicio, Data dataFim, Data dataInicio2, Data dataFim2) {
    int dataInicioInt = dataInicio.ano * 10000 + dataInicio.mes * 100 + dataInicio.dia;
    int dataFimInt = dataFim.ano * 10000 + dataFim.mes * 100 + dataFim.dia;
    int dataInicio2Int = dataInicio2.ano * 10000 + dataInicio2.mes * 100 + dataInicio2.dia;
    int dataFim2Int = dataFim2.ano * 10000 + dataFim2.mes * 100 + dataFim2.dia;

    return (dataInicioInt >= dataInicio2Int && dataFimInt <= dataFim2Int);
}

Data perguntarData() {
    int diaMax;
    Data data;

    printf("Qual é o ano: ");
    lerInteiro(&data.ano);
    while (data.ano < 2000) {
        printf("O ano não pode ser menor a 2000!\n");
        printf("Qual é o ano: ");
        lerInteiro(&data.ano);
    }

    printf("Qual é o mês: ");
    lerInteiro(&data.mes);
    while (data.mes <= 0 || data.mes > 12) {
        printf("O mês não pode ser menor ou igual a 0 ou maior que 12!\n");
        printf("Qual é o mês: ");
        lerInteiro(&data.mes);
    }

    diaMax = diaMes(data.mes, data.ano);

    printf("Qual é o dia: ");
    lerInteiro(&data.dia);
    while (data.dia <= 0 || data.dia > diaMax) {
        printf("O dia não pode ser menor ou igual a 0 ou maior que %d!\n", diaMax);
        printf("Qual é o dia: ");
        lerInteiro(&data.dia);
    }

    return data;
}

void clientesPassaramCaloriasPeriodoTempo() {
    Data dataInicio, dataFim;
    int calorias, total = 0, totalCalorias;

    if ((*listaCliente) == NULL) {
        printf("Ainda não existem clientes carregados!\n");
        return;
    }

    if ((*listaDietaRealizada) == NULL) {
        printf("Ainda não existem dietas realizadas carregadas!\n");
        return;
    }

    printf("Qual é a data de início:\n");
    dataInicio = perguntarData();

    printf("Qual é a data de fim:\n");
    dataFim = perguntarData();

    while (!isValidDataRange(dataInicio, dataFim)) {
        printf("A data de início não pode ser maior que a data de fim!\n");
        printf("Qual é a data de início:\n");
        dataInicio = perguntarData();

        printf("Qual é a data de fim:\n");
        dataFim = perguntarData();
    }

    printf("Qual é o valor de calorias: ");
    lerInteiro(&calorias);
    while (calorias <= 0) {
        printf("O valor de calorias não pode ser menor ou igual a 0!\n");
        printf("Qual é o valor de calorias: ");
        lerInteiro(&calorias);
    }

    ElementoCliente* no = *listaCliente;
    while (no != NULL) {
        totalCalorias = 0;

        ElementoDietaRealizada* noDieta = *listaDietaRealizada;
        while (noDieta != NULL) {
            if (noDieta->dietaRealizada.pacienteID == no->cliente.pacienteID && 
                isInDataRange(noDieta->dietaRealizada.data, dataInicio, dataFim)) {
                totalCalorias += noDieta->dietaRealizada.calorias;
            }
            noDieta = noDieta->prox;
        }

        if (totalCalorias >= calorias) {
            total++;
        }

        no = no->prox;
    }
    
    printf("Total de clientes que passaram %d calorias no período de tempo: %d\n\n", calorias, total);
}

// Listagem dos pacientes, ordenada por ordem decrescente do número de paciente, que realizaram
// alguma refeição com quantidade de calorias fora do intervalo (de acordo com o plano nutricional)
// num determinado período;
void clientesPassaramPlanoNutricionalPeriodoTempoDecrescente() {
    ListaCliente* listaClienteDecrescente = criarListasClientes();
    Data dataInicio, dataFim, lastData = { 0, 0, 0 };
    int totalCal, idRefeicao;
    bool clienteInserted = false;
    
    if ((*listaCliente) == NULL) {
        printf("Ainda não existem clientes carregados!\n");
        return;
    }

    if ((*listaPlanoNutricional) == NULL) {
        printf("Ainda não existem planos nutricionais carregados!\n");
        return;
    }

    if ((*listaDietaRealizada) == NULL) {
        printf("Ainda não existem dietas realizadas carregadas!\n");
        return;
    }

    printf("Qual é a data de início:\n");
    dataInicio = perguntarData();

    printf("Qual é a data de fim:\n");
    dataFim = perguntarData();

    while (!isValidDataRange(dataInicio, dataFim)) {
        printf("A data de início não pode ser maior que a data de fim!\n");
        printf("Qual é a data de início:\n");
        dataInicio = perguntarData();

        printf("Qual é a data de fim:\n");
        dataFim = perguntarData();
    } 

    printf("Clientes que passaram o plano nutricional num período de tempo (por ordem decrescente do número de paciente):\n\n");

    ElementoCliente* no = *listaCliente;
    while (no != NULL) {
        totalCal = 0;
        idRefeicao = 0;
        lastData = (Data) { 0, 0, 0 };
        clienteInserted = false;

        ElementoPlanoNutricional* noPlano = *listaPlanoNutricional;
        while (noPlano != NULL) {
            if (noPlano->planoNutricional.pacienteID == no->cliente.pacienteID && 
                iSDateRangeInsideOther(noPlano->planoNutricional.dataInicio, noPlano->planoNutricional.dataFim, dataInicio, dataFim)) {
                ElementoDietaRealizada* noDieta = *listaDietaRealizada;
                while (noDieta != NULL) {
                    if (noDieta->dietaRealizada.pacienteID == no->cliente.pacienteID &&
                        noDieta->dietaRealizada.refeicao == noPlano->planoNutricional.refeicao &&
                        isInDataRange(noDieta->dietaRealizada.data, noPlano->planoNutricional.dataInicio, noPlano->planoNutricional.dataFim)) {
                        if (noDieta->dietaRealizada.data.ano == lastData.ano && 
                            noDieta->dietaRealizada.data.mes == lastData.mes && 
                            noDieta->dietaRealizada.data.dia == lastData.dia && 
                            noDieta->dietaRealizada.refeicao == idRefeicao) {
                            totalCal += noDieta->dietaRealizada.calorias;
                        } else {
                            totalCal = noDieta->dietaRealizada.calorias;
                            idRefeicao = noDieta->dietaRealizada.refeicao;
                            lastData = noDieta->dietaRealizada.data;
                        }
                    }
                    noDieta = noDieta->prox;
                }

                if (totalCal < noPlano->planoNutricional.min_cal || totalCal > noPlano->planoNutricional.max_cal) {
                    insertCliente(listaClienteDecrescente, no->cliente);
                    clienteInserted = true;
                    break;
                }
            }
            noPlano = noPlano->prox;

            if (clienteInserted) {
                break;
            }
        }
        no = no->prox;
    }

    if ((*listaClienteDecrescente) == NULL) {
        printf("Nenhum cliente passou o plano nutricional num período de tempo!\n");
        liberarListaClientes(listaClienteDecrescente);
        return;
    }

    ordenarClientesDecrescente(listaClienteDecrescente);

    no = *listaClienteDecrescente;
    while (no != NULL) {
        printf("ID: %d\n", no->cliente.pacienteID);
        printf("Nome: %s\n", no->cliente.nome);
        printf("Telefone: %d\n\n", no->cliente.telefone);
        no = no->prox;
    }

    liberarListaClientes(listaClienteDecrescente);
}

void listarPlanoNutricionalPacienteRefeicaoPeriodoTempo() {
    Data dataInicio, dataFim;
    int refeicao, pacienteID;

    if ((*listaCliente) == NULL) {
        printf("Ainda não existem clientes carregados!\n");
        return;
    }

    if ((*listaPlanoNutricional) == NULL) {
        printf("Ainda não existem planos nutricionais carregados!\n");
        return;
    }

    printf("Qual é a data de início:\n");
    dataInicio = perguntarData();

    printf("Qual é a data de fim:\n");
    dataFim = perguntarData();

    while (!isValidDataRange(dataInicio, dataFim)) {
        printf("A data de início não pode ser maior que a data de fim!\n");
        printf("Qual é a data de início:\n");
        dataInicio = perguntarData();

        printf("Qual é a data de fim:\n");
        dataFim = perguntarData();
    }

    printf("Qual é o tipo de refeição (1 - pequeno almoço | 2 - almoço | 3 - jantar): ");
    lerInteiro(&refeicao);
    while (refeicao <= 0 || refeicao > 3) {
        printf("O tipo de refeição não pode ser menor ou igual a 0 ou maior que 3!\n");
        printf("Qual é o tipo de refeição (1 - pequeno almoço | 2 - almoço | 3 - jantar): ");
        lerInteiro(&refeicao);
    }

    printf("Qual é o id do paciente: ");
    lerInteiro(&pacienteID);
    while (!checkClienteID(listaCliente, pacienteID)) {
        printf("Não existe nenhum paciente com o id %d!\n", pacienteID);
        printf("Qual é o id do paciente: ");
        lerInteiro(&pacienteID);
    }

    printf("Refeições: \n\n");

    ElementoPlanoNutricional* no = *listaPlanoNutricional;
    while (no != NULL) {
        if (no->planoNutricional.pacienteID == pacienteID &&
            iSDateRangeInsideOther(no->planoNutricional.dataInicio, no->planoNutricional.dataFim, dataInicio, dataFim) &&
            no->planoNutricional.refeicao == refeicao) {
            printf("Data Inicio: %d-%d-%d\n", no->planoNutricional.dataInicio.dia, no->planoNutricional.dataInicio.mes, no->planoNutricional.dataInicio.ano);
            printf("Data fim: %d-%d-%d\n", no->planoNutricional.dataFim.dia, no->planoNutricional.dataFim.mes, no->planoNutricional.dataFim.ano);
            printf("Calorias Mínimas: %d\n", no->planoNutricional.min_cal);
            printf("Calorias Máximas: %d\n\n", no->planoNutricional.max_cal);
        }
        no = no->prox;
    }
}

void calcularMediaCalRefeicaoPassadoPeriodoTempo() {
    Data dataInicio, dataFim;
    int count, totalCal, i;
    float mediaCal;

    if ((*listaCliente) == NULL) {
        printf("Ainda não existem clientes carregados!\n");
        return;
    }

    if ((*listaDietaRealizada) == NULL) {
        printf("Ainda não existem dietas realizadas carregadas!\n");
        return;
    }

    printf("Qual é a data de início:\n");
    dataInicio = perguntarData();

    printf("Qual é a data de fim:\n");
    dataFim = perguntarData();

    while (!isValidDataRange(dataInicio, dataFim)) {
        printf("A data de início não pode ser maior que a data de fim!\n");
        printf("Qual é a data de início:\n");
        dataInicio = perguntarData();

        printf("Qual é a data de fim:\n");
        dataFim = perguntarData();
    }

    printf("Média de calorias por refeição: \n\n");

    ElementoCliente* no = *listaCliente;
    while (no != NULL) {
        count = 0;
        totalCal = 0;	
        mediaCal = 0;
        i = 1;

        while (i <= 3) {
            ElementoDietaRealizada* noDieta = *listaDietaRealizada;
            while (noDieta != NULL) {
                if (noDieta->dietaRealizada.pacienteID == no->cliente.pacienteID &&
                    isInDataRange(noDieta->dietaRealizada.data, dataInicio, dataFim) &&
                    noDieta->dietaRealizada.refeicao == i) {
                    count++;
                    totalCal += noDieta->dietaRealizada.calorias;
                }
                noDieta = noDieta->prox;
            }

            if (count > 0) {
                mediaCal = totalCal / count;

                printf("ID do Paciente: %d\n", no->cliente.pacienteID);
                printf("Nome: %s\n", no->cliente.nome);
                printf("Refeição: %s\n", convertRefeicaoString(i));
                printf("Média de calorias: %.2f\n\n", mediaCal);

                count = 0;
                totalCal = 0;	
                mediaCal = 0;
            }

            i++;
        }

        no = no->prox;
    }
}

void gerarTabelaRefeicoesPlaneadas() {
    Data lastData = { 0, 0, 0 };
    int totalCal, idRefeicao;
    bool stop = false;

    if ((*listaCliente) == NULL) {
        printf("Ainda não existem clientes carregados!\n");
        return;
    }

    if ((*listaPlanoNutricional) == NULL) {
        printf("Ainda não existem planos nutricionais carregados!\n");
        return;
    }

    ElementoCliente* no = *listaCliente;
    while (no != NULL || stop) {
        totalCal = 0;
        idRefeicao = 0;
        lastData = (Data) { 0, 0, 0 };

        ElementoPlanoNutricional* noPlano = *listaPlanoNutricional;
        while (noPlano != NULL || stop) {
            if (noPlano->planoNutricional.pacienteID == no->cliente.pacienteID) {
                ElementoDietaRealizada* noDieta = *listaDietaRealizada;
                while (noDieta != NULL || stop) {
                    if (noDieta->dietaRealizada.pacienteID == no->cliente.pacienteID &&
                        noDieta->dietaRealizada.refeicao == noPlano->planoNutricional.refeicao &&
                        isInDataRange(noDieta->dietaRealizada.data, noPlano->planoNutricional.dataInicio, noPlano->planoNutricional.dataFim)) {
                        if (noDieta->dietaRealizada.data.ano == lastData.ano && 
                            noDieta->dietaRealizada.data.mes == lastData.mes && 
                            noDieta->dietaRealizada.data.dia == lastData.dia && 
                            noDieta->dietaRealizada.refeicao == idRefeicao) {
                            totalCal += noDieta->dietaRealizada.calorias;
                        } else {
                            totalCal = noDieta->dietaRealizada.calorias;
                            idRefeicao = noDieta->dietaRealizada.refeicao;
                            lastData = noDieta->dietaRealizada.data;
                        }
                    }
                    noDieta = noDieta->prox;
                }

                RefeicoesPlaneadas refeicoesPlaneadas;
                refeicoesPlaneadas.pacienteID = no->cliente.pacienteID;
                strcpy(refeicoesPlaneadas.nome, no->cliente.nome);
                refeicoesPlaneadas.refeicao = noPlano->planoNutricional.refeicao;
                refeicoesPlaneadas.dataInicio = noPlano->planoNutricional.dataInicio;
                refeicoesPlaneadas.dataFim = noPlano->planoNutricional.dataFim;
                refeicoesPlaneadas.min_cal = noPlano->planoNutricional.min_cal;
                refeicoesPlaneadas.max_cal = noPlano->planoNutricional.max_cal;
                refeicoesPlaneadas.consumo_cal = totalCal;

                if (!insertRefeicaoPlaneada(listaRefeicoesPlaneadas, refeicoesPlaneadas)) {
                    printf("Ocorreu um erro a gerar os dados para a tabela.\n");
                    stop = true;
                    liberarListaRefeicoesPlaneadas(listaRefeicoesPlaneadas);
                    listaRefeicoesPlaneadas = criarListasRefeicoesPlaneadas();
                    return;
                }
            }
            noPlano = noPlano->prox;
        }
        no = no->prox;
    }

    if (stop) return;

    if ((*listaRefeicoesPlaneadas) == NULL) {
        printf("Nenhum cliente passou o plano nutricional num período de tempo!\n");
        liberarListaRefeicoesPlaneadas(listaRefeicoesPlaneadas);
        listaRefeicoesPlaneadas = criarListasRefeicoesPlaneadas();
        return;
    }

    printf("Tabela de refeições planeadas:\n\n");

    //Header da tabela
    printf("| %-10s | %-30s | %-30s | %-10s | %-10s | %-8s | %-8s | %-12s |\n",
           "PacienteID", "Nome", "Refeição", "Data Início", "Data Fim", "Min Cal", "Max Cal", "Consumo Cal");

    ElementoRefeicoesPlaneadas* noRefeicoesPlaneadas = *listaRefeicoesPlaneadas;
    while (noRefeicoesPlaneadas != NULL) {
        printf("| %-10d | %-30s | %-30s | %02d-%02d-%04d | %02d-%02d-%04d | %-8d | %-8d | %-12d |\n",
            noRefeicoesPlaneadas->refeicoesPlaneadas.pacienteID, noRefeicoesPlaneadas->refeicoesPlaneadas.nome, 
            convertRefeicaoString(noRefeicoesPlaneadas->refeicoesPlaneadas.refeicao),
            noRefeicoesPlaneadas->refeicoesPlaneadas.dataInicio.dia, noRefeicoesPlaneadas->refeicoesPlaneadas.dataInicio.mes, noRefeicoesPlaneadas->refeicoesPlaneadas.dataInicio.ano,
            noRefeicoesPlaneadas->refeicoesPlaneadas.dataFim.dia, noRefeicoesPlaneadas->refeicoesPlaneadas.dataFim.mes, noRefeicoesPlaneadas->refeicoesPlaneadas.dataFim.ano,
            noRefeicoesPlaneadas->refeicoesPlaneadas.min_cal, noRefeicoesPlaneadas->refeicoesPlaneadas.max_cal,
            noRefeicoesPlaneadas->refeicoesPlaneadas.consumo_cal / noRefeicoesPlaneadas->refeicoesPlaneadas.n_compridas);
        noRefeicoesPlaneadas = noRefeicoesPlaneadas->prox;
    }

    printf("\n\n");

    liberarListaRefeicoesPlaneadas(listaRefeicoesPlaneadas);
    listaRefeicoesPlaneadas = criarListasRefeicoesPlaneadas();
}
