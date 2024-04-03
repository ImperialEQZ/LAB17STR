//
// Created by Александр on 02.04.2024.
//
#ifndef LAB17STR_STRING__H
#define LAB17STR_STRING__H
#include <stdio.h>
#include <ctype.h>
#include <memory.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>

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
#endif //LAB17STR_STRING__H
