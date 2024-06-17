# Nome do projeto
PROJ_NAME=prog_nutricional

# Diretórios
SRC_DIR = .
OBJ_DIR = ./obj

# Arquivos .c
C_SOURCE=$(wildcard $(SRC_DIR)/*.c)

# Arquivos .h
H_SOURCE=$(wildcard $(SRC_DIR)/*.h)

# Arquivos .o
OBJ=$(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(C_SOURCE))

# Compilador
CC=gcc

# Flags para o compilador
CC_FLAGS=-c \
         -W \
         -Wall \
         -ansi \
         -pedantic \
         -g \
         -std=c99 \
         -I$(SRC_DIR)

# Nome do executável
TARGET=$(PROJ_NAME)

all: | clean create_dirs $(TARGET)

create_dirs:
	mkdir -p $(OBJ_DIR)

$(TARGET): $(OBJ)
	$(CC) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CC_FLAGS) $< -o $@

.PHONY: clean
clean:
	rm -rf $(OBJ_DIR) $(TARGET)