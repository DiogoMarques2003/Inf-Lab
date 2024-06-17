/**
 * @file main.c
 * @brief 
 * @version 0.1
 * @date 2023-12-21
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#include "menus.h"
#include "functions.h"

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "Portuguese");
	
	printf("A iniciar o programa...\n\n");
	
	if (verificarParametros(argc, argv)) {
		menuAjuda();
	} else {
		if (!criarListas()) {
			printf("Ocorreu um erro ao criar as listas.\n");
			return 1;
		}

		menuPrincipal();
	}

	return 0;
}