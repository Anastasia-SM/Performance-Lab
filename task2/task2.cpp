// task2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath> 

using namespace std;

int check_vertices(vector <pair<double, double >> vec_of_points, pair <double, double> p);                    //Проверка: находится ли точка на одной из вершин
int check_edges(vector <pair<double, double >> vec_of_points, pair <double, double> p);                      //Проверка: находится ли точка на одном из ребер
int edges(double px, double py, double x1, double y1, double x2, double y2);                                                  //Функция: проверка принадлежности точки прямой, заданной двумя вершинами фигуры
int check_inside(vector <pair<double, double >> vec_of_points, pair <double, double> p);                   //Проверка: находится ли точка внутри фигуры
int intersections(double px, double py, double x1, double y1, double x2, double y2);                                           //Функция подсчета пересечений

int main(int argc, char* argv[])
{
    double x,y;
    pair <double, double> p;
    vector <pair<double, double >> vec_of_points;     // контейнер, содержащий пары значений (x;y) для точек, считанных из файла.
    ifstream file1(argv[1]);		// файл с координатами вершин четырехугольника

    //ifstream file("D:/Performance Lab/test21.txt");

    if (!file1)
    {
        cout << "\nCant find the file";
        return 0;
    }
 
    while (!file1.eof())                
    {
        file1 >> x;
        file1 >> y;
        p = make_pair(x, y);
        vec_of_points.push_back(p);
    }
    file1.close();

    ifstream file2 (argv[2]);		// файл с координатами вершин четырехугольника
    if (!file2)
    {
        cout << "\nCant find the file";
        return 0;
    }
    while (!file2.eof())                 
    {
        file2 >> x;
        file2 >> y;
        p = make_pair(x, y);

        if (check_vertices(vec_of_points, p) == 1)
            cout << 0 << endl;
        else if (check_edges(vec_of_points, p) == 1)
            cout << 1 << endl;
        else if (check_inside(vec_of_points, p) == 1)
            cout << 2 << endl;
        else cout << 3 << endl;
    }
    file2.close();
    return 0;
}

int check_vertices(vector <pair<double, double >> vec_of_points, pair <double, double> p)
{
    for (int i = 0; i < 4; i++)
    {
        if (p.first == vec_of_points[i].first && p.second == vec_of_points[i].second)
            return 1;
    }
    return 0;
}

int check_edges(vector <pair<double, double >> vec_of_points, pair <double, double> p)
{
    double x2,y2;
    double xp = p.first;
    double yp = p.second;
    double x1 = vec_of_points[3].first;
    double y1 = vec_of_points[3].second;\

    for (int i = 0; i < 4; ++i)
    {
        double x2 = vec_of_points[i].first;
        double y2 = vec_of_points[i].second;
        if (edges(xp, yp, x1, y1, x2, y2) == 1)
        {
            if (y1 > y2)
            {
                swap(x1, x2);
                swap(y1, y2);
            }
            if (yp < y1 || yp > y2)
                return 0;
            else
                return 1;
        }
        x1 = x2;
        y1 = y2;
    }
    return 0;
}

int edges(double px, double py, double x1, double y1, double x2, double y2)
{
    double x = x1 + (py - y1) * (x2 - x1) / (y2 - y1);
    if (x == px)
        return 1;
    else 
        return 0;
    //x = round(x * 100) / 100;
}

int check_inside(vector <pair<double, double >> vec_of_points, pair <double, double> p)
{
    //Из точки проводится бесконечный луч. Если точка внутри фигуры, то число пересечений луча с фигурой будет нечетным, если точка находится снаружи - четным. 

    int intersect_cnt = 0;      // счетчик пересечений;
    double xp = vec_of_points[3].first;
    double yp = vec_of_points[3].second;

    for (int i = 0; i < 4; ++i)
    {
        intersect_cnt += intersections(p.first, p.second, xp, yp, vec_of_points[i].first, vec_of_points[i].second);
        xp = vec_of_points[i].first;
        yp = vec_of_points[i].second;
    }
    if (intersect_cnt % 2 != 0)
        return 1;
    else return 0;

}

int intersections(double px, double py, double x1, double y1, double x2, double y2)
{
    if (y1 > y2) {
        std::swap(x1, x2);
        std::swap(y1, y2);
    }

    if (py < y1 || py >= y2)
        return 0;

    if (x1 == x2)
        return px <= x1;

    int x = x1 + (py - y1) * (x2 - x1) / (y2 - y1);
    return px <= x;
}