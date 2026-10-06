# 41443113

# 作業一_1

## 解題說明
本題要求實現阿克曼函式，並使用遞迴的方式完成計算。

### 解題策略
1. 建立Ackermann()遞迴函式，並使用m,n作為參數。
2. 當 m < 0 或 n < 0 時，表示輸入不符合題目條件，因此拋出異常。
3. 當 m == 0 時回傳 n + 1。
4. 當 m > 0 且 n == 0 時，遞迴計算 A(m-1,1)。
5. 當 m > 0 且 n > 0 時，遞迴計算 A(m-1,A(m,n-1))。
6. 主程式呼叫函式並輸出結果。

## 程式實作

以下為主要程式碼：

```cpp
#include<iostream>
using namespace std;
int Ackermann(int m, int n) {
	if (m == 0) {
		return n + 1;
	}
	else if (n == 0) {
		return Ackermann(m - 1, 1);
	}
	else {
		return Ackermann(m-1,Ackermann(m ,n - 1));
	}
}

int main() {
	int m, n;
	cout << "Input m and n :";
	cin >> m >> n;
	if (m < 0 || n < 0)return 0;
	cout << "A(" << m << "," << n << ")=" << Ackermann(m, n);
	return 0;
}
```
## 效能分析
1. 時間複雜度：隨著 m 與 n 增加而改變， m = 0 為 O(1) 、 m = 1 時為 O(n) ，因此其時間複雜度無法使用一般簡單的 O(n) 或 O(log n) 來表示。對於實際程式而言，可以描述為：O(A(m,n)) 。
2. 空間複雜度：每次遞迴呼叫堆疊，其空間複雜度可表示為：O(A(m,n))。

## 測試與驗證

### 測試案例

| 測試案例 | 輸入參數  | 預期輸出 | 實際輸出 |
|----------|--------------|----------|----------|
| 測試一   | m = 0 , n = 3    | 4        | 4        |
| 測試二   | m = 1 , n = 4    | 6        | 6        |
| 測試三   | m = 3 , n = 2    | 29       | 29       |
| 測試四   | m = 3 , n = 6    | 509      | 509      |
| 測試五   | m = -1 , n = 2   | 異常拋出  | 異常拋出  |

### 編譯與執行指令

```shell
$ g++ Problem_1_1.cpp --std=c++21 -o Problem_1_1.exe
$ .\Problem_1_1.exe
Input m and n :3 6
A(3,6)=509
```
## 申論及開發報告
### 選擇遞迴的原因
本程式使用遞迴來實作Ackermann，主要原因是因為Ackermann本身就是用遞迴的方式定義的，可以直接透過數學公式來進行實作。
#### 例如:
```cpp
return Ackermann(m-1,Ackermann(m,n-1));
```
#### 便可對應到數學公式當中的:
```
A(m,n)=A(m-1,A(m,n-1))
```
可以直接由程式看出與數學公式當中的關係，因此較容易理解Ackermann函數的遞迴運作方式。

# 作業一_2

## 解題說明
本題要求實現阿克曼函式，並使用非遞迴的方式完成計算。

### 解題策略
1. 建立一個容量為 16 的整數陣列，作為 Stack 的儲存空間。
2. 使用 top 記錄 Stack 目前的位置，初始值設定為 -1，代表堆疊為空。
3. 創建 s 作為 Stack 。
4. 創建 push_s() 函式將資料放入 Stack。
5. 創建 pop_s() 函式從 Stack 頂端取出資料。
6. 將輸入的 m 放入 Stack。
7. 使用 while 迴圈處理 Stack，直到 Stack 為空。
8. 當 m == 0 時，n++。
9. 當 m > 0，且 n == 0時，將 m - 1 放入Stack，並將 n 設為 1。
10. 當 m > 0，且 n > 0 時，先將 n--，再依照原本遞迴的執行順序先將 m - 1 放入 Stack，再將 m 放入 Stack。
11. 當 Stack 為空時，代表所有計算完成，最後回傳 n。

## 程式實作

以下為主要程式碼：

```cpp
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
```
## 效能分析
1. 時間複雜度：時間複雜度為：O(A(m,n))
2. 空間複雜度：因為堆疊容量固定，空間複雜度可表示為：O(1)。

## 測試與驗證

### 測試案例

| 測試案例 | 輸入參數  | 預期輸出 | 實際輸出 |
|----------|--------------|----------|----------|
| 測試一   | m = 0 , n = 3    | 4        | 4        |
| 測試二   | m = 1 , n = 4    | 6        | 6        |
| 測試三   | m = 3 , n = 2    | 29       | Stack Overflow   |
| 測試四   | m = 2 , n = 2    | 7        | 7        |
| 測試五   | m = -1 , n = 2   | 異常拋出  | 異常拋出  |

