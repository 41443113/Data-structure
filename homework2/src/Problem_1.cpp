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
	Polynomial add = p.Add(p1);
	cout << "相加:" << add << "\n";
	Polynomial mult = p.Mult(p1);
	cout << "相乘:" << mult << "\n";
	float eval = p.Eval(x);
	cout << "x帶入A:" << eval << "\n";
	return 0;
}