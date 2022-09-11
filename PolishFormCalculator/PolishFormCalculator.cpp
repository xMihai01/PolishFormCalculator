#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stack>

int prec2(std::string elem) {
	if (elem == "(")
		return 0;
	else if (elem == "+" || elem == "-")
		return 1;
	else if (elem == "*" || elem == "/")
		return 2;
	else if (elem == "^")
		return 3;
	else if (elem == ")")
		return -1;

	return 4;

}

bool elementValid(std::string elem) {
	for (int i = 0; i < elem.length(); i++) {
		if (elem == "+" || elem == "-" || elem == "*" || elem == "/" || elem == "^" || elem == ")" || elem == "(")
			return true;
		else if (((elem[i] >= 65 && elem[i] <= 90) || (elem[i] >= 97 && elem[i] <= 122)))
			return false;
	}
	return true;

}

std::vector<std::string> formaPoloneza(std::vector<std::string> expresie) {

	std::stack<std::string> OP;
	std::vector <std::string> FP;

	for (int i = 0; i < expresie.size(); i++) {


		if (prec2((expresie[i])) == 4) {
			FP.push_back((expresie[i]));

		}
		else {
			if (expresie[i] == "(")
				OP.push("(");
			else {
				if (expresie[i] == ")") {
					while (!OP.empty() && OP.top() != "(") {
						FP.push_back(OP.top());
						OP.pop();
					}
					OP.pop();
				}
				else {
					while (!OP.empty() && prec2((expresie[i])) <= prec2(OP.top())) {
						FP.push_back(OP.top());
						OP.pop();
					}
					OP.push((expresie[i]));
				}

			}
		}

	}

	while (!OP.empty()) {
		FP.push_back(OP.top());
		OP.pop();
	}

	return FP;

}

void evaluareExpresie(std::vector<std::string> FP) {

	std::stack<double> num;
	double rez = 0;

	for (unsigned int i = 0; i < FP.size(); i++) {
		double elem = 0;

		if (prec2(FP[i]) == 4) {
			elem = stod(FP[i]);
			num.push(elem);
		}
		else {
			double y = num.top();
			num.pop();
			double x = num.top();
			num.pop();
			if (FP[i] == "+") {
				rez = x + y;
			}
			else if (FP[i] == "-") {
				rez = x - y;
			}
			else if (FP[i] == "*") {
				rez = x * y;
			}
			else if (FP[i] == "/") {
				rez = x / y;
			}
			else if (FP[i] == "^") {
				rez = pow(x, y);
			}
			num.push(rez);

		}
	}
	std::cout << "\nRezultatul expresiei este " << rez << "\n";
}


void citireExpresie(std::vector<std::string>& expresie) {

	std::vector<std::string> temp;
	std::ifstream citire("fisier.txt");
	char car = ' ';
	while (citire >> car) {
		std::string str(1, car);
		if (car != ' ')
			temp.push_back(str);
	}

	std::cout << std::endl;

	int k = 0;
	for (unsigned int i = 0; i < temp.size(); i++) {

		int j = 1;
		expresie.push_back(temp[i]);
		while ((i + 1 < temp.size()) && prec2(temp[i]) == 4) {
			if (prec2(temp[i + 1]) == 4) {
				expresie[k] += temp[i + j];
				i++;
			}
			else
				break;

		}
		k++;
	}

}

bool validareExpresie(std::vector<std::string> expresie) {


	std::stack<char> paranteze;
	std::string parantezeString = "";

	for (unsigned int i = 0; i < expresie.size(); i++) {


		if ((prec2(expresie[i]) == 1 || prec2(expresie[i]) == 2) || prec2(expresie[i]) == 3)
			if (i < expresie.size() - 1 && ((prec2(expresie[i + 1]) == 2 || prec2(expresie[i + 1]) == 1) || prec2(expresie[i + 1]) == 3))
				return false;
		if (!elementValid(expresie[i]))
			return false;

		if (expresie[i] == "(" || expresie[i] == ")")
			parantezeString += expresie[i];

	}

	for (unsigned int i = 0; i < parantezeString.length(); i++) {

		if (parantezeString[i] == '(')
		{
			paranteze.push('(');
		}
		else {
			if (paranteze.empty())
				return false;

			paranteze.pop();
		}
	}

	return true;
}

int main() {

	std::ifstream citire("fisier.txt");
	char car;

	std::vector<std::string> expresie;
	citireExpresie(expresie);
	if (validareExpresie(expresie)) {
		std::vector<std::string> postfix = formaPoloneza(expresie);
		std::cout << "Forma poloneza postfixata este: ";
		for (unsigned int i = 0; i < postfix.size(); i++) {
			std::cout << postfix[i];
		}
		evaluareExpresie(postfix);
	}
	else {
		std::cout << "Expresia nu este valida!";
	}


	return 0;
}