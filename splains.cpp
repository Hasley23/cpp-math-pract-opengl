#include<iostream>
#include <stdio.h>
#include <math.h>
#include <cmath>
#include <stdlib.h>
#include <iomanip>
#include <iostream>
#include <fstream>

using namespace std;

float CalcD(float x) {
	return (27 / 6) * cosh(3 * x);
}

float CalcC(float x, float h) {
	float C;
	C = 9 * sinh(3 * x) - 6 * CalcD(x) * h;
	return C;
}

float CalcB(float x, float h) {
	float B;
	B = 3 * cosh(3 * x) - 2 * h * CalcC(x, h) - 3 * h*h*CalcD(x);
	return B;
}

float CalcA(float x, float h) {
	float A;
	A = sinh(3 * x) - CalcB(x, h) * h - CalcC(x, h) * h* h - CalcD(x)*h*h*h;
	return A;
}




int main() {
	float x, y, h, N, a1, a2;
	// h - значение шага (x-xk)
	cout << "Enter segment : ";
	cin >> a1 >> a2;
	cout << "Input N = " ;
	cin >> N;
	h = (a2-a1) / N;

	ofstream out;
	out.open("output_splain.txt");
	for (x = a1; x < a2; x += h) {
		y = CalcA(x, h) + CalcB(x, h)*h + CalcC(x, h)*h*h + CalcD(x)*h*h*h;
		cout << x << "; " << y << endl;
		out << x << "; " << y << endl;
	}

	system("pause");
}