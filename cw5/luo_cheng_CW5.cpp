#include <iostream>
#include <vector>
#include <assert.h>
#include <iterator>
#include <cmath>
#include <complex>

using namespace std;

template <typename T>
class mathvector{
	vector<T> v;
public:
	mathvector<T>(unsigned int n = 0){ v.resize(n); };
	mathvector<T>(const vector<T>& _v) : v(_v){};
	virtual ~mathvector(){};

	unsigned int dim() const { return v.size(); };
	void push_back(T e) { v.push_back(e); };
	void print(ostream& os) const{ os << "[ "; copy(v.begin(), v.end(), ostream_iterator<T>(os, " ")); os << "]"; };

	T l2_norm() const;
	T operator*(const mathvector<T>& _v) const;
	mathvector<T> operator/(T d) const;
	T& operator[](unsigned int i){ return v[i]; };
	T operator[](unsigned int i) const { return v[i]; };

	mathvector<T> hadamard(const mathvector<T>& _v) const;
};

template <typename T>
T mathvector<T>::operator*(const mathvector<T>& _v) const{
	assert(this->dim() == _v.dim() && "multiply 2 vectors with different dimension!");
	T r(0);
	for (size_t i = 0; i < _v.dim(); i++)
	{
		r += v[i] * _v[i];
	}
	return r;
}

template <typename T>
mathvector<T> mathvector<T>::operator/(T d) const{
	assert(d!=0 && "divid by 0!");
	mathvector<T> _v(v.size());
	for (size_t i = 0; i < v.size(); i++)
	{
		_v[i] = (v[i] / static_cast<T>(d));
	}
	return _v;
}

template <typename T>
T mathvector<T>::l2_norm() const{
	T norm(0);
	for (size_t i = 0; i < v.size(); i++)
	{
		norm += v[i] * v[i];
	}
	return sqrt(norm);
}

template <typename T>
mathvector<T> mathvector<T>::hadamard(const mathvector<T>& _v) const{
	assert(this->dim() == _v.dim() && "multiple 2 vectors with different dimension!");
	mathvector<T> r(v.size());
	for (size_t i = 0; i < _v.dim(); i++)
	{
		r[i] = v[i] * _v[i];
	}
	return r;
}

template <typename T>
ostream& operator<< (ostream& os, const mathvector<T>& _v){
	_v.print(os);
	return os;
}

template <typename T>
class mathmatrix{
protected:
	unsigned int n;
public:
	mathmatrix<T>(unsigned int _n = 0) : n(_n){};
	virtual mathvector<T> operator*(const mathvector<T>&) const = 0;
	virtual void y_eq_Ax(mathvector<T> &, const mathvector<T> &) const = 0;
	T power_method(const mathvector<T> &, int) const;
};

template <typename T>
T mathmatrix<T>::power_method(const mathvector<T> &_v, int k) const{
	unsigned int _k = static_cast<unsigned int>(k);
	mathvector<T> q = _v / _v.l2_norm();
	mathvector<T> z(n);
	for (size_t i = 0; i < _k; i++)
	{
		y_eq_Ax(z, q);
		q = z / z.l2_norm();
	}
	y_eq_Ax(z, q);
	return q*(z);
}

template <typename T>
class fullmatrix : public mathmatrix<T>{
	vector<mathvector<T> > m; // vector stored by row
public:
	fullmatrix<T>(unsigned int _n = 0) : mathmatrix<T>(_n){};
	fullmatrix<T>(const vector<vector<T> >&);
	mathvector<T> operator*(const mathvector<T>&) const;
	fullmatrix<T>& operator-=(T);
	fullmatrix<T>& operator+=(T);
	void y_eq_Ax(mathvector<T> &, const mathvector<T> &) const;
};

template <typename T>
fullmatrix<T>::fullmatrix(const vector<vector<T> >& v) : mathmatrix<T>(v.size()){
	m.resize(fullmatrix<T>::n);
	for (size_t i = 0; i < mathmatrix<T>::n; i++)
	{
		m[i] = v[i];
	}
}

template <typename T>
mathvector<T> fullmatrix<T>::operator*(const mathvector<T>& v) const{
	assert(mathmatrix<T>::n == v.dim() && "dimension not agree when multiplying by vector!");
	mathvector<T> r(mathmatrix<T>::n);
	for (size_t i = 0; i < mathmatrix<T>::n; i++)
	{
		r[i] = m[i] * v;
	}
	return r;
}

