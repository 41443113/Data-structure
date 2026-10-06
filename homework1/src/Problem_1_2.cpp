#include<iostream>
using namespace std;

bool push_s(int* s, int& top, int capacity, int value) {
	if (top >= capacity - 1) {//當超出堆疊上限
		return false;
	}
	s[++top] = value;//存入堆疊
	return true;
}

int pop_s(int* s, int& top) {
	return s[top--];//取出堆疊
}

int Ackermann(int m, int n) {
	int capacity = 16;//堆疊容量
	int top = -1;//堆疊位置
	int* s = new int[capacity];
	if (!push_s(s, top, capacity, m)) {
		delete[] s;
		return -1;
	}
	while (top >= 0) {
		m = pop_s(s, top);
		if (m == 0) {
			n++;
		}
		else if (n == 0) {
			n = 1;
			if (!push_s(s, top, capacity, m - 1)) {//存入m-1
				delete[] s;
				return -1;
			}
		}
		else {
			n--;
			if (!push_s(s, top, capacity, m - 1)) {//先存入m-1
				delete[] s;
				return -1;
			}
			if (!push_s(s, top, capacity, m)) {//再存入m先算
				delete[] s;
				return -1;
			}
		}
	}
	delete[] s;
	return n;
}
int main() {
	int m, n;
	cout << "Input m and n :";
	cin >> m >> n;
	if (m < 0 || n < 0)return 0;
	int c = Ackermann(m, n);
	if (c != -1) {
		cout << "A(" << m << "," << n << ")=" << c;
	}
	else {
		cout<< "Stack Overflow";
	}
	return 0;
}
