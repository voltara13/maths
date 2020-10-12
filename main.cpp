#include <iostream>

using namespace std;

double f(double x)
{
	return x * x * x - x * x - 7 * x + 5;
}

double df(double x)
{
	return x * (3 * x - 2) - 7;
}

double d2f(double x)
{
	return 6 * x - 2;
}

double phi(double x)
{
	return (x * x * x - x * x + 5) / 7;
}

bool NewthonMethod()
{
	int i = 0;
	double a, b, eps, x0, xn;
	do
	{
		i = 0;
		cout << "Введите границы отрезка [a; b] через пробел: ";
		cin >> a >> b;
		cout << "Введите точность вычислений: ";
		cin >> eps;
		if (a > b)
			swap(a, b);
		if (f(a) * f(b) >= 0)
		{
			cout << "Ошибка, корней на данном отрезке нет\n";
			return false;
		}
		else
		{
			if (f(a) * d2f(a) > 0) x0 = a;
			else x0 = b;
			xn = x0 - f(x0) / df(x0);
			while (fabs(x0 - xn) > eps)
			{
				x0 = xn;
				xn = x0 - f(x0) / df(x0);
				cout << ++i << "-я итерация: " << xn << endl;
			}
			cout << "\nКорень: " << xn << ", количество итераций: " << i << endl;
		}
		cout << "\nВведите '0', чтобы выйти или '1', чтобы продолжить: ";
		cin >> i;
	} while (i);
	return true;
}

bool HalfDivision()
{
	int i = 0;
	double a, b, eps, x;
	do
	{
		cout << "Введите границы отрезка [a; b] через пробел: ";
		cin >> a >> b;
		cout << "Введите точность вычислений: ";
		cin >> eps;
		if (a > b)
			swap(a, b);
		if (f(a) * f(b) >= 0)
		{
			cout << "Ошибка, корней на данном отрезке нет\n";
			return false;
		}
		else
		{
			do
			{
				i++;
				x = (a + b) / 2;
				if (f(a) * f(x) > 0) a = x;
				else b = x;
			} while ((b - a) / 2 > eps);
			cout << "\nКорень: " << x << ", количество итераций: " << i << endl;
		}
		cout << "\nВведите '0', чтобы выйти или '1', чтобы продолжить: ";
		cin >> i;
	} while (i);
	return true;
}

void SimpleIterations()
{
	int i = 0;
	double x, x0, x1, x2, d, eps;
	do
	{
		i = 0;
		cout << "Введите 'x': ";
		cin >> x;
		cout << "Введите точность вычислений: ";
		cin >> eps;
		do
		{
			i++;
			x0 = x;
			x1 = phi(x0);
			x2 = phi(x1);
			d = x0 - 2 * x1 + x2;
			if (d) x = (x0 * x2 - x1 * x1) / d;
			else break;
		} while (fabs(x - x0) > eps);
		cout << "\nКорень: " << x << ", количество итераций: " << i << endl;
		cout << "\nВведите '0', чтобы выйти или '1', чтобы продолжить: ";
		cin >> i;
	} while (i);
}

int main()
{
	setlocale(LC_ALL, "Russian");
	if (!NewthonMethod()) if (!HalfDivision()) SimpleIterations();
	return 0;
}