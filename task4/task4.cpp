// task4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
using namespace std;
struct bank_visit			//структура для хранения данных об одной встрече
{
	int start;			// время входа в банк
	int finish;			// время выхода из банка
};

void get_bank_visitors(ifstream& file, vector<bank_visit>& bank_visitors);		//Процедура: считать из файла и сохранить в векторе время прихода и ухода посетителей;
void assess_visit_time(map <int, pair <int,int> >& time_and_visitors, vector<bank_visit> bank_visitors);			//Процедура: найти промежутки времени с наибольшим количеством посетителей;
void print_most_bank_visits_time(map <int, pair <int, int> > time_and_visitors);				//Процедура: вывести временные промежутки с наибольшим числом посетителей;
void print_time(int start, int finish);

int main(int argc, char* argv[])
{
    
	vector <bank_visit> bank_visitors;						// Вектор элементов, содержащих данные о встречах

	ifstream file(argv[1]);									// файл с запросами

	// контейнер map для хранения начала и конца промежутка времени, а также число посетителей в этот промежуток времени, которые посетили банк;
	map  <int, pair <int, int> > time_and_visitors;				// map <начало промежутка, <конец промежутка, количествро посетителей>>. "Начало временного промежутка" является ключом 
	

	if (!file) 
	{
		cout << "\nCant find the file";
		return 0;
	}
	
	get_bank_visitors(file, bank_visitors);
	assess_visit_time(time_and_visitors, bank_visitors);
	print_most_bank_visits_time(time_and_visitors);
	
}

void get_bank_visitors(ifstream& file, vector<bank_visit>& bank_visitors)
{
	bank_visit visit;				// структура для вставки данных в вектор структур
	int hours;
	int mins;
	while (!file.eof())
	{
		file >> hours;
		file.ignore(1);
		file >> mins;

		mins += hours * 60;
		visit.start = mins;

		file >> hours;
		file.ignore(1);
		file >> mins;

		mins += hours * 60;
		visit.finish = mins;

		bank_visitors.push_back(visit);
	}

}
void assess_visit_time(map <int, pair <int, int> >& time_and_visitors, vector<bank_visit> bank_visitors)
{
	bank_visit check;										//переменная для хранения времени начала и конца рассматриваемого промежутка времени
	int cnt;												//счетчик количества посетителей в данный промежуток времени
	pair <int, int> p;

	for (int i = 0; i < bank_visitors.size(); ++i)
	{
		check.start = bank_visitors[i].start;
		check.finish = bank_visitors[i].finish;
		cnt = 1;
		for (int j = 0; j < bank_visitors.size(); j++)
		{
			if (i == j)
				j++;
			if (j < bank_visitors.size())
			{
				if (bank_visitors[j].start< check.finish && bank_visitors[j].finish > check.start)
				{
					cnt++;
					if (check.finish > bank_visitors[j].finish)
						check.finish = bank_visitors[j].finish;
					if (check.start < bank_visitors[j].start)
						check.start = bank_visitors[j].start;
				}
			}
		}
		// Вставить информацию о времени и количестве посетителей в контейнер только в том случае, если такого времени не было вставлено ранее
		if (time_and_visitors.find(check.start) == time_and_visitors.end())
		{
			p = make_pair(check.finish, cnt);
			time_and_visitors[check.start] = p;
		}
		cnt = 1;
	}
}
void print_most_bank_visits_time(map <int, pair <int, int> > time_and_visitors)
{
	int MaxVisitors=0;//Количество посетителей, максимальное за один промежуток времени среди всех промежутков
	map<int, pair <int, int> >::iterator it = time_and_visitors.begin();
	int start = 0;
	int finish = 0;

	while (it != time_and_visitors.end())				// Ищем максимальное количество посетителей
	{
		if (it->second.second > MaxVisitors)
			MaxVisitors = it->second.second;
		++it;
	}

	it = time_and_visitors.begin();
	while (it != time_and_visitors.end())
	{
		if (it->second.second == MaxVisitors)
		{
			if (start == 0)
			{
				start = it->first;
				finish = it->second.first;
				it++;
			}
			if (it == time_and_visitors.end())
			{
				print_time(start, finish);
				//--it;
			}
			else if (it->first == finish)
			{
				finish = finish = it->second.first;
				++it;
			}
			else
			{
				print_time(start, finish);
				start = 0;
			}
		}
	}
}

void print_time(int start, int finish)
{
	cout << start / 60 << ":";
	if (start % 60 == 0)
		cout << "00";
	else if (start % 60 < 10)
		cout << "0" << start % 60;
	else
		cout << start % 60;

	cout << " " << finish / 60 << ":";
	if (finish % 60 == 0)
		cout << "00";
	else if (finish % 60 < 10)
		cout << "0" << finish % 60;
	else
		cout << finish % 60;

	cout << endl;
}