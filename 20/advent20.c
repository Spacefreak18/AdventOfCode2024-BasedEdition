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

#define PROGNAME "advent20"

#define ROWS 141
#define COLS 141
#define ROWSIZE 141
#define COLSIZE 141
//#define ROWS 15
//#define COLS 15
//#define ROWSIZE 15
//#define COLSIZE 15



int rowDirs[] = {-1, 1, 0, 0};
int colDirs[] = {0, 0, -1, 1};
int maze[ROWS][COLS];
int dist[ROWS][COLS];
int movemap[4096*32];

typedef struct
{
    int x;
    int y;
    int dir;
    int dist;
} Point;

typedef struct
{
    Point* arr;
    int size;
} MinHeap;

// Function to create a min-heap
MinHeap* createMinHeap(int size)
{
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->arr = (Point*)malloc(size * sizeof(Point));
    heap->size = 0;
    return heap;
}

// Swap two points in the min-heap
void swap(Point* a, Point* b)
{
    Point temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(MinHeap* heap, int idx)
{
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < heap->size && heap->arr[left].dist < heap->arr[smallest].dist)
    {
        smallest = left;
    }
    if (right < heap->size && heap->arr[right].dist < heap->arr[smallest].dist)
    {
        smallest = right;
    }

    if (smallest != idx)
    {
        swap(&heap->arr[idx], &heap->arr[smallest]);
        minHeapify(heap, smallest);
    }
}

void insertMinHeap(MinHeap* heap, Point p)
{
    heap->arr[heap->size] = p;
    int idx = heap->size++;

    while (idx > 0 && heap->arr[(idx - 1) / 2].dist > heap->arr[idx].dist)
    {
        swap(&heap->arr[(idx - 1) / 2], &heap->arr[idx]);
        idx = (idx - 1) / 2;
    }
    minHeapify(heap, 0);
}

Point extractMin(MinHeap* heap)
{
    if (heap->size == 0)
    {
        return (Point){-1, -1, -1, -1};
    }

    Point min = heap->arr[0];
    heap->arr[0] = heap->arr[--heap->size];
    minHeapify(heap, 0);
    return min;
}

bool isValidMove(int x, int y, int visited[ROWS][COLS])
{
    if(maze[x][y] == 0 && x > -1 && y > -1)
    {
        return true;
    }
    return false;
}

// Dijkstra's Algorithm to find the shortest path
int dijkstra(int startX, int startY, int endX, int endY)
{


    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            dist[i][j] = INT_MAX;
            //prev[i][j][0] = prev[i][j][1] = -1;  // No predecessor at first
        }
    }

    MinHeap* heap = createMinHeap(ROWS * COLS);

    dist[startX][startY] = 0;
    insertMinHeap(heap, (Point){startX, startY, 0, 0});

    // While the heap is not empty
    while (heap->size > 0)
    {

        Point current = extractMin(heap);
        int x = current.x, y = current.y, dir = current.dir;

        // If we reach the destination, stop
        if (x == endX && y == endY)
        {
            ylogd("maze end found %i %i in %i moves", x, y, dist[x][y]);
            free(heap->arr);
            free(heap);
            return dist[x][y];
        }


        for (int i = 0; i < 4; i++)
        {
            int newDir = i;
            int newX = x + rowDirs[i];
            int newY = y + colDirs[i];

            int newDist = dist[x][y] + 1;

            if (isValidMove(newX, newY, dist) == true)
            {
                if (newDist < dist[newX][newY])
                {
                    dist[newX][newY] = newDist;
                    //prev[newX][newY][0] = x;
                    //prev[newX][newY][1] = y;
                    insertMinHeap(heap, (Point)
                    {
                        newX, newY, newDir, newDist
                    });
                }
            }
        }

    }

    ylogd("heap exhausted");
    free(heap->arr);
    free(heap);
    return -1;
}


