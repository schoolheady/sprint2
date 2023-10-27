#include <stdio.h>
#include <stdlib.h>

int cijfersachter(int num,int *pa)
{
    while(num >= 100)
    {
        num = num / 10;
    }
    printf("num:%d\n", num);
    *pa = DoublleIntToInt(*pa, num);
}
int DoublleIntToInt(int a, int b)
{
    int result,temp1 = 0;
    temp1 = a *100;
    result = temp1 + b;
    return result;
}
int main()
{
    int een = 1234;
    int twee = 568572467;
    twee = cijfersachter(twee,&een);
    printf("een:%d\n", een);
}
