#include <stdio.h>
#include <stdlib.h>
#include <string>

int main()
{
    FILE *S1, *S2;
    S1 = fopen("S02_R03_events.dat", "r"); /// Исходный файл
    S2 = fopen("RE_S02_R03_events.txt", "w"); /// Запись результатов
    fprintf(S2, "m\t");
    fprintf(S2, "%R\t");
    fprintf(S2, "%R0\n");
    size_t lines_count = 0;
    while (! feof(S1))
    {
        if (fgetc(S1) == '\n')
            lines_count++;
    } /// Количество строчек в файле
    printf("%d",lines_count);
    printf("\n");
    fclose(S1);
    S1 = fopen("S02_R03_events.dat", "r");
    float result[49];
    int result2[49];
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
    int i,j,n=0, m=0, m1=0, st=49,p=0,k,r;
    /*
    st - кол-во интересующих столбцов = 49
    p - расстояние до интересующих столбцов = 16
    i - общий счетчик
    j - внутренний счетчик <49
    buf - представление в двумерном виде
    result - буфер значений
    result2 - результат на котором видны пятна
    m - кол-во пикселей в пятне
    s - сумма пикселей в пятне
    A - самое большое число в пятне
    B - второе по значимости
    */
    float s=0,A=0,B=0,R=0,R0=0;
    for(i=0;i<49;i++)
    {
        result2[i]=0;
    }
    while (1)
    {
        if (fgetc(S1) == '\n')
            break;
    } /// переход на новую строчку
    for(r=0;r<lines_count;r++)
    {
        while(p!=16)
            if (fgetc(S1) == '\t')
                p++; ///доходим до наших столбцов
        for(k=0;k<49;k++)
    {
        fscanf(S1, "%f", &result[k]);
    }
    for ( i = 0; i < 11; i++)
        for ( j = 0; j < 11; j++)
            if (buf[i][j]!=0)
                if(result[buf[i][j]-1]!=0&&(result[buf[i+1][j]-1]!=0||result[buf[i-1][j]-1]!=0||result[buf[i][j-1]-1]!=0||result[buf[i][j+1]-1]!=0||result[buf[i-1][j+1]-1]!=0||result[buf[i+1][j-1]-1]!=0))
                    {
                        result2[buf[i][j]-1] = 1;///проходим по пикселям, ищем пятна
                        m+=1;
                        s+=result[buf[i][j]-1];
                        if(result[buf[i][j]-1]>B&&result[buf[i][j]-1]<A)
                            B=result[buf[i][j]-1];
                        if(result[buf[i][j]-1]>A)
                        {
                            B=A;
                            A=result[buf[i][j]-1]; ///определяем A и B
                        }
                    }
    if(s!=0)
    {
        R=A/s;
        R0=(B+A)/s;
    }
    fprintf(S2, "%d\t", m);
    fprintf(S2, "%0.2f\t", R);
    fprintf(S2, "%0.2f\t", R0);
    for(k=0;k<49;k++)
    {
        fprintf(S2, "%d ", result2[k]);
        result2[k] = 0; ///выводим результат, обнуляем буфер
    }
    fprintf(S2, "\n");
    while (1)
    {
        if (fgetc(S1) == '\n')
            break;
        if (feof(S1))
            break; ///переходим на новую строку
    }
    p=0;
    m=0;
    s=0;
    A=0;
    B=0;
    }
    fclose(S1);
    fclose(S2);
}


