#include "matrix.h"

Matrix::Matrix()
{
	this->elements = NULL;
	this->cols = 0;
	this->rows = 0;
}

Matrix::~Matrix()
{
	reset();
}

Matrix::Matrix(int rows_in, int cols_in, const float* array)
{
	this->cols = cols_in;
	this->rows = rows_in;
	//更具传进来的数组大小申请矩阵存储空间
	this->elements = new float*[rows_in];
	for (int counter = 0; counter < rows_in; counter++)
	{
		elements[counter] = new float[cols_in];
	}

	//将传进来的矩阵保存下来
	if (array == NULL)
	{
		for (int counter0 = 0; counter0 < rows_in; counter0++)
		{
			for (int counter1 = 0; counter1 < cols_in; counter1++)
			{
				elements[counter0][counter1] = 0;
			}
		}
	}
	else
	{
		int coun = 0;
		for (int counter0 = 0; counter0 < rows_in; counter0++)
		{
			for (int counter1 = 0; counter1 < cols_in; counter1++)
			{
				elements[counter0][counter1] = array[coun++];
			}
		}
	}
}

/*
*根据传进来的matirx新建一个Matrix
*/
Matrix::Matrix(const Matrix& matrix)
{
	this->cols = matrix.cols;
	this->rows = matrix.rows;
	//更具传进来的数组大小申请矩阵存储空间
	this->elements = new float*[this->rows];
	for (int counter = 0; counter < this->rows; counter++)
	{
		elements[counter] = new float[this->cols];
	}

	//将传进来的矩阵保存下来
	for (int counter0 = 0; counter0 < this->rows; counter0++)
	{
		for (int counter1 = 0; counter1 < this->cols; counter1++)
		{
			elements[counter0][counter1] = matrix.elements[counter0][counter1];
		}
	}
}

/*
*设置矩阵某个位置的元素
@row:哪一行(从1开始）
@col:那一列（从1开始）
@value:元素值
*/
void  Matrix::setElement(int row, int col, float value)
{
	if (row > this->rows || col > this->cols || row < 1 || col < 1) {
		cout << "Position error from void  Matrix::setElement(int row, int col, float value)\n";
		system("pause");
	}
		
	this->elements[row-1][col-1] = value;
}

/*
	*获取矩阵某个位置的元素
	@row:哪一行（从1开始）
	@col:那一列（从1开始）
	@value:元素值
	*/
float  Matrix::getElement(int row, int col)
{
	if (row > this->rows || col > this->cols || row < 1 || col < 1) {
		cout << "Position error from float  Matrix::getElement(int row, int col)\n";
		system("pause");
	}
	return this->elements[row - 1][col - 1];
}

/*
*返回矩阵的列数
*/
int Matrix::getCols()const
{
	return this->cols;
}

/*
*返回矩阵的行数
*/
int Matrix::getRows()const
{
	return this->rows;
}

float Matrix::det()
{
	if (this->rows != this->cols)
	{
		cout<< "Matrix must be square!\n";
		system("pause");
	}
	return detSub(*this);
}

/*
*求一个矩阵某位置的代数余子式
@row:所在行（从1开始）
@col:所在列（从1开始）
*/
float  Matrix::algebraicComplment(int row, int col)
{
	if (row > this->rows || col > this->cols || row < 1 || col < 1) {
		cout << "Position error from float  Matrix::algebraicComplment(int row, int col)\n";
		system("pause");
	}
	float *newarray = new float[pow(this->cols - 1, 2)];
	int count = 0;
	//cout << this->rows << "  " << this->cols << " rows cols"<<row<<" "<<col << endl;
	for (int counter2 = 0;counter2 < this->rows; counter2++)
	{
		if (counter2 == row - 1)
			continue;
		for (int counter3 = 0; counter3 < this->cols; counter3++)
		{
			//cout << "66666";
			if (counter3 != col - 1)
			{
				newarray[count] = this->elements[counter2][counter3];
				count++;
			}
		}
	}
	Matrix newMatrix(this->rows - 1, this->cols - 1, newarray);
	//cout << row << " " << col << endl;
	//newMatrix.printMatrix();
	return pow(-1, row + col)*(newMatrix.det());

}

/*
*求矩阵的逆
*/
Matrix Matrix::inverse()
{
	float d = det();
	if (d == 0)
	{
		cout << "Divid with zero error from Matrix Matrix::inverse()\n";
		system("pause");
	}
	Matrix newMatrix(this->rows, this->cols);

	for (int counter1 = 0; counter1 < this->rows; counter1++)
	{
		for (int counter2 = 0; counter2 < this->cols; counter2++)
		{
			newMatrix.elements[counter2][counter1] = 1/d * this->algebraicComplment(counter1 + 1, counter2 + 1);
		}
	}

	return newMatrix;
}

/*
*求一个矩阵的转置
*/
Matrix Matrix::trans()
{
	Matrix newMatrix(this->cols, this->rows);
	for (int counter1 = 0; counter1 < this->rows; counter1++)
	{
		for (int counter2 = 0; counter2 < this->cols; counter2++)
		{
			newMatrix.elements[counter2][counter1] = this->elements[counter1][counter2];
		}
	}

	return newMatrix;
}

