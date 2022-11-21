#include "PolyCal.h"
#include <map>
#include <cmath>
#include <string>
#include <string.h>
#include <vector>
#include <fstream>
#include <istream>
#include <algorithm>
#include <iostream>

using namespace std;


//constructor
PolyCal::PolyCal() {}

string PolyCal::checkEquation(string str1, string str2, string proc) {
	fstream file;
	file.open("Calculator.txt");
	string line, s1, s2, s3, s4, temp = "";
	while (!file.eof()) {
		file >> s1 >> s2 >> s3 >> s4;
		//if (file == "")break;

		if (s1 == str1 && s2 == str2 && s3 == proc) {
			temp = s4;
		}
		else {
			if (proc == "Sum" || proc == "Multibly") {
				if (str1 == s2 && str2 == s1) {
					temp = s4;
				}
			}
		}

	}

	file.close();
	return temp;
}

//GCD function
int PolyCal::gcd(int x, int y) {
	if (!y)return x;
	return gcd(y, x%y);
}


//Double to fraction function
string PolyCal::doubleToFraction(double number) {

	int sum = round(120 * number), temp = number;
	if ((double)temp == number) return to_string(temp);
	else {

		int x = gcd(sum, 120);
		return to_string(abs(sum / x)) + '/' + to_string(abs(120 / x));
	}
}

//string to int function 
int PolyCal::strToInt(string str) {

	int sum = 0;

	for (int i = str.size() - 1, j = 0; i >= 0; i--, j++) {
		sum += (str[i] - '0')*pow(10, j);
	}

	return sum;
}


//string to double function 
double PolyCal::strToDouble(string str) {

	double sum = 0;

	string str1 = str.substr(0, str.find('/')), str2 = str.substr(str.find('/') + 1);

	sum = (double)strToInt(str1) / (double)strToInt(str2);

	return sum;
}


//calculation function
string PolyCal::Calculation(string str) {

	map<string, double>mp;

	double fact;

	string t = str;

	t = t[0];

	for (int i = 1; i < str.size(); i++) {

		if (str[i] == '-' || str[i] == '+') {

			//it's a positive term
			if (t[0] == '+') {

				//the power of the variable not equals to zero
				if (t.find('x') != -1) {

					string subfact = t.substr(1, t.find('x') - 1);
					string subvar = t.substr(t.find('x'));

					//the factor is greater than one  
					if (subfact != "") {

						if (subfact.find('/') != -1) {
							fact = strToDouble(subfact);
						}

						else {
							fact = strToInt(subfact);
						}

						mp[subvar] += fact;

					}


					//the factor equals to one 
					else {
						mp[subvar] ++;
					}

				}

				//the power of the variable equals to zero
				else {

					string subfact = t.substr(1);

					if (subfact.find('/') != -1) {
						fact = strToDouble(subfact);
					}

					else {
						fact = strToInt(subfact);
					}

					mp["sum"] += fact;

				}

			}

			//it's a negative term
			if (t[0] == '-') {

				//the power of the variable not equals to zero
				if (t.find('x') != -1) {

					string subfact = t.substr(1, t.find('x') - 1);
					string subvar = t.substr(t.find('x'));

					//the factor is greater than one  
					if (subfact != "") {

						if (subfact.find('/') != -1) {
							fact = strToDouble(subfact);
						}

						else {
							fact = strToInt(subfact);
						}

						mp[subvar] -= fact;

					}

					//the factor equals to one 
					else {
						mp[subvar] --;
					}
				}

				//the power of the variable equals to zero
				else {

					string subfact = t.substr(1);

					if (subfact.find('/') != -1) {
						fact = strToDouble(subfact);
					}

					else {
						fact = strToInt(subfact);
					}

					mp["sum"] -= fact;

				}

			}

			t = str[i];

		}

		else {
			t += str[i];
		}

	}

	string result = "";
	vector<pair<string, double>>v;

	int facti;
	for (auto i : mp) {
		v.emplace_back(make_pair(i.first, i.second));
	}

	sort(v.rbegin(), v.rend());

	for (auto i : v) {

		if (i.first == "sum") {

			if (i.second == 0) {
				continue;
			}

			else if (i.second > 0) {


				facti = i.second;

				if (facti == i.second) {
					result += '+' + doubleToFraction(abs(facti));
				}

				else {
					result += '+' + doubleToFraction(abs(i.second));
				}

			}

			else {

				facti = i.second;

				if (facti == i.second) {
					result += '-' + doubleToFraction(abs(facti));
				}
				else {
					result += '-' + doubleToFraction(abs(i.second));
				}

			}

		}

		else {

			facti = i.second;

			if (i.second == 0) {
				continue;
			}

			else if (i.second > 0) {

				if (i.second == 1) {
					result += '+' + i.first;
				}

				else {
					if (facti == i.second) {
						result += '+' + doubleToFraction(abs(facti)) + i.first;
					}

					else {
						result += '+' + doubleToFraction(abs(i.second)) + i.first;
					}

				}
			}

			else {

				if (i.second == -1) {
					result += '-' + i.first;
				}
				else {

					if (facti == i.second) {
						result += '-' + doubleToFraction(abs(facti)) + i.first;
					}

					else {
						result += '-' + doubleToFraction(abs(i.second)) + i.first;
					}

				}
			}

		}

	}

	if (result[0] == '+') {
		result.erase(0, 1);
	}

	return result != "" ? result : "0";

}


