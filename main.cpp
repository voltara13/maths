#include <iomanip>
#include <iostream>

using namespace std;

int prec, n;
double a, b;


double f(double x)
{
	return (x * x * log(x)) / (10 + x * x);
}

void Input()
{
	cout << "Введите количество знаков после запятой: ";
	cin >> prec;
	cout << "Введите пределы интегрирования (через пробел): ";
	cin >> a >> b;
	cout << "Введите число отрезков: ";
	cin >> n;
	cout << fixed << setprecision(prec);
}

void MiddleRectangles()
{
	double res = 0, h = 0, x = a;
	h = (b - a) / n;
	for (int i = 0; i < n; i++, x += h)
		res += f(x + h / 2);
	cout << "Метод средних прямоугольников\n" << 
		h * res << endl;
}

void RightRectangles()
{
	double res = 0, h = 0, x = a;
	h = (b - a) / n;
	x -= h;
	for (int i = 0; i < n; i++, x += h)
		res += f(x + h);
	cout << "Метод правых прямоугольников\n" << 
		h * res << endl;
}

void NewtonCotes()
{
	int n = 3;
	int wi[4] = { 1, 3, 3, 1 };
	double res = 0, h = 0, x = a, C0 = 3.0 / 8.0;
	h = (b - a) / n;
	for (int i = 0; i <= n; i++, x += h)
		res += wi[i] * f(x);
	cout << "Метод Ньютона-Котеса 3-го порядка\n" << 
		C0 * h * res << endl;
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