/*
*重载=号
*/
void Matrix::operator=(const Matrix matrix)
{
	if (this->elements != NULL)
		this->reset();
	this->cols = matrix.cols;
	this->rows = matrix.rows;
	//更具传进来的数组大小申请矩阵存储空间
	this->elements = new float*[this->rows];
	for (int counter = 0; counter < this->rows; counter++)
	{
		elements[counter] = new float[this->cols];
	}

	//将传进来的矩阵保存下来
	for (int counter0 = 0; counter0 < this->rows; counter0++)
	{
		for (int counter1 = 0; counter1 < this->cols; counter1++)
		{
			elements[counter0][counter1] = matrix.elements[counter0][counter1];
		}
	}
}

/*
*重载*号
*/
Matrix Matrix::operator*(const  Matrix& matrix_in)
{
	if (this->cols != matrix_in.rows)
	{
		cout<< "Dimension error from Matrix Matrix::operator*( Matrix& matrix_in)\n";
		system("pause");
	}
	Matrix newMatrix(this->rows, matrix_in.cols);
	for (int counter0 = 0; counter0 < newMatrix.rows; counter0++)
	{
		for (int counter1 = 0; counter1 < newMatrix.cols; counter1++)
		{
			float value = 0;
			for (int counter2 = 0; counter2 < this->cols; counter2++)
			{
				value += this->elements[counter0][counter2]*matrix_in.elements[counter2][counter1];
			}
			newMatrix.elements[counter0][counter1] = value;
		}
	}

	return newMatrix;
}

/*
*重载+号
*/
Matrix  Matrix::operator+(const Matrix& matrix_in)
{
	if (this->rows != matrix_in.rows || this->cols != matrix_in.cols)
	{
		cout << "Dimension error from Matrix  Matrix::operator+(const Matrix& matrix_in)\n";
		system("pause");
	}
	Matrix newMatrix(this->rows,this->cols);
	for (int counter0 = 0; counter0 < newMatrix.rows; counter0++)
	{
		for (int counter1 = 0; counter1 < newMatrix.cols; counter1++)
		{
			newMatrix.elements[counter0][counter1] =this->elements[counter0][counter1] + matrix_in.elements[counter0][counter1];
		}
	}
	return newMatrix;
}

/*
*重载-号
*/
Matrix Matrix::operator-(const Matrix& matrix_in)
{
	if (this->rows != matrix_in.rows || this->cols != matrix_in.cols)
	{
		cout << "Dimension error from Matrix  Matrix::operator+(const Matrix& matrix_in)\n";
		system("pause");
	}
	Matrix newMatrix(this->rows, this->cols);
	for (int counter0 = 0; counter0 < newMatrix.rows; counter0++)
	{
		for (int counter1 = 0; counter1 < newMatrix.cols; counter1++)
		{
			newMatrix.elements[counter0][counter1] = this->elements[counter0][counter1] - matrix_in.elements[counter0][counter1];
		}
	}
	return newMatrix;
}

/*
*重置，释放矩阵空间
*/
void  Matrix::reset()
{
	for (int counter = 0; counter < this->rows; counter++)
	{
		delete[]this->elements[counter];
	}
	delete[]this->elements;

	this->elements = NULL;
	this->rows = 0;
	this->cols = 0;
}

void Matrix::printMatrix()
{
	cout << endl;
	for (int counter0 = 0; counter0 < rows; counter0++)
	{
		for (int counter1 = 0; counter1 < cols; counter1++)
		{
			cout << elements[counter0][counter1]<< "  ";
		}
		cout << endl;
	}
	cout << endl;
}

/*
	*当矩阵只有一个元素的时候返回这个元素
	*/
float  Matrix::matrixToFloat()
{
	if (this->cols == 1 && this->rows == 1)
		return this->elements[0][0];
	else
	{
		cout << "Error from float  Matrix::matrixToFloat();\n";
		system("pause");
	}
}

float  Matrix::detSub(Matrix &matrix)
{
	if (matrix.cols == 2)
	{
		return matrix.elements[0][0] * matrix.elements[1][1] - matrix.elements[0][1] * matrix.elements[1][0];
	}
	float value = 0;
	for (int counter1 = 0; counter1 < matrix.cols; counter1++)
	{
		float *newarray = new float[pow(matrix.cols - 1 , 2)];
		int count = 0;
		for (int counter2 = 1; counter2 < matrix.rows; counter2++)
		{
			for (int counter3 = 0; counter3 < matrix.cols; counter3++)
			{
				if (counter3 != counter1)
				{
					newarray[count] = matrix.elements[counter2][counter3];
					count++;
				}
					
			}
		}
		Matrix newMatrix(matrix.cols-1,matrix.cols-1, newarray );
		value = value + pow(-1,counter1)* matrix.elements[0][counter1]*detSub(newMatrix);
		delete[]newarray;
	}
	return value;
}

/*
*重载*号
*/
 Matrix operator*(const float factor, const  Matrix& matrix_in)
{
	Matrix newMatrix(matrix_in.rows, matrix_in.cols);
	for (int counter0 = 0; counter0 < newMatrix.rows; counter0++)
	{
		for (int counter1 = 0; counter1 < newMatrix.cols; counter1++)
		{
			newMatrix.elements[counter0][counter1] = factor*matrix_in.elements[counter0][counter1];
		}
	}
	return newMatrix;
}