### 編譯與執行指令

```shell
$ g++ Problem_1_2.cpp --std=c++21 -o Problem_1_2.exe
$ .\Problem_1_2.exe
Input m and n :1 4
A(1,4)=6
```
## 申論及開發報告

1. 使用 Stack 的原因

   本題目要求使用非遞迴的方式進行阿克曼函數的實作，因此不能使用函式呼叫自己的方式執行。

   程式改用自己建立的 Stack，模擬原本遞迴函式的執行方式。
   #### 程式使用：
   ```
   int* s = new int[capacity];
   ```
   建立整數陣列 s 來作為 Stack。

   並使用 top 來記錄 Stack 的頂端。
   
2. Push

   將資料存放至 Stack當中，如果超過堆疊上限會回傳 flase，溢位。

3. Pop

   使用pop_s將存放在 Stack 最頂端的資料取出。

4. 模擬遞迴 

   本程式不能直接進行遞迴，因此透過 Stack 模擬這個過程。
   ```cpp
   n--;
   push_s(s, top, capacity, m - 1);
   push_s(s, top, capacity, m);
   ```
   先將 m - 1 放入 Stack，再將 m 放入 Stack，利用後進先出的特性相當於處理了A(m,n-1)，再處理A(m-1,前一個的結果)。

   因此可以利用 Stack 的先進後出特性模擬原本的遞迴流程。
   
本程式雖然沒有使用 Ackermann() 函式自己呼叫自己的方式，但仍然可以完成阿克曼函式的計算。

另外，本程式的 Stack 容量設定為 16，當存入資料超過容量時 posh_s 會回傳 flase ，程式會釋放記憶體配置並回傳 -1，由主程式輸出 Stack Overflow。如果要處理更大的輸入，可以進一步修改 Stack 的容量。

# 作業二

## 解題說明
本題要求實現冪集合的計算，給定一個包含 s 個元素的集合 S，找出其所有可能子集合，並使用遞迴的方式完成計算。

### 解題策略
1. 建立 sort() 函式，先將輸入的字元陣列進行氣泡排序，並去除重複的元素，確保產生的冪集合不會有重複的組合。
2. 建立 chosen[] 布林陣列，用來記錄集合中的每一個元素是否被選中加入當前的子集合中。
3. 建立 powerset() 遞迴函式，帶入 index、m、chosen[] 與字元陣列 p。
4. 當 index == m 時代表所有元素都決定完選或不選，根據 chosen 陣列決定列印那些元素。
5. 在遞迴過程中，對每一個元素分別進行「不選 (chosen[index] = false)」與「選 (chosen[index] = true)」的兩條分支，以窮舉列出所有可能。
6. 主程式負責接收輸入、呼叫排序與去除重複、建立 chosen[] 陣列，並啟動遞迴列印所有。

## 程式實作

以下為主要程式碼：

```cpp
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
```
## 效能分析
1. 時間複雜度：有m個元素，每個都有選與不選，時間複雜度為：O(2^m)
2. 空間複雜度：空間複雜度可表示為：O(m)。

## 測試與驗證

### 測試案例
| 測試案例 | 輸入參數  | 預期輸出 | 實際輸出 |
|----------|--------------|----------|----------|
| 測試一   | s = 3, p = [a,b,c]      | (),(c),(b),(b,c),(a),(a,c),(a,b),(a,b,c)       | (),(c),(b),(b,c),(a),(a,c),(a,b),(a,b,c)       |
| 測試二   | s = 2, p = [a,a]        | (),(a)       | (),(a)    |
| 測試三   | s = 4, p = [a,b,a,c]    | (),(c),(b),(b,c),(a),(a,c),(a,b),(a,b,c)       | (),(c),(b),(b,c),(a),(a,c),(a,b),(a,b,c)       |

### 編譯與執行指令

```shell
$g++ Problem_2.cpp --std=c++21 -o Problem_2.exe
$.\Problem_2.exe
輸入元素數量:3
輸入元素:a b c
powerset(S) = {(),(c),(b),(b,c),(a),(a,c),(a,b),(a,b,c)}
```
## 申論及開發報告
1. 選擇遞迴與 chosen 陣列的原因
   
   本程式使用遞迴來實作冪集合，因為冪集合生成過程中具有樹狀分支結構(選與不選)

   程式使用：
   ```
   bool* chosen = new bool[m];
   ```
   來記錄是否有被選到

   在遞迴時透過
   ```
   chosen[index] = false;
   powerset(index + 1, m, chosen, p);

   chosen[index] = true;
   powerset(index + 1, m, chosen, p);
   ```
   來進行選與不選將所有的子集合列出來，此外為避免重複的元素導致重複的集合，在先前的 sort 函式便將其排序好並將重複的去掉。
