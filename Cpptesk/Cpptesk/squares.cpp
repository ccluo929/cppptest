#include "Squares.h"

four_square::four_square()
{
	side = 1 + rand() % 10;
}

void four_square::show() const {
	cout << "生成了一个正方形" << endl;
	cout << "边长是:" << side;
}

double four_square::getside()
{
	return side;
}

double four_square::area() const
{
	return side * side;
}

double four_square::perimeter() const
{
	return 4 * side;
}

rectangle::rectangle()
{
	do
	{
		lenth = 1 + rand() % 10;
		width = 1 + rand() % 10;
	} while (lenth == width);
}

void rectangle::show() const {
	cout << "生成了一个长方形" << endl;
	cout << "长是:" << lenth << "宽是:" << width;
}

double rectangle::getlenth() {
	return lenth;
}

double rectangle::getwidth() {
	return width;
}

double rectangle::area() const
{
	return width * lenth;
}

double rectangle::perimeter() const
{
	return 2 * (width + lenth);
}

trapezoid::trapezoid() {
	upper_base = 1 + rand() % 10;
	lower_base = 1 + rand() % 10;
	height = 1 + rand() % 10;
	leg1 = leg2 = sqrt((upper_base - lower_base) * (upper_base - lower_base) + height * height);
}

void trapezoid::show() const {
	cout << "生成了一个梯形" << endl;
	cout << "上底:" << upper_base << endl;
	cout << "下底:" << lower_base << endl;
	cout << "两腰:" << leg1 << "," << leg2 << endl;
	cout << "高:" << height << endl;
}

double trapezoid::getupper_base() {
	return upper_base;
}

double trapezoid::getlower_base() {
	return lower_base;
}

double trapezoid::getheight() {
	return height;
}

double trapezoid::area() const {
	return (upper_base + lower_base) * height / 2;
}

double trapezoid::perimeter() const {
	return upper_base + lower_base + leg1 * 2;
}