int findend(char* puzzle, int rows, int cols, int rowsize, int colsize)
{
    int i =0;
    int end = 0;
    while(i < (rows * cols))
    {
        if(puzzle[i] == 'E')
        {
            end = i;
            ylogd("found ending position %i", i);
        }
        i++;
    }

    return end;
}

int findstart(char* puzzle, int rows, int cols, int rowsize, int colsize)
{
    int i =0;
    int start = 0;
    while(i < (rows * cols))
    {
        if(puzzle[i] == 'S')
        {
            start = i;
            ylogd("found starting position %i", i);
        }
        i++;
    }

    return start;
}

void mazify(char* puzzle, int rows, int cols, int rowsize)
{
    for(int i = 0; i < (rows*cols); i++)
    {
        int row = i / rowsize;
        int col = i % rowsize;
        if(puzzle[i] == '#')
        {
            maze[row][col] = 1;
        }
        if(puzzle[i] == '.')
        {
            maze[row][col] = 0;
        }
        if(puzzle[i] == 'E')
        {
            maze[row][col] = 0;
        }
        if(puzzle[i] == 'S')
        {
            maze[row][col] = 0;
        }
    }
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
    //char* str = fileslurp("advent20_sample.txt");
    char* str = fileslurp("advent20.txt");

    int start = findstart(str, ROWS, COLS, ROWSIZE, COLSIZE);
    int end = findend(str, ROWS, COLS, ROWSIZE, COLSIZE);
    mazify(str, ROWS, COLS, ROWSIZE);

    int startX = start/ROWSIZE;
    int startY = start%ROWSIZE;
    int endX = end/ROWSIZE;
    int endY = end%ROWSIZE;

    ylogi("starting at %i,%i and ending at %i,%i", startX, startY, endX, endY);
    int shortestPath = dijkstra(startX, startY, endX, endY);
    ylogi("shortest path %i", shortestPath);

    int i = 1;
    int k = 1;
    int ret = shortestPath;
    while(i < ROWS)
    {
        int temp1 = maze[i][k];
        int temp2 = maze[i][k+1];
        int temp3 = maze[i+1][k];
        maze[i][k] = 0;
        //maze[i][k+1] = 0;
        ret = dijkstra(startX, startY, endX, endY);
        int savings = shortestPath - ret;
        ylogd("saved %i from %i,%i", savings, i, k+1);
        movemap[savings] = movemap[savings] + 1;
        //maze[i][k+1] = temp2;

        //maze[i+1][k] = 0;
        //ret = dijkstra(startX, startY, endX, endY);
        //savings = shortestPath - ret;
        //ylogd("saved %i from %i,%i", savings, i+1, k);
        //movemap[ret] = movemap[ret] + 1;
        //maze[i+1][k] = temp3;
        maze[i][k] = temp1;

        k++;
        if(k == (COLS-1))
        {
            i++;
            k=1;
        }
    }

    ylogi("there are %i cheats that save 2 picoseconds", movemap[2]);
    ylogi("there are %i cheats that save 4 picoseconds", movemap[4]);
    ylogi("there are %i cheats that save 6 picoseconds", movemap[6]);
    ylogi("there are %i cheats that save 8 picoseconds", movemap[8]);
    ylogi("there are %i cheats that save 10 picoseconds", movemap[10]);
    ylogi("there are %i cheats that save 12 picoseconds", movemap[12]);

    uint64_t sum = 0;
    for(int j = 100; j < (4096*32); j++)
    {
        sum = sum + movemap[j];
    }
    //for(int i = 0; i < ROWS; i++)
    //{
    //    for(int j = 0; j < COLS; j++)
    //        printf("%i", maze[i][j]);
    //    printf("\n");
    //}



    ylogi("there are %llu cheats that save atleast 100 seconds", sum);

    free(str);
    free(p);
    double elapsed_time = (double)(clock() - start_time) / CLOCKS_PER_SEC;
    ylogi("time : %f", elapsed_time);
    y_close_logs();
    return 0;
}
