#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

vector<pair<double, double>> points;
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

void PolynomialInLagrange(vector<double> &pointsY)
{
	auto det
	{
		[pointsY](vector<vector<double>>& _matrix, int p = -1)
		{
			double det = 1;
			const double EPS = 1E-9;
			vector<vector<double>> matrix = _matrix;
			if (p != -1)
			{
				for (int i = 0; i < pointsY.size(); i++)
					if (i == p)
					{
						for (int j = 0; j < pointsY.size(); j++)
							matrix[i][j] = pointsY[j];
						break;
					}
			}
			for (int i = 0; i < pointsY.size(); i++)
			{
				int iM = i;
				for (int j = i + 1; j < pointsY.size(); j++)
				{
					if (abs(matrix[j][i]) > abs(matrix[iM][i]))
						iM = j;
				}
				if (abs(matrix[iM][i]) < EPS)
				{
					det = 0;
					break;
				}
				swap(matrix[i], matrix[iM]);
				if (i != iM)
					det = -det;
				det *= matrix[i][i];
				for (int j = i + 1; j < pointsY.size(); j++)
					matrix[i][j] /= matrix[i][i];
				for (int j = 0; j < pointsY.size(); j++)
				{
					if (j != i && abs(matrix[j][i]) > EPS)
					{
						for (int k = i + 1; k < pointsY.size(); k++)
							matrix[j][k] -= matrix[i][k] * matrix[j][i];
					}					
				}
			}
			return det;
		}
	};
	vector<double> res(pointsY.size());
	vector<vector<double>> matrix(pointsY.size(), vector<double>(pointsY.size()));
	stringstream resStr;

	for (int i = 0; i < pointsY.size(); i++)
		for (int j = 0; j < pointsY.size(); j++)
			matrix[i][j] = pow(points[j].first, n - i - 1);
	double det2 = det(matrix);
	for (int i = 0; i < pointsY.size(); i++)
		res[i] = det(matrix, i) / det2;
	for (int i = 0; i < pointsY.size(); i++)
	{
		if (res[pointsY.size() - i - 1])
		{
			if (i)
			{
				if (res[pointsY.size() - i - 1] > 0)
				{
					if (resStr.str()[0]) resStr << "+";
					resStr << res[pointsY.size() - i - 1] << "x";
				}
				else if (res[pointsY.size() - i - 1] < 0)
					resStr << res[pointsY.size() - i - 1] << "x";
				if (i != 1)
					resStr << "^" << i;
			}
			else resStr << res[pointsY.size() - i - 1];
		}
	}
	cout << resStr.str() << endl;
}

void CubicSpline()
{
	stringstream resStr;
	vector<vector<double>> matrix(n - 1, vector<double>(4));
	vector<double> h(n - 1);
	vector<double> b(n);
	vector<double> alpha(n);
	vector<double> beta(n);
	vector<double> gamma(n);
	double c = 0.0;

	for (long i = 0; i + 1 <= n - 1; i++)
		h[i] = points[i + 1].first - points[i].first;

	for (long i = 1; i + 1 <= n - 1; i++)
		b[i] = 3.0 * (h[i] * ((points[i].second - points[i - 1].second) / h[i - 1]) + h[i - 1] * ((points[i + 1].
			second - points[i].second) / h[i]));

	b[0] = ((h[0] + 2.0 * (points[2].first - points[0].first)) * h[1] * ((points[1].second - points[0].second) / h[0]
		) +
		pow(h[0], 2.0) * ((points[2].second - points[1].second) / h[1])) / (points[2].first - points[0].first);

	b[n - 1] = (pow(h[n - 2], 2.0) * ((points[n - 2].second - points[n - 3].second) / h[n - 3]) + (2.0 * (points[n - 1
		].first - points[n - 3].first)
		+ h[n - 2]) * h[n - 3] * ((points[n - 1].second - points[n - 2].second) / h[n - 2])) / (points[n - 1].first -
		points[n - 3].first);

	beta[0] = h[1];
	gamma[0] = points[2].first - points[0].first;
	beta[n - 1] = h[n - 2];
	alpha[n - 1] = (points[n - 1].first - points[n - 3].first);

	for (long i = 1; i < n - 1; i++)
	{
		beta[i] = 2.0 * (h[i] + h[i - 1]);
		gamma[i] = h[i];
		alpha[i] = h[i - 1];
	}

	for (long i = 0; i < n - 1; i++)
	{
		c = beta[i];
		b[i] /= c;
		beta[i] /= c;
		gamma[i] /= c;

		c = alpha[i + 1];
		b[i + 1] -= c * b[i];
		alpha[i + 1] -= c * beta[i];
		beta[i + 1] -= c * gamma[i];
	}

	b[n - 1] /= beta[n - 1];
	beta[n - 1] = 1.0;

	for (long i = n - 2; i >= 0; i--)
	{
		c = gamma[i];
		b[i] -= c * b[i + 1];
		gamma[i] -= c * beta[i];
	}

	for (int i = 0; i < n - 1; i++)
	{
		double dzzdx = (points[i + 1].second - points[i].second) / pow(h[i], 2.0) - b[i] / h[i];
		double dzdxdx = b[i + 1] / h[i] - (points[i + 1].second - points[i].second) / pow(h[i], 2.0);
		matrix[i][0] = points[i].second;
		matrix[i][1] = b[i];
		matrix[i][2] = (2.0 * dzzdx - dzdxdx);
		matrix[i][3] = (dzdxdx - dzzdx) / h[i];
	}
	
	cout << "Интерполяция кубическим сплайном\n";
	for (int i = 0; i < n - 1; i++)
	{
		resStr << "S" << i + 1 << "(x) = ";
		for (int j = 0; j < 4; j++)
		{
			if (matrix[i][j])
			{
				if (j)
				{
					if (matrix[i][j] > 0 && resStr.str()[7 + to_string(i + 1).size()])
						resStr << "+";
					resStr << matrix[i][j] << "(x";
					if (points[i].first >= 0)
						resStr << "-" << points[i].first << ")";
					else if (points[i].first < 0)
						resStr << "+" << -points[i].first << ")";
					if (j != 1)
						resStr << "^" << j;
				}
				else resStr << matrix[i][j];
			}
		}
		resStr << " при " << points[i].first << " <= x <= " << points[i + 1].first;
		cout << resStr.str() << endl;
		resStr.str("");
	}
}

void Derivative()
{
	vector<double> f(n);
	vector<double> df(n - 1);
	vector<double> d2f(n - 2);
	
	for (int i = 0; i < n; i++)
		f[i] = points[i].second;
	for (int i = 0; i < n - 1; i++)
		df[i] = (points[i + 1].second - points[i].second) /
		(points[i + 1].first - points[i].first);
	for (int i = 2; i < n - 2; i++)
		d2f[i] = (points[i + 2].second - 2 * points[i].second + points[i - 2].second) / 
		(4 * pow(points[i + 1].first - points[i].first, 2));
	
	cout << "f(x) = ";
	PolynomialInLagrange(f);
	cout << "df(x) = ";
	PolynomialInLagrange(df);
	cout << "d2f(x) = ";
	PolynomialInLagrange(d2f);
}

int main()
{
	setlocale(LC_ALL, "Russian");
	Request();
	CubicSpline();
	Derivative();
	return 0;
}
