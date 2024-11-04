#include <stdio.h>
#include <assert.h>
#include<string.h>
#include <stdarg.h>

int printcount = 0;
char testbuffer[25][1024] = {0};

int printColorMap() {
    const char* majorColor[] = {"White", "Red", "Black", "Yellow", "Violet"};
    const char* minorColor[] = {"Blue", "Orange", "Green", "Brown", "Slate"};
    int i = 0, j = 0;
    for(i = 0; i < 5; i++) 
    {
        for(j = 0; j < 5; j++) 
        {
            printf("%d | %s | %s\n", i * 5 + j, majorColor[i], minorColor[i]);
        }
    }
    return i * j;
}

void print(const char *format, ...)
{
    static int count = 0;
    va_list args;
    va_start(args, format);
    vsprintf(testbuffer[count], format, args);
    va_end(args);
    count++;
    printcount++;
    if(count == 24)
    {
        count = 0;
    }
}

void printtest(void)
{
    char testarr[2][50] = {"2 | White | Orange","3 | White | Green"};
    int result = printColorMap();

    /*testing the number of times print function called*/
    assert(result == printcount);
    /*testing the printed statement with actual output*/
    assert(testarr[0] == testbuffer[1]);
    assert(testarr[1] == testbuffer[2]);

}

int main() {
    printtest();
    printf("All is well (maybe!)\n");
    return 0;
}
