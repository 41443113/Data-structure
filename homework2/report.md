# 41443113

# 作業一

## 解題說明
本題要求實現多項式抽象資料型態，使用動態記憶體來儲存多像是當中的每一項，以及實作多項式加法(Add)、乘法(Mult)、以及求值(Eval)，此外還需實現運算子多載(<<與>>)。
### 解題策略
1. 建立Term類別，包含係數coef(float)、指數exp(int)。
2. 建立Polynomial類別，動態陣列termArray(Term)、當前容量capacity(int)、當前位置terms(int)。
3. 建立建構子、解構子、複製建構子、賦值運算子。
4. 建立NewTern用來將指數係數存入陣列，係數為零不存入，遇到指數相同自動合併，容量達到上限時擴充容量，插入排序並存入。
5. 建立加法Add(Polynomial poly)，建立r，i1=0、i2=0，當(i1<this的當前位置或i2<poly的當前位置)時重複(當this與poly指數相同時、指數和係數各自相加放入r、i1+1、i2+1，this指數>poly指數時將this指數係數放入r、i1+1，反之poly指數系數放入r、i2+1)，再將剩下的this或poly放入r，回傳r。
6. 建立乘法Mult(Polynomial poly)，建立r，利用雙迴圈將this與poly的每個係數相乘、指數相加、並交由NewTern排序存入r，回傳r。
7. 建立求值Eval(float f)，建立S，利用迴圈將cofe乘f的exp次方放入S，回傳S。
8. 建立輸出多載，輸出第零項，利用迴圈將第一項到最後一項跑一遍，如果係數大於零輸出+coef x^exp，如果小於零輸出-|cofe| x^exp，如果exp=0就不用輸出後面的x^exp。
9. 建立輸入多載，先輸入項數、再利用迴圈依序輸入係數和指數，如果指數是負數就重新輸入該項並存入。
10. 建立主程式負責呼叫、和輸出結果

## 程式實作

