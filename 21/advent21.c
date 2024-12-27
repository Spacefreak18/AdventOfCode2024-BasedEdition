#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#include <limits.h>

#include <orcania.h>
#include <yder.h>

#include "../advent.h"

#define PROGNAME "advent21"

#define ROWS 4
#define COLS 3

#define NUMROBOTS 2

int keypad1pos = 2;
char keypad1presses[4096];
int keypress = 0;

int robotpos[25];
char robotpresses[25][4096*4096];
uint64_t robotpress[25];

char MEM1[5][5];


uint64_t robot(char c, int robot)
{
    int rows = 2;
    int cols = 3;
    int destpos = 5;


    if(c == '^')
    {
        destpos = 4;
    }
    if(c == '>')
    {
        destpos = 2;
    }
    if(c == 'd')
    {
        destpos = 1;
    }
    if(c == '<')
    {
        destpos = 0;
    }

    uint64_t moverows = abs((destpos/cols) - (robotpos[robot]/cols));
    uint64_t movecols = abs((destpos%cols) - (robotpos[robot]%cols));
    if(destpos == 5)
    {
    for(uint64_t i = 0; i < movecols; i++)
    {
        char movechar;
        if((destpos%cols) > (robotpos[robot]%cols))
        {
            movechar = '>';
        }
        else
        {
            movechar = '<';
        }
        robotpresses[robot][robotpress[robot]] = movechar;
        robotpress[robot]++;
    }
    for(uint64_t i = 0; i < moverows; i++)
    {
        char movechar;
        if(destpos > robotpos[robot])
        {
            movechar = '^';
        }
        if(destpos < robotpos[robot])
        {
            movechar = 'd';
        }
        robotpresses[robot][robotpress[robot]] = movechar;
        robotpress[robot]++;
    }
    }
    else
    {
    if(destpos == 0)
    {

    for(uint64_t i = 0; i < moverows; i++)
    {
        char movechar;
        if(destpos > robotpos[robot])
        {
            movechar = '^';
        }
        if(destpos < robotpos[robot])
        {
            movechar = 'd';
        }
        robotpresses[robot][robotpress[robot]] = movechar;
        robotpress[robot]++;
    }
    for(uint64_t i = 0; i < movecols; i++)
    {
        char movechar;
        if((destpos%cols) > (robotpos[robot]%cols))
        {
            movechar = '>';
        }
        else
        {
            movechar = '<';
        }
        robotpresses[robot][robotpress[robot]] = movechar;
        robotpress[robot]++;
    }
    }
    else
    {

    for(uint64_t i = 0; i < movecols; i++)
    {
        char movechar;
        if((destpos%cols) > (robotpos[robot]%cols))
        {
            movechar = '>';
        }
        else
        {
            movechar = '<';
        }
        robotpresses[robot][robotpress[robot]] = movechar;
        robotpress[robot]++;
    }
    for(uint64_t i = 0; i < moverows; i++)
    {
        char movechar;
        if(destpos > robotpos[robot])
        {
            movechar = '^';
        }
        if(destpos < robotpos[robot])
        {
            movechar = 'd';
        }
        robotpresses[robot][robotpress[robot]] = movechar;
        robotpress[robot]++;
    }
    }
    }

    //ylogd("moving %i rows %i cols", moverows, movecols);

    robotpos[robot] = destpos;

    robotpresses[robot][robotpress[robot]] = 'A';
    robotpress[robot]++;
    return (moverows+movecols+1);

}



int entercode(char c, int dir)
{
    int rows = 4;
    int cols = 3;

    char temp[2];
    temp[0] = c;
    temp[1] = '\0';
    int t = atoi(temp);
    int destpos = t + 2;

    if(c == '0')
    {
        destpos = 1;
    }
    if(c == 'A')
    {
        destpos = 2;
    }

    int moverows = abs((destpos/cols) - (keypad1pos/cols));
    int movecols = abs((destpos%cols) - (keypad1pos%cols));


    int goingleft = ((keypad1pos%cols) - (destpos%cols));
    if(goingleft > 0)
    {
        goingleft = 1;
    }
    if(dir > 0)
    {
        if(((keypad1pos%cols==0) && (destpos/cols==0)))
        {
            for(int i = 0; i < movecols; i++)
            {
                char movechar;
                if((destpos%cols) > (keypad1pos%cols))
                {
                    movechar = '>';
                }
                else
                {
                    movechar = '<';
                }
                keypad1presses[keypress] = movechar;
                keypress++;
            }
            for(int i = 0; i < moverows; i++)
            {
                char movechar;
                if(destpos > keypad1pos)
                {
                    movechar = '^';
                }
                if(destpos < keypad1pos)
                {
                    movechar = 'd';
                }
                keypad1presses[keypress] = movechar;
                keypress++;
            }
        }
        else
        {
            for(int i = 0; i < moverows; i++)
            {
                char movechar;
                if(destpos > keypad1pos)
                {
                    movechar = '^';
                }
                if(destpos < keypad1pos)
                {
                    movechar = 'd';
                }
                keypad1presses[keypress] = movechar;
                keypress++;
            }
            for(int i = 0; i < movecols; i++)
            {
                char movechar;
                if((destpos%cols) > (keypad1pos%cols))
                {
                    movechar = '>';
                }
                else
                {
                    movechar = '<';
                }
                keypad1presses[keypress] = movechar;
                keypress++;
            }
        }

    }
    else
    {

        if(((keypad1pos/cols==0) && (destpos%cols==0)))
        {
            for(int i = 0; i < moverows; i++)
            {
                char movechar;
                if(destpos > keypad1pos)
                {
                    movechar = '^';
                }
                if(destpos < keypad1pos)
                {
                    movechar = 'd';
                }
                keypad1presses[keypress] = movechar;
                keypress++;
            }
            for(int i = 0; i < movecols; i++)
            {
                char movechar;
                if((destpos%cols) > (keypad1pos%cols))
                {
                    movechar = '>';
                }
                else
                {
                    movechar = '<';
                }
                keypad1presses[keypress] = movechar;
                keypress++;
            }
        }
        else
        {
            for(int i = 0; i < movecols; i++)
            {
                char movechar;
                if((destpos%cols) > (keypad1pos%cols))
                {
                    movechar = '>';
                }
                else
                {
                    movechar = '<';
                }
                keypad1presses[keypress] = movechar;
                keypress++;
            }
            for(int i = 0; i < moverows; i++)
            {
                char movechar;
                if(destpos > keypad1pos)
                {
                    movechar = '^';
                }
                if(destpos < keypad1pos)
                {
                    movechar = 'd';
                }
                keypad1presses[keypress] = movechar;
                keypress++;
            }
        }

    }


    keypad1presses[keypress] = 'A';
    keypress++;

    keypad1pos = destpos;

    return (moverows+movecols+1);

}




