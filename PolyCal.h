#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <iomanip>
#include <sstream>
using namespace std;
class PolyCal
{

public:
	PolyCal();
	int gcd(int, int);
	int strToInt(string);
	double strToDouble(string);
	string Calculation(string);
	string doubleToFraction(double);
	string Summation(string, string);
	string checkEquation(string, string, string);
	string Subtraction(string, string);
	string Multiplication(string, string);
	~PolyCal();
};

