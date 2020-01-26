// task3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>

using namespace std;
int main(int argc, char* argv[])
{
    // файлы со значениями средней длины очереди в кассу для 5 касс
    ifstream fcash1(argv[1]), fcash2(argv[2]), fcash3(argv[3]), fcash4(argv[4]), fcash5(argv[5]);

    pair<double, int> MaxQueue;          //Пара - максимальная суммарная длина в 5 касс и соответствующий промежуток времени (1..16)
    double SumQueueL = 0.0;                 //переменная для подсчета длины очереди в 5 касс в каждый промежуток времени
    double queueL;

    MaxQueue.first = SumQueueL;
    if (!fcash1)
    {
        cout << "\nCant find the file Cash1.txt";
        return 0;
    }
    if (!fcash2)
    {
        cout << "\nCant find the file Cash2.txt";
        return 0;
    }
    if (!fcash3)
    {
        cout << "\nCant find the file Cash3.txt";
        return 0;
    }
    if (!fcash4)
    {
        cout << "\nCant find the file Cash4.txt";
        return 0;
    }
    if (!fcash5)
    {
        cout << "\nCant find the file Cash5.txt";
        return 0;
    }


    for(int i=1; i<=16; ++i)             
    {
        fcash1 >> queueL;
        SumQueueL += queueL;
        fcash2 >> queueL;
        SumQueueL += queueL;
        fcash3 >> queueL;
        SumQueueL += queueL;
        fcash4 >> queueL;
        SumQueueL += queueL;
        fcash5 >> queueL;
        SumQueueL += queueL;
        
        if (MaxQueue.first < SumQueueL)
        {
            MaxQueue.first = SumQueueL;
            MaxQueue.second = i;
        }
        SumQueueL = 0.0;
    }
 //   cout << MaxQueue.first << endl;
    cout << MaxQueue.second<<endl;

    fcash1.close();
    fcash2.close();
    fcash3.close();
    fcash4.close();
    fcash5.close();
}
