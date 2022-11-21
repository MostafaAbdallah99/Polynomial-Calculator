#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "PolyCal.h"

using namespace std;

int main()
{
	PolyCal p;

	string s1, s2;
	cin >> s1 >> s2;
	
    p.Subtraction(s1, s2);

	return 0;
}

