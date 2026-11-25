#pragma once
#include<iostream>
#include<cmath>
#include<cstdlib>
#include "Squares.h"
using namespace std;
class Triangle:public Shape {
private:
	double a, b, c;
public:
	Triangle();
	double geta();
	double getb();
	double getc();
	void show()const override;
	double area() const override ;
	double perimeter() const override;
};
