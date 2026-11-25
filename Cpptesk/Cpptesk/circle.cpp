#include "circle.h"

circle::circle() {
	r = 1 + rand() % 10;
}

void circle::show() const {
	cout << "生成了一个圆(Π取3.14)" << endl;
	cout << "半径是:" << r << endl;
}

double circle::getr() {
	return r;
}

double circle::area() const {
	return 3.14 * r * r;
}

double circle::perimeter() const {
	return 6.28 * r;
}