uint64_t countpresses(char code[4], int numrobots)
{
    uint64_t press = 0;
    for(int i = 0; i < 4; i++)
    {
        uint64_t t1 = 0;
        uint64_t t2 = 0;
        int keypos = keypad1pos;
        keypress = 0;
        entercode(code[i], 0);
        for(int j = 0; j < keypress; j++)
        {
            robotpress[0] = 0;
            uint64_t y = robot(keypad1presses[j], 0);
            for(int m = 1; m < numrobots; m++)
            {
                robotpress[m] = 0;
                for(uint64_t k = 0; k < robotpress[m-1]; k++)
                {
                    uint64_t z = robot(robotpresses[m-1][k], m);
                    if(m == (numrobots-1))
                    {
                      t1 = t1 + z;
                    }
                }
            }
        }

        keypad1pos = keypos;
        keypress = 0;
        entercode(code[i], 1);

        for(int j = 0; j < keypress; j++)
        {
            robotpress[0] = 0;
            robot(keypad1presses[j], 0);
            for(int m = 1; m < numrobots; m++)
            {
                robotpress[m] = 0;
                for(uint64_t k = 0; k < robotpress[m-1]; k++)
                {
                    uint64_t z = robot(robotpresses[m-1][k], m);
                    if(m == (numrobots-1))
                    {
                      t2 = t2 + z;
                    }
                }
            }
        }
        if(t1 < t2)
        {
          press = press + t1;
        }
        else
        {
            press = press + t2;
        }
    }

    return press;
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

    for(int b = 0; b < NUMROBOTS; b++)
    {
        robotpos[b] = 5;
    }

    uint64_t totalcomplexity = 0;
    int tnum = 0;
    char num[4];

    //char num1[3] = {'0', '2', '9'};
    //char num2[3] = {'9', '8', '0'};
    //char num3[3] = {'1', '7', '9'};
    //char num4[3] = {'4', '5', '6'};
    //char num5[3] = {'3', '7', '9'};

    //129A 176A 985A 170A 528A
    char num1[3] = {'1', '2', '9'};
    char num2[3] = {'1', '7', '6'};
    char num3[3] = {'9', '8', '5'};
    char num4[3] = {'1', '7', '0'};
    char num5[3] = {'5', '2', '8'};

    num[0] = num1[0];
    num[1] = num1[1];
    num[2] = num1[2];
    num[3] = 'A';

    char temp[4];
    temp[0] = num[0];
    temp[1] = num[1];
    temp[2] = num[2];
    temp[3] = '\0';
    tnum = atoi(temp);

    uint64_t press = countpresses(num, NUMROBOTS);
    totalcomplexity = totalcomplexity + (press*tnum);
    //ylogd("presses is %i", press);

    num[0] = num2[0];
    num[1] = num2[1];
    num[2] = num2[2];
    num[3] = 'A';

    temp[0] = num[0];
    temp[1] = num[1];
    temp[2] = num[2];
    temp[3] = '\0';
    tnum = atoi(temp);
    press = countpresses(num, NUMROBOTS);
    totalcomplexity = totalcomplexity + (press*tnum);
    //ylogd("presses is %i", press);

    num[0] = num3[0];
    num[1] = num3[1];
    num[2] = num3[2];
    num[3] = 'A';

    temp[0] = num[0];
    temp[1] = num[1];
    temp[2] = num[2];
    temp[3] = '\0';
    tnum = atoi(temp);
    press = countpresses(num, NUMROBOTS);
    totalcomplexity = totalcomplexity + (press*tnum);
    //ylogd("presses is %i", press);

    num[0] = num4[0];
    num[1] = num4[1];
    num[2] = num4[2];
    num[3] = 'A';

    temp[0] = num[0];
    temp[1] = num[1];
    temp[2] = num[2];
    temp[3] = '\0';
    tnum = atoi(temp);
    press = countpresses(num, NUMROBOTS);
    totalcomplexity = totalcomplexity + (press*tnum);
    //ylogd("presses is %i", press);

    num[0] = num5[0];
    num[1] = num5[1];
    num[2] = num5[2];
    num[3] = 'A';

    temp[0] = num[0];
    temp[1] = num[1];
    temp[2] = num[2];
    temp[3] = '\0';
    tnum = atoi(temp);
    press = countpresses(num, NUMROBOTS);
    totalcomplexity = totalcomplexity + (press*tnum);
    //ylogd("presses is %i", press);


    ylogi("found a total complexity score of %llu", totalcomplexity);

    free(p);
    double elapsed_time = (double)(clock() - start_time) / CLOCKS_PER_SEC;
    ylogi("time : %f", elapsed_time);
    y_close_logs();
    return 0;
}
