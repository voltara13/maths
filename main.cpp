#include <iostream>

using namespace std;

double A[3][3] = {
	    {5, 3, 1},
	    {3, 0, 7},
	    {1, 8, 1}
    },
    B[3] = {12, 10, 18},
    A2[3][3] = {
    	{3, 0, 7},
    	{5, 3, 1},
    	{1, 8, 1}
    },
	B2[3] = {10, 12, 18},
    res[3], resN[3];

void SimpleIterations()
{
	double eps;
	cin >> eps;
	for (int i = 0; i < 3; i++) 
		res[i] = B2[i] / A2[i][i];
	do
	{
		for (int i = 0; i < 3; i++)
		{
			resN[i] = B2[i] / A2[i][i];
			for (int j = 0; j < 3; j++)
				if (i != j) 
					resN[i] -= A2[i][j] / A2[i][i] * res[j];
		}
		bool flag = true;
		for (int i = 0; i < 2; i++)
		{
			if (abs(resN[i]) - res[i] > eps)
			{
				flag = false;
				break;
			}
		}
		for (int i = 0; i < 3; i++)
			res[i] = resN[i];
		if (flag) break;
	}
	while (true);
}


int main()
{
	setlocale(LC_ALL, "Russian");
	SimpleIterations();
	for (int i = 0; i < 3; i++) cout << res[i] << " ";
	return 0;
}