#pragma once
#include <iostream>
using namespace std;

class Matrix {
public:
	Matrix();

	/*
	*释放内存空间
	*/
	~Matrix();

	/*
	@array:一个二维数组
	@rows_in:array的行数
	@cols_in:array的列数
	*/
	Matrix( int rows_in, int cols_in, const float* array = NULL);

	/*
	*复制构造函数
	*/
	Matrix(const Matrix& matrix);

	/*
	*设置矩阵某个位置的元素
	@row:哪一行
	@col:那一列
	*/
	void setElement(int row, int col, float value);

	/*
	*获取矩阵某个位置的元素
	@row:哪一行（从1开始）
	@col:那一列（从1开始）
	@value:元素值
	*/
	float getElement(int row, int col);

	/*
	*返回矩阵的列数
	*/
	int getCols()const;

	/*
	*返回矩阵的行数
	*/
	int getRows()const;

	/*
	*求矩阵的行列式
	*/
	float det();

	/*
	*求一个矩阵某位置的代数余子式
	@row:所在行（从1开始）
	@col:所在列（从1开始）
	*/
	float algebraicComplment(int row, int col);

	/*
	*求矩阵的逆
	*/
	Matrix inverse();

	/*
	*求一个矩阵的转置
	*/
	Matrix trans();

	/*
	*重载=号
	*/
	void operator=(Matrix matrix_in);

	/*
	*重载*号
	*/
	Matrix operator*( const Matrix& matrix_in);

	/*
	*重载+号
	*/
	Matrix operator+(const Matrix& matrix_in);

	/*
	*重载-号
	*/
	Matrix operator-(const Matrix& matrix_in);

	/*
	*重置，释放矩阵空间
	*/
	void reset();
	/*
	@打印出矩阵
	*/
	void printMatrix();

	/*
	*当矩阵只有一个元素的时候以float形式返回这个元素
	*/
	float matrixToFloat();

	/*
	*重载*号为其友元函数
	*/
	friend Matrix operator*(const float factor, const Matrix& matrix_in);

	/*
	*重载-号
	*/
	friend Matrix operator-(const Matrix& matrix_in1, const Matrix& matrix_in2);
private:
	float** elements;
	int cols;
	int rows;

	float detSub(Matrix &matrix);
};

/*
*计算欧式距离，开方后结果
*vec1,vec2:是维度相同的向量，即cols = 1, rows1 = rows2的矩阵
*return: vec1和vec2之间的
*/
float eDist(const Matrix vec1, const Matrix vec2);