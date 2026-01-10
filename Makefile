# Makefile

# Компилятор
CC = gcc

# Флаги компиляции
CFLAGS = -Wall -Wextra -Iinclude

# Имя исполняемого файла
TARGET = program

# Исходные файлы
SRC_DIR = src
INCLUDE_DIR = include
OBJ_DIR = obj

# Список исходников (без .c)
SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Целевая цель — сборка программы
all: $(TARGET)

# Правило сборки целевой программы
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

# Правило для создания объектных файлов
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

# Очистка
clean:
	rm -f $(TARGET) $(OBJECTS)
	rmdir --ignore-fail-on-non-empty $(OBJ_DIR)

# Полная очистка (включая папку obj)
distclean: clean
	rm -rf $(OBJ_DIR)

.PHONY: all clean distclean
