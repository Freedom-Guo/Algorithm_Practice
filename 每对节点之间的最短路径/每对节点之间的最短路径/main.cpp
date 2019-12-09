//
//  main.cpp
//  每对节点之间的最短路径
//
//  Created by 郭倜维 on 2018/11/13.
//  Copyright © 2018 郭倜维. All rights reserved.
//

#include <iostream>
#include <limits>
#include <cstring>
#include <fstream>
using namespace std;

const int MAX = 101;
float cost[MAX][MAX];
float A[MAX][MAX];
int   P[MAX][MAX];

void PrintAllPath(int n, FILE *out);
void PrintPath(int i, int j, FILE *out);
void AllPaths(float cost[][MAX], float A[][MAX], int n);
int num;

int main()
{
    FILE *f_in, *f_out;
    char line[MAX];
    f_in = fopen("input.dat", "r");
    f_out = fopen("output.dat", "w");
    while(!feof(f_in))
    {
        fgets(line, MAX, f_in);
        num = atoi(line);
        fprintf(f_out, "%d", num);
        fputs("\n", f_out);
        int i = 0;
        for(; i<num; i++)
        {
            memset(A, 0, sizeof(float)*MAX*MAX);
            memset(P, 0, sizeof(float)*MAX*MAX);
            memset(cost, 0, sizeof(float)*MAX*MAX);
            fgets(line, MAX, f_in);
            int n = atoi(line);
            int j = 1;
            for(; j<=n; j++)
            {
                for(int l=1; l<=n; l++)
                {
                    fscanf(f_in, "%f", &cost[j][l]);
                }
            }
            for(j=1; j<=n; j++)
            {
                for(int l=1; l<=n; l++)
                {
                    if(cost[j][l]>=100)
                        cost[j][l]=999999;
                }
            }
            AllPaths(cost, A, n);
            PrintAllPath(n, f_out);
            fgets(line, MAX, f_in);
        }
        if(i == num)
            break;
    }
    fclose(f_in);
    fclose(f_out);
    return 0;
}

void AllPaths(float cost[][MAX], float A[][MAX], int n)
{
    //cout << "Graph weight:" << endl;
    for(int i=1; i<=n; i++)
        for(int j=1; j<=n; j++)
        {
            A[i][j] = cost[i][j];
        }
    for(int k=1; k<=n; k++)
    {
        for(int i=1; i<=n; i++)
            for(int j=1; j<=n; j++)
            {
                if(A[i][k] + A[k][j] < A[i][j])
                {
                    A[i][j] = A[i][k] + A[k][j];
                    P[i][j] = k;
                }
            }
        //cout << "A" << k << ":" << endl;
        //PrintCost(A, n);
    }
}

void PrintAllPath(int n, FILE *out)
{
    fprintf(out, "%d", n);
    fputs("\n", out);
    int j;
    for(int i=1; i<=n; i++)
    {
        for(j=1; j<n; j++)
        {
            if(A[i][j] < 32767)
            {
                fprintf(out, "%.0f ", A[i][j]);
            }
            else
            {
                fputs("32767 ", out);
            }
        }
        if(A[i][j] < 32767)
        {
            fprintf(out, "%.0f", A[i][j]);
        }
        else
        {
            fputs("32767", out);
        }
        fputs("\n", out);
    }
    for(int i=1; i<=n; i++)
    {
        for(int j=1; j<=n; j++)
        {
             if(j != i)
             {
                 if(A[i][j]<32767)
                 {
                     fprintf(out, "%d ", i);
                     PrintPath(i, j, out);
                     fprintf(out, "%d", j);
                     fputs("\n", out);
                 }
                 else
                 {
                     fputs("NULL\n", out);
                 }
             }
             else
             {
                 fprintf(out, "%d", i);
                 fputs("\n", out);
             }
        }
    }
}

void PrintPath(int i, int j, FILE *out)
{
    int k = P[i][j];
    if(k == 0)
        return;
    
    PrintPath(i, k, out);
    fprintf(out, "%d ", k);
    //cout << k << " ";
    PrintPath(k, j, out);
}
