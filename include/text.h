#ifndef TEXT_H
#define TEXT_H
#define MAX_SIZE 256
#include <stdbool.h>
#include <wchar.h>
typedef struct Sentence {
  wchar_t *ssentence;
  size_t scapacity;
} Sentence;

typedef struct Text {
  Sentence *tsentence;
  size_t tcapacity;
  size_t count;
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
#endif