以下為主要程式碼：
```cpp
#include<iostream>
#include <cmath>
using namespace std;
class Polynomial;

class Term {
	friend class Polynomial;
	friend ostream& operator<<(ostream& os, const Polynomial& p);
	friend istream& operator>>(istream& is, Polynomial& poly);
private:
	float coef;
	int exp;
};

class Polynomial {
public:
	Polynomial() {
		capacity = 1;
		terms = 0;
		termArray = new Term[capacity];
	};

	~Polynomial() {
		delete[] termArray;
	}

	Polynomial(const Polynomial& p) {//複製建構子
		capacity = p.capacity;
		terms = p.terms;
		termArray = new Term[capacity];//// 重新配置一塊獨立的記憶體
		for (int i = 0; i < terms; i++) {
			termArray[i] = p.termArray[i];
		}
	}

	Polynomial& operator=(const Polynomial& p) {//賦值運算子
		if (this == &p) return *this;
		delete[] termArray;
		capacity = p.capacity;
		terms = p.terms;
		termArray = new Term[capacity];
		for (int i = 0; i < terms; i++) {
			termArray[i] = p.termArray[i];
		}
		return *this;
	}

	Polynomial Add(Polynomial poly) {//加
		Polynomial r;
		int i1 = 0, i2 = 0;
		while (i1 < this->terms && i2 < poly.terms) {
			if (this->termArray[i1].exp == poly.termArray[i2].exp) {
				float sum = this->termArray[i1].coef + poly.termArray[i2].coef;
				if (sum != 0) {
					r.NewTerm(sum, this->termArray[i1].exp);
				}
				i1++;
				i2++;
			}
			else if (this->termArray[i1].exp > poly.termArray[i2].exp) {
				r.NewTerm(this->termArray[i1].coef, this->termArray[i1].exp);
				i1++;
			}
			else {
				r.NewTerm(poly.termArray[i2].coef, poly.termArray[i2].exp);
				i2++;
			}
		}
		while (i1 < this->terms) {
			r.NewTerm(this->termArray[i1].coef, this->termArray[i1].exp);
			i1++;
		}
		while (i2 < poly.terms) {
			r.NewTerm(poly.termArray[i2].coef, poly.termArray[i2].exp);
			i2++;
		}
		return r;
	};

	Polynomial Mult(Polynomial poly) {//乘
		Polynomial r;
		for (int i = 0; i < this->terms; i++) {
			for (int j = 0; j < poly.terms; j++) {
				float c = (this->termArray[i].coef) * (poly.termArray[j].coef);
				int e = (this->termArray[i].exp) + (poly.termArray[j].exp);
				r.NewTerm(c, e);
			}
		}
		return r;
	};

	float Eval(float f) {//帶入求值
		float S = 0;
		for (int i = 0; i < terms; i++) {
			S += this->termArray[i].coef * pow(f, this->termArray[i].exp);
		}
		return S;
	};

	void NewTerm(const float theCoeff, const int theExp) {
		if (theCoeff == 0) return;

		for (int i = 0; i < terms; i++) {//找是否有指數一樣的
			if (termArray[i].exp == theExp) {
				termArray[i].coef += theCoeff;
				return;
			}
		}
		if (terms == capacity) {
			capacity *= 2;
			Term* temp = new Term[capacity];
			copy(termArray, termArray + terms, temp);
			delete[] termArray;
			termArray = temp;
		}
		int i = terms - 1;
		while (i >= 0 && termArray[i].exp < theExp) {
			termArray[i + 1].exp = termArray[i].exp;
			termArray[i + 1].coef = termArray[i].coef;
			i--;
		}
		i++;
		termArray[i].coef = theCoeff;
		termArray[i].exp = theExp;
		terms++;
	}

	friend ostream& operator<<(ostream& os, const Polynomial& p) {
		if (p.terms == 0) {
			os << "0";
			return os;
		}
		os << p.termArray[0].coef << "x^" << p.termArray[0].exp;
		for (int i = 1; i < p.terms; i++) {
			if (p.termArray[i].coef > 0) {
				if (p.termArray[i].exp == 0) {
					os << " + " << p.termArray[i].coef;
				}
				else {
					os << " + " << p.termArray[i].coef << "x^" << p.termArray[i].exp;
				}
			}
			else {
				if (p.termArray[i].exp == 0) {
					os << " - " << p.termArray[i].coef * (-1);
				}
				else {
					os << " - " << p.termArray[i].coef * (-1) << "x^" << p.termArray[i].exp;
				}
			}
		}
		return os;
	}

	friend istream& operator>>(istream& is, Polynomial& poly) {
		int x, e;
		float c;
		is >> x;
		for (int i = 0; i < x; i++) {
			is >> c >> e;
			if (e < 0) {
				cout << "輸入錯誤請重新輸入\n";
				i--;
			}
			else poly.NewTerm(c, e);
		}
		return is;
	}

private:
	Term* termArray;
	int capacity;
	int terms;
};

int main() {
	Polynomial p, p1;
	cout << "請輸入A有幾項(再輸入係數 指數):";
	cin >> p;
	cout << "請輸入B有幾項(再輸入係數 指數):";
	cin >> p1;
	cout << "輸入x:";
	float x;
	cin >> x;
	cout << "A:" << p << "\n";
	cout << "B:" << p1 << "\n";
	Polynomial add = p.Add(p1);
	cout << "相加:" << add << "\n";
	Polynomial mult = p.Mult(p1);
	cout << "相乘:" << mult << "\n";
	float eval = p.Eval(x);
	cout << "x帶入A:" << eval << "\n";
	return 0;
}
```
## 效能分析
1. 加法函式:

    時間複雜度: O(M+N)，分析: 假設A有M項B有N項最多執行M+N次迴圈，因此呈線性時間成長。
   
    空間複雜度: O(M+N)，分析: 會建立多項式r，最多包含M+N個非零項，需配置對應大小的動態記憶體。
2. 乘法函式:

    時間複雜度: O(M+N)^2，分析: 交叉相乘會產生M * N項，每一項都會呼叫NewTerm，最壞的情況下(每次都需要排序搬移)單次插入時間需要O(K)(K為當前項數)，因此總時間複雜度需要1+2+...+(M * N) = 1/2(M * N)^2+1/2(M * N)，所以需要O(M * N)^2。
   
    空間複雜度: O(M+N)，分析: 最多可能擁有M * N項，因此動態陣列最大為M * N。
