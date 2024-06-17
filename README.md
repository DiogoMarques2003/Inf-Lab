# Trabalho Prático

Licenciatura em Engenharia de Sistemas Informáticos 2023-24

Laboratórios de Informática

## grupo  *35*
| Número | Nome | Tarefas |
| -----   | ---- | ---- |
| 22999     | Joana Pimenta  | Criação dos menus, make file e relatório em latex |
| 23000     | Diogo Marques  | Criação da lógica para os pontos pedidos no relatório e documentação em Doxygen|
| 23135     | Miguel Simões  | Criação do sistema para ler os arquivos, criação das listas e realização dos testes |

## organização

[doc/](./doc/)  documentação com o relatório

[src/](./src/)  Código da solução desenvolvida 

[documentação doxygen pdf](./doc/latex/d-35-refman.pdf) Documentação gerada pelo doxygen

[relatório](./doc/relatorio/d-35-doc.pdf) Relatório do trabalho

## como compilar
```
cd src
make all
```

## como executar
```
./prog_nutricional 

Parâmetros (Todas as parâmetros são opcionais, o programa funciona sem nenhum):
    -ajuda -> mostra o menu de ajuda do programa
    -bin   -> ler arquivos em binário
    -tab   -> ler arquivos separados por tabuladores

    O -bin e o -tab podem ser usados em simultâneo, já o -ajuda termina o programa ao fim de dar display ao menu de ajuda
```
