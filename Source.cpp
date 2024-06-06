#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <cstring>
#include <vector>
#include<list>
#include<iterator>
using namespace std;


void add_edge(list<int> adj_list[], int u, int v)       //�إ�adjlist
{
	adj_list[u].push_back(v);
	adj_list[v].push_back(u);
}
static int nodeiy;
static double START,END;
void sorting(list<int> adj_list[], int v)               //��X�̪���list
{
	START = clock();
	int iy, max = 0;
	for (iy = 1; iy < v; ++iy)
	{
		if (adj_list[iy].size() > max) {
			max = adj_list[iy].size();
			nodeiy = iy;
		}
	}
	cout << "Node " << nodeiy
		<< "'s size is max=" << max << endl;
}
void greedyColoring(list<int> adj_list[], int v, int nodeiy)         //�γg�ߺt��k�W��
{
	START = clock();
	int* result;
	result = new int[v + 1];
	for (int k = 1; k <= v; k++)
	{
		result[k] = -1;
	}
	result[0] = 0;
	bool* available;
	available = new bool[v + 1];
	for (int k = 1; k <= v; k++)
	{
		available[k] = false;
	}

	if (nodeiy == 0) {
		for (int i = 1; i <= v; i++)
		{
			list<int>::iterator it;                  //�N�۾F�`�I���C��аO�����i��
			for (it = adj_list[i].begin(); it != adj_list[i].end(); ++it)
			{
				if (result[*it] != -1)
				{
					available[result[*it]] = true;
				}
			}

			int cr;                                  //�M��ö�W�Ĥ@�ӥi�Ϊ��C��
			for (cr = 1; cr <= v; cr++)
			{
				if (available[cr] == false)
					break;
			}

			result[i] = cr;
	   												 //�N�C�⭫�]���i��
			for (it = adj_list[i].begin(); it != adj_list[i].end(); ++it)
			{
				if (result[*it] != -1)
					available[result[*it]] = false;
			}
		}
	}
	if (nodeiy != 0) {
		for (int i = 1; i <= v; i++)
		{
			result[nodeiy] = 1;                      //�N�s���̦h���Y�`�I��W�Ĥ@��
			list<int>::iterator it;
			for (it = adj_list[i].begin(); it != adj_list[i].end(); ++it)
				if (result[*it] != -1)
					available[result[*it]] = true;

			int cr;
			for (cr = 1; cr <= v; cr++)
				if (available[cr] == false)
					break;

			result[i] = cr;

			for (it = adj_list[i].begin(); it != adj_list[i].end(); ++it)
				if (result[*it] != -1)
					available[result[*it]] = false;
		}
		cout << result[nodeiy] << endl;
	}
	
	int color = 0;									//��X���G
	for (int i = 1; i <= v; i++)
	{
		if (result[i] > color) {
			color = result[i];
		}
	}
	cout << "�@" << color << "���C��" << endl << endl;
	END = clock();

}

int main()
{
	cout << "�n�}�Ҫ��ɦW��node___--?" << endl
		<< "(��J�Ʀr)" << endl;
	int num = 0;
	cin >> num;

	ifstream inf;
	if (num == 40) inf.open("node40.txt", ios::in);
	if (num == 100) inf.open("node100.txt", ios::in);
	if (num == 200) inf.open("node200.txt", ios::in);
	if (num == 300) inf.open("node300.txt", ios::in);
	if (num == 500) inf.open("node500.txt", ios::in);
	if (num == 1000) inf.open("node1000.txt", ios::in);
	if (num == 2000) inf.open("node2000.txt", ios::in);
	if (num == 3000) inf.open("node3000.txt", ios::in);
	if (num == 5000) inf.open("node5000.txt", ios::in);
	if (num == 10000) inf.open("node10000.txt", ios::in);
	if (!inf)
	{
		cout << "�L�kŪ�J�ɮ�\n";
		system("pause");
		return 0;
	}
	if (inf.is_open())
	{
		int numoflink = 0;
		cout << "�}��node" << num << ".txt" << endl;
		string line;

		getline(inf, line);                 //Ū�Ĥ@��
		int first = line.find(':');
		string substr = line.substr(first + 2);
		num = atoi(substr.c_str());
		cout << "num of nodes " << num << endl;

		getline(inf, line);                 //Ū�ĤG��
		first = line.find(':');
		substr = line.substr(first + 2);
		numoflink = atoi(substr.c_str());
		cout << "num of links " << numoflink << endl;

		int v = num;

		list<int>* adj_list;
		adj_list = new list<int>[v + 1];

		while (!inf.eof())                  //Ū�ĤT��H��
		{
			int p1 = 0, p2 = 0;
			inf >> p1 >> p2;
			getline(inf, line);
			add_edge(adj_list, p1, p2);
		}
		inf.close();


		int mode = 0;
		do {
			cout << endl << "(1)�n�q�Ĥ@���I�}�l��H" << endl
				<< "(2)�٬O�q�s���̦h���I�}�l�H" << endl
				<< "��J1��2__" << endl;
			cin >> mode;

			if (mode != 1 && mode != 2)
				mode = 0;
		} while (mode == 0);

		if (mode == 1) {
			cout << endl << "�ۦ⵲�G---->" << endl;
			greedyColoring(adj_list, v, nodeiy);
		}
		if (mode == 2) {
			cout << endl << "�ۦ⵲�G---->" << endl;
			sorting(adj_list, v);
			greedyColoring(adj_list, v, nodeiy);
		}


		cout << endl << "�i��B��Ҫ�O���ɶ��G"		//�p�����ɶ�
			<< (END - START) / CLOCKS_PER_SEC << " S" << endl;
	}

	system("pause");
	return 0;
}