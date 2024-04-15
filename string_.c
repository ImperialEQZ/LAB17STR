#include "string_.h"
//поиск длины строки
size_t findStrLen(const char *start){
    char *end = start;
    while (*end != '\0')
        end++;
    return end - start;
}
/*возвращает указатель
на первый элемент с кодом ch, расположенным на ленте памяти между
адресами begin и end не включая end*/
char* find(char *begin, char *end, int ch) {
    while (begin != end && *begin != ch)
        begin++;
    return begin;
}
/*возвращает указатель на первый
символ, отличный от пробельных*/
char* findNonSpace(char *begin) {
    while (*begin != '\0' && isspace(*begin)) {
        begin++;
    }
    return begin;
}
/*возвращает указатель на первый пробельный символ,
* расположенный на ленте памяти начиная с адреса begin
или на первый ноль-символ.*/
char *findSpace(char *begin) {
    while (*begin != '\0' && !isspace(*begin)) {
        begin++;
    }
    return begin;
}
/*возвращает указатель на первый справа символ, отличный от пробельных,
расположенный на ленте памяти, начиная с rbegin (последний символ
строки, за которым следует ноль-символ) и заканчивая rend (адрес символа перед началом строки).
 Если символ не найден, возвращается адрес rend*/
char *findNonSpaceReverse(char *rbegin, const char *rend) {
    while (rbegin >= rend && isspace(*rbegin))
        rbegin--;
    return rbegin;
}
/*возвращает указатель на первый пробельный символ справа,
 * расположенный на ленте памяти, начиная с rbegin и заканчивая rend.
 * Если символ не найден, возвращается адрес rend.*/
char *findSpaceReverse(char *rbegin, const char *rend) {
    while (rbegin >= rend && !isspace(*rbegin))
        rbegin--;
    return rbegin;
}
/*записывает по адресу beginDestination
фрагмент памяти, начиная с адреса beginSource до endSource.
Возвращает указатель на следующий свободный фрагмент памяти в
destination*/
char *copy(const char *beginSource,
           const char *endSource,
           char*beginDestination) {
    size_t size = endSource - beginSource;

    memcpy(beginDestination, beginSource, size);

    *(beginDestination + size) = '\0';

    return beginDestination + size;
}
/*записывает по адресу
beginDestination элементы из фрагмента памяти начиная с beginSource
заканчивая endSource, удовлетворяющие функции-предикату f. Функция
возвращает указатель на следующий свободный для записи фрагмент в
памяти*/
char *copyIf(char *beginSource,
             const char *endSource,
             char*beginDestination,
             int (*f)(int)) {

    while (beginSource != endSource) {
        if (f(*beginSource)) {
            *beginDestination = *beginSource;
            beginDestination++;
        }
        beginSource++;
    }
    *beginDestination = '\0';

    return beginDestination;
}
/*записывает по адресу
beginDestination элементы из фрагмента памяти начиная с rbeginSource
заканчивая rendSource, удовлетворяющие функции-предикату f. Функция возвращает значение
 beginDestination по окончанию работы функции.*/
char* copyIfReverse(char *rbeginSource,
                    const char *rendSource,
                    char *beginDestination,
                    int (*f)(int)) {
    while (rbeginSource != rendSource) {
        if (f(*(rbeginSource - 1))) {
            *beginDestination = *(rbeginSource - 1);
            beginDestination++;
        }
        rbeginSource--;
    }
    beginDestination[*(rbeginSource - 1)] = '\0';

    return beginDestination;
}
void test_findStrLen() {
    char *str = "Hello";
    char *str1 = "Boss";
    char *str2 = "";
    char *str3 = "testing";
    assert(findStrLen(str) == 5);
    assert(findStrLen(str1) == 4);
    assert(findStrLen(str2) == 0);
    assert(findStrLen(str3) == 7);//новый тест
}

void test_find() {
    char *str = "12345";
    char *str2 = "user cool";
    assert(find(&str[0], &str[9], '1') == &str[0]);
    assert(find(&str[0], &str[9], '0') == &str[9]);
    assert(find(&str[0], &str[9], '2') == &str[1]);
    assert(find(&str2[0], &str2[8], ' ') == &str2[4]);//новый тест
}

