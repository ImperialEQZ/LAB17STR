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

void getBagOfWords(BagOfWords *bag, char *s) {
    WordDescriptor word;
    bag->size = 0;
    while (getWord(s, &word)) {
        bag->words[bag->size] = word;
        bag->size++;
        s = word.end;
    }
}

void test_getBagOfWords() {
//Тестирование, основанное на примере из пособия
    BagOfWords bag;
    bag.size = 0;
    char s[] = "a bc  d";

    getBagOfWords(&bag,s);

    for (int i = 0; i < bag.size; i++) {
        printf("letter %d - %.*s\n", i+1, (int)(bag.words[i].end - bag.words[i].begin), bag.words[i].begin);
    }

    return;
}
//вспомогательная функция, не такая как char* copyIfReverse:
char *Copy_Reverse(char *rbegin_source, const char *rend_source, char
*beginDestination) {
    while (rbegin_source != rend_source)
        (*beginDestination++) = *rbegin_source--;

    return beginDestination;
}


void reverseWordsBag(char *s) {
    *copy(s, getEndOfString(s), _stringBuffer) = '\0';
    getBagOfWords(&_bag, _stringBuffer);
    char *copy_str = s;
    for (int i = 0; i < _bag.size; i++) {
        copy_str = Copy_Reverse(_bag.words[i].end - 1, _bag.words[i].begin -
                                                   1, copy_str);
        *copy_str++ = ' ';
    }
    if (copy_str != s)
        copy_str--;

    *copy_str = '\0';
}
//для 12 задания
int isWordInBagOfWords(WordDescriptor word, BagOfWords bag) {
    for (size_t i = 0; i < bag.size; ++i) {
        if (strncmp(word.begin, bag.words[i].begin, word.end - word.begin) == 0)
            return 1;
    }

    return 0;
}
//для 12 задания
BagOfWords createBagOfWordsFromString(char *s) {
    BagOfWords bag;
    bag.size = 0;

    char *wordBegin = s;
    for (; *s; s++) {
        if (isspace(*s)) {
            if (s > wordBegin) {
                bag.words[bag.size].begin = wordBegin;
                bag.words[bag.size].end = s;
                bag.size++;
            }

            wordBegin = s + 1;
        }
    }

    if (s > wordBegin) {
        bag.words[bag.size].begin = wordBegin;
        bag.words[bag.size].end = s;
        bag.size++;
    }

    return bag;
}
//для 12 задания
void wordDescriptorToString(WordDescriptor word, char *destination) {
    int length = word.end - word.begin;
    strncpy(destination, word.begin, length);
    destination[length] = '\0';
}

void test_reverseWordsBag() {
    char s[MAX_STRING_SIZE] = "";
    reverseWordsBag(s);

    ASSERT_STRING("", s);

    char s1[MAX_STRING_SIZE] = "Sasha";
    reverseWordsBag(s1);

    ASSERT_STRING("ahsaS", s1);

    char s2[MAX_STRING_SIZE] = "ABCD";
    reverseWordsBag(s2);

    ASSERT_STRING("DCBA", s2);

    char s3[MAX_STRING_SIZE] = "123";
    reverseWordsBag(s3);

    ASSERT_STRING("321", s3);
}
//Вспомогательная функция на проверку слова-палиндрома
int isWordPalindrome(char *begin, char *end) {
    while (begin < end) {
//Пропуск пробелов и знаков пунктуации
        if (!isalpha(*begin)) {
            begin++;
        } else if (!isalpha(*end)) {
            end--;
        } else {
//Сравниваю символы
            if (tolower(*begin) != tolower(*end)) {
                return 0; // Не палиндром
            }
            begin++;
            end--;
        }
    }
    return 1; // Палиндром
}

size_t howManyWordsPalindromes(char *s) {
    char *end_str = getEndOfString(s);
    char *beginSearch = findNonSpace(s);
    int countPalindromes = 0;
    char *position_first_comma = find(beginSearch, end_str, ',');
    int last_comma = *position_first_comma == '\0' && end_str - beginSearch != 0;

    while (*position_first_comma != '\0' || last_comma) {
        beginSearch = findNonSpace(beginSearch);
        countPalindromes += isWordPalindrome(beginSearch, position_first_comma);
        beginSearch = position_first_comma + 1;
        if (last_comma)
            break;

        position_first_comma = find(beginSearch, end_str, ',');
        last_comma = *position_first_comma == '\0';
    }

    return countPalindromes;
}

void test_howManyWordsPalindromes() {
    char s[] = "";
    assert(howManyWordsPalindromes(s) == 0);

    char s1[] = "ANNA";
    assert(howManyWordsPalindromes(s1) == 1);

    char s2[] = "ANNA, level";
    assert(howManyWordsPalindromes(s2) == 2);

    char s3[] = "p";
    assert(howManyWordsPalindromes(s3) == 1);

    char s4[] = "ANNA, Sasha";
    assert(howManyWordsPalindromes(s4) == 1);

    char s5[] = "biMBIMbamBAAAAM";
    assert(howManyWordsPalindromes(s5) == 0);
}

void task_9(char *str1, char *str2, char *res) {
    char *word1 = strtok(str1, " ");
    char *word2 = strtok(str2, " ");

    while (word1 != NULL || word2 != NULL) {
        if (word1 != NULL) {
            strcat(res, word1);
            strcat(res, " ");
            word1 = strtok(NULL, " ");
        }
        if (word2 != NULL) {
            strcat(res, word2);
            strcat(res, " ");
            word2 = strtok(NULL, " ");
        }
    }
}

