//
//  main.cpp
//  最近点对问题的算法实现
//
//  Created by 郭倜维 on 2018/10/30.
//  Copyright © 2018 郭倜维. All rights reserved.
//

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define Max 9999

struct POINT
{
    double x, y;
};

struct PAIRS
{
    int fp = -1, lp = -1;
    double distance = 100000000;
};

int comp(const void*p1, const void*p2)
{
    return(*(POINT*)p2).x < (*(POINT*)p1).x ? 1 : -1;
}

double Get_Distance(POINT &A, POINT &B)
{
    double abs_x = pow(double(A.x - B.x), 2);
    double abs_y = pow(double(A.y - B.y), 2);
    return sqrt(abs_x+abs_y);
}

double Find_Point(int low, int high, POINT *p);
double Find_Point_cross(int low, int high, POINT *p);

PAIRS result[100];
int result_num = 0;

int main()
{
    FILE* f_in, *f_out;
    char line[Max];
    f_in = fopen("input.dat", "r");
    f_out = fopen("output.dat", "w");
    while(!feof(f_in))
    {
        fgets(line, Max, f_in);
        int num = atoi(line);
        int i = 0;
        for(; i<num; i++)
        {
            fgets(line, Max, f_in);
            int n = atoi(line);
            int j = 0;
            POINT point[100];
            PAIRS temp;
            for(; j<n; j++)
            {
                fgets(line, Max, f_in);
                sscanf(line, "%lf %lf", &point[j].x, &point[j].y);
            }
            qsort(point, num, sizeof(POINT), comp);
            Find_Point(0, n - 1, point);
            for(int i=0;i<result_num;i++)
                for(int j=i+1;j<=result_num;j++)
                    if (point[result[i].fp].x > point[result[j].fp].x)
                    {
                        temp = result[j];
                        result[j] = result[i];
                        result[i] = temp;
                    }
            for (int i = 0;i <= result_num;i++)
                fprintf(f_out, "%.0lf %.0lf %.0lf %.0lf\t", point[result[i].fp].x, point[result[i].fp].y, point[result[i].lp].x, point[result[i].lp].y);
            fputs("\n", f_out);
            result_num = 0;
            temp.distance = 100000000;
            temp.fp = -1;
            temp.lp = -1;
            for (int i = 0;i < 100;i++)
            {
                result[i] = temp;
            }
        }
        break;
    }
    fclose(f_in);
    fclose(f_out);
    return 0;
}

double Find_Point_cross(int low, int high, POINT *p)
{
    int mid = (low + high) / 2;
    double cloest = 100000000;
    double distance;
    for (int i = mid;i != low - 1;i--)
        for (int j = mid + 1;j <= high;j++)
        {
            distance = Get_Distance(p[i], p[j]);
            if (distance < result[result_num].distance)
            {
                cloest = distance;
                result_num = 0;
                result[result_num].fp = i;
                result[result_num].lp = j;
                result[result_num].distance = cloest;
            }
            else if (distance == result[result_num].distance)
            {
                cloest = distance;
                result_num++;
                result[result_num].fp = i;
                result[result_num].lp = j;
                result[result_num].distance = cloest;
            }
        }
    return cloest;
}

double Find_Point(int low, int high, POINT *p)
{
    int mid = (low + high) / 2;
    if (low == high - 1)
    {
        double temp = Get_Distance(p[low], p[high]);
        if (temp < result[0].distance)
        {
            result_num = 0;
            result[result_num].fp = low;
            result[result_num].lp = high;
            result[result_num].distance = temp;
        }
        else if (temp == result[result_num].distance)
        {
            result_num++;
            result[result_num].fp = low;
            result[result_num].lp = high;
            result[result_num].distance = temp;
        }
        return temp;
    }
    if (low >= high)
        return 100000000;
    
    double left = Find_Point(low, mid, p);
    double right = Find_Point(mid + 1, high, p);
    double crossing = Find_Point_cross(low, high, p);
    double temp;
    
    if(left<right)
        temp = left;
    else
        temp = right;
    if(temp<crossing)
        temp = temp;
    else
        temp =crossing;
    return temp;
}
