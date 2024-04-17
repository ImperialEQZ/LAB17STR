#ifndef LAB17STR_STRING__H
#define LAB17STR_STRING__H
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <memory.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>

#define MAX_STRING_SIZE 100
#define MAX_N_WORDS_IN_STRING 100
#define MAX_WORD_SIZE 20

typedef struct WordDescriptor {
    char *begin; // позиция начала слова
    char *end; // позиция первого символа, после последнего символа слова
} WordDescriptor;

typedef struct BagOfWords {
    WordDescriptor words[MAX_N_WORDS_IN_STRING];
    size_t size;
} BagOfWords;

BagOfWords _bag;
BagOfWords _bag2;


typedef enum WordBeforeFirstWordWithAReturnCode {
    FIRST_WORD_WITH_A,
    NOT_FOUND_A_WORD_WITH_A,
    WORD_FOUND,
    EMPTY_STRING
} WordBeforeFirstWordWithAReturnCode;

size_t findStrLen(const char *start);

char* find(char *begin, char *end, int ch);

char* findNonSpace(char *begin);

char *findSpace(char *begin);

char *findNonSpaceReverse(char *rbegin, const char *rend);

char *findSpaceReverse(char *rbegin, const char *rend);

char *copy(const char *beginSource,
           const char *endSource,
           char*beginDestination);

char *copyIf(char *beginSource,
             const char *endSource,
             char*beginDestination,
             int (*f)(int));

char* copyIfReverse(char *rbeginSource,
                    const char *rendSource,
                    char *beginDestination,
                    int (*f)(int));

char *getEndOfString(char *begin);

void removeNonLetters(char *s);

void assertString(const char *expected, char *got,
                  char const *fileName, char const *funcName,
                  int line);

void removeExtraSpaces(char *s);

void removeAdjacentEqualLetters(char *s);

#endif //LAB17STR_STRING__H
