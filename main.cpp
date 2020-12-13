#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

double x_0 = 1;
double y_0 = 15;
double x_n;
int prec;

double f(double x, double y)
{
	return 1 - y + x;
}

void Input()
{
	cout << "Введите координату конечной точки x: ";
	cin >> x_n;
	cout << "Введите количество знаков после запятой: ";
	cin >> prec;
	cout << fixed << setprecision(prec);
}

void Euler()
{
	vector<pair<double, double>> points = { make_pair(x_0, y_0) };
	double h = abs(abs(x_n) - abs(x_0)) / pow(10, prec);
	double x = points[0].first;
	while (abs(x_n) - abs(x) > 0)
		points.emplace_back(
			x += h, 
			points.back().second + h * f(
				points.back().first, 
				points.back().second));
	for (const auto& element : points)
		cout << element.first << ";" << element.second << endl;
}

void RungeKuttaMerson()
{
	vector<pair<double, double>> points = { make_pair(x_0, y_0) };
	double h = 1;
	double x = points[0].first;
	while (abs(x_n) - abs(x) > 0)
	{
		double k_1 = h * f(points.back().first, points.back().second);
		double k_2 = h * f(
			points.back().first + 1.0 / 3.0 * h,
			points.back().second + 1.0 / 3.0 * k_1);
		double k_3 = h * f(
			points.back().first + 1.0 / 3.0 * h,
			points.back().second + 1.0 / 6.0 * k_1 + 1.0 / 6.0 * k_2);
		double k_4 = h * f(
			points.back().first + 1.0 / 2.0 * h,
			points.back().second + 1.0 / 8.0 * k_1 + 3.0 / 8.0 * k_3);
		double k_5 = h * f(
			points.back().first + h,
			points.back().second + 1.0 / 2.0 * k_1 - 3.0 / 2.0 * k_3 + 2 * k_4);
		double delta = 1.0 / 30.0 * (2 * k_1 - 9 * k_3 + 8 * k_4 - k_5);
		if (abs(delta) >= pow(10, -prec) * abs(points.back().second))
		{
			h /= 2;
			continue;
		}
		points.emplace_back(
			x += h,
			points.back().second + 1.0 / 6.0 * k_1 + 2.0 / 3.0 * k_4 + 1.0 / 6.0 * k_5);
		if (abs(delta) <= pow(10, -prec) * abs(points.back().second) / 32)
			h *= 2;
	}
	for (const auto& element : points)
		cout << element.first << ";" << element.second << endl;
}

void CorrectedEuler()
{
	vector<pair<double, double>> points = { make_pair(x_0, y_0) };
	double h = abs(abs(x_n) - abs(x_0)) / pow(10, prec);
	double x = points[0].first;
	while (abs(x_n) - abs(x) > 0)
		points.emplace_back(
			x += h,
			points.back().second + h * 0.5 * (f(points.back().first, points.back().second) + f(
			points.back().first + h, points.back().second + h * f(
			points.back().first, points.back().second))));
	for (const auto& element : points)
		cout << element.first << ";" << element.second << endl;
}

void Adams()
{
	
}

int main()
{
	setlocale(LC_ALL, "Russian");
	Input();
	Euler();
	RungeKuttaMerson();
	CorrectedEuler();
	return 0;
}