template <typename T>
fullmatrix<T>& fullmatrix<T>::operator-=(T x){
	for (size_t i = 0; i < mathmatrix<T>::n; i++)
	{
		m[i][i] -= x;
	}
	return *this;
}

template <typename T>
fullmatrix<T>& fullmatrix<T>::operator+=(T x){
	return (*this) -= (-x);
}

template <typename T>
void fullmatrix<T>::y_eq_Ax(mathvector<T> &y, const mathvector<T> &x) const{
	y = (*this)*x;
}

template <typename T>
class diagmatrix : public mathmatrix<T>{
	mathvector<T> d;
public:
	diagmatrix<T>(unsigned int _n = 0) : mathmatrix<T>(_n){};
	diagmatrix<T>(const vector<T>& v) : mathmatrix<T>(v.size()), d(v){};
	mathvector<T> operator*(const mathvector<T>&) const;
	void y_eq_Ax(mathvector<T> &, const mathvector<T> &) const;
};

template <typename T>
mathvector<T> diagmatrix<T>::operator*(const mathvector<T>& v) const{
	return d.hadamard(v);
}

template <typename T>
void diagmatrix<T>::y_eq_Ax(mathvector<T> &y, const mathvector<T> &x) const{
	y = (*this)*x;
}

template <typename T>
class CW5_matrix : public mathmatrix<T>{
public:
	CW5_matrix<T>(signed int _n = 0) : mathmatrix<T>(_n){};
	mathvector<T> operator*(const mathvector<T>&) const;
	void y_eq_Ax(mathvector<T> &, const mathvector<T> &) const;
};

template <typename T>
mathvector<T> CW5_matrix<T>::operator*(const mathvector<T>& v) const{
	assert(mathmatrix<T>::n == v.dim() && "dimension not agree when multiplying CW5 matrix by vector!");
	mathvector<T> r(mathmatrix<T>::n);
	r[0] = v[0] * 2 - v[1] - v[mathmatrix<T>::n - 1];
	for (size_t i = 1; i < mathmatrix<T>::n - 1; i++)
	{
		T e = v[i] * 2 - v[i + 1] - v[i - 1];
		r[i] = e;
	}
	r[mathmatrix<T>::n - 1] = v[mathmatrix<T>::n - 1] * 2 - v[mathmatrix<T>::n - 2] - v[0];
	return r;
}

template <typename T>
void CW5_matrix<T>::y_eq_Ax(mathvector<T> &y, const mathvector<T> &x) const{
	y = (*this)*x;
}

int main() {
	int N = 10000, K = 4000;
	mathvector<double> x_a;
	for (int i = 0; i < N; i++) x_a.push_back(i + 1); // x = (1,2,...,N)^T
	CW5_matrix<double> A(N); // matrix A
	double lambda = A.power_method(x_a, K);
	cout << "largest lambda (in modulus) for A = " << lambda << endl;
	double b[] = { 1.0, 1.0, 1.0, 1.0 };
	vector<double> vb(b, b + 4); mathvector<double> x_b(vb); // x = (1,1,1,1)^T
	cout << " x . x = " << x_b * x_b << endl;
	double r1[] = { 3.0, 1.0, 2.0, 5.0 }, r2[] = { 1.0, 1.0, 3.0, 7.0 },
		r3[] = { 2.0, 3.0, 2.0, 4.0 }, r4[] = { 5.0, 7.0, 4.0, 2.0 };
	vector<double> row1(r1, r1 + 4), row2(r2, r2 + 4), row3(r3, r3 + 4), row4(r4, r4 + 4);
	vector<vector<double> > BB;
	BB.push_back(row1); BB.push_back(row2); BB.push_back(row3); BB.push_back(row4);
	fullmatrix<double> B(BB); // matrix B
	B.y_eq_Ax(x_a, x_b); cout << x_a << endl; // y = B * x
	lambda = B.power_method(x_b, K);
	B -= lambda; // B = B - lambda * Id
	double l2 = B.power_method(x_b, K);
	B += lambda; // B = B + lambda * Id
	cout << "The spectrum of B lies between " << lambda << " and " << l2 + lambda << endl;
	diagmatrix<double> D(row4);
	lambda = D.power_method(x_b, K);
	cout << "largest lambda (in modulus) for D = " << lambda << endl;
	vector<vector<complex<double> > > CC; // ... fill CC appropriately ...
	fullmatrix<complex<double> > C(CC); // ... etc ...
	return 0;
}