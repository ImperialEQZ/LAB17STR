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
#define English_Alphabet 26

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

int getWord(char *beginSearch, WordDescriptor *word);

void digitToStart(WordDescriptor word);

void digitsToStart(char *s);

void replaceDigitsToNumOfSpaces(char *s);

void replace(char *source, char *w1, char *w2);

int areWordsEqual(WordDescriptor w1, WordDescriptor w2);

bool areWordsOrdered(char *s);

void getBagOfWords(BagOfWords *bag, char *s);

char *Copy_Reverse(char *rbegin_source, const char *rend_source, char
*beginDestination);

void reverseWordsBag(char *s);

int isWordInBagOfWords(WordDescriptor word, BagOfWords bag);

BagOfWords createBagOfWordsFromString(char *s);

void wordDescriptorToString(WordDescriptor word, char *destination);

int isWordPalindrome(char *begin, char *end);

size_t howManyWordsPalindromes(char *s);

void task_9(char *str1, char *str2, char *res);

WordBeforeFirstWordWithAReturnCode getWordBeforeFirstWordWithA(char *s, WordDescriptor *w);

WordDescriptor task_12(char *s1, char *s2);

int DuplicateWords(char *s);

void Str_parse(char *str, BagOfWords *bag);

int compareWords(char *word1, char *word2);

int task_14(BagOfWords *bag);

char *task_15(char *str);

int ThisWordInBag(BagOfWords bag, WordDescriptor word);

int isPalindrome(char *s);

void removePalindromes(char *str);

void task_18(char *s1, char *s2);

int task19(const char *word, const char *str);

#endif //LAB17STR_STRING__H
