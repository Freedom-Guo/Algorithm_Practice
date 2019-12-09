//
//  main.cpp
//  最优二分查找法
//
//  Created by 郭倜维 on 2018/11/13.
//  Copyright © 2018 郭倜维. All rights reserved.
//

#include<iostream>
using namespace std;
#define MAX 9999


void OPTIMAL_BST(int n, float p[], float q[], float **e, float **w, int **root);
void CONSTRUCT_OPTIMAL_BST(int** &root, int i, int j, int flag, FILE *out);

int main()
{
    FILE* f_in = fopen("input.dat", "r");
    FILE* f_out = fopen("output.dat", "w");
    char line[MAX];
    int num;
    while(!feof(f_in))
    {
        fgets(line, MAX, f_in);
        num = atoi(line);
        int i = 0;
        for(; i<num; i++)
        {
            fgets(line, MAX, f_in);
            int n = atoi(line);
            float *p = new float[n + 1];
            float *q = new float[n + 1];
            float **e = new float *[n + 2];
            float **w = new float *[n + 2];
            int **root = new int *[n + 1];
            
            for (int i = 0;i < n + 2;i++)
                e[i] = new float[n + 1];
            for (int i = 0;i < n + 2;i++)
                w[i] = new float[n + 1];
            for (int i = 0;i < n + 1;i++)
                root[i] = new int[n + 1];
            
            for (int i = 1;i <= n;i++)
                fscanf(f_in, "%f", &p[i]);
            for (int i = 0;i <= n;i++)
                fscanf(f_in, "%f", &q[i]);
            
            OPTIMAL_BST(n, p, q, e,w, root);
            
            fputs("最小搜索代价为：", f_out);
            fprintf(f_out, "%f", e[1][n]);
            fputs("\n", f_out);
            CONSTRUCT_OPTIMAL_BST(root, 1, n, 1, f_out);
            
        }
    }
    fclose(f_in);
    fclose(f_out);
    return 0;
}

void OPTIMAL_BST(int n, float p[], float q[], float **e, float **w, int **root)
{
    int i = 1;
    for(; i <= n+1; i++)
    {
        e[i][i-1] = q[i-1];
        w[i][i-1] = q[i - 1];
    }
    int l = 1;
    for(; l <= n; l++)
    {
        int i = 1;
        for (; i <= n - l + 1;i++)
        {
            int j = i + l - 1;
            e[i][j] = 999999;
            w[i][j] = w[i][j-1] + p[j] + q[j];
            int r = i;
            for (; r <= j; r++)
            {
                float t = e[i][r - 1] + e[r + 1][j] + w[i][j];
                if (t < e[i][j])
                {
                    e[i][j] = t;
                    root[i][j] = r;
                }
                //cout<<root[i][j]<<"\n";
            }
        }
    }
}

void CONSTRUCT_OPTIMAL_BST(int** &root, int i, int j, int flag, FILE *out)
{
    if (i <= j){
        if (flag == 1){
            fprintf(out,"k%d为根\n",root[i][j]);
        }
        else if (flag == 0){
            fprintf(out, "k%d为k%d的左孩子\n", root[i][j], j + 1);
        }
        else{
            //cout << "k" << root[i][j] << "为k" << i - 1 << "的右孩子" << endl;
            //cout<<i<<" "<<j<<"\n";
            fprintf(out, "k%d为k%d的右孩子\n", root[i][j], i-1);
        }
        CONSTRUCT_OPTIMAL_BST(root, i, root[i][j] - 1, 0, out);
        CONSTRUCT_OPTIMAL_BST(root, root[i][j] + 1, j, 2, out);
    }
    else if (j == (i - 1)){
        if (flag == 0){
            //cout<<i<<" "<<j<<"\n";
            fprintf(out, "d%d为k%d的左孩子\n", j, j + 1);
        }
        else if (flag == 2){
            fprintf(out, "d%d为k%d的右孩子\n", j, i - 1);
        }
    }
}
