#include<stdio.h>

int main()
{
    char str[200], newstr[200];
    int i, j = 0;

    printf("Enter a sentence: ");
    fgets(str, sizeof(str), stdin);

    for(i = 0; str[i] != '\0'; i++)
    {
        // copy current character
        newstr[j] = str[i];

        // check for multiple spaces
        if(str[i] == ' ' && str[i+1] == ' ')
        {
            continue;
        }

        j++;
    }

    newstr[j] = '\0';

    printf("String after removing extra spaces:\n");
    printf("%s", newstr);

    return 0;
}