void test_task_9() {
    char s1[] = "1 3 5 7";
    char s2[] = "2 4 6 8";
    char result[200] = "";

    task_9(s1, s2, result);

    ASSERT_STRING("1 2 4 6 8 ", result);

    char s1_1[] = "Hi, how are you";
    char s2_1[] = "smart peter ";
    char result1[200] = "";

    task_9(s1_1, s2_1, result1);

    ASSERT_STRING("Hi, smart peter ", result1);

    char s1_2[] = "";
    char s2_2[] = "";
    char result2[200] = "";

    task_9(s1_2, s2_2, result2);

    ASSERT_STRING("", result2);
}

void task_11(char *s) {
    char *word = NULL;
    char *key = strtok(s, " ");

    while (key != NULL) {
        int foundA = 0;
        for (int i = 0; key[i] != '\0'; i++) {
            if (tolower(key[i]) == 'a') {
                foundA = 1;
                break;
            }
        }

        if (foundA) {
            if (word != NULL) {
                printf("%s\n", word);
                return;
            }
        } else {
            word = key;
        }

        key = strtok(NULL, " ");
    }
}
//как бы продолжение 11 номера
WordBeforeFirstWordWithAReturnCode getWordBeforeFirstWordWithA(char *s, WordDescriptor *w) {
    if (s == NULL || strlen(s) == 0)
        return EMPTY_STRING;

    char *wordBegin = NULL;
    char *wordEnd = NULL;
    char *key = strtok(s, " ");

    while (key != NULL) {
        int found_a = 0;
        for (int i = 0; key[i] != '\0'; i++)
            if (tolower(key[i]) == 'a') {
                found_a = 1;
                break;
            }

        if (found_a) {
            if (wordBegin != NULL) {
                w->begin = wordBegin;
                w->end = wordEnd;
                return WORD_FOUND;
            } else
                return FIRST_WORD_WITH_A;

        } else {
            wordBegin =key;
            wordEnd = key + strlen(key);
        }

        key = strtok(NULL, " ");
    }

    return NOT_FOUND_A_WORD_WITH_A;
}
//тест с пособия
void testAll_getWordBeforeFirstWordWithA() {
    WordDescriptor word;
    char s1[] = "";
    assert(getWordBeforeFirstWordWithA(s1, &word) == EMPTY_STRING);
    char s2[] = "ABC";
    assert(getWordBeforeFirstWordWithA(s2, &word) == FIRST_WORD_WITH_A);
    char s3[] = "BC A";
    assert(getWordBeforeFirstWordWithA(s3, &word) == WORD_FOUND);

    char s4[] = "B Q WE YR OW IUWR";
    assert(getWordBeforeFirstWordWithA(s4, &word) == NOT_FOUND_A_WORD_WITH_A);
}

WordDescriptor task_12(char *s1, char *s2) {
    BagOfWords bag = createBagOfWordsFromString(s2);
    WordDescriptor lastWord = {NULL, NULL};

    BagOfWords wordsInS1 = createBagOfWordsFromString(s1);
    for (size_t i = 0; i < wordsInS1.size; ++i) {
        if (isWordInBagOfWords(wordsInS1.words[i], bag))
            lastWord = wordsInS1.words[i];
    }

    return lastWord;
}

void test_task_12() {
    char s1[] = "";
    char s2[] = "";
    WordDescriptor word1 = task_12(s1, s2);
    char str1[MAX_WORD_SIZE];

    wordDescriptorToString(word1, str1);

    ASSERT_STRING("", str1);

    char s1_1[] = "bimbim bam bam";
    char s2_1[] = "bum bam";
    WordDescriptor word2 = task_12(s1_1, s2_1);
    char str2[MAX_WORD_SIZE];

    wordDescriptorToString(word2, str2);

    ASSERT_STRING("bam", str2);

    char s1_2[] = "123 456 789";
    char s2_2[] = "098 456 586";
    WordDescriptor word3 = task_12(s1_2, s2_2);
    char str3[MAX_WORD_SIZE];

    wordDescriptorToString(word3, str3);

    ASSERT_STRING("456", str3);
}

int DuplicateWords(char *s) {
    char *words[100];
    int wordCount = 0;

    char *word = strtok(s, " ");
    while (word != NULL) {
        words[wordCount] = word;
        wordCount++;
        word = strtok(NULL, " ");
    }

    for (int i = 0; i < wordCount; i++)
        for (int j = i + 1; j < wordCount; j++)
            if (strcmp(words[i], words[j]) == 0)
                return 1;

    return 0;
}

void test_hasDuplicateWords() {
    char str1[] = "";
    assert(DuplicateWords(str1) == false);

    char str2[] = "Hi friend";
    assert(DuplicateWords(str2) == false);

    char str3[] = "bim bim";
    assert(DuplicateWords(str3) == true);

    char str4[] = "123 321 123";
    assert(DuplicateWords(str4) == true);
}

int main() {
    //test_removeExtraSpaces();
    //test_removeAdjacentEqualLetters();
    //test_digitsToStart();
    //test_replaceDigitsToNumOfSpaces();
    //test_replace();
    //test_areWordsEqual();
    //test_areWordsOrdered();
    //test_getBagOfWords();
    //test_reverseWordsBag();
    //test_howManyWordsPalindromes();
    //test_task_9();
    //testAll_getWordBeforeFirstWordWithA();
    //test_task_12();
    test_hasDuplicateWords();
}
