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

#define PROGNAME "advent15"

#define ROWS 50
#define COLS 50
#define ROWSIZE 50
#define COLSIZE 50
//#define ROWS 10
//#define COLS 10
//#define ROWSIZE 10
//#define COLSIZE 10

void printgrid(char grid[ROWS*COLS])
{
    printf("\n");
    printf("\n");
    int i = 0;
    int j = 0;
    while(i < ROWS*COLS)
    {
        while(j < COLS)
        {
            printf("%c", grid[i]);
            j++;
            i++;
        }
        j=0;
        printf("\n");
    }
    printf("\n");
    printf("\n");
    //sleep(2);
}

int getdirections(char dir)
{
    if(dir=='<')
    {
        return 3;
    }
    if(dir=='^')
    {
        return 0;
    }
    if(dir=='>')
    {
        return 1;
    }
    if(dir=='v')
    {
        return 2;
    }
    return 0;
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

int dopatrol(char* puzzle, char* moves, int xmoves, int start, int rows, int cols, int rowsize)
{
    int pos = 0;

    pos = start;
    int row = pos / rowsize;
    int col = pos % rowsize;
    int i = 0;
    int curdir = 0;
    while(i < xmoves)
    {

        curdir = getdirections(moves[i]);
        ylogd("next move is %i", curdir);
        int nextopen = -1;
        // up
        if(curdir == 0)
        {
            int testpos = pos - rowsize;
            int testrow = row-1;
            int testcol = col;
            nextopen = -1;
            ylogd("testing up position %i row: %i col: %i %c", testpos, testrow, testcol, puzzle[testpos]);
            if(checkpuzzleend(curdir, testrow, col)==0 && (puzzle[testpos] == '.' || puzzle[testpos] == 'O'))
            {


                if(puzzle[testpos] == 'O')
                {
                    //box
                    ylogd("box detected");
                    int testpos2 = testpos - rowsize;
                    int testrow2 = testrow - 1;
                    int testcol2 = testcol;
                    nextopen = testpos2;
                    while(checkpuzzleend(curdir, testrow2, testcol2)==0 && puzzle[testpos2]=='O')
                    {
                        testpos2 = testpos2 - rowsize;
                        testrow2 = testrow2 - 1;
                        testcol2 = testcol;
                        nextopen=testpos2;
                    }
                    if(puzzle[testpos2]=='#')
                    {
                        nextopen = -1;
                    }
                    if(checkpuzzleend(curdir, testrow2, testcol2)==0)
                    {
                        if(puzzle[testpos2]=='#')
                        {
                            nextopen = -1;
                        }
                    }
                    else
                    {
                        nextopen = -1;
                    }
                }
                else
                {
                    nextopen = testpos;
                }
                if(nextopen != -1)
                {
                    ylogd("moving");
                    int tmp = nextopen;
                    while(tmp != pos)
                    {
                        puzzle[tmp] = puzzle[tmp+rowsize];
                        tmp=tmp+rowsize;
                    }
                    puzzle[pos] = '.';
                    pos = pos-rowsize;
                }
            }
            ylogd("Attempted to move up from %i, next open space is at %i", pos, nextopen);
        }

        if(curdir == 1)
        {
            int testpos = pos + 1;
            int testrow = row;
            int testcol = col + 1;
            nextopen = -1;
            ylogd("testing right position %i row: %i col: %i %c", testpos, testrow, testcol, puzzle[testpos]);
            if(checkpuzzleend(curdir, testrow, col)==0 && (puzzle[testpos] == '.' || puzzle[testpos] == 'O'))
            {


                if(puzzle[testpos] == 'O')
                {
                    //box
                    ylogd("box detected");
                    int testpos2 = testpos + 1;
                    int testrow2 = testrow;
                    int testcol2 = testcol + 1;
                    nextopen = testpos2;
                    while(checkpuzzleend(curdir, testrow2, testcol2)==0 && puzzle[testpos2]=='O')
                    {
                        testpos2 = testpos2 + 1;
                        testrow2 = testrow2;
                        testcol2 = testcol + 1;
                        nextopen=testpos2;
                    }
                    if(puzzle[testpos2]=='#')
                    {
                        nextopen = -1;
                    }

                    if(checkpuzzleend(curdir, testrow2, testcol2)==0)
                    {
                        if(puzzle[testpos2]=='#')
                        {
                            nextopen = -1;
                        }
                    }
                    else
                    {
                        nextopen = -1;
                    }
                }
                else
                {
                    nextopen = testpos;
                }
                if(nextopen != -1)
                {
                    ylogd("moving");
                    int tmp = nextopen;
                    while(tmp != pos)
                    {
                        puzzle[tmp] = puzzle[tmp-1];
                        tmp--;
                    }
                    puzzle[pos] = '.';
                    pos = pos+1;
                }
            }
            ylogd("Attempted to move right from %i, next open space is at %i", pos, nextopen);
        }

        if(curdir == 2)
        {
            int testpos = pos + rowsize;
            int testrow = row+1;
            int testcol = col;
            nextopen = -1;
            ylogd("testing down position %i row: %i col: %i %c", testpos, testrow, testcol, puzzle[testpos]);
            if(checkpuzzleend(curdir, testrow, col)==0 && (puzzle[testpos] == '.' || puzzle[testpos] == 'O'))
            {


                if(puzzle[testpos] == 'O')
                {
                    //box
                    ylogd("box detected");
                    int testpos2 = testpos + rowsize;
                    int testrow2 = testrow + 1;
                    int testcol2 = testcol;
                    nextopen = testpos2;
                    while(checkpuzzleend(curdir, testrow2, testcol2)==0 && puzzle[testpos2]=='O')
                    {
                        testpos2 = testpos2 + rowsize;
                        testrow2 = testrow2 + 1;
                        testcol2 = testcol;
                        nextopen=testpos2;
                    }
                    if(puzzle[testpos2]=='#')
                    {
                        nextopen = -1;
                    }
                    if(checkpuzzleend(curdir, testrow2, testcol2)==0)
                    {
                        if(puzzle[testpos2]=='#')
                        {
                            nextopen = -1;
                        }
                    }
                    else
                    {
                        nextopen = -1;
                    }
                }
                else
                {
                    nextopen = testpos;
                }
                if(nextopen != -1)
                {
                    ylogd("moving");
                    int tmp = nextopen;
                    while(tmp != pos)
                    {
                        puzzle[tmp] = puzzle[tmp-rowsize];
                        tmp=tmp-rowsize;
                    }
                    puzzle[pos] = '.';
                    pos = pos+rowsize;
                }
            }
            ylogd("Attempted to move down from %i, next open space is at %i", pos, nextopen);
        }

        if(curdir == 3)
        {
            int testpos = pos - 1;
            int testrow = row;
            int testcol = col-1;
            nextopen = -1;
            ylogd("testing left position %i row: %i col: %i %c", testpos, testrow, testcol, puzzle[testpos]);
            if(checkpuzzleend(curdir, testrow, col)==0 && (puzzle[testpos] == '.' || puzzle[testpos] == 'O'))
            {


                if(puzzle[testpos] == 'O')
                {
                    //box
                    ylogd("box detected");
                    int testpos2 = testpos - 1;
                    int testrow2 = testrow;
                    int testcol2 = testcol - 1;
                    nextopen = testpos2;
                    while(checkpuzzleend(curdir, testrow2, testcol2)==0 && puzzle[testpos2]=='O')
                    {
                        testpos2 = testpos2 - 1;
                        testrow2 = testrow2;
                        testcol2 = testcol-1;
                        nextopen=testpos2;
                    }
                    if(puzzle[testpos2]=='#')
                    {
                        nextopen = -1;
                    }
                    if(checkpuzzleend(curdir, testrow2, testcol2)==0)
                    {
                        if(puzzle[testpos2]=='#')
                        {
                            nextopen = -1;
                        }
                    }
                    else
                    {
                        nextopen = -1;
                    }
                }
                else
                {
                    nextopen = testpos;
                }
                if(nextopen != -1)
                {
                    ylogd("moving");
                    int tmp = nextopen;
                    while(tmp != pos)
                    {
                        puzzle[tmp] = puzzle[tmp+1];
                        tmp++;
                    }
                    puzzle[pos] = '.';
                    pos = pos-1;
                }
            }
            ylogd("Attempted to move left from %i, next open space is at %i", pos, nextopen);
        }
        row = pos / rowsize;
        col = pos % rowsize;
        i++;
        //printgrid(puzzle);
    }
}


int findstart(char* puzzle, int rows, int cols, int rowsize, int colsize)
{
    int i =0;
    int start = 0;
    while(i < (rows * cols))
    {
        if(puzzle[i] == '@')
        {
            start = i;
            ylogd("found starting position %i", i);
        }
        i++;
    }

    return start;
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
    // tr --delete '\n' < advent06.txt > advent06_nonewlines.txt
    char* puzzle = fileslurp("advent15grid.txt");
    char* moves = fileslurp("advent15moves.txt");
    //char* puzzle = fileslurp("advent15samplegrid.txt");
    //char* moves = fileslurp("advent15samplemoves.txt");
    //char* puzzle = fileslurp("advent15samplegrid2.txt");
    //char* moves = fileslurp("advent15samplemoves2.txt");

    int xmoves = strlen(moves)-1;
    ylogi("making %i moves", xmoves);

    int start = findstart(puzzle, ROWS, COLS, ROWSIZE, COLSIZE);
    dopatrol(puzzle, moves, xmoves, start, ROWS, COLS, ROWSIZE);

    int gps = 0;
    for(int i = 0; i<strlen(puzzle); i++)
    {
        if(puzzle[i]=='O')
        {
            int row = i/ROWSIZE;
            int col = i%ROWSIZE;
            gps = gps + ((row*100)+col);
        }
    }



    free(puzzle);
    free(moves);
    free(p);
    ylogi("gps value of %i", gps);
    double elapsed_time = (double)(clock() - start_time) / CLOCKS_PER_SEC;
    ylogi("time : %f", elapsed_time);
    y_close_logs();
    return 0;
}
