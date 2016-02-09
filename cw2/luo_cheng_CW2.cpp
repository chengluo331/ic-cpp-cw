#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

/* class Point */
class Point{
	unsigned int x; // x coordinate
	unsigned int y; // y coordinate
	bool s; // true if it is the left end of a building, false if it is the right end
public:
	Point(const Point&); // constructor by copy
	Point(unsigned int _x = 0, unsigned int _y = 0, bool _s = true); // constructor

	bool is_starting_point() const; // return true if the point is the left end
	unsigned int get_x() const;	// get the value of x
	unsigned int get_y() const; // get the value of y

	static bool before(const Point&, const Point&); // comparison between points for sorting algorithm
};

Point::Point(const Point& p){
	x = p.x;
	y = p.y;
	s = p.s;
}

Point::Point(unsigned int _x, unsigned int _y, bool _s){
	x = _x;
	y = _y;
	s = _s;
}

bool Point::is_starting_point() const{
	return s;
}

unsigned int Point::get_x() const{
	return x;
}

unsigned int Point::get_y() const{
	return y;
}

bool Point::before(const Point & p1, const Point& p2){
	if (p1.x < p2.x) return true;	// if x1 < x2, p1 is before p2
	if (p1.x > p2.x) return false;	// if x1 > x2, p2 is before p1
	/* in case they both have the same x coordinate */
	if (p1.y > p2.y){ // p1 is higher then p2
		if (p1.s) return true; // p1 is sorted before p2 only when it is the left end
		return false;
	}
	if (p1.y < p2.y){ // p2 is higher then p1
		if (p2.s) return false; // p2 is sorted before p1 only when it is the left end
		return true;
	}
	/* in case both points have the same coordinates */
	if (p1.s & !p2.s) return true; // p1 is sorted before p2 only when p1 is left end and p2 is right end
	return false;
}
/* end of class Point*/

int main(int argc, char* argv[]){
	const char* fname = "skyline.in";
	if (argc > 1){
		fname = argv[1];
	}
	std::ifstream in(fname);

	std::vector<Point> v;
	// load input file and create a vector holding points
	if (in){
		unsigned int x1, y1, x2, y2;
		while (in >> x1 >> y1 >> x2 >> y2)
		{
			Point pl(x1, y1, true); // left end of building
			Point pr(x2, y2, false); // right end of building
			v.push_back(pl);
			v.push_back(pr);
		}
		in.close();
	}
	else {
		std::cout << "File cannot be opened for reading, ";
		std::cout << "please make sure the input file \'skyline.in\' is on the same path as the programme!" << std::endl;
		return -1; // terminate programme
	}
		
	std::sort(v.begin(), v.end(), Point::before); // sort the points vector

	std::multiset<unsigned int> T; // create a multiset to track the current max height at the point
	T.insert(0);
	std::ofstream out("skyline.out");
	if (out){
		for (size_t i = 0; i < v.size(); i++)
		{
			unsigned int x = v[i].get_x();
			unsigned int y = v[i].get_y();
			if (v[i].is_starting_point()){
				if (y > *T.rbegin()){ // if the point's height is above the current max height
					out << x << " " << *T.rbegin() << std::endl;
					out << x << " " << y << std::endl;
				}
				T.insert(y);
			}
			else{
				std::pair<std::multiset<unsigned int>::const_iterator,
					std::multiset<unsigned int>::const_iterator> p = T.equal_range(y);
				if (p.first != p.second){ 
					T.erase(p.first); // erase the height of a building when evaluating the right end
				}
				if (y > *T.rbegin()){ // if the point's height is above the current max height
					out << x << " " << y << std::endl;
					out << x << " " << *T.rbegin() << std::endl;
				}
			}
		}
	}
	else{
		std::cout << "File cannot be opened for writing, ";
		std::cout << "please make sure you have permission to write on the output file \'skyline.out\'!" << std::endl;
		return -1; // terminate programme
	}	
	return 0;
}