/**
 * @file structs.h
 * @brief 
 * @version 0.1
 * @date 2023-12-21
 * 
 * @copyright Copyright (c) 2023
 * 
 */

// Estruturas
typedef struct {
	int dia, mes, ano;
} Data;

typedef struct {
    int pacienteID;
    char nome[30];
    int telefone;
} Cliente;

typedef struct {
    int pacienteID;
    Data data;
    int refeicao; // 1 - pequeno almoço; 2 - almoço; 3 - jantar
    char alimento[50];
    int calorias;
} DietaRealizada;

typedef struct {
    int pacienteID;
    Data dataInicio, dataFim;
    int refeicao; // 1 - pequeno almoço; 2 - almoço; 3 - jantar
    int min_cal, max_cal;
} PlanoNutricional;

typedef struct {
    int pacienteID;
    char nome[30];
    int refeicao; // 1 - pequeno almoço; 2 - almoço; 3 - jantar
    Data dataInicio, dataFim;
    int min_cal, max_cal, consumo_cal, n_compridas;
} RefeicoesPlaneadas;
//

// Elementos das listas
typedef struct elementoCliente {
    Cliente cliente;
    struct elementoCliente *prox;
} ElementoCliente;

typedef struct elementoDietaRelizada {
    DietaRealizada dietaRealizada;
    struct elementoDietaRelizada *prox;
} ElementoDietaRealizada;

typedef struct elementoPlanoNutricional {
    PlanoNutricional planoNutricional;
    struct elementoPlanoNutricional *prox;
} ElementoPlanoNutricional;

typedef struct elementoRefeicoesPlaneadas {
    RefeicoesPlaneadas refeicoesPlaneadas;
    struct elementoRefeicoesPlaneadas *prox;
} ElementoRefeicoesPlaneadas;
//

// Listas
typedef ElementoCliente* ListaCliente;
typedef ElementoDietaRealizada* ListaDietaRealizada;
typedef ElementoPlanoNutricional* ListaPlanoNutricional;
typedef ElementoRefeicoesPlaneadas* ListaRefeicoesPlaneadas;
//