#include "string_.h"
#include "string_.c"


#define ASSERT_STRING(expected, got) assertString(expected, got, \
__FILE__, __FUNCTION__, __LINE__)

char _stringBuffer[MAX_STRING_SIZE + 1];

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
//удаляет повторяющиеся символы
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

int getWord(char *beginSearch, WordDescriptor *word) {
    word->begin = findNonSpace(beginSearch);
    if (*word->begin == '\0')
        return 0;
    word->end = findSpace(word->begin);
    return 1;
}

void digitToStart(WordDescriptor word) {
    char *endStringBuffer = copy(word.begin, word.end,
                                 _stringBuffer);
    char *recPosition = copyIfReverse(endStringBuffer - 1,
                                      _stringBuffer - 1,
                                      word.begin, isdigit);
    copyIf(_stringBuffer, endStringBuffer, recPosition, isalpha);
}

void digitsToStart(char *s) {
    char *beginSearch = s;
    WordDescriptor word;
    while (getWord(beginSearch, &word)) {

        digitToStart(word);
        beginSearch = word.end;
    }
}


void test_digitsToStart() {
    char str[] = "9AbdSH7H6j";
    char exp[] = "679AbdSHHj";
    digitsToStart(str);

    ASSERT_STRING(exp, str);

    char str1[] = "";
    char exp1[] = "";
    digitsToStart(str1);

    ASSERT_STRING(exp1, str1);

    char str2[] = "1b2im_1b2im3_b3am5_b34am";
    char exp2[] = "435332121bimbimbambam";
    digitsToStart(str2);

    ASSERT_STRING(exp2, str2);
}


void replaceDigitsToNumOfSpaces(char *s) {
    copy(s, getEndOfString(s), _stringBuffer);
    char *recPtr = s;
    char *readPtr = _stringBuffer;
    for (int i = 0; i < strlen(_stringBuffer); ++i) {
        if (strlen(s) >= MAX_STRING_SIZE) {
            fprintf(stderr, "Out of MAX_STRING_SIZE");
            exit(1);
        }
        if (!isdigit(_stringBuffer[i])) {
            *recPtr = *readPtr;
            recPtr++;
            readPtr++;
        } else {
            int counter = _stringBuffer[i] - '0';
            for (int j = counter; j > 0; --j) {
                *recPtr = ' ';
                recPtr++;
            }
            readPtr++;
        }
    }
    _stringBuffer[0] = '\0';
    *recPtr = '\0';
}


void test_replaceDigitsToNumOfSpaces() {
    char str[MAX_STRING_SIZE] = "";
    char exp[] = "";
    replaceDigitsToNumOfSpaces(str);

    ASSERT_STRING(exp, str);

    char str1[MAX_STRING_SIZE] = "Bo4bR";
    char exp1[] = "Bo    bR";//4 пробела
    replaceDigitsToNumOfSpaces(str1);

    ASSERT_STRING(exp1, str1);

    char str2[MAX_STRING_SIZE] = "123";
    char exp2[] = "      ";//1+2+3=6 пробелов
    replaceDigitsToNumOfSpaces(str2);

    ASSERT_STRING(exp2, str2);

    char str3[MAX_STRING_SIZE] = "sentence without numbers";
    char exp3[] = "sentence without numbers";
    replaceDigitsToNumOfSpaces(str3);

    ASSERT_STRING(exp3, str3);
}


int main(){
    //test_removeExtraSpaces();
    //test_removeAdjacentEqualLetters();
    //test_digitsToStart();
    test_replaceDigitsToNumOfSpaces();
}
