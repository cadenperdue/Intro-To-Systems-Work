#include <stdio.h>
int print1ToNWhile(int n)
{
    int i = 0;
    if (n < 1)
    {
        printf("{}");
    }
    else
    {
        printf("{");
        while (i < n)
        {
            printf("%d,", i);
            i++;
        }
        printf("%d}", n);
    }
    return 0;    
}
int print1ToNFor (int n)
{
    if (n < 0)
    {
        printf("{}");
    }
    else
    {
        printf("{");
        for (int i = 1; i < n; i++)
        {
            printf("%d,", i);
        }
        printf("%d}", n);
    }
    return 0;
}

