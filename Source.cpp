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

struct GraphData
{
	int nodeiy;
	double START, END;
};

void add_edge(vector<int> adj_list[], int u, int v)       //建立adjlist
{
	adj_list[u].push_back(v);
	adj_list[v].push_back(u);
}

void sorting(vector<int> adj_list[], int v, GraphData& data)               //找出最長的list
{
	data.START = clock();
	int iy, max = 0;
	for (iy = 1; iy < v; ++iy)
	{
		if (adj_list[iy].size() > max) {
			max = adj_list[iy].size();
			data.nodeiy = iy;
		}
	}
	cout << "Node " << data.nodeiy
		<< "'s size is max=" << max << endl;
}

void processNode(vector<int> adj_list[], int i, int v, int* result, bool* available)	//提取原先在 greedyColoring()中重複的程式碼
{
	vector<int>::iterator it;                  //將相鄰節點的顏色標記為不可用
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

void greedyColoring(vector<int> adj_list[], int v, int nodeiy, GraphData& data, int* result, bool* available)         //用貪心演算法上色
{
	data.START = clock();
	//int* result = new int[v + 1];
	//bool* available = new bool[v + 1];

	for (int k = 1; k <= v; k++)
	{
		result[k] = -1;
		available[k] = false;
	}
	result[0] = 0;


	if (nodeiy == 0) {
		for (int i = 1; i <= v; i++)
		{
			processNode(adj_list, i, v, result, available);
		}
	}
	if (nodeiy != 0) {
		for (int i = 1; i <= v; i++)
		{
			result[nodeiy] = 1;                      //將連結最多的某節點塗上第一色
			processNode(adj_list, i, v, result, available);
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
	data.END = clock();

	
}

int main()
{
	GraphData data;									//創建了一個 GraphData 類型的對象
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
	if (!inf.is_open())
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

		vector<int>* adj_list = new vector<int>[v + 1];

		while (!inf.eof())                  //讀第三行以後
		{
			int p1 = 0, p2 = 0;
			inf >> p1 >> p2;
			if (p1 > v || p2 > v) {
				cout << "節點數超出範圍" << endl;
				continue;					//跳過getline() add_edge()
			}
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

		int* result = new int[v + 1];
		bool* available = new bool[v + 1];

		if (mode == 1) {
			cout << endl << "著色結果---->" << endl;
			greedyColoring(adj_list, v, 0, data, result, available);
		}
		if (mode == 2) {
			cout << endl << "著色結果---->" << endl;
			sorting(adj_list, v, data);
			greedyColoring(adj_list, v, data.nodeiy, data, result, available);
		}

		delete[] result;								//釋放動態分配記憶體
		delete[] available;
		delete[] adj_list;

		cout << endl << "進行運算所花費的時間："		//計算執行時間
			<< (data.END - data.START) / CLOCKS_PER_SEC << " S" << endl;
	}

	system("pause");
	return 0;
}