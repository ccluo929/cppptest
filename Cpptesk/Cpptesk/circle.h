#pragma once
#include<iostream>
#include<cmath>
#include<cstdlib>
#include "Squares.h"
using namespace std;
class circle :public Shape
{
private:
	double r;
public:
	circle();
	void show() const override;
	double getr();
	double area() const override;
	double perimeter() const override;
};
