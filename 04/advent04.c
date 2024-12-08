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

#define XMASSIZE 4
#define ROWS 140
#define COLS 140
#define ROWSIZE 140
#define COLSIZE 140
//#define ROWS 10
//#define COLS 10
//#define ROWSIZE 10
//#define COLSIZE 10

#include <orcania.h>
#include <yder.h>

#include "../advent.h"

#define PROGNAME "advent04"


int checkword(char word[4])
{
    if(word[0] == 'X' && word[1] == 'M' && word[2] == 'A' && word[3] == 'S')
    {
        return 1;
    }
    return 0;
}

int checkwordx(char word[5])
{
    // center is 0, top left is 1, top right is 2, bottom left is 3, bottom right is 4
    if(word[0] == 'A')
    {
        if(word[1] == 'M' && word[3] == 'M' && word[2] == 'S' && word[4] == 'S')
        {
            return 1;
        }
        if(word[1] == 'S' && word[3] == 'S' && word[2] == 'M' && word[4] == 'M')
        {
            return 1;
        }
        // this is the bullshit they pull, it wasn't at all clear in the question, always test the sample
        // but that isn't always necessary and sufficient to get all the requirements
        if(word[1] == 'S' && word[2] == 'S' && word[3] == 'M' && word[4] == 'M')
        {
            return 1;
        }
        if(word[1] == 'M' && word[2] == 'M' && word[3] == 'S' && word[4] == 'S')
        {
            return 1;
        }
    }
    return 0;
}

int findxmasatpos(char* puzzle, int row, int col, int pos, int rows, int cols, int rowsize, int colsize)
{

    //ylogd("searching for christmas at pos %i row %i col %i start char is %c", pos, row, col, puzzle[pos]);
    int xmases = 0;
    // check horizontal forward
    if(col < (cols - 3))
    {
        char word[4];
        word[0] = puzzle[pos];
        word[1] = puzzle[pos+1];
        word[2] = puzzle[pos+2];
        word[3] = puzzle[pos+3];
        if(checkword(word) > 0)
        {
            ylogd("found xmas horizontally forward at pos: %i col: %i row %i", pos, col, row);
            xmases++;
        }
    }

    // check horizontal backward
    if(col >= 3)
    {
        char word[4];
        word[0] = puzzle[pos];
        word[1] = puzzle[pos-1];
        word[2] = puzzle[pos-2];
        word[3] = puzzle[pos-3];
        if(checkword(word) > 0)
        {
            ylogd("found xmas horizontally backwards at pos: %i col: %i row %i", pos, col, row);
            xmases++;
        }
    }

    // check vertically down
    if(row < (rows-3))
    {
        char word[4];
        word[0] = puzzle[pos];
        word[1] = puzzle[pos+rowsize];
        word[2] = puzzle[pos+(rowsize*2)];
        word[3] = puzzle[pos+(rowsize*3)];
        if(checkword(word) > 0)
        {
            ylogd("found xmas vertically down at pos: %i col: %i row %i", pos, col, row);
            xmases++;
        }
    }

    // check vertically up
    if(row >= 3)
    {
        char word[4];
        word[0] = puzzle[pos];
        word[1] = puzzle[pos-rowsize];
        word[2] = puzzle[pos-(rowsize*2)];
        word[3] = puzzle[pos-(rowsize*3)];
        if(checkword(word) > 0)
        {
            ylogd("found xmas vertically up at pos: %i col: %i row %i", pos, col, row);
            xmases++;
        }
    }

    // check diagonal down and right
    if(row < (rows - 3) && col < (cols - 3))
    {
        char word[4];
        word[0] = puzzle[pos];
        word[1] = puzzle[pos+(rowsize + 1)];
        word[2] = puzzle[pos+((rowsize*2) + 2)];
        word[3] = puzzle[pos+((rowsize*3) + 3)];
        if(checkword(word) > 0)
        {
            ylogd("found xmas diagonally down and right at pos: %i col: %i row %i", pos, col, row);
            xmases++;
        }
    }

    // check diagonal down and left
    if(row < (rows - 3) && col >= 3)
    {
        char word[4];
        word[0] = puzzle[pos];
        word[1] = puzzle[pos+(rowsize - 1)];
        word[2] = puzzle[pos+((rowsize*2) - 2)];
        word[3] = puzzle[pos+((rowsize*3) - 3)];
        if(checkword(word) > 0)
        {
            ylogd("found xmas diagonally down and left at pos: %i col: %i row %i", pos, col, row);
            xmases++;
        }
    }


    // check diagonal up and left
    if(row >= 3 && col >= 3)
    {
        char word[4];
        word[0] = puzzle[pos];
        word[1] = puzzle[pos - (rowsize + 1)];
        word[2] = puzzle[pos - ((rowsize*2) + 2)];
        word[3] = puzzle[pos - ((rowsize*3) + 3)];
        if(checkword(word) > 0)
        {
            ylogd("found xmas diagonally up and left at pos: %i col: %i row %i", pos, col, row);
            xmases++;
        }
    }

    // check diagonal up and right
    if(row >= 3 && col < (cols - 3))
    {
        char word[4];
        word[0] = puzzle[pos];
        word[1] = puzzle[pos - ( rowsize - 1 )];
        word[2] = puzzle[pos - ((rowsize*2) - 2 )];
        word[3] = puzzle[pos - (( rowsize*3) - 3 )];
        if(checkword(word) > 0)
        {
            ylogd("found xmas diagonally up and right at pos: %i col: %i row %i", pos, col, row);
            xmases++;
        }
    }

    return xmases;
}

