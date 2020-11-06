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

void CubicSpline()
{
	
}

int main()
{
	setlocale(LC_ALL, "Russian");
	Request();
	CubicSpline();
	return 0;
}
