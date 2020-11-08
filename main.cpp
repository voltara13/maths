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

//void GaussMethod()
//{
//	double max = 0, factor = 0;
//	int iM = 0, jM = 0;
//	//Находим главный элемент по всей матрице
//	for (int i = 0; i < 3; i++)
//		for (int j = 0; j < 3; j++)
//			if (abs(A[i][j]) > max)
//				max = A[i][j], iM = i, jM = j;
//	//Делаем перестановку строк и столбцов относительно главного элемента
//	for (int j = 0; j < 3; j++)
//		swap(A[0][j], A[iM][j]);
//	for (int i = 0; i < 3; i++)
//		swap(A[i][0], A[i][jM]);
//	swap(B[0], B[iM]);
//	//Начинаем приводить каждую строку
//	for (int i = 0; i < 3; i++)
//	{
//		factor = A[i][i];
//		for (int j = 0; j < 3; j++)
//			A[i][j] /= factor;
//		B[i] /= factor;
//		for (int k = i + 1; k < 3; k++)
//			if (A[k][i])
//			{
//				factor = A[k][i] / A[i][i];
//				for (int j = 0; j < 3; j++)
//					A[k][j] -= factor * A[i][j];
//				B[k] -= B[i] * factor;
//			}
//	}
//	//Обратная подстановка
//	for (int i = 2; i >= 0; i--)
//	{
//		resG[i] = B[i] / A[i][i];
//		for (int j = 0; j < i; j++)
//			B[j] -= A[j][i] * resG[i];
//	}
//	cout << "Метод Гаусса итераций был выполнен\nКорни: ";
//	for (int i = 0; i < 3; i++) cout << resG[i] << " ";
//}

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
	stringstream resStr;
	vector<vector<double>> matrix(n - 1, vector<double>(4));
	vector<double> dx(n - 1);
	vector<double> b(n);
	vector<double> alpha(n);
	vector<double> beta(n);
	vector<double> gamma(n);

	for (long i = 0; i + 1 <= n - 1; i++)
		dx[i] = points[i + 1].first - points[i].first;

	for (long i = 1; i + 1 <= n - 1; i++)
		b[i] = 3.0 * (dx[i] * ((points[i].second - points[i - 1].second) / dx[i - 1]) + dx[i - 1] * ((points[i + 1].second - points[i].second) / dx[i]));

	b[0] = ((dx[0] + 2.0 * (points[2].first - points[0].first)) * dx[1] * ((points[1].second - points[0].second) / dx[0]) +
		pow(dx[0], 2.0) * ((points[2].second - points[1].second) / dx[1])) / (points[2].first - points[0].first);

	b[n - 1] = (pow(dx[n - 2], 2.0) * ((points[n - 2].second - points[n - 3].second) / dx[n - 3]) + (2.0 * (points[n - 1].first - points[n - 3].first)
		+ dx[n - 2]) * dx[n - 3] * ((points[n - 1].second - points[n - 2].second) / dx[n - 2])) / (points[n - 1].first - points[n - 3].first);

	beta[0] = dx[1];
	gamma[0] = points[2].first - points[0].first;
	beta[n - 1] = dx[n - 2];
	alpha[n - 1] = (points[n - 1].first - points[n - 3].first);
	for (long i = 1; i < n - 1; i++)
	{
		beta[i] = 2.0 * (dx[i] + dx[i - 1]);
		gamma[i] = dx[i];
		alpha[i] = dx[i - 1];
	}
	double c = 0.0;
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
		double dzzdx = (points[i + 1].second - points[i].second) / pow(dx[i], 2.0) - b[i] / dx[i];
		double dzdxdx = b[i + 1] / dx[i] - (points[i + 1].second - points[i].second) / pow(dx[i], 2.0);
		matrix[i][0] = points[i].second;
		matrix[i][1] = b[i];
		matrix[i][2] = (2.0 * dzzdx - dzdxdx);
		matrix[i][3] = (dzdxdx - dzzdx) / dx[i];
	}
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
					if (points[i].first > 0) 
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

int main()
{
	setlocale(LC_ALL, "Russian");
	Request();
	CubicSpline();
	return 0;
}
