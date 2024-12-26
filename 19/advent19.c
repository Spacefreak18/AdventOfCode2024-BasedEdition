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

#define PROGNAME "advent19"


char shirts[1024][64];
int shirtlen[1024];
int numshirts = 0;
int maxshirtlen = 0;


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

    // to get this run
    FILE* file = fopen("advent19.txt", "r"); /* should check the result */
    //FILE* file = fopen("advent19_sample.txt", "r"); /* should check the result */

    FILE* file1 = fopen("advent19_1.txt", "r"); /* should check the result */
    //FILE* file1 = fopen("advent19_sample1.txt", "r"); /* should check the result */

    char line[512];
    int ss = 0;
    while (fgets(line, sizeof(line), file1))
    {
        int totalsize = 0;
        int remainingsize = 0;
        char* temp = o_strdup(trimwhitespace(line));
        shirtlen[ss] = strlen(temp);
        ylogd("shirt %s len %i", temp, shirtlen[ss]);
        if(shirtlen[ss] > maxshirtlen)
        {
            maxshirtlen = shirtlen[ss];
        }
        for(int j = 0; j < shirtlen[ss]; j++)
        {
            shirts[ss][j] = temp[j];
        }
        free(temp);
        ss++;
    }
    fclose(file1);
    numshirts = ss;

    char** returnstring1;
    int possibles = 0;

    int l = 0;
    while (fgets(line, sizeof(line), file))
    {
        int totalsize = 0;
        int remainingsize = 0;
        if(l == 0)
        {
            //size_t sz1 = split_string(line, ",", &returnstring1);

            //numshirts = sz1;

            //maxshirtlen = 0;
            //for(int i = 0; i < numshirts; i++)
            //{
            //    char* temp;
            //    if(strlen(returnstring1[i]) > 1)
            //    {
            //        temp = o_strdup(trimwhitespace(returnstring1[i]));
            //    }
            //    else
            //    {
            //        temp = o_strdup(returnstring1[i]);
            //    }
            //    shirtlen[i] = strlen(temp);
            //    if(shirtlen[i] > maxshirtlen)
            //    {
            //        maxshirtlen = shirtlen[i];
            //    }
            //    for(int j = 0; j < shirtlen[i]; j++)
            //    {
            //        shirts[i][j] = temp[j];
            //    }
            //    if(shirtlen[i] == 1)
            //    {
            //        ylogd("shirt with size 1 %s", temp);
            //    }
            //    free(temp);
            //}

            //ylogd("found %i shirts maxlen is %i", sz1, maxshirtlen);
            //free_string_array(returnstring1);

        }
        if(l == 1)
        {
            l++;
            ylogd("continue");
            continue;
        }
        if(l > 1)
        {
            bool continuedo = true;
            bool continuedo2 = true;

            int ns[20];
            int n = 0;
            char* linetemp = o_strdup(trimwhitespace(line));
            totalsize = strlen(linetemp);
            ylogd("matching %s size is %i", linetemp, totalsize);
            remainingsize = totalsize;
            int trylen = maxshirtlen;
            while(remainingsize > 0 && continuedo == true)
            {
                bool submatch = false;
                //ylogd("reset match");
                int lastmatchi = 0;
                //for(int i = 1; i <= maxshirtlen; i++)
                for(int i = trylen; i > 0; i--)
                {
                    if(submatch == false)
                    {
                        if(i > remainingsize)
                        {
                            continue;
                        }
                        else
                        {
                            //ylogd("len is %i", i);
                            if(submatch == false)
                            {
                                char temp[i];
                                char temp2[i];
                                for(int k = 0; k < i; k++)
                                //for(int k = i-1; k >= 0; k--)
                                {
                                    temp[k] = linetemp[totalsize - remainingsize + k];
                                    //ylogd("testing %c", temp[k]);
                                }
                                if(submatch == false)
                                {
                                    for(int j = 0; j < numshirts; j++)
                                    {
                                        //if(shirtlen[j] == i)
                                        if(shirtlen[j] == i && submatch == false)
                                        {
                                            for(int m = 0; m < i; m++)
                                            //for(int m = i - 1; m >= 0; m--)
                                            {
                                                temp2[m] = shirts[j][m];
                                                //ylogd("fill %c", temp2[m]);
                                            }

                                            int matches = 0;
                                            for(int m = 0; m < i; m++)
                                            {
                                                if(temp[m] == temp2[m])
                                                {
                                                    matches++;
                                                }
                                            }
                                            if(matches == i)
                                            {
                                                //remainingsize = remainingsize - i;
                                                lastmatchi = i;
                                                //ylogd("matched and reamining size is %i", remainingsize);
                                                submatch = true;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

                if(submatch == false)
                {
                    n--;
                    ylogd("backtrack? n is %i", n);
                    if(n < 0)
                    {
                        continuedo = false;
                    }
                    else
                    {
                        ylogd("backtracking");
                        remainingsize = remainingsize + ns[n];
                        trylen = ns[n]-1;
                    }
                }
                else
                {
                    ns[n] = lastmatchi;
                    trylen = maxshirtlen;
                    remainingsize = remainingsize - lastmatchi;
                    n++;
                    //ylogd("continuing");
                }
            }
            if(remainingsize == 0 && totalsize > 0)
            {
                ylogd("%s is possible", linetemp);
                possibles++;
            }
            free(linetemp);
        }


        l++;
    }
    fclose(file);




    ylogi("%i shirts are able to be made", possibles);

    free(p);
    double elapsed_time = (double)(clock() - start_time) / CLOCKS_PER_SEC;
    ylogi("time : %f", elapsed_time);
    y_close_logs();
    return 0;
}
