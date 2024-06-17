/**
 * @file menus.c
 * @brief 
 * @version 0.1
 * @date 2023-12-21
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdio.h>
#include <stdlib.h>

#include "menus.h"     // Importar a defenição das funções
#include "functions.h" // Importar a defenição das funções

void menuPrincipal() {
    int opcao;

    do {
        printf("Menu Principal:\n");
        printf("1 - Carregar Dados;\n");
        printf("2 - Mostrar Dados;\n");
        printf("3 - Listar pacientes a passar calorias num periodo de tempo;\n");
        printf("4 - Listar pacientes que passaram o plano nutricional num periodo de tempo ordenados decrescente pelo nº de paciente;\n");
        printf("5 - Listar Plano nutricional do paciente de uma determinada refeição num periodo de tempo;\n");
        printf("6 - Calcular média das calorias consumidas por refeição por cada paciente num determinado periodo de tempo;\n");
        printf("7 - Gerar tabela com as refeições planeadas e realizadas para todos os pacientes;\n");
        printf("0 - Sair;\n");
        printf("Escolha a opção: ");
        lerInteiro(&opcao);

        switch (opcao) {
            case 1:
                menuCarregarDados();
                break;
            case 2:
                menuDisplayDados();
                break;
            case 3:
                clientesPassaramCaloriasPeriodoTempo();
                break;
            case 4:
                clientesPassaramPlanoNutricionalPeriodoTempoDecrescente();
                break;
            case 5:
                listarPlanoNutricionalPacienteRefeicaoPeriodoTempo();
                break;
            case 6:
                calcularMediaCalRefeicaoPassadoPeriodoTempo();
                break;
            case 7:
                gerarTabelaRefeicoesPlaneadas();
                break;
            case 0:
                printf("A sair do Programa\n");
                endProgram();
                break;
            default:
                printf("Opção inválida!! Tente novamente.\n\n");
                break;
        }
    } while(opcao != 0);    
}

void menuCarregarDados() {
    int opcao;

    do {
        printf("\n\nMenu Carregar Dados:\n");
        printf("1 - Carregar pacientes;\n");
        printf("2 - Carregar dieta realizada pelos pacientes;\n");
        printf("3 - Carregar dados dos planos nutricionais;\n");
        printf("0 - Sair;\n");
        printf("Escolha a opção: ");
        lerInteiro(&opcao);

        switch (opcao) {
            case 1:
                if (carregarClientes()) {
                    printf("Clientes carregados com sucesso!");
                }
                break;
            case 2:
                if (carregarDietasRealizadas()) {
                    printf("Dietas realizadas carregadas com sucesso!");
                }
                break;
            case 3:
                if (carregarPlanosNutricionais()) {
                    printf("Planos nutricionais carregados com sucesso!");
                }
                break;
            case 0:
                printf("A voltar para o menu principal\n\n");
                break;
            default:
                printf("Opção inválida!! Tente novamente.\n\n");
                break;
        }
    } while(opcao != 0);
}

void menuAjuda() {
    printf("Ajuda de utilização\n");
    printf("Parâmetros opcionais:\n");
    printf("-tab -> Leitura de arquivos separados por tabulação\n");
    printf("-bin -> Leitura de arquivos binários\n");
}

void menuDisplayDados() {
    int opcao;

    do {
        printf("\nMenu Display Dados:\n");
        printf("1 - Mostrar dados dos pacientes;\n");
        printf("2 - Mostrar dados das dietas realizadas;\n");
        printf("3 - Mostrar dados dos planos nutricionais;\n");
        printf("0 - Sair;\n");
        printf("Escolha a opção: ");
        lerInteiro(&opcao);

        switch (opcao) {
            case 1:
                displayClientes();
                break;
            case 2:
                displayDietasRealizadas();
                break;
            case 3:
                displayPlanosNutricionais();    
                break;
            case 0:
                printf("A voltar para o menu principal\n\n");
                break;
            default:
                printf("Opção inválida!! Tente novamente.\n\n");
                break;
        }
    } while(opcao != 0);
}
