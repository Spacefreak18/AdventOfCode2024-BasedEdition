#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>

#include <orcania.h>
#include <yder.h>

#include "../advent.h"

#define PROGNAME "advent09"


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




    char* str = fileslurp("advent09sample.txt");
    //char* str = fileslurp("advent09.txt");

    struct _pointer_list* fsmap = o_malloc(sizeof(struct _pointer_list));
    pointer_list_init(fsmap);

    int i = 0;
    int file_id = 0;

    int len = strlen(str);
    ylogd("string length is %i", len);

    char cblock[2];
    cblock[1] = '\0';
    for(int i = 0; i < strlen(str); i++)
    {
        cblock[0] = str[i];
        int blocks = atoi(cblock);
        //ylogd("arranging %i blocks", blocks);
        if((i+1)%2 == 0)
        {
            for(int j = 0; j<blocks; j++)
            {
                pointer_list_append(fsmap, o_strdup("."));
            }
        }
        else
        {
            char* temp;
            asprintf(&temp, "%i", file_id);
            for(int j = 0; j<blocks; j++)
            {
                pointer_list_append(fsmap, o_strdup(temp));
            }
            free(temp);
            file_id++;
        }
    }
    free(str);


    int sz = pointer_list_size(fsmap);
    ylogd("list size %i", pointer_list_size(fsmap));

    int* arr = malloc(sizeof(int) * sz);
    for(int j = 0; j<sz; j++)
    {
        arr[j] = -1;
    }
    for(int j = 0; j<sz; j++)
    {
        char* inode = pointer_list_get_at(fsmap, j);

        if(strcmp(inode, ".") == 0)
        {
        }
        else
        {
            arr[j] = atoi(pointer_list_get_at(fsmap, j));
        }
    }

    for(int e = 0; e < pointer_list_size(fsmap); e++)
    {
        free(pointer_list_get_at(fsmap, e));
    }
    pointer_list_clean(fsmap);
    o_free(fsmap);

    if(p->part2 > 0)
    {
        for(int j = sz-1; j>0; j--)
        {
            int inode = arr[j];
            if(inode < 0)
            {
                continue;
            }
            int fsize = 0;
            for(int jj = sz-1; jj>0; jj--)
            {
                if(arr[jj] == inode)
                {
                    fsize++;
                }
            }
            //ylogd("filesize of %i is %i", inode, fsize);
            int k = 0;
            bool rearranged = false;
            while(k<sz && rearranged == false)
            {
                int free_inode = arr[k];
                if (free_inode == -1)
                {
                    int kk = k;
                    int blocksfree = 0;
                    int free = 0;
                    while(free == 0)
                    {
                        if(arr[kk] == -1)
                        {
                            blocksfree++;
                        }
                        else
                        {
                            free++;
                        }
                        kk++;
                    }
                    //ylogd("found %i blocks free", blocksfree);
                    if(blocksfree >= fsize && k<j)
                    {
                        //ylogd("moving file %i position %i", inode, k);
                        for(int a = 0; a < fsize; a++)
                        {
                            arr[k+a] = inode;
                        }
                        //ylogd("position %i", k+fsize);
                        for(int a = (k+fsize); a < sz; a++)
                        {
                            if(arr[a] == inode)
                            {
                                arr[a] = -2;
                            }
                        }
                        rearranged = true;
                    }

                }
                k++;
            }
        }
    }
    else
    {
        for(int j = sz-1; j>0; j--)
        {
            int inode = arr[j];
            int k = 0;
            bool rearranged = false;
            while(k<sz && rearranged == false)
            {
                int free_inode = arr[k];
                if (free_inode == -1)
                {
                    arr[k] = inode;
                    arr[j] = -2;
                    rearranged = true;
                }
                k++;
            }
        }
    }



    uint64_t checksum = 0;
    for(int j = 0; j < sz; j++)
    {
        int i = arr[j];
        if(i > 0)
        {
            checksum += (i*j);
        }
    }

    free(arr);
    free(p);
    ylogi("file checksum is %llu", checksum);
    double elapsed_time = (double)(clock() - start_time) / CLOCKS_PER_SEC;
    ylogi("time : %f", elapsed_time);
    y_close_logs();

    return 0;
}
