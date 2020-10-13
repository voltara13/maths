#include <iostream>

using namespace std;

double A[3][3] = {
	       {5, 3, 1},
	       {3, 0, 7},
	       {1, 8, 1}
       },
       B[3] = {12, 10, 18},
       A2[3][3] = {
	       {7, 3, 0},
	       {1, 5, 3},
	       {1, 1, 8}
       },
       B2[3] = {10, 12, 18},
       resG[3], resI[3];

void GaussMethod()
{
	double max = 0, factor = 0;
	int iM = 0, jM = 0;
	//Находим главный элемент по всей матрице
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (abs(A[i][j]) > max)
				max = A[i][j], iM = i, jM = j;
	//Делаем перестановку строк и столбцов относительно главного элемента
	for (int j = 0; j < 3; j++)
		swap(A[0][j], A[iM][j]);
	for (int i = 0; i < 3; i++)
		swap(A[i][0], A[i][jM]);
	swap(B[0], B[iM]);
	//Начинаем приводить каждую строку
	for (int i = 0; i < 3; i++)
	{
		factor = A[i][i];
		for (int j = 0; j < 3; j++)
			A[i][j] /= factor;
		B[i] /= factor;
		for (int k = i + 1; k < 3; k++)
			if (A[k][i])
			{
				factor = A[k][i] / A[i][i];
				for (int j = 0; j < 3; j++)
					A[k][j] -= factor * A[i][j];
				B[k] -= B[i] * factor;
			}
	}
	//Обратная подстановка
	for (int i = 2; i >= 0; i--)
	{
		resG[i] = B[i] / A[i][i];
		for (int j = 0; j < i; j++)
			B[j] -= A[j][i] * resG[i];
	}
	cout << "Метод Гаусса итераций был выполнен\nКорни: ";
	for (int i = 0; i < 3; i++) cout << resG[i] << " ";
}

void SimpleIterations()
{
	double xE[3], eps = 0;
	int k = 0;
	cout << "\nВведите точность: ";
	cin >> eps;
	for (int i = 0; i < 3; i++)
		resI[i] = B2[i] / A2[i][i];
	while (true)
	{
		for (int i = 0; i < 3; i++)
		{
			xE[i] = B2[i] / A2[i][i];
			for (int j = 0; j < 3; j++)
				if (i != j)
					xE[i] -= A2[i][j] / A2[i][i] * resI[j];
		}
		bool flag = true;
		for (int i = 0; i < 2; i++)
			if (fabs(xE[i] - resI[i]) > eps)
			{
				flag = false;
				break;
			}
		for (int i = 0; i < 3; i++)
			resI[i] = xE[i];
		k++;
		if (flag)
			break;
	}
	cout << "Метод простых итераций был выполнен за "
		<< k << " итераций\nКорни: ";
	for (int i = 0; i < 3; i++) cout << resI[i] << " ";
}

int main()
{
	setlocale(LC_ALL, "Russian");
	GaussMethod();
	SimpleIterations();
	return 0;
}
