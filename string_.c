#include "string_.h"

size_t findStrLen(const char *start){
    char *end = start;
    while (*end != '\0')
        end++;
    return end - start;
}

void test_findStrLen() {
    char *str = "Hello";
    char *str1 = "Boss";
    char *str2 = "";
    assert(findStrLen(str) == 5);
    assert(findStrLen(str1) == 4);
    assert(findStrLen(str2) == 0);
}

void test() {
    test_findStrLen();
}

int main() {
    test();
}