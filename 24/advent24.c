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

#define PROGNAME "advent24"

bool x[46];
bool y[46];
bool z[46][2];
int gates = 46;
int instructions = 222;

//bool x[13];
//bool y[13];
//bool z[13][2];
//int gates = 13;
//int instructions = 36;

bool l[256][256][256][2];

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

x[0] = 1;
x[1] = 0;
x[2] = 0;
x[3] = 1;
x[4] = 1;
x[5] = 1;
x[6] = 0;
x[7] = 0;
x[8] = 0;
x[9] = 1;
x[10] = 0;
x[11] = 0;
x[12] = 0;
x[13] = 0;
x[14] = 0;
x[15] = 1;
x[16] = 1;
x[17] = 0;
x[18] = 1;
x[19] = 0;
x[20] = 0;
x[21] = 0;
x[22] = 0;
x[23] = 1;
x[24] = 1;
x[25] = 0;
x[26] = 0;
x[27] = 0;
x[28] = 1;
x[29] = 0;
x[30] = 1;
x[31] = 0;
x[32] = 0;
x[33] = 0;
x[34] = 1;
x[35] = 1;
x[36] = 1;
x[37] = 0;
x[38] = 1;
x[39] = 1;
x[40] = 0;
x[41] = 0;
x[42] = 0;
x[43] = 1;
x[44] = 1;
y[0] = 1;
y[1] = 1;
y[2] = 1;
y[3] = 1;
y[4] = 0;
y[5] = 1;
y[6] = 0;
y[7] = 1;
y[8] = 0;
y[9] = 1;
y[10] = 1;
y[11] = 1;
y[12] = 1;
y[13] = 1;
y[14] = 1;
y[15] = 0;
y[16] = 0;
y[17] = 0;
y[18] = 1;
y[19] = 1;
y[20] = 1;
y[21] = 1;
y[22] = 1;
y[23] = 1;
y[24] = 0;
y[25] = 1;
y[26] = 1;
y[27] = 0;
y[28] = 1;
y[29] = 0;
y[30] = 1;
y[31] = 0;
y[32] = 1;
y[33] = 0;
y[34] = 1;
y[35] = 1;
y[36] = 0;
y[37] = 1;
y[38] = 0;
y[39] = 0;
y[40] = 0;
y[41] = 0;
y[42] = 0;
y[43] = 0;
y[44] = 1;


    //x[0] = 1;
    //x[1] = 0;
    //x[2] = 1;
    //x[3] = 1;
    //x[4] = 0;

    //y[0] = 1;
    //y[1] = 1;
    //y[2] = 1;
    //y[3] = 1;
    //y[4] = 1;

    //x[0] = 1;
    //x[1] = 1;
    //x[2] = 1;
    //y[0] = 0;
    //y[1] = 1;
    //y[2] = 0;

    //FILE* file = fopen("temp.txt", "r"); /* should check the result */
    //FILE* file = fopen("advent24sample.txt", "r"); /* should check the result */
    FILE* file = fopen("advent24.txt", "r"); /* should check the result */
    char line[512];


    int rescount = 0;
    char** returnstring1;
    char** returnstring2;
    int i = 0;
    while(rescount < instructions)
    {
        rescount = 0;
        while (fgets(line, sizeof(line), file))
        {
            size_t sz = split_string(line, " ", &returnstring1);
            size_t sz1 = split_string(line, ">", &returnstring2);

            char* side1 = o_strdup(trimwhitespace(returnstring1[0]));
            char* side2 = o_strdup(trimwhitespace(returnstring1[2]));
            char* result = o_strdup(trimwhitespace(returnstring2[1]));

	    ylogd("%c%c%c %c%c%c %c%c%c", side1[0], side1[1], side1[2], side2[0], side2[1], side2[2], result[0], result[1], result[2]);

            if(strcasecmp(returnstring1[1], "XOR") == 0)
            {
                bool s1 = 0;
                bool s2 = 0;
                bool r = 0;
                bool s1set = 0;
                bool s2set = 0;
                char temp[3];

                temp[0] = side1[1];
                temp[1] = side1[2];
                temp[2] = '\0';
                if(side1[0] == 'x')
                {
                    s1set = 1;
                    int xy = atoi(temp);
                    s1 = x[xy];
                }
                if(side1[0] == 'y')
                {
                    s1set = 1;
                    int xy = atoi(temp);
                    s1 = y[xy];
                }
                if(side1[0] != 'x' && side1[0] != 'y')
                {
                    s1 = l[side1[0]][side1[1]][side1[2]][0];
                    s1set = l[side1[0]][side1[1]][side1[2]][1];
                }

                temp[0] = side2[1];
                temp[1] = side2[2];
                temp[2] = '\0';
                if(side2[0] == 'x')
                {
                    s2set = 1;
                    int xy = atoi(temp);
                    s2 = x[xy];
                }
                if(side2[0] == 'y')
                {
                    s2set = 1;
                    int xy = atoi(temp);
                    s2 = y[xy];
                }
                if(side2[0] != 'x' && side2[0] != 'y')
                {
                    s2 = l[side2[0]][side2[1]][side2[2]][0];
                    s2set = l[side2[0]][side2[1]][side2[2]][1];
                }

		r = s1 ^ s2;

                if(s1set == 1 && s2set == 1)
                {
                    temp[0] = result[1];
                    temp[1] = result[2];
                    temp[2] = '\0';
                    //if(result[0] == 'x')
                    //{
                    //    int xy = atoi(temp);
                    //    x[xy] = r;
                    //}
                    //if(result[0] == 'y')
                    //{
                    //    int xy = atoi(temp);
                    //    y[xy] = r;
                    //}
                    if(result[0] == 'z')
                    {
                        int xy = atoi(temp);
                        if(z[xy][1] == 0)
                        {
                            z[xy][0] = r;
                            z[xy][1] = 1;
                        }
                    }
                    if(result[0] != 'x' && result[0] != 'y' && result[0] != 'z')
                    {
                        if( l[result[0]][result[1]][result[2]][1] == 0 )
                        {
                            l[result[0]][result[1]][result[2]][0] = r;
                            l[result[0]][result[1]][result[2]][1] = 1;
                        }
                    }
                    rescount++;
                }
            }

            else if(strcasecmp(returnstring1[1], "OR") == 0)
            {
                bool s1 = 0;
                bool s2 = 0;
                bool r = 0;
                bool s1set = 0;
                bool s2set = 0;
                char temp[3];

                temp[0] = side1[1];
                temp[1] = side1[2];
                temp[2] = '\0';
                if(side1[0] == 'x')
                {
                    s1set = 1;
                    int xy = atoi(temp);
                    s1 = x[xy];
                }
                if(side1[0] == 'y')
                {
                    s1set = 1;
                    int xy = atoi(temp);
                    s1 = y[xy];
                }
                if(side1[0] != 'x' && side1[0] != 'y')
                {
                    s1 = l[side1[0]][side1[1]][side1[2]][0];
                    s1set = l[side1[0]][side1[1]][side1[2]][1];
                }

                temp[0] = side2[1];
                temp[1] = side2[2];
                temp[2] = '\0';
                if(side2[0] == 'x')
                {
                    s2set = 1;
                    int xy = atoi(temp);
                    s2 = x[xy];
                }
                if(side2[0] == 'y')
                {
                    s2set = 1;
                    int xy = atoi(temp);
                    s2 = y[xy];
                }
                if(side2[0] != 'x' && side2[0] != 'y')
                {
                    s2 = l[side2[0]][side2[1]][side2[2]][0];
                    s2set = l[side2[0]][side2[1]][side2[2]][1];
                }

		r = s1 | s2;

                if(s1set == 1 && s2set == 1)
                {
                    temp[0] = result[1];
                    temp[1] = result[2];
                    temp[2] = '\0';
                    //if(result[0] == 'x')
                    //{
                    //    int xy = atoi(temp);
                    //    x[xy] = r;
                    //}
                    //if(result[0] == 'y')
                    //{
                    //    int xy = atoi(temp);
                    //    y[xy] = r;
                    //}
                    if(result[0] == 'z')
                    {
                        int xy = atoi(temp);
                        if(z[xy][1] == 0)
                        {
                            z[xy][0] = r;
                            z[xy][1] = 1;
                        }
                    }
                    if(result[0] != 'x' && result[0] != 'y' && result[0] != 'z')
                    {
                        if( l[result[0]][result[1]][result[2]][1] == 0 )
                        {
                            l[result[0]][result[1]][result[2]][0] = r;
                            l[result[0]][result[1]][result[2]][1] = 1;
                        }
                    }
                    rescount++;
                }
            }

            else if(strcasecmp(returnstring1[1], "AND") == 0)
            {
                bool s1 = 0;
                bool s2 = 0;
                bool r = 0;
                bool s1set = 0;
                bool s2set = 0;
                char temp[3];

                temp[0] = side1[1];
                temp[1] = side1[2];
                temp[2] = '\0';
                if(side1[0] == 'x')
                {
                    s1set = 1;
                    int xy = atoi(temp);
                    s1 = x[xy];
                }
                if(side1[0] == 'y')
                {
                    s1set = 1;
                    int xy = atoi(temp);
                    s1 = y[xy];
                }
                if(side1[0] != 'x' && side1[0] != 'y')
                {
                    s1 = l[side1[0]][side1[1]][side1[2]][0];
                    s1set = l[side1[0]][side1[1]][side1[2]][1];
                }

                temp[0] = side2[1];
                temp[1] = side2[2];
                temp[2] = '\0';
                if(side2[0] == 'x')
                {
                    s2set = 1;
                    int xy = atoi(temp);
                    s2 = x[xy];
                }
                if(side2[0] == 'y')
                {
                    s2set = 1;
                    int xy = atoi(temp);
                    s2 = y[xy];
                }
                if(side2[0] != 'x' && side2[0] != 'y')
                {
                    s2 = l[side2[0]][side2[1]][side2[2]][0];
                    s2set = l[side2[0]][side2[1]][side2[2]][1];
                }

		r = s1 & s2;

                if(s1set == 1 && s2set == 1)
                {
                    temp[0] = result[1];
                    temp[1] = result[2];
                    temp[2] = '\0';
                    //if(result[0] == 'x')
                    //{
                    //    int xy = atoi(temp);
                    //    x[xy] = r;
                    //}
                    //if(result[0] == 'y')
                    //{
                    //    int xy = atoi(temp);
                    //    y[xy] = r;
                    //}
                    if(result[0] == 'z')
                    {
                        int xy = atoi(temp);
                        if(z[xy][1] == 0)
                        {
                            z[xy][0] = r;
                            z[xy][1] = 1;
                        }
                    }
                    if(result[0] != 'x' && result[0] != 'y' && result[0] != 'z')
                    {
                        if( l[result[0]][result[1]][result[2]][1] == 0 )
                        {
                            l[result[0]][result[1]][result[2]][0] = r;
                            l[result[0]][result[1]][result[2]][1] = 1;
                        }
                    }
                    rescount++;
                }
            }
            else
            {
            }

            o_free(side1);
            o_free(side2);
            o_free(result);
            free_string_array(returnstring1);
            free_string_array(returnstring2);
        }
        fseek(file, 0, SEEK_SET);
        i++;
    }
    fclose(file);

    ylogd("ran it %i times", i);
    printf("\n");
    for(int j = (gates-1); j >= 0; j--)
    {
        printf("%i", z[j][0]);
    }
    printf("\n");

    //ylogi("bfw: %i", l['b']['f']['w'][0]);
    //ylogi("bqk: %i", l['b']['q']['k'][0]);
    //ylogi("djm: %i", l['d']['j']['m'][0]);
    //ylogi("ffh: %i", l['f']['f']['h'][0]);
    //ylogi("fgs: %i", l['f']['g']['s'][0]);
    //ylogi("frj: %i", l['f']['r']['j'][0]);
    //ylogi("fst: %i", l['f']['s']['t'][0]);
    //ylogi("gnj: %i", l['g']['n']['j'][0]);
    //ylogi("hwm: %i", l['h']['w']['m'][0]);
    //ylogi("kjc: %i", l['k']['j']['c'][0]);
    //ylogi("kpj: %i", l['k']['p']['j'][0]);
    //ylogi("kwq: %i", l['k']['w']['q'][0]);
    //ylogi("mjb: %i", l['m']['j']['b'][0]);
    //ylogi("nrd: %i", l['n']['r']['d'][0]);
    //ylogi("ntg: %i", l['n']['t']['g'][0]);
    //ylogi("pbm: %i", l['p']['b']['m'][0]);
    //ylogi("psh: %i", l['p']['s']['h'][0]);
    //ylogi("qhw: %i", l['q']['h']['w'][0]);
    //ylogi("rvg: %i", l['r']['v']['g'][0]);
    //ylogi("tgd: %i", l['t']['g']['d'][0]);
    //ylogi("tnw: %i", l['t']['n']['w'][0]);
    //ylogi("vdt: %i", l['v']['d']['t'][0]);
    //ylogi("wpb: %i", l['w']['p']['b'][0]);

    free(p);


    double elapsed_time = (double)(clock() - start_time) / CLOCKS_PER_SEC;
    ylogi("time : %f", elapsed_time);
    y_close_logs();

    return 0;
}
