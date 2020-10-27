#include <iostream>
#include <vector>

using namespace std;

vector<pair <double, double>> points;
int n;
void Request()
{
	double x, y;
	cout << "Введите количество точек: ";
	cin >> n;
	cout << "Введите 'x' и 'y' через пробел\n";
	for (int i = 0; i < n; i++)
	{
		cin >> x >> y;
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
	
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			matrix[i][j] = pow(points[j].first, n - i - 1);
	for (int i = 0; i < n; i++)
		res[i] = pow(-1, n - 1) * det(matrix, i) / det(matrix);
	cout << "Коэффициенты, полученные методом Лагранжа\n";
	for (int i = 0; i < n; i++) cout << "a" << i << " = " << res[n - i - 1] << endl;
}

void PolynomialInNewthon()
{
	vector<double> res(n);
	
	for (int i = 0; i < n; i++)
	{
		double val = 0;
		for (int j = 0; j < i; j++)
		{
			double seq = 1;
			for (int k = 0; k < i; k++)
				if (k != j) seq *= points[j].first - points[k].first;
			val += points[j].second / seq;
		}
		res[i] = val;
	}
	cout << "Коэффициенты, полученные методом Ньютона\n";
	for (int i = 0; i < n; i++) cout << "a" << i << " = " << res[i] << endl;
}

void LeastSquareMethod()
{
	double max = 0, factor = 0;
	int iM = 0, jM = 0, polyDeg;
	cout << "Введите степень многочлена: ";
	cin >> polyDeg;
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
	for (int i = 0; i < polyDeg + 1; i++) cout << "a" << i << " = " << res[polyDeg - i] << endl;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	Request();
	PolynomialInLagrange();
	PolynomialInNewthon();
	LeastSquareMethod();
	return 0;
}
