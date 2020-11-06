#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

vector<pair <double, double>> points;
int n;

int CheckValue()
{
	while (true)
	{
		int a;
		cin >> a;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(32767, '\n');
			cout << "Введено неверное значение, пожалуйста, попробуйте ещё раз: ";
		}
		else
		{
			cin.ignore(32767, '\n');
			return a;
		}
	}
}

void Request()
{
	double x, y;
	cout << "Введите количество точек: ";
	n = CheckValue();
	cout << "Введите 'x' и 'y' через пробел\n";
	for (int i = 0; i < n; i++)
	{
		cin >> x >> y;
		cin.ignore(32767, '\n');
		points.emplace_back(x, y);
	}
}

void PolynomialInLagrange()
{
	auto det
	{
		[](vector<vector<double>>& _matrix, int p = -1)
		{
			double det = 1;
			const double EPS = 1E-9;
			vector<vector<double>> matrix = _matrix;
			if (p != -1)
				for (int i = 0; i < n; i++)
					if (i == p)
					{
						for (int j = 0; j < n; j++)
							matrix[i][j] = points[j].second;
						break;
					}
			for (int i = 0; i < n; i++)
			{
				int iM = i;
				for (int j = i + 1; j < n; j++)
					if (abs(matrix[j][i]) > abs(matrix[iM][i]))
						iM = j;
				if (abs(matrix[iM][i]) < EPS)
				{
					det = 0;
					break;
				}
				swap(matrix[i], matrix[iM]);
				if (i != iM)
					det = -det;
				det *= matrix[i][i];
				for (int j = i + 1; j < n; j++)
					matrix[i][j] /= matrix[i][i];
				for (int j = 0; j < n; j++)
					if (j != i && abs(matrix[j][i]) > EPS)
						for (int k = i + 1; k < n; k++)
							matrix[j][k] -= matrix[i][k] * matrix[j][i];
			}
			return det;
		}
	};
	vector<double> res(n);
	vector<vector<double>> matrix(n, vector<double>(n));
	stringstream resStr;
	
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			matrix[i][j] = pow(points[j].first, n - i - 1);
	double det2 = det(matrix);
	for (int i = 0; i < n; i++)
		res[i] = det(matrix, i) / det2;
	for (int i = 0; i < n; i++) 
	{
		if (res[n - i - 1])
		{
			if (i)
			{
				if (res[n - i - 1] > 0)
				{
					if (resStr.str()[0]) resStr << "+";
					resStr << res[n - i - 1] << "x";
				}
				else if (res[n - i - 1] < 0)
					resStr << res[n - i - 1] << "x";
				if (i != 1)
					resStr << "^" << i;
			}
			else resStr << res[n - i - 1];
		}
	}
	cout << "Полином, полученный методом Лагранжа\n" << resStr.str() << endl;
}

void PolynomialInNewton()
{
	vector<double> res(n);
	stringstream resStr;

	for (int i = 0; i < n; i++)
	{
		double val = 0;
		for (int j = 0; j <= i; j++)
		{
			double seq = 1;
			for (int k = 0; k <= i; k++)
				if (k != j) seq *= points[j].first - points[k].first;
			val += points[j].second / seq;
		}
		res[i] = val;
	}
	for (int i = 0; i < n; i++)
	{
		if (res[i])
		{
			if (i)
			{
				if (res[i] > 0)
				{
					if (resStr.str()[0]) resStr << "+";
					resStr << res[i];
				}		
				else if (res[i] < 0) resStr << res[i];
				for (int j = 0; j < i; j++)
				{
					if (points[j].first)
					{
						resStr << "(x";
						if (points[j].first > 0) resStr << "-" << points[j].first << ")";
						else if (points[j].first < 0) resStr << "+" << -points[j].first << ")";
					}
					else resStr << "x";
				}
			}
			else resStr << res[0];
		}
	}
	cout << "Полином, полученный методом Ньютона\n" << resStr.str() << endl;
}

void LeastSquareMethod()
{
	double max = 0, factor = 0;
	int iM = 0, jM = 0, polyDeg;
	cout << "Введите степень многочлена: ";
	polyDeg = CheckValue();
	vector<vector<double>> rssA(polyDeg + 1, vector<double>(polyDeg + 1));
	vector<double> rssB(polyDeg + 1);
	vector<double> res(polyDeg + 1);

	for (int i = 0; i < polyDeg + 1; i++)
	{
		for (auto &it : points)
			rssB[i] += it.second * pow(it.first, i);
		for (int j = 0; j < polyDeg + 1; j++)
		{
			for (auto &it : points)
				rssA[i][j] += pow(it.first, i + j);
			if (abs(rssA[i][j]) > max)
				max = rssA[i][j], iM = i, jM = j;
		}
	}
	for (int j = 0; j < polyDeg + 1; j++)
		swap(rssA[0][j], rssA[iM][j]);
	for (int i = 0; i < polyDeg + 1; i++)
		swap(rssA[i][0], rssA[i][jM]);
	swap(rssB[0], rssB[iM]);
	for (int i = 0; i < polyDeg + 1; i++)
	{
		factor = rssA[i][i];
		for (int j = 0; j < polyDeg + 1; j++)
			rssA[i][j] /= factor;
		rssB[i] /= factor;
		for (int k = i + 1; k < polyDeg + 1; k++)
			if (rssA[k][i])
			{
				factor = rssA[k][i] / rssA[i][i];
				for (int j = 0; j < polyDeg + 1; j++)
					rssA[k][j] -= factor * rssA[i][j];
				rssB[k] -= rssB[i] * factor;
			}
	}
	for (int i = polyDeg; i >= 0; i--)
	{
		res[i] = rssB[i] / rssA[i][i];
		for (int j = 0; j < i; j++)
			rssB[j] -= rssA[j][i] * res[i];
	}
	cout << "Коэффициенты, полученные методом наименьших квадратов\n";
	for (int i = 0; i < polyDeg + 1; i++) cout << "a" << i << " = " << res[i] << endl;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	Request();
	PolynomialInLagrange();
	PolynomialInNewton();
	LeastSquareMethod();
	return 0;
}
