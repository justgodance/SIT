#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <cmath>

using namespace std;

int main() {
    int count_of_files;
    cin >> count_of_files;
    string st3 = "C:\\Users\\Xiaomi\\Desktop\\kk\\ALL_TIME.txt";
    char name[255];
    strcpy(name,st3.c_str());
    ofstream fileo(name); ///������
    for(int v=0;v<count_of_files;v++){
        string st5 = "C:\\Users\\Xiaomi\\Desktop\\kk\\";
        string inc;
        cin >> inc;;
        st5.append(inc);
        string st1 = ".txt";
        st5.append(st1);
        char name3[255];
        strcpy(name3,st5.c_str()); ///������� � ��������� ������
        ifstream filer2 (name3); ///��������-������
        string str;
        getline(filer2,str);/// ������� �� ����� �������
        float time[61];
        int matrix[61];
        float check=0;
        float sum = 0;
        int k,p,n=0;
        char sbuf;
        /*
        time - �������� �������
        matrix - ��������/������
        check - ����� �������
        k - ��������
        p - ����� ��� ������ �������
        str - �������� ������
        n - ������� �����
        */
        while (!filer2.eof()){
                filer2>>sbuf;
                if(sbuf=='0')
                    cout<<" ";
                else{
                    for(k=0;k<3;k++){
                        filer2>>check;
                    } /// ������� �� ������� �������
                    for(k=0;k<61;k++){
                        filer2>>matrix[k];
                    } ///������ �����-��������
                    for(k=0;k<61;k++){
                        filer2>>time[k];
                        if(matrix[k]==1){
                            sum+=time[k];
                            n++;
                        }
                    } ///��������� � �������� ������ ��������
                    sum/=n;
                    for(k=0;k<61;k++){
                       if(time[k]!=0)
                           fileo << fixed <<setprecision(1) << abs(time[k]-sum) << "\n";
                    } ///������� ������ t
                    sum=0;
                    n=0;
                    for(k=0;k<61;k++){
                       time[k]=0;
                       matrix[k]=0;
                    } ///��������
                }
                    getline(filer2,str);
        }
        filer2.close();
    }
    fileo.close();
}
