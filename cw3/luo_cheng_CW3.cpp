#include <iostream>
#include <assert.h>
#include <stdlib.h>
using namespace std;

class fraction {
	friend ostream &operator<< (ostream &os, const fraction &f);
private:
	int numerator, denominator;
	void reduce();
public:
	fraction(int n = 0, int d = 1) : numerator(n), denominator(d) { reduce(); }
	fraction(const fraction& f){ numerator = f.numerator; denominator = f.denominator; reduce(); }

	bool operator< (const fraction &f) const;
	fraction operator- () const { fraction res(-numerator, denominator); return res; }
	fraction operator+ (const fraction &f) const;	
	fraction operator* (const fraction &f) const;
	fraction operator- (const fraction &f) const;
	fraction operator/ (const fraction &f) const;

	fraction operator+ (int i) const;
	fraction operator- (int i) const;

	fraction &operator+= (const fraction &f);
	fraction &operator-= (const fraction &f);
	fraction &operator/= (const fraction &f);
	fraction &operator*= (const fraction &f);
	operator double() const;
};


int gcd(int a, int b){
	if (a < b) return gcd(b, a);
	if (b == 0) return 0; // by convention define the gcd between 2 integers with a 0 is 0
	int r = a%b;
	if (r == 0) return b;
	return gcd(b, r);
}

int sign(int x){
	return (x > 0) - (x < 0);
}

ostream &operator<< (ostream &os, const fraction &f){
	if (f.numerator == 0) {
		os << 0;
	}
	else if (f.denominator == 1) {
		os << f.numerator;
	}
	else{
		os << f.numerator << "/" << f.denominator;
	}
	return os;
}

/*
* reduce a fraction
*	- assert on non zero denominator
*	- do nothing if numerator is 0
*	- divide both n and d by their positive gcd, attribute sign of the fraction on numerator
*/
void fraction::reduce(){
	assert(denominator != 0 && "create fraction with 0 as denominator");
	if (numerator == 0) return;
	int _sign = sign(numerator)*sign(denominator);
	numerator = abs(numerator);
	denominator = abs(denominator);
	int _gcd = gcd(numerator, denominator);
	if (_gcd > 1){
		numerator /= _gcd;
		denominator /= _gcd;
	}
	numerator *= _sign;
}

bool fraction::operator< (const fraction &f) const{
	return numerator*f.denominator < f.numerator*denominator;
}

fraction &fraction::operator+= (const fraction &f){
	numerator = numerator*f.denominator + denominator*f.numerator;
	denominator = denominator*f.denominator;
	reduce();
	return *this;
}

fraction fraction::operator+ (const fraction &f) const{
	fraction r(*this);
	return r += f;
}

fraction fraction::operator* (const fraction &f) const{
	fraction res(numerator*f.numerator, denominator*f.denominator); 
	return res;
}

fraction fraction::operator- (const fraction &f) const{
	return *this+(-f);
}

fraction fraction::operator/ (const fraction &f) const{
	fraction res(numerator*f.denominator, denominator*f.numerator);
	return res;
}

fraction fraction::operator+ (int i) const{
	fraction r(i, 1);
	return *this + r;
}


fraction  fraction::operator- (int i) const{
	return *this+(-1);
}


fraction &fraction::operator-= (const fraction &f){
	return *this += -f;
}

fraction &fraction::operator/= (const fraction &f){
	numerator *= f.denominator;
	denominator *= f.numerator;
	reduce();
	return *this;
}

fraction &fraction::operator*= (const fraction &f){
	numerator *= f.numerator;
	denominator *= f.denominator;
	reduce();
	return *this;
}

fraction::operator double() const {
	return static_cast<double>(numerator) / denominator;
}

fraction operator+ (int i, const fraction& f){
	return f + i;
}

int main(){
	fraction a(1, 12), b(1, 25), c(1, 300), e(3, 4), f(2, 5), g(7, 2), h;
	cout << a << " + " << b << " + " << c << " = " << a + b + c << endl;
	if (-a < b) cout << -a << " < " << b << endl;
	else cout << -a << " >= " << b << endl;
	h = e*f - g;
	cout << e << " * " << f << " - " << g << " = " << h << endl;
	fraction i(-1, 6), j(5, 17), k(3, 5);
	cout << i << " + " << j << " / " << k << " = " << i + j / k << endl; // associativity can not be changed
	int m = 2, q = 1;
	fraction n(1, 3), p(4, 5), s(a), t(b), u(c), w(e), x(f), y(g), v, z;
	cout << m << " + " << n << " = " << m + n << endl;
	cout << p << " - " << q << " = " << p - q << endl;
	v = (a += b -= u);
	cout << s << " += " << t << " -= " << u << " = " << v << endl;
	z = (e *= f /= g);
	cout << w << " *= " << x << " /= " << y << " = " << z << endl;
	double d = e;
	if (d < f) cout << d << " < " << f << endl;
	else cout << d << " >= " << f << endl;
	return 0;
}