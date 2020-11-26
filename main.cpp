#include <iomanip>
#include <iostream>

using namespace std;

int prec;
double a, b;

double f(double x)
{
	return (x * x * log(x)) / (10 + x * x);
}

void Input()
{
	cout << "Введите количество знаков после запятой: ";
	cin >> prec;
	prec++;
	cout << "Введите пределы интегрирования (через пробел): ";
	cin >> a >> b;
}

void MiddleRectangles()
{
	int n;
	double res = 0, h = 0, x = a;
	cout << "Введите число отрезков: ";
	cin >> n;
	h = (b - a) / n;
	for (int i = 0; i < n; i++, x += h)
		res += f(x + h / 2);
	cout << setprecision(prec) << h * res << endl;
}

void RightRectangles()
{
	int n;
	double res = 0, h = 0, x = 0;
	cout << "Введите число отрезков: ";
	cin >> n;
	h = (b - a) / n;
	x = a - h;
	for (int i = 0; i < n; i++, x += h)
		res += f(x + h);
	cout << setprecision(prec) << h * res << endl;
}

void NewtonCotes()
{
	
}

int main()
{
	setlocale(LC_ALL, "Russian");
	Input();
	MiddleRectangles();
	RightRectangles();
	NewtonCotes();
	return 0;
}
