#include "../include/text.h"
#include <stdlib.h>
#include <wchar.h>
/*
 * Инцализация текста
 * */
void init_text(Text *text) {
  text->tcapacity = 4;
  text->count = 0;
  text->tsentence = (Sentence *)malloc(sizeof(Sentence) * text->tcapacity);
  if (!text->tsentence) {
    fprintf(stderr, "Error mammory allocation");
    exit(EXIT_FAILURE);
  }
  text->tsentence[0].ssentence = malloc(MAX_SIZE * sizeof(wchar_t));
  if (!text->tsentence[0].ssentence) {
    fprintf(stderr, "Error mammory allocation");
    exit(EXIT_FAILURE);
  }
  text->tsentence[0].ssentence[0] = '\0';
  text->tsentence[0].scapacity = MAX_SIZE - 1;
}
/*
 * Увеличение количество допустимых предложений
 * */
void increase_text_size(Text *text) {
  text->tcapacity *= 2;
  Sentence *t = realloc(text->tsentence, sizeof(Sentence) * text->tcapacity);
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
  tsentence->scapacity = tsentence->scapacity + len;
  wchar_t *s = realloc(tsentence->ssentence,
                       sizeof(wchar_t) * (tsentence->scapacity + 1));
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
  if (text->count == (text->tcapacity - 1)) {
    increase_text_size(text);
  }
  text->count++;
  text->tsentence[text->count].scapacity = MAX_SIZE - 1;
  text->tsentence[text->count].ssentence = malloc(MAX_SIZE * sizeof(wchar_t));
  if (!text->tsentence[text->count].ssentence) {
    fprintf(stderr, "Error mammory allocation");
    exit(EXIT_FAILURE);
  }
  text->tsentence[text->count].ssentence[0] = '\0';
}
/*
 * Добавление предложения в текст
 * */
void add_sentence_text(Text *text, wchar_t *buffer, bool end) {
  if (text->count == (text->tcapacity - 1)) {
    increase_text_size(text);
  }
  wchar_t *s = malloc(sizeof(wchar_t) * (wcslen(buffer) + (end ? 2 : 1)));
  if (!s) {
    fprintf(stderr, "Error memory allocation");
    exit(EXIT_FAILURE);
  }
  /* Для сокращения записи*/
  Sentence *tsentence = &text->tsentence[text->count];
  if (end) {
    swprintf(s, wcslen(buffer) + 2, L"%ls.", buffer);
  } else {
    swprintf(s, wcslen(buffer) + 1, L"%ls", buffer);
  }
  if ((tsentence->scapacity - wcslen(tsentence->ssentence)) < wcslen(s)) {
    increase_sentence_size(tsentence, wcslen(s));
  }
  wcscat(tsentence->ssentence, s);
  if (end) {
    init_next_sentence(text);
  }
  free(s);
}
