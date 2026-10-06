#include<iostream>
using namespace std;
bool is_first_subset = true;

void sort(char* p, int s,int &m) {
	for (int i = 0; i < s - 1; i++) {//氣泡排序由小到大
		for (int j = 0; j < s - 1 - i; j++) {
			if (p[j] > p[j + 1]) {
				char sd = p[j];
				p[j] = p[j + 1];
				p[j + 1] = sd;
			}
		}
	}
	int news = 0;
	for (int i = 1; i < s; i++) {//將重複的去掉，已經排序好了，重複的都靠再一起，所以只要跟最新存進去的做比對就行
		if (p[i] != p[news]) {
			news++;
			p[news] = p[i];
		}
	}
	m = news + 1;
}

void powerset(int index,int m, bool* chosen, char* p) {
	if (index == m) {
		if (!is_first_subset) {//判斷是否為第一個子集合
			cout << ",";
		}
		is_first_subset = false;
		cout << "(";
		bool first_element = true;
		for (int i = 0; i < m; i++) {
			if (chosen[i]) {
				if (!first_element) {//判斷是否為第一個元素
					cout << ",";
				}
				cout << p[i];
				first_element = false;
			}
		}
		cout << ")";
		return;
	}
	
	chosen[index] = false;//不選中當前元素
	powerset(index + 1, m, chosen, p);

	chosen[index] = true;//選中當前元素
	powerset(index + 1, m, chosen, p);
}
int main() {
	int s;
	cout << "輸入元素數量:";
	cin >> s;
	char* p = new char[s];//儲存元素
	cout << "輸入元素:";
	for (int i = 0; i < s; i++) {
		cin >> p[i];
	}
	int m = s;
	sort(p, s, m);
	bool* chosen = new bool[m];//用來記錄元素是否要列印
	cout << "powerset(S) = {";
	powerset(0, m, chosen, p);
	cout << "}";
	delete[] p;
	delete[] chosen;
	return 0;
}
