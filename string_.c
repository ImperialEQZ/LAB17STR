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
void test() {
    test_findStrLen();
    test_find();
}

int main() {
    test();
}