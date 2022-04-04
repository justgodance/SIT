#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

int main() {
    int count_of_files;
    cin >> count_of_files;
    for(int v=0;v<count_of_files;v++)
    {
    string st3 = "C:\\Users\\Xiaomi\\Desktop\\kk\\";
    string st4 = "C:\\Users\\Xiaomi\\Desktop\\kk\\";
    string inc;
    cin >> inc;
    st3.append(inc);
    st4.append(inc);
    string st1 = ".txt";
    string st2 = ".dat";
    st3.append(st1);
    st4.append(st2);
    char name[255];
    char name2[255];
    strcpy(name,st3.c_str());
    strcpy(name2,st4.c_str()); ///шаманим с названием файлов
    ofstream fileo(name);
    ifstream filer (name2);
    fileo << "N" << "\t";
    fileo << "m" << "\t";
    fileo << "R" << "\t";
    fileo << "s" << "\t";
    fileo << "\n";
    size_t lines_count = 0;
    string str;
    while (!filer.eof()) {
        getline(filer,str);
            lines_count++;
    } /// Количество строчек в файле
    lines_count--;
    printf("%d",lines_count);
    printf("\n");
    filer.close();
    ifstream filer2 (name2);
    float result[50];
    int result2[50];
    int megabuf[50];
    int compare[50];
    char buffer[256];
    int buf[11][11] = {
        {0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,44,45,0,0},
        {0,0,0,0,41,23,24,25,26,0,0},
        {0,0,0,40,22,10,11,12,27,48,0},
        {0,0,0,21,9,3,4,13,28,49,0},
        {0,0,20,8,2,1,5,14,29,0,0},
        {0,47,37,19,7,6,15,30,0,0,0},
        {0,46,36,18,17,16,31,38,0,0,0},
        {0,0,35,34,33,32,39,0,0,0,0},
        {0,0,43,42,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0} ///как расположены пиксели
        };
    int i,j, m=0, m1=0,p=0,k,r=1,imax,jmax,l=1, curr = 0,u=1,d=1,a,N=1,t,memory=0,cmp=0;
    float s=0,A=0,B=0,R=0,R0=0,smax=0,R1=0,s1=0,n=0,check=0;
    char sbuf;
     /* i,j,k,a,t - счетчики
    m - множественность
    st - число столбцов до нужных
    p - переход до столбцов
    r,u,d,l - счетчики в талбице
    curr - проверка на наличие пятна
    imax,jmax - позиция самого мощного
    s - сумма
    A,B,R,R0 - для разных подсчетов
    N - номер пятна
    */
    for(i=1;i<50;i++) {
        result2[i]=0;
    }
    getline(filer2,str);/// переход на новую строчку
    result2[0]=1000;
    for(a=0;a<lines_count;a++) {
        p=0;
    while(p!=16)
    {
        filer2.getline(buffer,256,'\t');
        p++;
    }; ///доходим до наших столбцов
    for(k=1;k<50;k++)
    {
        filer2>>result[k];
        result2[k]=0;
    } /// в массив
    N=1;
    for ( i = 0; i < 11; i++)
        for ( j = 0; j < 11; j++)
            if (buf[i][j]!=0)
                if(result[buf[i][j]]!=0&&result[buf[i][j]]>smax&&result2[buf[i][j]]==0) {
                    smax = result[buf[i][j]];
                    imax = i;
                    jmax = j;
                }/// определяем самый максимальный по значению первый пиксель
    if(smax!=0) {
        result2[buf[imax][jmax]] = 1;
        m+=1;
        s+=result[buf[imax][jmax]];
        B=result[buf[imax][jmax]];
        A=B;
    }
    while(smax!=0) {
    n=0;
    l=jmax;
    r=jmax+1;
    d=imax+1;
    u=imax;
    while(1){
         if(d<10)
            d+=1;
        else
            d=10;
        if(u>0)
            u-=1;
        else
            u=0;
        if(r<10)
            r+=1;
        else
            r=10;
        if(l>0)
            l-=1;
        else
            l=0;///увеличиваем площадь квадрата
        for(i=u;i<d;i++)
            for ( j = l; j < r; j++) {
                if (buf[i][j]!=0)
                    if(result2[buf[i][j]]==0&&result[buf[i][j]]!=0&&(result2[buf[i+1][j]]==1||result2[buf[i-1][j]]==1||result2[buf[i][j-1]]==1||result2[buf[i][j+1]]==1||result2[buf[i-1][j+1]]==1||result2[buf[i+1][j-1]]==1)){///ищем пиксели
                    result2[buf[i][j]] = 1;
                    m+=1;
                    curr+=1;
                    s+=result[buf[i][j]];
                    if(result[buf[i][j]]>B&&result[buf[i][j]]<A)
                        B=result[buf[i][j]];
                    if(result[buf[i][j]]>A) {
                            B=A;
                            A=result[buf[i][j]]; ///определяем A и B
                        }
                    }
            }
        if(curr==0)
            break;
        curr=0; ///отрезаем квадратики
    }
    if(s!=result[buf[imax][jmax]]) {
        R=A/s;
    }
    else {
      result2[buf[imax][jmax]] = 0;
      result[buf[imax][jmax]] = 0;
      m--;
      cmp=0;
    if(N==1)
    {
        fileo << "No events" << "     ";
        for(k=0;k<73;k++)
        {
            filer2>>check;
            fileo << "  ";
        }
        for(t=1;t<50;t++)
        {
                filer2>>check;
                fileo << check << " ";
                if(check==1)
                    cmp++;
        }
        for(t=0;t<12;t++)
            fileo << "0" << " "; ///запись в файл
        fileo << "\t";
        fileo << (49-cmp)*100/49;
        fileo << "\n";
        cmp=0;
    }
    p=0;
    m=0;
    s=0;
    A=0;
    B=0;
    smax=0;
    n=1;
      break;
    }///проверка на изолированный
    if (m>memory){
    R1=R;
    s1=s;
    m1=m;
    for(t=1;t<50;t++) {
        megabuf[t]=result2[t];
        if(result2[t] == 1) {
                result2[t] = 0;
                result[t] = 0;
            }///выводим результат, обнуляем буфер
    }
    }
    memory = m;
    p=0;
    m=0;
    s=0;
    A=0;
    B=0;
    smax=0;
    for ( i = 0; i < 11; i++)
        for ( j = 0; j < 11; j++)
            if (buf[i][j]!=0)
                if(result[buf[i][j]]!=0&&result[buf[i][j]]>smax&&result2[buf[i][j]]==0) {
                    smax = result[buf[i][j]];
                    imax = i;
                    jmax = j;
                }/// определяем самый максимальный по значению другие пиксели(если есть)
                if(smax!=0) {
                    result2[buf[imax][jmax]] = 1;
                    m+=1;
                    s+=result[buf[imax][jmax]];
                    B=result[buf[imax][jmax]];
                    A=B;
                    N+=1;
                }
    }
    if(memory!=0){
    fileo << N << "\t";
    fileo << m1 << "\t";
    fileo <<setprecision(2)<< R1 << "\t";
    fileo <<setprecision(4)<< s1 << "\t";
    for(t=1;t<50;t++)
            fileo << megabuf[t] << " ";
     for(t=0;t<12;t++)
        fileo << "0" << " "; ///запись в файл
    fileo << "\t";
    for(k=0;k<73;k++)
    {
        filer2>>check;
    }
    for(t=1;t<50;t++)
    {
            filer2>>check;
            fileo << check << " ";
            if(check==megabuf[t])
              cmp++;
    }
     for(t=0;t<12;t++)
        fileo << "0" << " ";
    fileo << "\t";
    fileo << cmp*100/49;
    fileo << "\n";
    cmp=0; /// процент совместимости
    }
    memory = 0;
    getline(filer2,str);
    if(filer2.eof())
        break;
    }
    filer2.close();
    fileo.close();
}
}











