#pragma once
#include<iostream>
#include<cmath>
#include<cstdlib>
using namespace std;
class Shape{
//private:
//	double a, b, c, d;
public:
	virtual ~Shape() = default;
	virtual double area() const = 0 ;
	virtual double perimeter() const = 0;
	virtual void show() const = 0;
};
class four_square :public Shape {
private:
	double side;
public:
	four_square();
	void show() const override;
	double getside();
	double area() const override;
	double perimeter() const override;
};
class rectangle :public Shape {
private:
	double lenth, width;
public:
	rectangle();
	void show() const override;
	double getlenth();
	double getwidth();
	double area() const override;
	double perimeter() const override;
};
class trapezoid :public Shape {
private:
	double upper_base, lower_base,height,leg1,leg2;
public:
	trapezoid();
	void show() const override;
	double getupper_base();
	double getlower_base();
	double getheight();
	double area() const override;
	double perimeter() const override;
};