int findmasatpos(char* puzzle, int row, int col, int pos, int rows, int cols, int rowsize, int colsize)
{

    int xmases = 0;
    // check horizontal forward
    if(col > 0 && row > 0 && row < (rowsize-1) && col < (colsize-1))
    {
        char word[5];
        word[0] = puzzle[pos];
        word[1] = puzzle[pos-(rowsize+1)];
        word[2] = puzzle[pos-(rowsize-1)];
        word[3] = puzzle[pos+(rowsize-1)];
        word[4] = puzzle[pos+(rowsize+1)];
        if(checkwordx(word) > 0)
        {
            ylogd("found mas at pos: %i col: %i row %i", pos, col, row);
            xmases++;
        }
    }


    return xmases;
}

int findxmas(Parameters* p, char* puzzle, int rows, int cols, int rowsize, int colsize)
{
    int xmases = 0;
    int i = 0;
    int row = 0;
    int col = 0;
    while(i < (rows * cols))
    {
        if(p->part2 > 0)
        {
            xmases = xmases + findmasatpos(puzzle, row, col, i, rows, cols, rowsize, colsize);
        }
        else
        {
            xmases = xmases + findxmasatpos(puzzle, row, col, i, rows, cols, rowsize, colsize);
        }

        i++;
        col++;
        if((i % rowsize) == 0)
        {
            col = 0;
            row++;
            ylogd("wrapping row at %i row is now %i col is now %i", i, row, col);
        }
    }
    ylogd("done searching for Christmas", i);

    return xmases;
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

    int a = 0;

    // to get this run
    // tr --delete '\n' < advent04.txt > advent04_nonewlines.txt
    char* str;
    str = fileslurp("advent04_nonewlines.txt");
    //str = fileslurp("advent04sample_nonewlines.txt");

    a = findxmas(p, str, ROWS, COLS, ROWSIZE, COLSIZE);

    ylogi("found xmas %i times", a);


    free(str);
    free(p);
    double elapsed_time = (double)(clock() - start_time) / CLOCKS_PER_SEC;
    ylogi("time : %f", elapsed_time);
    y_close_logs();
    return 0;
}
