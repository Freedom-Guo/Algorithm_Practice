//
//  main.cpp
//  分治法求大数乘法
//
//  Created by 郭倜维 on 2018/10/30.
//  Copyright © 2018 郭倜维. All rights reserved.
//

#include <iostream>
#include <string>
#include <cstdio>
#include <cmath>
#define Max 9999
using namespace std;

void cal(char* line, FILE*f_in, FILE* f_out);

string add(string s1,string s2)
{
    long len1,len2;
    len1 = s1.length();
    len2 = s2.length();
    long len = 0,M=max(len1,len2);
    int p = 0,s=0;
    string tem(M+1,'0');
    for(; len1 > s || len2 > s; len1--, len2--)
    {
        if(len1>0&&len2>0)
        {
            tem[M-len] = (((s1[len1-1]-'0')+(s2[len2-1]-'0')+p)%10)+'0';
            p = ((s1[len1-1]-'0')+(s2[len2-1]-'0')+p)/10;
        }
        else if(len1<=0)
        {
            tem[M-len] = (((s2[len2-1]-'0')+p)%10)+'0';
            p = ((s2[len2-1]-'0')+p)/10;
        }
        else
        {
            tem[M-len] = (((s1[len1-1]-'0')+p)%10)+'0';
            p = ((s1[len1-1]-'0')+p)/10;
        }
        len++;
    }
    if(p>0)
        tem[M-len]='1';
    else
    {
        int i=0;
        while(tem[i]=='0')
        {
            i++;
        }
        tem=tem.substr(i);
    }
    return tem;
}

string sub(string s1,string s2)
{
    long m=s1.length(),n=s2.length();
    long M=max(m,n);
    long i;
    int a[M],b[M],c[M];
    for(i=0; i<M; i++)
    {
        a[i] = 0;
        b[i] = 0;
        c[i] = 0;
    }
    for(i=0; i<m; i++)
        a[i]=s1[m-i-1]-'0';
    for(i=0; i<n; i++)
        b[i]=s2[n-i-1]-'0';
    for(i=0; i<M; i++)
        c[i]=a[i]-b[i];
    int s=0;
    for(i=M-1; i>=0; i--)
    {
        if(c[i]==0) continue;
        else if(c[i]>0)
        {
            s=1;
            break;
        }
        else if(c[i]<0)
        {
            s=-1;
            break;
        }
    }
    if(s==0)return "0";
    else if(s>0)
    {
        for(i=0; i<M; i++)
            if(c[i]<0)
            {
                while(c[i]<0)
                {
                    c[i+1]=c[i+1]-1;//借位（高位减一，低位加十）
                    c[i]+=10;
                }
            }
    }
    else if(s<0)
    {
        for(i=0; i<M; i++)
            c[i]=b[i]-a[i];
        for(i=0; i<M; i++)
            if(c[i]<0)
            {
                while(c[i]<0)
                {
                    c[i+1]=c[i+1]-1;//借位（高位减一，低位加十）
                    c[i]+=10;
                }
            }
    }
    i=M-1;
    while(c[i]==0)
    {
        i--;
    }
    string tem(i+1,'0');
    int x=0;
    while(i>=0)
    {
        tem[x]=c[i]+'0';
        i--;
        x++;
    }
    if(s<0) tem="-"+tem;
    return tem;
}

bool iszero(string  s1)
{
    if(s1[0]=='+'||s1[0]=='-')
        s1=s1.substr(1);
    for(int i=0; i<=s1.length()-1; i++)
    {
        if(s1[i]!='0') return false;
    }
    return true;
}

string op(string s1,string s2)
{
    if(s1[0]=='+')s1=s1.substr(1);
    if(s2[0]=='+')s2=s2.substr(1);
    string tem,t1,t2;
    if(s1[0]=='-'&&s2[0]=='-')
    {
        tem="-"+add(s1.substr(1),s2.substr(1));
    }
    else if(s1[0]!='-'&&s2[0]!='-')
    {
        tem=add(s1,s2);
    }
    else if(s1[0]!='-'&&s2[0]=='-')
    {
        tem=sub(s1,s2.substr(1));
    }
    else if(s1[0]=='-'&&s2[0]!='-')
    {
        tem=sub(s2,s1.substr(1));
    }
    return tem;
}