//summation function
string PolyCal::Summation(string str1, string str2) {

	if (checkEquation(str1, str2, "sum") != "") {
		return checkEquation(str1, str2, "sum");
	}

	string str;

	if (str2[0] == '-') {
		str = str1 + str2;
	}

	else {
		str = str1 + '+' + str2;
	}

	if (str[0] != '-') {
		str = '+' + str;
	}

	str += '+';
	string answer = Calculation(str);
	fstream file;
	file.open("Calculator.txt", ios::app);
	file << str1 << "\n" << str2 << "\nSum\n" << answer << "\n";
	file.close();
	return answer;
}


//subtraction function
string PolyCal::Subtraction(string str1, string str2) {

	if (checkEquation(str1, str2, "sub") != "") {
		return checkEquation(str1, str2, "sub");
	}

	string str;

	if (str2[0] != '-') {
		str2 = '+' + str2;
	}

	for (int i = 0; i < str2.size(); i++) {
		if (str2[i] == '-') {
			str2[i] = '+';
		}
		else if (str2[i] == '+') {
			str2[i] = '-';
		}
	}

	str = str1 + str2;

	if (str[0] != '-') {
		str = '+' + str;
	}

	str += '+';

	string answer = Calculation(str);
	fstream file;
	file.open("Calculator.txt", ios::app);
	file << str1 << "\n" << str2 << "\nSub\n" << answer << "\n";
	file.close();
	return answer;
}


