#include<stdio.h>

int main()
{
    int n, temp, rem, i = 0, j;
    char str[20], ch;

    printf("Enter a number: ");
    scanf("%d", &n);

    temp = n;

    // for negative number
    if(n < 0)
    {
        temp = -temp;
    }

    // converting number to string
    while(temp > 0)
    {
        rem = temp % 10;
        str[i] = rem + '0';
        i++;
        temp = temp / 10;
    }

    // add negative sign
    if(n < 0)
    {
        str[i] = '-';
        i++;
    }

    str[i] = '\0';

    // reverse the string
    for(j = 0; j < i/2; j++)
    {
        ch = str[j];
        str[j] = str[i-j-1];
        str[i-j-1] = ch;
    }

    printf("String is: %s", str);

    return 0;
}