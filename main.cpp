#include <iostream>

using namespace std;

int A[3][3] = {
	    {5, 3, 1},
	    {3, 0, 7},
	    {1, 8, 1}
    },
    B[3] = {12, 10, 18};



int main()
{
	setlocale(LC_ALL, "Russian");
	for (int i = 0; i < 3; i++)
	{
		cout << endl;
		for (int j = 0; j < 3; j++)
			cout << A[i][j];
	}

	return 0;
}