//Multiplication function
string PolyCal::Multiplication(string eq1, string eq2)
{

	if (checkEquation(eq1, eq2, "Multiply") != "") {
		return checkEquation(eq1, eq2, "Multiply");
	}

	map<string, double>mp;
	map<string, double>result;
	string factor = "";

	for (int i = 0; i < eq1.size(); i++) {

		if (((eq1[i] == '+' || eq1[i] == '-') && i != 0) || i == eq1.size() - 1) {

			if (i == eq1.size() - 1) {
				factor += eq1[i];
			}


			if (factor[0] != '+' && factor[0] != '-') {
				factor = "+" + factor;
			}


			//check if the factor contain dom&nom
			if (factor[0] == '+' || factor[0] == '-') {

				if (factor.find('/') != -1) {

					int indx = factor.find('/');
					int indx2 = factor.find('x');

					string nom = factor.substr(1, indx - 1);
					string dom = indx2 != -1 ? factor.substr(indx + 1, indx2 - 1) : factor.substr(indx + 1);

					//convert the string nom to double
					double Nom = stod(nom);
					//convert the string dom to double
					double Dom = stod(dom);
					double fact = Nom / Dom;

					string var = indx2 != -1 ? factor.substr(indx2) : "x^0";

					mp[var] = factor[0] == '+' ? fact : -fact;
					factor = "";

				}

				else {

					int indx2 = factor.find('x');
					double fact;

					if (indx2 - 1 < 1 && indx2 != -1) {
						fact = 1;
					}

					else {
						fact = indx2 != -1 ? stod(factor.substr(1, indx2 - 1)) : stod(factor.substr(1));
					}

					string var = indx2 != -1 ? factor.substr(indx2) : "x^0";

					mp[var] = factor[0] == '+' ? fact : -fact;
					factor = "";

				}

			}
		}

		factor += eq1[i];

	}

	factor = "";
	for (int i = 0; i < eq2.size(); i++) {

		if (((eq2[i] == '+' || eq2[i] == '-') && i != 0) || i == eq2.size() - 1) {

			if (i == eq2.size() - 1) {
				factor += eq2[i];
			}

			// if it's the first factor factor[0] will be '-' or ' '
			if (factor[0] != '+' && factor[0] != '-') {
				factor = "+" + factor;
			}

			//check if the factor contain dom&nom
			if (factor[0] == '+' || factor[0] == '-') {

				if (factor.find('/') != -1) {

					int indx = factor.find('/');
					int indx2 = factor.find('x');

					string nom = factor.substr(1, indx - 1);
					string dom = indx2 != -1 ? factor.substr(indx + 1, indx2 - 1) : factor.substr(indx + 1);

					//convert the string nom to double
					double Nom = stod(nom);
					//convert the string dom to double
					double Dom = stod(dom);
					double fact = Nom / Dom;

					string var = indx2 != -1 ? factor.substr(indx2) : "x^0";
					fact = factor[0] == '+' ? fact : -fact;

					map<string, double>::iterator itr;

					for (itr = mp.begin(); itr != mp.end(); ++itr) {

						//get the new power after the multiplication
						string s1 = itr->first;

						int pow1 = s1.find('^') != -1 ? stoi(s1.substr(s1.find('^') + 1)) : 1;
						int pow2 = var.find('^') != -1 ? stoi(var.substr(var.find('^') + 1)) : 1;
						int newPow = pow1 + pow2;

						string newVar = "x^" + to_string(newPow);
						//get the new factor after the multiplication
						double fact2 = itr->second;
						double newFact = fact2 * fact;
						//if (newPow == 1)newVar = "x";

						result[newVar] += newFact;
					}

					factor = "";

				}

				else {

					int indx2 = factor.find('x');
					double fact;
					if (indx2 - 1 < 1 && indx2 != -1) {
						fact = 1;
					}

					else {
						fact = indx2 != -1 ? stod(factor.substr(1, indx2 - 1)) : stod(factor.substr(1));
					}

					string var = indx2 != -1 ? factor.substr(indx2) : "x^0";
					fact = factor[0] == '+' ? fact : -fact;
					map<string, double>::iterator itr;

					for (itr = mp.begin(); itr != mp.end(); ++itr) {
						//get the new power after the multiplication
						string s1 = itr->first;
						int pow1;
						int pow2;

						s1.find('^') != -1 ? pow1 = stoi(s1.substr(s1.find('^') + 1)) : pow1 = 1;
						var.find('^') != -1 ? pow2 = stoi(var.substr(var.find('^') + 1)) : pow2 = 1;

						int newPow = pow1 + pow2;

						string newVar = "x^" + to_string(newPow);
						//if (newPow == 1)newVar = "x";

						//get the new factor after the multiplication
						double fact2 = itr->second;
						double newFact = fact2 * fact;
						result[newVar] += newFact;

					}

					factor = "";

				}

			}
		}

		factor += eq2[i];

	}

	string finalResult = "";

	map<string, double>::reverse_iterator itr;
	for (itr = result.rbegin(); itr != result.rend(); ++itr) {

		double factf = itr->second;
		int facti = factf;
		string var = itr->first;
		cout << itr->first << "\n";
		if (var == "x^1")
			var = "x";
		if (itr->second == 0)continue;

		if (facti != factf) {

			if (factf < 0) {

				if (factf == -1) {
					if (itr->first == "x^0") {
						finalResult += '-' + '1';
					}
				}

				else {
					if (itr->first == "x^0")finalResult += doubleToFraction(factf);
					else finalResult += doubleToFraction(factf) + var;
				}
			}

			else {
				if (finalResult != "") {
					if (factf == 1) {
						if (itr->first == "x^0") {
							finalResult += '+' + '1';
						}
					}

					else {
						if (itr->first == "x^0")finalResult += "+" + doubleToFraction(factf);

						else finalResult += "+" + doubleToFraction(factf) + var;
					}
				}

				else {

					if (factf == 1) {
						if (itr->first == "x^0")finalResult += "1";

						else finalResult += var;
					}

					else {
						if (itr->first == "x^0")finalResult += doubleToFraction(factf);

						else finalResult += doubleToFraction(factf) + var;
					}
				}

			}
		}

		else {
			if (facti < 0) {

				if (facti == -1) {
					if (itr->first == "x^0") {
						finalResult += '-' + '1';
					}
				}

				else {
					if (itr->first == "x^0")finalResult += doubleToFraction(facti);
					else finalResult += doubleToFraction(facti) + var;
				}
			}

			else {
				if (finalResult != "") {
					if (facti == 1) {
						if (itr->first == "x^0") {
							finalResult += '+' + '1';
						}
						else
							finalResult += '+' + var;

					}

					else {
						if (itr->first == "x^0")finalResult += "+" + doubleToFraction(facti);

						else finalResult += "+" + doubleToFraction(facti) + var;
					}
				}

				else {

					if (facti == 1) {
						if (itr->first == "x^0")finalResult += "1";

						else finalResult += var;
					}

					else {
						if (itr->first == "x^0")finalResult += doubleToFraction(facti);

						else finalResult += doubleToFraction(facti) + var;
					}
				}

			}
		}


	}


	fstream file;
	file.open("Calculator.txt", ios::app);
	file << eq1 << "\n" << eq2 << "\nMultiply\n" << finalResult << "\n";
	file.close();

	return finalResult;
}

//destructor
PolyCal::~PolyCal() {}
