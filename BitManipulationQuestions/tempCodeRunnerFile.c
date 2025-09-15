void printBin(int n)
{

    for (int i = 31; i >= 0; i--)
    {

        if (n & (1 << i))
            printf("1");
        else
            printf("0");
    }
}