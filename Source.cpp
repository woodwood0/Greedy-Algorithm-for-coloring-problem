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


void add_edge(list<int> adj_list[], int u, int v)       //建立adjlist
{
	adj_list[u].push_back(v);
	adj_list[v].push_back(u);
}
static int nodeiy;
static double START,END;
void sorting(list<int> adj_list[], int v)               //找出最長的list
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
void greedyColoring(list<int> adj_list[], int v, int nodeiy)         //用貪心演算法上色
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
			list<int>::iterator it;                  //將相鄰節點的顏色標記為不可用
			for (it = adj_list[i].begin(); it != adj_list[i].end(); ++it)
			{
				if (result[*it] != -1)
				{
					available[result[*it]] = true;
				}
			}

			int cr;                                  //尋找並塗上第一個可用的顏色
			for (cr = 1; cr <= v; cr++)
			{
				if (available[cr] == false)
					break;
			}

			result[i] = cr;
	   												 //將顏色重設為可用
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
			result[nodeiy] = 1;                      //將連結最多的某節點塗上第一色
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
	
	int color = 0;									//輸出結果
	for (int i = 1; i <= v; i++)
	{
		if (result[i] > color) {
			color = result[i];
		}
	}
	cout << "共" << color << "種顏色" << endl << endl;
	END = clock();

}

int main()
{
	cout << "要開啟的檔名為node___--?" << endl
		<< "(輸入數字)" << endl;
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
		cout << "無法讀入檔案\n";
		system("pause");
		return 0;
	}
	if (inf.is_open())
	{
		int numoflink = 0;
		cout << "開啟node" << num << ".txt" << endl;
		string line;

		getline(inf, line);                 //讀第一行
		int first = line.find(':');
		string substr = line.substr(first + 2);
		num = atoi(substr.c_str());
		cout << "num of nodes " << num << endl;

		getline(inf, line);                 //讀第二行
		first = line.find(':');
		substr = line.substr(first + 2);
		numoflink = atoi(substr.c_str());
		cout << "num of links " << numoflink << endl;

		int v = num;

		list<int>* adj_list;
		adj_list = new list<int>[v + 1];

		while (!inf.eof())                  //讀第三行以後
		{
			int p1 = 0, p2 = 0;
			inf >> p1 >> p2;
			getline(inf, line);
			add_edge(adj_list, p1, p2);
		}
		inf.close();


		int mode = 0;
		do {
			cout << endl << "(1)要從第一個點開始塗？" << endl
				<< "(2)還是從連結最多的點開始？" << endl
				<< "輸入1或2__" << endl;
			cin >> mode;

			if (mode != 1 && mode != 2)
				mode = 0;
		} while (mode == 0);

		if (mode == 1) {
			cout << endl << "著色結果---->" << endl;
			greedyColoring(adj_list, v, nodeiy);
		}
		if (mode == 2) {
			cout << endl << "著色結果---->" << endl;
			sorting(adj_list, v);
			greedyColoring(adj_list, v, nodeiy);
		}


		cout << endl << "進行運算所花費的時間："		//計算執行時間
			<< (END - START) / CLOCKS_PER_SEC << " S" << endl;
	}

	system("pause");
	return 0;
}