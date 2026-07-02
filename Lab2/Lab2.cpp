#include <cstring>
#include <iostream>
using namespace std;

void removeDigits(char *array);

int main() {
    cout << "1." << endl;
    char test1[] = "1a3er";
    cout << "Original: " << test1 << endl;
    removeDigits(test1);
    cout << "Remove digits: " << test1 << endl;
    // Verify that all digits are removed and non-digit order is preserved.
    if(strcmp(test1, "aer") == 0) {
        cout << "PASS";
    } else {
        cout << "FAIL";
    }
    cout << endl;
    cout << "2." << endl;
    char test2[] = "1576843";
    cout << "Original: " << test2 << endl;
    removeDigits(test2);
    cout << "Remove digits: " << test2 << endl;
    // A string containing only digits should become an empty string.
    if(strcmp(test2, "") == 0) {
        cout << "PASS";
    } else {
        cout << "FAIL";
    }
    cout << endl;
    cout << "3." << endl;
    char test3[] = "Hello!";
    cout << "Original: " << test3 << endl;
    removeDigits(test3);
    cout << "Remove digits: " << test3 << endl;
    if(strcmp(test3, "Hello!") == 0) {
        cout << "PASS";
    } else {
        cout << "FAIL";
    }
    return 0;
}

void removeDigits(char *array) {
    char *p = array;
    char *sp = array;
    while(*p != '\0') {
        if(*p > '9' || *p < '0') {
            *sp = *p;
            sp++;
        }
        p++;
    }
    *sp = '\0';
}