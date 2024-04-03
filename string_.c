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

void test_findStrLen() {
    char *str = "Hello";
    char *str1 = "Boss";
    char *str2 = "";
    assert(findStrLen(str) == 5);
    assert(findStrLen(str1) == 4);
    assert(findStrLen(str2) == 0);
}

void test_find() {
    char *str = "12345";
    assert(find(&str[0], &str[9], '1') == &str[0]);
    assert(find(&str[0], &str[9], '0') == &str[9]);
    assert(find(&str[0], &str[9], '2') == &str[1]);
}

void test_findNonSpace() {
    char *str = " 8642BOBR";
    char *str2 = "14 88";
    assert(findNonSpace(str) == &str[1]);
    assert(*findNonSpace(str2) == '1');
}

void test_findSpace() {
    char *str = "123456789";
    char *str1 = "\tBOBR\tr31";
    char *str2 = "123 123";
    assert(*findSpace(str) == '\0');//нет пробелов
    assert(*findSpace(str1) == '\t');//проверка с символом табуляции
    assert(*findSpace(str2) == ' ');//"просто пробел"
}

void test() {
    //test_findStrLen();
    //test_find();
    //test_findNonSpace();
    test_findSpace();
}

int main() {
    test();
}