3. 帶入求值函式:

    時間複雜度: O(M)，分析: M項，每項執行一次pow(f,exp)數學運算，若將次方運算pow視作常數時間，則整體為線性迴圈，時間複雜度為O(M)。
   
    空間複雜度: O(1)，分析: 求值只使用少數區域變數(如:S進行累加)來存放計算結果，不需要額外動態記憶體。
4. 存入項和排序:

    時間複雜度: O(N)，分析 :指數相同檢查需要耗費N，容量倍增搬移需要耗費N，插入排序最多耗費N跑每一項，所以時間複雜度為O(N)。
   
    空間複雜度: O(N)，分析 :當容量達到上限時會配置capacity*2的新陣列，因此空間以倍率成長。
5. 輸入運算子多載:

    時間複雜度: O(X^2)，分析: 讀入X項並逐一呼叫NewTerm()，時間複雜度為O(X^2)。
   
    空間複雜度: O(1)，分析: 不需要額外的記憶體。
6. 輸出運算子多載:

    時間複雜度: O(N)，分析: 走訪N項列印，時間複雜度為N。
    
    空間複雜度: O(1)，分析: 不需要額外的記憶體。
7. 總結:

    時間複雜度: O(N^4)，分析: 運算量最大的多項式乘法為基準，假設A、B都為N項，交叉相乘與插入排序，其總時間複雜度為O(N^4)。
    
    空間複雜度: O(N)，分析: 採用稀疏矩陣只存非零項，因此無論多項式、加法、乘法，其記憶體空間都對應當前實際項數N(相乘上限為M * N)，總空間複雜度為O(N)。
## 測試與驗證

### 測試案例

|   測試案例   | 	  輸入參數  		|		 預期輸出 		| 	   實際輸出 		|
|-------------|---------------------|-----------------------|-------------------|
| 加法測試     | 2 3 4 5 4 1 1.6 6 1	| 相加:1.6x^6 + 8x^4 	| 相加:1.6x^6 + 8x^4|
| 乘法測試     | 2 3 2 2 0 1 2 1 1  	| 相乘:6x^3 + 4x^1   	| 相乘:6x^3 + 4x^1 	|
| 求值測試     | 2 4 2 6 1 1 1.2 1 2	| x帶入A:28  			| x帶入A:28        	|
| 負指數測試   | 2 0 4 1.3 -1       	| 輸入錯誤請重新輸入		| 輸入錯誤請重新輸入	|

### 編譯與執行指令
```shell
$ g++ Problem_1.cpp --std=c++11 -o Problem_1.exe
$ .\Problem_1.exe
請輸入A有幾項(再輸入係數 指數):2
1 2
3 4
請輸入B有幾項(再輸入係數 指數):2
3 2
1 0
輸入x:2
A:3x^4 + 1x^2
B:3x^2 + 1
相加:3x^4 + 4x^2 + 1
相乘:9x^6 + 6x^4 + 1x^2
x帶入A:52
```
## 申論及開發報告
### 建立NewTerm()原因
1. 使用了插入排序，再cin>>p時不需要擔心輸入的項是否有由大到小，會自動遞減排序好。
2. 合併同次方，在進行乘法時可以把數字直接丟進去，內部會自動合併同次方的數，以及由大至小排序好。

###記憶體安全
類別當中使用動態記憶體(new產生的指標)時，如果沒有定義複製建構子和賦值運算子，系統會使用淺拷貝，導致兩個物件指向同一個位置，當物件生命週期結束時，各自呼叫解構子(delete[])時，系統會試圖對一塊記憶體釋放兩次，導致程式崩潰，如果其中一個物件被提前釋放記憶體，另一個物件上的指標就會變成空指標，如若再去存取或釋放就會造成當機。程式實作了完整的深拷貝，所以不會發生上述問題，徹底確的保記憶體安全。
