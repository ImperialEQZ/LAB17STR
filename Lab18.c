#include "string_.h"
#include "string_.c"


#define ASSERT_STRING(expected, got) assertString(expected, got, \
__FILE__, __FUNCTION__, __LINE__)

char *getEndOfString(char *begin) {
    char *end = begin;
    while (*end != '\0')
        end++;

    return end;
}

void removeNonLetters(char *s) {
    char *endSource = getEndOfString(s);
    char *destination = copyIf(s, endSource, s, isgraph);
    *destination = '\0';
}

void assertString(const char *expected, char *got,
                  char const *fileName, char const *funcName,
                  int line) {
    if (strcmp(expected, got)) {
        fprintf(stderr, "File %s\n", fileName);
        fprintf(stderr, "%s - failed on line %d\n", funcName, line);
        fprintf(stderr, "Expected: \"%s\"\n", expected);
        fprintf(stderr, "Got: \"%s\"\n\n", got);
    } else
        fprintf(stderr, "%s - You're a cool bro.\n", funcName);
}
//Удаление лишних пробелов (оставляет один пробел)
void removeExtraSpaces(char *s) {
    int i, j;
    for (i = 0, j = 0; s[i]; i++) {
        if (s[i] != ' ' || (i > 0 && s[i - 1] != ' ')) {
            s[j++] = s[i];
        }
    }

    s[j] = '\0';
}
//удаление повторяющихся символов
void removeAdjacentEqualLetters(char *s) {
    if ((s == NULL || strlen(s) == 0))
        return;
    int i, j;
    for (i = 0, j = 0; s[i] != '\0'; i++) {
        if (s[i] != s[i + 1]) {
            s[j] = s[i];
            j++;
        }
    }

    s[j] = '\0';
}

void test_removeExtraSpaces() {
    char str[] = "What    time    is it   , bro      ?";
    char exp[] = "What time is it , bro ?";
    removeExtraSpaces(str);

    ASSERT_STRING(exp, str);

    char str1[] = "                        ";
    char exp1[] = "";
    removeExtraSpaces(str1);

    ASSERT_STRING(exp1, str1);

    char str2[] = "sentence without unnecessary spaces";
    char exp2[] = "sentence without unnecessary spaces";
    removeExtraSpaces(str2);

    ASSERT_STRING(exp2, str2);
}
//удаляет повторяющиеся символы
void test_removeAdjacentEqualLetters() {
    char str[] = "88005553535";
    char exp[] = "8053535";
    removeAdjacentEqualLetters(str);

    ASSERT_STRING(exp, str);

    char str1[] = "GGGGGggggg";
    char exp1[] = "Gg";
    removeAdjacentEqualLetters(str1);

    ASSERT_STRING(exp1, str1);

    char str2[] = "";
    char exp2[] = "";
    removeAdjacentEqualLetters(str2);

    ASSERT_STRING(exp2, str2);

    char str3[] = "Walter";
    char exp3[] = "Walter";
    removeAdjacentEqualLetters(str3);

    ASSERT_STRING(exp3, str3);
}

int main(){
    //test_removeExtraSpaces();
    test_removeAdjacentEqualLetters();
}
