#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

#include <orcania.h>
#include <yder.h>

#include "../advent.h"

#define PROGNAME "advent13"


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


    //FILE* file = fopen("advent13sample.txt", "r"); /* should check the result */
    FILE* file = fopen("advent13.txt", "r"); /* should check the result */
    char line[512];

    int a1 = 0;
    uint64_t sum1 = 0;
    int a2 = 0;
    uint64_t sum2 = 0;

    char** returnstring;
    char** returnstring2;
    char** returnstring3;
    char** returnstring4;
    char** returnstring5;
    int k = 0;
    int ax = 0;
    int ay = 0;
    int bx = 0;
    int by = 0;
    int px = 0;
    int py = 0;
    while (fgets(line, sizeof(line), file))
    {
        if(k == 0)
        {
            size_t sz = split_string(line, ":", &returnstring);
            size_t sz1 = split_string(returnstring[1], "+", &returnstring2);
            size_t sz2 = split_string(returnstring2[1], ",", &returnstring3);

            ax = atoi(returnstring3[0]);
            ay = atoi(returnstring2[2]);
            ylogd("found ax of %i", ax);
            ylogd("found ay of %i", ay);
            free_string_array(returnstring3);
            free_string_array(returnstring2);
            free_string_array(returnstring);
        }
        if(k == 1)
        {
            size_t sz = split_string(line, ":", &returnstring);
            size_t sz1 = split_string(returnstring[1], "+", &returnstring2);
            size_t sz2 = split_string(returnstring2[1], ",", &returnstring3);
            bx = atoi(returnstring3[0]);
            by = atoi(returnstring2[2]);
            ylogd("found bx of %i", bx);
            ylogd("found by of %i", by);
            free_string_array(returnstring3);
            free_string_array(returnstring2);
            free_string_array(returnstring);
        }
        if(k == 2)
        {
            size_t sz = split_string(line, ":", &returnstring);
            size_t sz1 = split_string(returnstring[1], "=", &returnstring2);
            size_t sz2 = split_string(returnstring2[1], ",", &returnstring3);
            px = atoi(returnstring3[0]);
            py = atoi(returnstring2[2]);
            ylogd("found px of %i", px);
            ylogd("found py of %i", py);
            free_string_array(returnstring3);
            free_string_array(returnstring2);
            free_string_array(returnstring);

            int z1 = ay*ax;
            int z2 = ay*bx;
            int z3 = ay*px;
            int w1 = ax*ay;
            int w2 = ax*by;
            int w3 = ax*py;

            int ww1 = w3-z3;
            int ww2 = w2-z2;

            int bpresses = ww1/ww2;

            if(ww1 % ww2 != 0)
            {
                ylogd("no prize possible");
            }
            else
            {
                int apresses = (px-(bx*bpresses))/ax;
                a1 += apresses;
                a2 += bpresses;
                ylogd("you need %i presses of a and %i presses of b", apresses, bpresses);
            }
        }
        k++;
        if(k==4)
        {
            k=0;
        }

    }
    fclose(file);


    free(p);

    ylogi("Found %i apresses %i bpresses for a total cost of %i", a1, a2, ((a1*3)+(a2)));

    double elapsed_time = (double)(clock() - start_time) / CLOCKS_PER_SEC;
    ylogi("time : %f", elapsed_time);
    y_close_logs();

    return 0;
}
