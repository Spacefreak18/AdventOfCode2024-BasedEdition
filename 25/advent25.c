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

#define PROGNAME "advent25"

#define ROWS 7
#define COLS 5

#define LOCKIDENT "#####"
#define KEYIDENT "....."

struct keylocks
{
    int type;
    char keylock[ROWS][COLS];
};



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
    // generate with tr , '\n' < file
    // and sort and uniq
    FILE* file = fopen("advent25.txt", "r"); /* should check the result */
    //FILE* file = fopen("advent25_sample.txt", "r"); /* should check the result */


    struct keylocks* keys = malloc(sizeof(struct keylocks) * 512);
    char line[512];
    int i = 0;
    int k = 0;
    int locks = 0;
    while (fgets(line, sizeof(line), file))
    {
        char* temp = o_strdup(trimwhitespace(line));

        if(i == 0)
        {

            if(strcmp(line, KEYIDENT) == 0)
            {
                ylogd("type 0");

                keys[k].type = 0;
                for(int j = 0; j < COLS; j++)
                {
                    keys[k].keylock[i][j] = '.';
                }
            }
            if(strcmp(line, LOCKIDENT) == 0)
            {
                locks++;
                ylogd("type 1");
                keys[k].type = 1;
                for(int j = 0; j < COLS; j++)
                {
                    keys[k].keylock[i][j] = '#';
                }
            }
        }
        if(i>0 && i < ROWS)
        {
            for(int j = 0; j < (ROWS-1); j++)
            {
                keys[k].keylock[i][j] = temp[j];
            }
        }
        free(temp);
        if(i == ROWS)
        {
            k++;
            i=0;
            continue;
        }
        i++;

    }
    fclose(file);

    //for(int j = 0; j < k+1; j++)
    //{
    //    for(int m = 0; m < 7; m++)
    //    {
    //        for(int n = 0; n < 5; n++)
    //        {
    //            printf("%c", keys[j].keylock[m][n]);
    //        }
    //        printf("\n");
    //    }
    //    printf("\n");
    //}
    //
    //

    uint64_t totalcombos = 0;
    uint64_t overlaps = 0;

    for(int j = 0; j < k+1; j++)
    {
        int lockcols[COLS];
        int keycols[COLS];

        if(keys[j].type == 1)
        {
            for(int n = 0; n < COLS; n++)
            {
                int t = 0;
                char lastchar = keys[j].keylock[0][n];

                for(int m = 1; m < ROWS; m++)
                {
                    if(lastchar == keys[j].keylock[m][n])
                    {
                        t++;
                    }
                }

                lockcols[n] = t;
            }
            for(int q = 0; q < k+1; q++)
            {

                if(keys[q].type == 0)
                {
                    ylogd("testing");
                    for(int n = 0; n < COLS; n++)
                    {
                        int t = 0;
                        char lastchar = keys[q].keylock[ROWS-1][n];
                        for(int m = ROWS-2; m > 0; m--)
                        {
                            if(lastchar == keys[q].keylock[m][n])
                            {
                                t++;
                            }
                        }
                        keycols[n] = t;
                    }
                    bool overlap = false;
                    totalcombos++;
                    for(int n = 0; n < COLS; n++)
                    {
                        ylogd(" %i %i ", lockcols[n], keycols[n]);
                        if((keycols[n] + lockcols[n]) > COLS && overlap == false)
                        {
                            overlaps++;
                            overlap = true;
                            //ylogd("overlap!");
                        }
                    }
                }
            }
        }
    }



    ylogi("There are %llu total combos and %llu of them overlap, meaning %i do not overlap", totalcombos, overlaps, (totalcombos-overlaps));

    free(keys);

    free(p);

    double elapsed_time = (double)(clock() - start_time) / CLOCKS_PER_SEC;
    ylogi("time : %f", elapsed_time);
    y_close_logs();
    return 0;
}
