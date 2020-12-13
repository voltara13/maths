#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

double x_0 = 1;
double y_0 = 15;
double x_n;

double f(double x, double y)
{
	return 1 - y + x;
}

void Input()
{
	cout << "Введите координату конечной точки x: ";
	cin >> x_n;
}

void Euler()
{
	vector<pair<double, double>> points = { make_pair(x_0, y_0) };
	double h;
	cout << "\nВведите значение шага: ";
	cin >> h;
	for (double x = points[0].first + h; abs(x_n) - abs(x) > 0; x += h)
		points.emplace_back(
			x, 
			points.back().second + h * f(
				points.back().first, 
				points.back().second));
	cout << "Точки полученные через метод Эйлера\n";
	for (const auto& element : points)
		cout << element.first << ";" << element.second << endl;
}

void RungeKuttaMerson()
{
	vector<pair<double, double>> points = { make_pair(x_0, y_0) };
	int prec;
	double h = 1;
	cout << "\nВведите количество знаков после запятой: ";
	cin >> prec;
	for (double x = points[0].first; abs(x_n) - abs(x) > 0;)
	{
		double k_1 = h * f(
			points.back().first, 
			points.back().second);
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
		if (abs(x_n) - abs(x + h) <= 0) break;
		points.emplace_back(
			x += h,
			points.back().second + 1.0 / 6.0 * k_1 + 2.0 / 3.0 * k_4 + 1.0 / 6.0 * k_5);
		if (abs(delta) <= pow(10, -prec) * abs(points.back().second) / 32)
			h *= 2;
	}
	cout << fixed << setprecision(prec);
	cout << "\nТочки полученные через метод Рунге–Кутты Мерсона\n";
	for (const auto& element : points)
		cout << element.first << ";" << element.second << endl;
}

void CorrectedEuler()
{
	vector<pair<double, double>> points = { make_pair(x_0, y_0) };
	double h;
	cout << "\nВведите значение шага: ";
	cin >> h;	
	for(double x = points[0].first + h; abs(x_n) - abs(x) > 0; x += h)
		points.emplace_back(
			x,
			points.back().second + h * 0.5 * (f(
				points.back().first, 
				points.back().second) + f(
				points.back().first + h, 
				points.back().second + h * f(
				points.back().first, 
				points.back().second))));
	cout << "Точки полученные через исправленный метод Эйлера\n";
	for (const auto& element : points)
		cout << element.first << ";" << element.second << endl;
}

void Adams()
{
	vector<pair<double, double>> points = { make_pair(x_0, y_0) };
	double h, x;
	cout << "\nВведите значение шага: ";
	cin >> h;
	for (x = points[0].first + h; points.size() != 3; x += h)
		points.emplace_back(
			x,
			points.back().second + h * 0.5 * (f(
				points.back().first, 
				points.back().second) + f(
				points.back().first + h, 
				points.back().second + h * f(
				points.back().first, 
				points.back().second))));
	for (; abs(x_n) - abs(x) > 0; x += h)
		points.emplace_back(
			x,
			points.back().second + h / 12.0 * (23 * f(
				points[points.size() - 1].first,
				points[points.size() - 1].second) - 16 * f(
				points[points.size() - 2].first,
				points[points.size() - 2].second) + 5 * f(
				points[points.size() - 3].first,
				points[points.size() - 3].second)));
	cout << "Точки полученные через метод Адамса\n";
	for (const auto& element : points)
		cout << element.first << ";" << element.second << endl;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	Input();
	Euler();
	RungeKuttaMerson();
	CorrectedEuler();
	Adams();
	return 0;
}