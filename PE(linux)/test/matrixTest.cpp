#include "matrix.h"
using namespace std;
int main()
{
	Matrix matrix2(2, 6);
	matrix2.setElement(1, 2, 6);
	matrix2.setElement(2, 3, 6);
	matrix2.setElement(1, 1, 6);
	matrix2.setElement(2, 6, 6);
	matrix2.printMatrix();

	(matrix2 + matrix2).printMatrix();
	(3.99 * matrix2).printMatrix();
	//测试时一定要测试小数
	float array[] = { 1.02, 2.03, 3.04,  4.05,  5.06, 6.07, 7.08, 8.09,  9.10, 5.06, 6.07, 8.09,  3.04, 6.07, 9.10, 8.09 };
	Matrix matrix(4, 4, array);
	//matrix.printMatrix();

	Matrix matrix1;
	matrix1 = matrix;
	//cout << matrix1.det() << endl;

	//matrix1.printMatrix();

	/*Matrix matrix2(2, 6);
	matrix2 = (matrix * matrix1);

	matrix2.printMatrix();*/

	//float vec[3] = { 1.03, 2.02, 3.55 };
	//Matrix matrix3( 3,1, vec);
	//float arr[] = {1.52, 2.65, 3.79,  4.95, 5.55, 6.88};
	//Matrix matrix4(2, 3, arr);

	//(matrix4*matrix3).printMatrix();

	//matrix.printMatrix();
	//(matrix.inverse()).printMatrix();

	/*float vect[2] = { 2,2.34 };
	Matrix matrix5(2, 1, vect);
	(matrix5*(matrix5.trans())).printMatrix();*/
	system("pause");
	return 0;
}