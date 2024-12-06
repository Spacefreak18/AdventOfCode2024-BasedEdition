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

#define PROGNAME "advent06"

#define ROWS 130
#define COLS 130
#define ROWSIZE 130
#define COLSIZE 130
//#define ROWS 10
//#define COLS 10
//#define ROWSIZE 10
//#define COLSIZE 10


int updatedir(int dir)
{
    dir++;
    if(dir > 3)
    {
        return 0;
    }

    return dir;
}

int checkpuzzleend(int dir, int row, int col)
{
    if(dir == 0 && row == 0)
    {
        ylogd("at puzzle top edge");
        return 1;
    }
    if(dir == 1 && col == (COLSIZE-1))
    {
        ylogd("at puzzle right edge, col %i", col);
        return 1;
    }
    if(dir == 2 && row == (ROWSIZE-1))
    {
        ylogd("at puzzle bottom edge");
        return 1;
    }
    if(dir == 3 && col == 0)
    {
        ylogd("at puzzle left edge");
        return 1;
    }
    return 0;
}

int dopatrol(char* puzzle, int curdir, int pos, int row, int col, int rowsize, bool modify)
{
    int giveup = 0;
    int moves = 0;
    int loop = 0;
    int maxmoves = ROWSIZE * COLSIZE;

    while(checkpuzzleend(curdir, row, col) == 0 && giveup < 1)
    {

        int move = 0;
        // up
        if(curdir == 0 && move == 0)
        {
            int testpos = pos - rowsize;
            ylogd("testing position %i row: %i col: %i %c", testpos, row-1, col, puzzle[testpos]);
            if(puzzle[testpos] == '.' || puzzle[testpos] == 'X')
            {
                ylogd("up is okay, completing move");
                pos = testpos;
                if(modify == true)
                {
                    puzzle[pos] = 'X';
                }
                row--;
            }
            else
            {
                if(puzzle[testpos] == '#')
                {
                    ylogd("up is not okay, moving right, currently at row %i col %i pos %i", row, col, pos);
                    curdir = updatedir(curdir);
                }
            }
            move++;
        }

        // right
        if(curdir == 1 && move == 0)
        {
            int testpos = pos+1;
            ylogd("testing from current position %i row: %i col: %i %c", testpos, row, col+1, puzzle[testpos]);
            if(puzzle[testpos] == '.' || puzzle[testpos] == 'X')
            {
                pos = testpos;
                if(modify == true)
                {
                    puzzle[pos] = 'X';
                }
                col++;
            }
            else
            {
                if(puzzle[testpos] == '#')
                {
                    ylogd("right is not okay, moving down, currently at row %i col %i pos %i", row, col, pos);
                    curdir = updatedir(curdir);
                }
            }
            move++;
        }

        // down
        if(curdir == 2 && move == 0)
        {
            int testpos = pos+rowsize;
            if(puzzle[testpos] == '.' || puzzle[testpos] == 'X')
            {
                ylogd("down is okay, completing move");
                pos = testpos;
                if(modify == true)
                {
                    puzzle[pos] = 'X';
                }
                row++;
            }
            else
            {
                if(puzzle[testpos] == '#')
                {
                    ylogd("down is not okay, moving left, currently at row %i col %i pos %i", row, col, pos);
                    curdir = updatedir(curdir);
                    ylogd("%i", curdir);
                }
            }
            move++;
        }

        // left
        if(curdir == 3 && move == 0)
        {
            int testpos = pos-1;
            ylogd("testing position %i row: %i col: %i %c", testpos, row-1, col, puzzle[testpos]);
            if(puzzle[testpos] == '.' || puzzle[testpos] == 'X')
            {
                pos = testpos;
                if(modify == true)
                {
                    puzzle[pos] = 'X';
                }
                move++;
                col--;
            }
            else
            {
                if(puzzle[testpos] == '#')
                {
                    curdir = updatedir(curdir);
                }
            }
            move++;
        }

        moves++;
        if(moves > maxmoves + 1)
        {
            giveup++;
            loop++;
            ylogi("looping detected");
        }
    }

return loop;
}

int dounobstructedpatrol(char* puzzle, int start, int rows, int cols, int rowsize, int colsize)
{
    // get initial direction 0 is up, 1 is right, 2, is down, 3 is left
    char dir = puzzle[start];
    int curdir = 0;
    int startdir = 0;
    if(puzzle[start] == '>')
    {
        startdir = 1;
    }
    if(puzzle[start] == '<')
    {
        startdir = 3;
    }
    curdir = startdir;

    int pos = start;
    puzzle[start] = '.';
    int row = 0;
    int col = 0;
    row = start / rowsize;
    col = start % rowsize;

    dopatrol(puzzle, curdir, pos, row, col, rowsize, true);

    return 0;
}

int doobstructedpatrol(char* puzzle, int start, int rows, int cols, int rowsize, int colsize)
{
    // get initial direction 0 is up, 1 is right, 2, is down, 3 is left
    char dir = puzzle[start];
    int curdir = 0;
    int startdir = 0;
    if(puzzle[start] == '>')
    {
        startdir = 1;
    }
    if(puzzle[start] == '<')
    {
        startdir = 3;
    }

    int maxmoves = ROWS * COLS * 4;
    int loops = 0;
    int obstruction = 0;
    while(obstruction < strlen(puzzle))
    {

        // reset
        int curdir = startdir;
        int pos = start;
        puzzle[start] = '.';
        int row = 0;
        int col = 0;
        row = start / rowsize;
        col = start % rowsize;

        ylogd("%c", puzzle[obstruction]);
        if(puzzle[obstruction] == '.')
        {
            puzzle[obstruction] = '#';
            int giveup = 0;
            int moves = 0;
            loops = loops + dopatrol(puzzle, curdir, pos, row, col, rowsize, false);

            puzzle[obstruction] = '.';
        }
        obstruction++;
    }

    return loops;
}

int findstart(char* puzzle, int rows, int cols, int rowsize, int colsize)
{
    int i =0;
    int start = 0;
    while(i < (rows * cols))
    {
        if(puzzle[i] == '>' || puzzle[i] == '<' || puzzle[i] == '^')
        {
            start = i;
            ylogd("found starting position %i", i);
        }
        i++;
    }

    return start;
}

int main(int argc, char** argv) {

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
    // tr --delete '\n' < advent06.txt > advent06_nonewlines.txt
    //char* str = fileslurp("advent06_sample.txt");
    char* str = fileslurp("advent06_nonewlines.txt");

    int start = findstart(str, ROWS, COLS, ROWSIZE, COLSIZE);
    int looped = doobstructedpatrol(str, start, ROWS, COLS, ROWSIZE, COLSIZE);
    dounobstructedpatrol(str, start, ROWS, COLS, ROWSIZE, COLSIZE);

    int strlength = strlen(str);
    int l = 0;
    while(l < strlength)
    {
        if(str[l] == 'X')
        {
            a++;
        }
        l++;
    }

    ylogi("found xmas %i times", a);
    ylogi("it got got stuck in a loop by adding something in a spot %i times", looped);


    free(str);
    free(p);
    double elapsed_time = (double)(clock() - start_time) / CLOCKS_PER_SEC;
    ylogi("time : %f", elapsed_time);
    y_close_logs();
    return 0;
}
