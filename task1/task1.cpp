// task1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <map>

//#include <iomanip>
#include <math.h>
#include <stdio.h>

//#include <vector>
//#include <string>
using namespace std;

float percentile90(map<int,int> map_of_vals, int cnt);          //функция вычисления 90 перцентиля
float median(map<int, int> map_of_vals, int cnt);               //функция вычисления медианы
//double maxv();
//double minv();
float mean(map<int, int> map_of_vals, int cnt);                 //функция вычисления среднего значение

int main(int argc, char* argv[])
{
    int val;
    int cnt=0;               //подсчет элементов в файле
    map <int, int> map_of_vals;     // контейнер, содержащий числа, считанные из файла. Ключ - считанное число, Значение - число повторения данного числа в файле
    ifstream file(argv[1]);		// файл с числами
   
    //ifstream file("D:/Performance Lab/test1.txt");

    if (!file)
    {
        cout << "\nCant find the file";
        return 0;
    }
 
    while (!file.eof())                 //считываение значений из файла в контейнер map
    {
        file >> val;
        map_of_vals[val]++;
        cnt++;
    }
    

    printf("%.2f\n", percentile90(map_of_vals, cnt));
    printf("%.2f\n", median(map_of_vals, cnt));

    map<int, int>::iterator it = map_of_vals.end(); it--;
    printf("%.2f\n", (float)(it->first));

    it = map_of_vals.begin();
    printf("%.2f\n", (float)(it->first));

    printf("%.2f\n", mean(map_of_vals, cnt));

    file.close();
    return 0;

}

float percentile90(map<int, int> map_of_vals, int cnt)
{
    float Pvalue = 0.0f;        // искомое значение перцентиля

    float n = 0.9f * (cnt - 1) + 1.0f;
    float ipart = (int)n;
    float fpart = n - ipart;

    int fr = 0;

    map<int, int>::iterator it = map_of_vals.begin();
    for (bool fl = false; fl== false; it++)
    {
        fr += it->second;

        if (fr > n)
        {
            it--;
            Pvalue = it->first;
            fl = true;
        }
    }
    
    Pvalue = Pvalue + fpart * (it->first - Pvalue);
    return Pvalue;
}

float median(map<int, int> map_of_vals, int cnt)
{
    int Nmed = cnt / 2;
    if (cnt % 2 != 0)
        Nmed += 1;
    float med = 0.0f;
    int fr = 0;

    map<int, int>::iterator it = map_of_vals.begin();
    for (bool fl = false; fl == false; it++)
    {
        fr += it->second;
        if (fr >= Nmed)
        {
            med = it->first;

            if (cnt % 2 == 0)
            {
                Nmed++;
                if (fr < Nmed)
                {
                    ++it;
                }
                med = (med + it->first) / 2;
            }

            fl = true;
        }
    }

    return med;
}

float mean(map<int, int> map_of_vals, int cnt)
{
    float mean = 0.0f;
    map<int, int>::iterator it = map_of_vals.begin();
    while (it != map_of_vals.end())
    {
        mean += it->first * it->second;
        ++it;
    }
    return mean / cnt;
}