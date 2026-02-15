#ifndef TEXT_H
#define TEXT_H
#define MAX_SIZE 256
#include <stdbool.h>
#include <wchar.h>
/*
 * Структура предожения
 * */
typedef struct Sentence {
  wchar_t *ssentence; // предожение
  size_t scapacity;   // размер предложения
} Sentence;
/*
 * Структура текста
 * */
typedef struct Text {
  Sentence *tsentence; // массив предложений
  size_t tcapacity;    // размер массива предложений
  size_t count;        // количество предложений
} Text;

/* Инцализация текста*/
void init_text(Text *text);
/* Увеличение количество допустимых предложений*/
void increase_text_size(Text *text);
/* Увеличение размера предложения*/
void increase_sentence_size(Sentence *tsentence, size_t len);
/* Инцализация следующего предложения*/
void init_next_sentence(Text *text);
/* Добавление предожения в теккст*/
void add_sentence_text(Text *text, wchar_t *buffer, bool end);
/* Чтение предожения*/
void write_sentence(Text *text);
/* Стерание пробелов и табов в начале предложения*/
void pass_start(wchar_t **start);
#endif
