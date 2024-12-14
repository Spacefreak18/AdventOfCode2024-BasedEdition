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

#define PROGNAME "advent14"

#define ROWS 103
#define COLS 101
#define ROWSIZE 101
#define COLSIZE 50
#define ROBOTS 500
#define SECONDS 100
//#define ROWS 7
//#define COLS 11
//#define ROWSIZE 11
//#define COLSIZE 11
//#define ROBOTS 12
//#define SECONDS 5


int robotstats[ROBOTS][4];


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

    int q1 = 0;
    int q2 = 0;
    int q3 = 0;
    int q4 = 0;



    //FILE* file = fopen("advent14_sample.txt", "r"); /* should check the result */
    FILE* file = fopen("advent14.txt", "r"); /* should check the result */
    char line[512];

    int64_t sum1 = 0;
    int64_t sum2 = 0;

    char** returnstring1;
    char** returnstring2;
    char** returnstring3;
    char** returnstring4;
    char** returnstring5;
    int k = 0;
    int64_t ax = 0;
    int64_t ay = 0;
    int64_t bx = 0;
    int64_t by = 0;
    int64_t px = 0;
    int64_t py = 0;
    int64_t correction = 10000000000000;
    int robot = 0;
    while (fgets(line, sizeof(line), file))
    {
        //p=0,4 v=3,-3
        size_t sz1 = split_string(line, ",", &returnstring1);
        size_t sz2 = split_string(returnstring1[0], "=", &returnstring2);

        size_t sz3 = split_string(returnstring1[1], " ", &returnstring3);
        size_t sz4 = split_string(returnstring1[1], "=", &returnstring4);
        size_t sz5 = split_string(returnstring1[2], ",", &returnstring5);
        //ylogd("found %s %s %s %s", returnstring2[1], returnstring3[0], returnstring4[1], returnstring5[0]);

        int py = atoi(returnstring2[1]);
        int px = atoi(returnstring3[0]);
        int vy = atoi(returnstring4[1]);
        int vx = atoi(returnstring5[0]);

        robotstats[robot][0] = px;
        robotstats[robot][1] = py;
        robotstats[robot][2] = vx;
        robotstats[robot][3] = vy;

        free_string_array(returnstring5);
        free_string_array(returnstring4);
        free_string_array(returnstring3);
        free_string_array(returnstring2);
        free_string_array(returnstring1);
        robot++;
    }


        for(int robot = 0; robot < ROBOTS; robot++)
        {
            int st1 = robotstats[robot][0];
            int st2 = robotstats[robot][1];
            int pos = st1 * ROWSIZE;
            pos = pos + (st2);

            int vx = robotstats[robot][2];
            int vy = robotstats[robot][3];

            ylogd("this robot is starting at %i,%i and will move %i,%i each second", st1, st2, vx, vy);

                for(int i = 1; i <= SECONDS; i++)
                {

                    int row = pos / ROWSIZE;
                    int col = pos % ROWSIZE;
                    row = row + vx;
                    col = col + vy;

                    if(col >= COLS)
                    {
                        col = col-COLS;
                    }
                    if(col < 0)
                    {
                        col = COLS+col;
                    }

                    if(row >= ROWS)
                    {
                        row = row-ROWS;
                    }
                    if(row < 0)
                    {
                        row = ROWS+row;
                    }

                    pos = (row * ROWSIZE) + col;
                    ylogd("finish pos is %i", pos);

                }

                int row = pos / ROWSIZE;
                int col = pos % ROWSIZE;
                ylogd("robot %i is at pos %i row %i col %i %i %i", robot, pos, row, col, ROWS/2, COLS/2);
                if(row < ROWS/2 && col < COLS/2)
                {
                    q1++;
                }
                if(row > ROWS/2 && col < COLS/2)
                {
                    q3++;
                }
                if(row < ROWS/2 && col > COLS/2)
                {
                    q2++;
                }
                if(row > ROWS/2 && col > COLS/2)
                {
                    q4++;
                }
    }

    free(p);
    ylogi("q1 contains %i robots", q1);
    ylogi("q2 contains %i robots", q2);
    ylogi("q3 contains %i robots", q3);
    ylogi("q4 contains %i robots", q4);
    ylogi("there are %i relevant robots", q1+q2+q3+q4);
    ylogi("the safety factor is %i", q1*q2*q3*q4);
    double elapsed_time = (double)(clock() - start_time) / CLOCKS_PER_SEC;
    ylogi("time : %f", elapsed_time);
    y_close_logs();
    return 0;
}
