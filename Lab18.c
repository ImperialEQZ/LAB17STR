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


void replace(char *source, char *w1, char *w2) {
    size_t size_w1 = strlen(w1);
    size_t size_w2 = strlen(w2);
    WordDescriptor word1 = {w1, w1 + size_w1};
    WordDescriptor word2 = {w2, w2 + size_w2};
    char *readPtr, *recPtr;
    if (size_w1 >= size_w2) {
        readPtr = source;
        recPtr = source;
    } else {
        copy(source, getEndOfString(source), _stringBuffer);
        readPtr = _stringBuffer;
        recPtr = source;
    }
    while (*readPtr != '\0') {
        if (memcmp(readPtr, w1, size_w1) == 0) {
            for (int i = 0; i < size_w2; i++) {
                *recPtr = w2[i];
                recPtr++;
            }

            readPtr += size_w1;
        } else {
            *recPtr = *readPtr;
            readPtr++;
            recPtr++;
        }
    }
    *recPtr = '\0';
}

void test_replace() {
    char str[MAX_STRING_SIZE] = " ";
    char w1[] = " ";
    char w2[] = "background-image";
    replace(str, w1, w2);
    char exp[MAX_STRING_SIZE] = "background-image";

    ASSERT_STRING(exp, str);

    char str1[MAX_STRING_SIZE] = "I love water";
    char w1_1[] = "water";
    char w2_1[] = "beer";
    replace(str1, w1_1, w2_1);
    char exp1[MAX_STRING_SIZE] = "I love beer";

    ASSERT_STRING(exp1, str1);

    char str2[MAX_STRING_SIZE] = "";
    char w1_2[] = "";
    char w2_2[] = "";
    replace(str2, w1_2, w2_2);
    char exp2[MAX_STRING_SIZE] = "";

    ASSERT_STRING(exp2, str2);

    char str3[MAX_STRING_SIZE] = "SeNteNcE CAPs";
    char w1_3[] = "SeNteNcE CAPs";
    char w2_3[] = "Sentence caps";
    replace(str3, w1_3, w2_3);
    char exp3[MAX_STRING_SIZE] = "Sentence caps";

    ASSERT_STRING(exp3, str3);
}
//Два слова одинаковые
int areWordsEqual(WordDescriptor w1, WordDescriptor w2) {
    char *ptr1 = w1.begin;
    char *ptr2 = w2.begin;
    while (ptr1 <= w1.end && ptr2 <= w2.end) {
        if (*ptr1 != *ptr2)
            return 0;

        ptr1++;
        ptr2++;
    }

    if (ptr1 > w1.end && ptr2 > w2.end)
        return 1;
    else
        return 0;
}

void test_areWordsEqual() {
    WordDescriptor w1 = {"bimbim", "bambam"};
    WordDescriptor w2 = {"bimbim", "bambam"};

    if(areWordsEqual(w1, w2)) {
        printf("You're a cool bro\n");
    } else {
        printf("You failed bro\n");
    }

    WordDescriptor w1_1 = {"", ""};
    WordDescriptor w2_1 = {"", ""};

    if(areWordsEqual(w1_1, w2_1)) {
        printf("You're a cool bro\n");
    } else {
        printf("You failed bro\n");
    }

    WordDescriptor w1_2 = {"777", "666"};
    WordDescriptor w2_2 = {"777", "666"};

    if(areWordsEqual(w1_2, w2_2)) {
        printf("You're a cool bro\n");
    } else {
        printf("You failed bro\n");
    }
}
//Определяет, упорядочены ли лексикографически слова данного предложения №6 (b)
bool areWordsOrdered(char *s) {
    WordDescriptor word1;
    WordDescriptor word2;
    if (getWord(s, &word1)) {
        word2 = word1;
        while (getWord(s, &word1)) {
            if (areWordsEqual(word1, word2) == 0)
                return false;
            word2 = word1;
            s = word1.end;
        }
        return true;

    } else
        return true;
}

void test_areWordsOrdered() {
    char s[] = "abc";
    assert(areWordsOrdered(s) == true);

    char s2[] = "b a c";
    assert(areWordsOrdered(s2) == false);

    char s3[] = "a";
    assert(areWordsOrdered(s3) == true);

    char s4[] = "";
    assert(areWordsOrdered(s4) == true);

    char s5[] = "aa";
    assert(areWordsOrdered(s5) == true);

    char s6[] = "a!b?c.";
    assert(areWordsOrdered(s6) == true);
}


int main() {
    //test_removeExtraSpaces();
    //test_removeAdjacentEqualLetters();
    //test_digitsToStart();
    //test_replaceDigitsToNumOfSpaces();
    //test_replace();
    //test_areWordsEqual();
    test_areWordsOrdered();
}
