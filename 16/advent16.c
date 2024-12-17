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

#define PROGNAME "advent16"

#define ROWS 141
#define COLS 141
#define ROWSIZE 141
#define COLSIZE 141
//#define ROWS 17
//#define COLS 17
//#define ROWSIZE 17
//#define COLSIZE 17



int rowDirs[] = {-1, 1, 0, 0};
int colDirs[] = {0, 0, -1, 1};
int maze[ROWS][COLS];


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
    if(maze[x][y] == 0)
    {
        return true;
    }
    return false;
}

// Dijkstra's Algorithm to find the shortest path
int dijkstra(int startX, int startY, int endX, int endY)
{
    int dist[ROWS][COLS];

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
    insertMinHeap(heap, (Point){startX, startY, 3, 0});

    // While the heap is not empty
    while (heap->size > 0)
    {

        Point current = extractMin(heap);
        int x = current.x, y = current.y, dir = current.dir;
        ylogd("at point %i %i", x, y);

        // If we reach the destination, stop
        if (x == endX && y == endY)
        {
            ylogd("maze end found %i %i", x, y);
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
            if(dir < 2)
            {
                if(newY != y)
                {
                    newDist+=1000;
                }
            }
            if(dir >= 2)
            {
                if(newX != x)
                {
                    newDist+=1000;
                }
            }


            if (isValidMove(newX, newY, dist) == true)
            {
                if (newDist < dist[newX][newY])
                {
                    dist[newX][newY] = newDist;
                    //prev[newX][newY][0] = x;
                    //prev[newX][newY][1] = y;
                    ylogd("coming from %i %i, dir %i, adding %i %i with a dist of %i", x, y, dir, newX, newY, newDist);
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

void reconstructPath(int prev[ROWS][COLS][2], int endX, int endY)
{
    int path[ROWS * COLS][2];
    int pathIndex = 0;

    int x = endX, y = endY;
    while (x != -1 && y != -1)
    {
        path[pathIndex][0] = x;
        path[pathIndex][1] = y;
        pathIndex++;

        int tempX = prev[x][y][0];
        int tempY = prev[x][y][1];
        x = tempX;
        y = tempY;
    }

    printf("Path: ");
    for (int i = pathIndex - 1; i >= 0; i--)
    {
        printf("(%d, %d) ", path[i][0], path[i][1]);
    }
    printf("\n");
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
    //char* str = fileslurp("advent16_sample.txt");
    char* str = fileslurp("advent16.txt");
    //char* str = fileslurp("sample2.txt");

    int start = findstart(str, ROWS, COLS, ROWSIZE, COLSIZE);
    int end = findend(str, ROWS, COLS, ROWSIZE, COLSIZE);
    mazify(str, ROWS, COLS, ROWSIZE);

    int startX = start/ROWSIZE;
    int startY = start%ROWSIZE;
    int endX = end/ROWSIZE;
    int endY = end%ROWSIZE;

    ylogi("starting at %i,%i and ending at %i,%i", startX, startY, endX, endY);
    int shortestPath = dijkstra(startX, startY, endX, endY);

    //for(int i = 0; i < ROWS; i++)
    //{
    //    for(int j = 0; j < COLS; j++)
    //        printf("%i", maze[i][j]);
    //    printf("\n");
    //}



    ylogi("found reindeer score %i", shortestPath);

    free(str);
    free(p);
    double elapsed_time = (double)(clock() - start_time) / CLOCKS_PER_SEC;
    ylogi("time : %f", elapsed_time);
    y_close_logs();
    return 0;
}
