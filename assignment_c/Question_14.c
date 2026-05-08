#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char str[200];
    int letters[26] = {0};
    int i;

    printf("Enter a sentence: ");
    fgets(str, sizeof(str), stdin);

    for (i = 0; str[i] != '\0'; i++) {
        char ch = str[i];
        if (isalpha(ch)) {
            ch = tolower(ch);
            letters[ch - 'a'] = 1;
        }
    }

    int pangram = 1;
    for (i = 0; i < 26; i++) {
        if (letters[i] == 0) {
            pangram = 0;
            break;
        }
    }

    if (pangram) {
        printf("The string is a pangram.\n");
    } else {
        printf("The string is NOT a pangram.\n");
    }

    return 0;
}