string mul1(string s1, string s2, unsigned long N)
{
    int s=0;
    if (iszero(s1) || iszero(s2))
        return "0";
    if(s1[0]=='-'&&s2[0]!='-')
    {
        s1=s1.substr(1);
        s=1;
    }
    else if(s1[0]=='-'&&s2[0]=='-')
    {
        s1=s1.substr(1);
        s2=s2.substr(1);
    }
    else if(s1[0]!='-'&&s2[0]=='-')
    {
        s2=s2.substr(1);
        s=1;
    }
    
    if (1 == N)
    {
        int x=s1[0]-'0';
        int y=s2[0]-'0';
        string tem(2,'0');
        tem[0]=(x*y)/10+'0';
        tem[1]=(x*y)%10+'0';
        if(tem[0]=='0')
            tem=tem.substr(1);
        if(s==1)
            tem="-"+tem;
        return tem;
    }
    unsigned long m=s1.length(),n=s2.length();
    if(m<n)
    {
        s1=string(n-m,'0')+s1;
        N=n;
        m=n;
    }
    else if(m>n)
    {
        s2=string(m-n,'0')+s2;
        N=m;
        n=m;
    }
    N=m;
    if(N%2==1)
    {
        N++;
        s1="0"+s1;
        s2="0"+s2;
    }
    string s1_l = s1.substr(0,N / 2) ;
    string s1_r = s1.substr(N / 2) ;
    string s2_l = s2.substr(0,N / 2);
    string s2_r = s2.substr(N / 2) ;
    
    string s12_l = mul1(s1_l, s2_l, N / 2);
    string s12_r = mul1(s1_r, s2_r, N / 2);
    string tem1_1=op(s1_l,"-"+s1_r);
    string tem1_2=op(s2_r,"-"+s2_l);       //66666
    string tem1=mul1(tem1_1, tem1_2, N/2);
    string tem2=op(tem1,s12_l);
    string s_lr =op(tem2,s12_r);
    s12_l+=string(N,'0');
    s_lr+=string(N/2,'0');
    string tem=op(s12_l,op( s_lr, s12_r));
    if(tem[0]=='-')
    {
        if(s==1)
            tem = tem.substr(1);
    }
    else if(tem[0]!='-')
    {
        if(s==1)
            tem = "-"+tem;
    }
    return tem;
}

string mul(string s1,string s2)
{
    int s=0;
    if(s1[0]=='-'&&s2[0]=='-')
    {
        s1=s1.substr(1);
        s2=s2.substr(1);
    }
    else if(s1[0]!='-'&&s2[0]!='-')
    {}
    else if(s1[0]=='-'&&s2[0]!='-')
    {
        s1=s1.substr(1);
        s=1;
    }
    else if(s1[0]!='-'&&s2[0]=='-')
    {
        s2=s2.substr(1);
        s=1;
    }
    unsigned long m=s1.length(),n=s2.length();
    string tem=mul1(s1, s2, max(m,n));
    if(s==1)tem="-"+tem;
    return tem;
}

int main(int argc, const char * argv[])
{
    FILE *f_in, *f_out;
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
            for(; j<n; j++)
            {
                fgets(line, Max, f_in);
                cal(line, f_in, f_out);
            }
        }
        break;
    }
    fclose(f_in);
    fclose(f_out);
    return 0;
}

