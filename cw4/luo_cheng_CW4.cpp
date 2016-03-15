#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
using namespace std;

struct point{
	double x, y;
	point(double _x=0, double _y=0):x(_x), y(_y){};
	point(const point& p) :x(p.x), y(p.y){};
	double dist(const point& p) const { return sqrt(pow(x - p.x, 2) + pow(y - p.y, 2)); };
};

class shape {
protected:
	point centre; // uses struct point { double x,y; };
public:
	shape() { centre.x = centre.y = 0.0; }
	shape(const point &p) : centre(p) {}
	virtual double area() const = 0;
	virtual double circ() const = 0;
	double dist(const shape &s) const{ return centre.dist(s.centre); };
	virtual ~shape() {}
};

class circle : public shape {
	double radius;
public:
	circle(const point &p, double r) : shape(p), radius(r) { radius = r < 0 ? 0 : r; }
	double area() const;
	double circ() const; // both may use constant M_PI from <cmath>
};

double circle::area() const{
	return M_PI*pow(radius, 2);
}

double circle::circ() const{
	return M_PI*radius * 2;
}

class triangle :public shape{
	point p1, p2, p3;
public:
	triangle(const point& _p1, const point& _p2, const point& _p3) :
		shape(point((_p1.x + _p2.x + _p3.x) / 3, (_p1.y + _p2.y + _p3.y) / 3)),
		p1(_p1), p2(_p2), p3(_p3){};
	double area() const;
	double circ() const;
};

double triangle::area() const{
	return (p1.x*(p2.y - p3.y) + p2.x*(p3.y - p1.y) + p3.x*(p1.y - p2.y)) / 2;
}

double triangle::circ() const{
	return p1.dist(p2)+p2.dist(p3)+p3.dist(p1);
}

class rectangle :public shape{
	point pbl, pur; // bottom left, upper right
public:
	rectangle(const point& _pbl, const point& _pur) :
		shape(point((_pbl.x + _pur.x) / 2, (_pbl.y + _pur.y) / 2)),
		pbl(_pbl), pur(_pur){};
	double area() const;
	double circ() const;
};

double rectangle::area() const{
	return abs(pbl.x - pur.x)*abs(pbl.y - pur.y);
}

double rectangle::circ() const{
	return (abs(pbl.x - pur.x) + abs(pbl.y - pur.y))*2;
}

double sratio(const shape &s){
	double area = s.area();
	double circ = s.circ();
	if (area == 0 || circ == 0) return 1;
	return area / circ;
}

int main(){
	point p(-15, 20), p1(0, 0), p2(3, 0), p3(1.5, 3), p4(0, 1), p5(3, 2);
	circle c(p, 5.0);
	triangle t(p1, p2, p3);
	rectangle r(p4, p5);
	cout << sratio(r) << endl;
	cout << "The distance between triangle and circle is " << t.dist(c) << endl;
	return 0;
}