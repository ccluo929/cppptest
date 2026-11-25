#pragma once
#include "circle.h"
#include "Squares.h"
#include "Triangle.h"
#include "Session.h"
#include <ctime>
#include <vector>
#include<iomanip>
#include <string>
#include <iostream>
#include<fstream>
using namespace std;

class TQB
{
private:
    const double eps = 1e-2;
    Session current;           
    double single_full = 0;
    double half_score = 0;
public:
    void start();
    Shape* generate_question(string& typeName, string& info, double& rightPeri, double& rightArea);
    void control();
    void doing();
    void end();
    void revise();
    void saveToFile(const string& userName);
    const Session& getSession() const;  
};