void cal(char* line, FILE*f_in, FILE* f_out)
{
    char *str_1, *str_2, *str_3;
    char str_out[100];
    str_1 = strtok(line, " ");
    str_2 = strtok(NULL, " ");
    str_3 = strtok(NULL, " ");
    string line_s1, line_s2, string_out;
    int line_s3;
    line_s1 = (str_1);
    line_s2 = (str_2);
    line_s3 = atoi(str_3);
    switch(line_s3)
    {
        case 1:
            if((line_s1.find("-")!=string::npos)&&(line_s2.find("-")!=string::npos))
            {
                string::iterator it;
                for (it = line_s1.begin(); it != line_s1.end(); it++)
                {
                    if (*it == '-')
                        line_s1.erase(it);          //删除it处的一个字符
                }
                for (it = line_s2.begin(); it != line_s2.end(); it++)
                {
                    if (*it == '-')
                        line_s2.erase(it);          //删除it处的一个字符
                }
                string_out = add(line_s1, line_s2);
                string_out = "-" + string_out;
                strcpy(str_out, string_out.c_str());
                fputs(str_out, f_out);
                fputs("\n", f_out);
                break;
            }
            else if((line_s1.find("-")==string::npos)&&(line_s2.find("-")==string::npos))
            {
                string_out = add(line_s1, line_s2);
                strcpy(str_out, string_out.c_str());
                fputs(str_out, f_out);
                fputs("\n", f_out);
                break;
            }
            else if((line_s1.find("-")!=string::npos)&&(line_s2.find("-")==string::npos))
            {
                string::iterator it;
                for (it = line_s1.begin(); it != line_s1.end(); it++)
                {
                    if (*it == '-')
                        line_s1.erase(it);          //删除it处的一个字符
                }
                string_out = sub(line_s2, line_s1);
                strcpy(str_out, string_out.c_str());
                fputs(str_out, f_out);
                fputs("\n", f_out);
                break;
            }
            else
            {
                string::iterator it;
                for (it = line_s2.begin(); it != line_s2.end(); it++)
                {
                    if (*it == '-')
                        line_s2.erase(it);          //删除it处的一个字符
                }
                string_out = sub(line_s1, line_s2);
                strcpy(str_out, string_out.c_str());
                fputs(str_out, f_out);
                fputs("\n", f_out);
                break;
            }
        case 2:
            if((line_s1.find("-")!=string::npos)&&(line_s2.find("-")!=string::npos))
            {
                string::iterator it;
                for (it = line_s1.begin(); it != line_s1.end(); it++)
                {
                    if (*it == '-')
                        line_s1.erase(it);          //删除it处的一个字符
                }
                for (it = line_s2.begin(); it != line_s2.end(); it++)
                {
                    if (*it == '-')
                        line_s2.erase(it);          //删除it处的一个字符
                }
                string_out = sub(line_s2, line_s1);
                strcpy(str_out, string_out.c_str());
                fputs(str_out, f_out);
                fputs("\n", f_out);
                break;
            }
            else if((line_s1.find("-")==string::npos)&&(line_s2.find("-")==string::npos))
            {
                string_out = sub(line_s1, line_s2);
                strcpy(str_out, string_out.c_str());
                fputs(str_out, f_out);
                fputs("\n", f_out);
                break;
            }
            else if((line_s1.find("-")!=string::npos)&&(line_s2.find("-")==string::npos))
            {
                string::iterator it;
                for (it = line_s1.begin(); it != line_s1.end(); it++)
                {
                    if (*it == '-')
                        line_s1.erase(it);          //删除it处的一个字符
                }
                string_out = add(line_s1, line_s2);
                string_out = "-" + string_out;
                strcpy(str_out, string_out.c_str());
                fputs(str_out, f_out);
                fputs("\n", f_out);
                break;
            }
            else
            {
                string::iterator it;
                for (it = line_s2.begin(); it != line_s2.end(); it++)
                {
                    if (*it == '-')
                        line_s2.erase(it);          //删除it处的一个字符
                }
                string_out = add(line_s1, line_s2);
                strcpy(str_out, string_out.c_str());
                fputs(str_out, f_out);
                fputs("\n", f_out);
                break;
            }
        case 3:
            if((line_s1.find("-")!=string::npos)&&(line_s2.find("-")!=string::npos))
            {
                string::iterator it;
                for (it = line_s1.begin(); it != line_s1.end(); it++)
                {
                    if (*it == '-')
                        line_s1.erase(it);          //删除it处的一个字符
                }
                for (it = line_s2.begin(); it != line_s2.end(); it++)
                {
                    if (*it == '-')
                        line_s2.erase(it);          //删除it处的一个字符
                }
                string_out = mul(line_s1, line_s2);
                strcpy(str_out, string_out.c_str());
                fputs(str_out, f_out);
                fputs("\n", f_out);
                break;
            }
            else if((line_s1.find("-")==string::npos)&&(line_s2.find("-")==string::npos))
            {
                string_out = mul(line_s1, line_s2);
                strcpy(str_out, string_out.c_str());
                fputs(str_out, f_out);
                fputs("\n", f_out);
                break;
            }
            else if((line_s1.find("-")!=string::npos)&&(line_s2.find("-")==string::npos))
            {
                string::iterator it;
                for (it = line_s1.begin(); it != line_s1.end(); it++)
                {
                    if (*it == '-')
                        line_s1.erase(it);          //删除it处的一个字符
                }
                string_out = mul(line_s1, line_s2);
                string_out = "-" + string_out;
                strcpy(str_out, string_out.c_str());
                fputs(str_out, f_out);
                fputs("\n", f_out);
                break;
            }
            else
            {
                string::iterator it;
                for (it = line_s2.begin(); it != line_s2.end(); it++)
                {
                    if (*it == '-')
                        line_s2.erase(it);          //删除it处的一个字符
                }
                string_out = mul(line_s1, line_s2);
                string_out = "-" + string_out;
                strcpy(str_out, string_out.c_str());
                fputs(str_out, f_out);
                fputs("\n", f_out);
                break;
            }
            
    }
}
