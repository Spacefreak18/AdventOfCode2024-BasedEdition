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

#define PROGNAME "advent23"


int computers = 520;
//int computers = 16;


int print_combination(char arr[][3], int n, int r) {
    // Loop through all possible combinations of size r

    FILE* file = fopen("advent23.txt", "r"); /* should check the result */
    //FILE* file = fopen("advent23_sample.txt", "r"); /* should check the result */

    int combos = 0;
    char** returnstring1;
    char line[512];
    for (int i = 0; i < n - 2; i++)
    {
        for (int j = i + 1; j < n - 1; j++)
        {
            for (int k = j + 1; k < n; k++)
            {
                int match1 = 0;
                int match2 = 0;
                int match3 = 0;
                if(arr[i][0] == 't' || arr[j][0] == 't' || arr[k][0] == 't')
                {
                    while (fgets(line, sizeof(line), file))
                    {
                        size_t sz1 = split_string(line, "-", &returnstring1);

                        char a = returnstring1[0][0];
                        char b = returnstring1[0][1];
                        char c = returnstring1[1][0];
                        char d = returnstring1[1][1];
                        char aa[2];
                        aa[0] = a;
                        aa[1] = b;
                        char bb[2];
                        bb[0] = c;
                        bb[1] = d;



                        free_string_array(returnstring1);
                        if( (arr[i][0] == aa[0] && arr[i][1] == aa[1] && arr[j][0] == bb[0] && arr[j][1] == bb[1]) ||
                            (arr[j][0] == aa[0] && arr[j][1] == aa[1] && arr[i][0] == bb[0] && arr[i][1] == bb[1]) )
                        {
                            match1 = 1;
                        }

                        if( (arr[k][0] == aa[0] && arr[k][1] == aa[1] && arr[j][0] == bb[0] && arr[j][1] == bb[1]) ||
                            (arr[j][0] == aa[0] && arr[j][1] == aa[1] && arr[k][0] == bb[0] && arr[k][1] == bb[1]) )
                        {
                            match2 = 1;
                        }

                        if( (arr[k][0] == aa[0] && arr[k][1] == aa[1] && arr[i][0] == bb[0] && arr[i][1] == bb[1]) ||
                            (arr[i][0] == aa[0] && arr[i][1] == aa[1] && arr[k][0] == bb[0] && arr[k][1] == bb[1]) )
                        {
                            match3 = 1;
                        }

                    }


                    if(match1 == 1 && match2 == 1 && match3 == 1)
                    {
                        printf("%c%c-%c%c-%c%c\n", arr[i][0], arr[i][1], arr[j][0], arr[j][1], arr[k][0], arr[k][1]);
                        combos++;
                    }
                    fseek(file, 0, SEEK_SET);
                }
            }
        }
    }
    fclose(file);
    return combos;
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
    // generate with tr , '\n' < file
    // and sort and uniq
    FILE* file = fopen("comps.txt", "r"); /* should check the result */
    //FILE* file = fopen("comps_sample.txt", "r"); /* should check the result */


    char comps[computers][3];
    char** returnstring1;
    int px = 0;
    int py = 0;
    int memory = 0;
    char line[512];
    int i = 0;
    while (fgets(line, sizeof(line), file))
    {
        comps[i][0]=line[0];
        comps[i][1]=line[1];
        comps[i][2]='\0';
        i++;
    }
    fclose(file);


    int combos = print_combination(comps, computers, 3);
    free(p);
    ylogi("found %i sets of 3 interconnected machines", combos);
    double elapsed_time = (double)(clock() - start_time) / CLOCKS_PER_SEC;
    ylogi("time : %f", elapsed_time);
    y_close_logs();
    return 0;
}
