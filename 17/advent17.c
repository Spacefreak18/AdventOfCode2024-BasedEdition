#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#include <limits.h>

#include <math.h>
#include <orcania.h>
#include <yder.h>

#include "../advent.h"

#define PROGNAME "advent17"

//int aregister = 729;
int aregister = 25986278;
int bregister = 0;
int cregister = 0;
int counter = 0;

int* output;
int outputsize = 0;

int adv(int operand)
{
    int den = pow((double) 2, (double) operand);
    return (aregister/den);
}

int bxl(int operand)
{
    return (bregister ^ operand);
}

int bst(int operand)
{
    return operand%8;
}

int jnz(int operand)
{
    if(aregister != 0)
    {
        counter = operand;
    }
    else
    {
        counter = counter + 2;
    }
}

int bxc(int operand)
{
    return (bregister ^ cregister);
}

int out(int operand)
{
    outputsize++;
    output[outputsize-1] = (operand % 8);
}

int getCombo(int combo)
{
    switch(combo)
    {
        case 4:
            return aregister;
        case 5:
            return bregister;
        case 6:
            return cregister;
        case 7:
            ylogd("invalid operand");
            return -1;
        default:
            return combo;
    }
}

int performOp(int op, int operand)
{
    switch(op)
    {
        case 0:
            aregister = adv(getCombo(operand));
            counter = counter + 2;
            ylogd("performed adv operation, counter is at %i", counter);
            break;
        case 1:
            bregister = bxl(operand);
            counter = counter + 2;
            ylogd("performed bxl operation, counter is at %i", counter);
            break;
        case 2:
            bregister = bst(getCombo(operand));
            ylogd("performed bst operation, counter is at %i", counter);
            counter = counter + 2;
            break;
        case 3:
            jnz(operand);
            ylogd("performed jnz operation, counter is at %i", counter);
            break;
        case 4:
            bregister = bxc(operand);
            counter = counter + 2;
            ylogd("performed bxc operation, counter is at %i", counter);
            break;
        case 5:
            out(getCombo(operand));
            counter = counter + 2;
            ylogd("performed out operation, counter is at %i", counter);
            break;
        case 6:
            bregister = adv(getCombo(operand));
            counter = counter + 2;
            ylogd("performed bdv operation, counter is at %i", counter);
            break;
        case 7:
            cregister = adv(getCombo(operand));
            counter = counter + 2;
            ylogd("performed cdv operation, counter is at %i", counter);
            break;
        default:
            return -1;
    }

}

int main(int argc, char** argv)
{

    clock_t start_time = clock();

    Parameters* p = malloc(sizeof(Parameters));
    ConfigError ppe = getParameters(argc, argv, p);

    if(p->verbosity_count>0)
    {
        y_init_logs(PROGNAME, Y_LOG_MODE_CONSOLE, Y_LOG_LEVEL_DEBUG, NULL, "Initializing logs mode: file, logs level: debug");
    }
    else
    {
        y_init_logs(PROGNAME, Y_LOG_MODE_CONSOLE, Y_LOG_LEVEL_INFO, NULL, "Initializing logs mode: file, logs level: info");
    }

    output = malloc(sizeof(int) * 1024);

    //int program[6] = {0, 1, 5, 4, 3, 0};
    int program[16] = {2,4,1,4,7,5,4,1,1,4,5,5,0,3,3,0};
    int plen = 16;

    counter = 0;
    while(counter < plen)
    {
        int r = performOp(program[counter], program[counter+1]);
        if(r == -1)
        {
            ylogd("invalid operation");
        }
    }

    for(int i = 0; i < outputsize; i++)
    {
        //ylogd("output %i is %i", i, output[i]);
        printf("%i,", output[i]);
    }
    printf("\n");

    ylogd("register a: %i register b: %i register c: %i", aregister, bregister, cregister);

    free(output);
    free(p);
    double elapsed_time = (double)(clock() - start_time) / CLOCKS_PER_SEC;
    ylogi("time : %f", elapsed_time);
    y_close_logs();
    return 0;
}
