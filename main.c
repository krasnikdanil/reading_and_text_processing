#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
 * Максимальная длина текста в buffer
 * */
#define MAX_SIZE 257
/*
 * Структура предложения
 * */
typedef struct Sentence {
  char *ssentence; /* Предложение*/
  size_t capacity; /* Размер предложения в байтах*/
} Sentence;
/*
 * Структура предложения
 * */
typedef struct Text {
  Sentence *tsentence; /* Массив предложения*/
  size_t capacity;     /* Размер массива предложений*/
  size_t count;        /* Количество предложений*/
} Text;
/*
 * Инцализация текста
 * */
void init_text(Text *text) {
  text->capacity = 4;
  text->count = 0;
  text->tsentence = (Sentence *)malloc(sizeof(Sentence) * text->capacity);
  if (!text->tsentence) {
    fprintf(stderr, "Error mammory allocation");
    exit(EXIT_FAILURE);
  }
  text->tsentence[0].ssentence = malloc(MAX_SIZE);
  if (!text->tsentence[0].ssentence) {
    fprintf(stderr, "Error mammory allocation");
    exit(EXIT_FAILURE);
  }
  text->tsentence[0].ssentence[0] = '\0';
  text->tsentence[0].capacity = MAX_SIZE - 1;
}
/*
 * Увеличение количество допустимых предложений
 * */
void increase_text_size(Text *text) {
  text->capacity *= 2;
  Sentence *t = realloc(text->tsentence, sizeof(Sentence) * text->capacity);
  if (!t) {
    fprintf(stderr, "Error mammory allocation");
    exit(EXIT_FAILURE);
  }
  text->tsentence = t;
}
/*
 * Увеличение размера предложения
 * */
void increase_sentence_size(Sentence *tsentence, size_t len) {
  tsentence->capacity = tsentence->capacity + len;
  char *s = realloc(tsentence->ssentence, tsentence->capacity + 1);
  if (!s) {
    fprintf(stderr, "Error mammory allocation");
    exit(EXIT_FAILURE);
  }
  tsentence->ssentence = s;
}
/*
 * Инцализация следующего предложения
 * */
void init_next_sentence(Text *text) {
  if (text->count == (text->capacity - 1)) {
    increase_text_size(text);
  }
  text->count++;
  text->tsentence[text->count].capacity = MAX_SIZE - 1;
  text->tsentence[text->count].ssentence = malloc(MAX_SIZE);
  if (!text->tsentence[text->count].ssentence) {
    fprintf(stderr, "Error mammory allocation");
    exit(EXIT_FAILURE);
  }
  text->tsentence[text->count].ssentence[0] = '\0';
}
/*
 * Добавление предложеия в текст
 * */
void add_sentence_text(Text *text, char *buffer, bool end) {
  if (text->count == (text->capacity - 1)) {
    increase_text_size(text);
  }
  char *s = malloc(strlen(buffer) + (end ? 2 : 1));
  if (!s) {
    fprintf(stderr, "Error memory allocation");
    exit(EXIT_FAILURE);
  }
  /* Для сокращения записи*/
  Sentence *tsentence = &text->tsentence[text->count];
  snprintf(s, strlen(buffer) + (end ? 2 : 1), "%s%s", buffer, (end ? "." : ""));
  if ((tsentence->capacity - strlen(tsentence->ssentence)) < strlen(s)) {
    increase_sentence_size(tsentence, strlen(s));
  }
  strcat(tsentence->ssentence, s);
  if (end) {
    init_next_sentence(text);
  }
  free(s);
}

/*
 * Убираем пробелы и другие знаки табуляции
 * */
void trim_spaces(char **s) {
  char *start = *s;
  while (*start != '\0' &&
         (isspace((unsigned char)*start) || iscntrl((unsigned char)*start))) {
    start++;
  }
  *s = start;
}
/*
 * Чтение текста
 * */
void write_text(Text *text) {
  char buffer[MAX_SIZE];
  while (fgets(buffer, MAX_SIZE - 1, stdin) != NULL) {
    char *start = buffer;
    char *end;
    while (*start && *start != '\n' &&
           (isspace((unsigned char)*start) || iscntrl((unsigned char)*start))) {
      start++;
    }
    if (strcmp(start, "\n") == 0) {
      break;
    }
    while ((end = strchr(start, '.')) && *start != '\0') {
      *end = '\0';
      trim_spaces(&start);
      if (*start == '\0') {
        break;
      }
      add_sentence_text(text, start, true);
      start = ++end;
    }
    if (*start != '\0') {
      end = strrchr(start, '\n');
      if (end) {
        *end = '\0';
      }
      trim_spaces(&start);
      if (*start == '\0') {
        break;
      }
      add_sentence_text(text, start, false);
    }
  }
}

/*
 * Вывод каждого предложения с новой строки
 **/
void print_text(Text *text) {
  for (size_t i = 0; i < text->count; i++) {
    printf("%s\n", text->tsentence[i].ssentence);
  }
}

/*
 * Очищение памяти
 * */
void free_text(Text *text) {
  for (size_t i = 0; i < text->count; i++) {
    free(text->tsentence[i].ssentence);
  }
  free(text->tsentence);
}

int main() {
  Text text;
  init_text(&text);
  write_text(&text);
  print_text(&text);
  free_text(&text);

  return 0;
}
