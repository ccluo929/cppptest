#include"Triangle.h"
Triangle::Triangle() {
	do {
		a = 1 + rand() % 10;
		b = 1 + rand() % 10;
		c = 1 + rand() % 10;
	} while (!(a + b > c && a + c > b && b + c > a));
}
double Triangle::geta() {
	return a;
}
double Triangle:: getb() {
	return b;
}
double Triangle:: getc() {
	return c;
}
void Triangle::show()const  {
	cout << "生成了一个三角形" << endl;
	cout << "三边是" << " " << a << " " << b << " " << c << endl;
}
double Triangle::area() const  {
	double p = (a + b + c) / 2;
	return sqrt(p * (p - a) * (p - b) * (p - c));
};
double Triangle::perimeter() const {
	return a + b + c;
};