void test_findNonSpace() {
    char *str = " 8642BOBR";
    char *str2 = "14 88";
    char *str3 = "     ";//только пробелы внутри
    assert(findNonSpace(str) == &str[1]);
    assert(*findNonSpace(str2) == '1');
    assert(*findNonSpace(str3) == '\0');//новый тест
}

void test_findSpace() {
    char *str = "123456789";
    char *str1 = "\tBOBR\tr31";
    char *str2 = "123 123";
    char *str3 = "12 3 4 5";
    assert(*findSpace(str) == '\0');//нет пробелов
    assert(*findSpace(str1) == '\t');//проверка с символом табуляции
    assert(*findSpace(str2) == ' ');//"просто пробел"
    assert(*findSpace(str3) == str3[2]);//новый тест
}

void test_findNonSpaceReverse() {
    char *str = " 1234567890";
    char *str1 = "\t \t123";
    char *str2 = "123 123\t";
    char *str3 = "\t\t\t";
    char *str4 = "123456789\t";// "9" на 8 позиции
    assert(*findNonSpaceReverse(&str[10], &str[0]) == '0');
    assert(*findNonSpaceReverse(&str1[9], &str1[0]) == '3');
    assert(*findNonSpaceReverse(&str2[7], &str2[0]) == '3');
    assert(*findNonSpaceReverse(&str3[2], &str3[0]) == '\0');
    assert(*findNonSpaceReverse(&str4[9], &str4[0]) == str4[8]);//новый тест
}

void test_findSpaceReverse() {
    char *str = "123456789";
    char *str1 = "\tBOBR\tr31";
    char *str2 = "AB CD";//пример из пособия
    char *str3 = "ABCDE";//пример из пособия
    char *str4 = "\t\t\t";//только символ табуляции
    assert(*findSpaceReverse(&str[8], &str[0]) == '\0');
    assert(findSpaceReverse(&str1[8], &str1[0]) == &str1[5]);
    assert(findSpaceReverse(&str2[4], &str2[0]) == &str2[2]);
    assert(findSpaceReverse(&str3[4], &str3[0]) == &str3[-1]);
    assert(findSpaceReverse(&str4[2], &str4[0]) == &str4[2]);//новый тест
}

void test_copy() {
    char *str = "12345";//пример с пособия
    char *str1 = "cool\tbro";//пример с пробелом и буквы

    char *str_copied[5];//5, т.к /0
    char *str1_copied[8];//8, т.к /0

    copy(&str[0], &str[5], (char *) str_copied);
    copy(&str1[0], &str1[8], (char *) str1_copied);

    assert(!strcmp(str, (const char *) str_copied));
    assert(!strcmp(str1, (const char *) str1_copied));//новый тест
}

int isLetter(int c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

void test_copyIf(){
    char str[] = "Hello123World456";
    char str2[] = "a1b23456c";
    char result1[20];
    char result2[20];

    copyIf(str, str + 14, result1, isLetter);
    copyIf(str2, str2 + 9, result2, isLetter);

    printf("%s\n", result1);//Вывод HelloWorld без пробела
    printf("%s\n", result2);//Вывод abc без пробела, новый тест
}

void test_copyIfReverse(){
    char *str = "Hello123World456";
    char str2[] = "a1b23456c8d";
    char result1[20];
    char result2[20];

    copyIfReverse(str+14, str, result1, isLetter);
    copyIfReverse(str2+11, str2, result2, isLetter);

    printf("%s\n", result1);//вывод dlroWolleH
    printf("%s\n", result2);//вывод dcba

}
void test() {
    //test_findStrLen();
    //test_find();
    //test_findNonSpace();
    //test_findSpace();
    //test_findNonSpaceReverse();
    //test_findSpaceReverse();
    //test_copy();
    //test_copyIf();
    //test_copyIfReverse();
}

/*int main() {
    test();
}*/
