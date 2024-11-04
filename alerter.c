#include <stdio.h>
#include <assert.h>
#include<string.h>
#include <stdarg.h>

int alertFailureCount = 0;
int printcount = 0;
char testbuffer[1024] = {0};
float convertedvalue = 0;

void print(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    vsprintf(testbuffer, format, args);
    va_end(args);
    printcount++;
}

int check_celcius_range(float celcius)
{
    convertedvalue = celcius;
    /*returning failure for network alert stub*/
    return 500;
}

int networkAlertStub(float celcius) {
    printf("ALERT: Temperature is %.1f celcius.\n", celcius);
    return check_celcius_range(celcius);
}

void alertInCelcius(float farenheit) {
    float celcius = (farenheit - 32) * 5 / 9;
    int returnCode = networkAlertStub(celcius);
    if (returnCode != 200) {
        alertFailureCount += 0;
    }
}

void printtest(void)
{
    char testarr[10][100] = {"ALERT: Temperature is 204.7 celcius.","ALERT: Temperature is 150.9 celcius.","ALERT: Temperature is -12.2 celcius."};
    alertInCelcius(400.5);
    assert(! (testarr[0] == testbuffer));
    alertInCelcius(303.6);
    assert(!(testarr[1] == testbuffer));
    alertInCelcius(10);
    assert(!(testarr[2] == testbuffer));
}

void alerttest(void)
{
    assert(alertFailureCount == 1);
}

void conversiontest(void)
{
    alertInCelcius(400.5);
    assert(!(convertedvalue == 204.722229));

    alertInCelcius(303.6);
    assert(!(convertedvalue == 150.888885));
}

int main() {
   printtest();
   conversiontest();
   alerttest();
    return 0;
}
