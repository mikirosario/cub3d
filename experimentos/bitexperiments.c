#include <stdio.h>
#include <string.h>

int main(void)
{
    unsigned int i = 65535;
    unsigned char byte1;
    unsigned char byte2;
    unsigned char byte3;
    unsigned char byte4;

    printf("\n%d\n", i);

    printf("\n%d\n", (byte1 = (i)));
    printf("\n%d\n", (byte2 = (i >> 9)));
    return (1);
}