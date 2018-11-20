#include "PE.h"
#include <string.h>
#include <float.h>
#include <cmath>
PE::PE()
{
	this->means = NULL;
	this->sigma = NULL;
	this->classSize = -1;
	this->sampleSize = -1;
	this->vecLen = -1;
	this->priorPro = NULL;
}

PE::~PE()
{
	if (this->means != NULL)
		delete[]means;
	if (this->sigma != NULL)
		delete[]sigma;
	if (this->priorPro != NULL)
		delete[]priorPro;
}

/*
*设置样本文件，该样本应该具有固定格式，详细会在实验报告中说明
*/
void PE::setSampleFile(string fileName_in)
{
	this->storage.setfile(fileName_in);
}

/*
*设置有多少个类别
*/
void PE::setClassSize(int classSize_in)
{
	this->classSize = classSize_in;
}

/*
*设置样本数据中向量的长度
*/
void PE::setVectorLen(int vecLen_in)
{
	//设置数据存储层次向量维度，在读取数据时会使用到
	this->storage.setVectorLen(vecLen_in);
	this->vecLen = vecLen_in;
}

/*
*设置样本大小
*/
void PE::setSampleSize(int sampleSize_in)
{
	this->sampleSize = sampleSize_in;
}

/*
*call the calculate function
*/
void PE::estimate()
{
		this->calculateMeans();
		this->calculateSigma();
}

/*
*call the calculate function
*it will be used in chapter3 problem 1_d
*/
void PE::estimate_d()
{
	this->calculateMeans();
	this->calculateSigma();
	for(int counter0 = 0; counter0 < this->classSize; counter0++)
	{
		for(int counter1 = 0; counter1 < this->sigma[counter0].getRows();counter1++)
		{
			for(int counter2 = 0; counter2 < this->sigma[counter0].getCols();counter2++)
			{
				if(counter1 != counter2)
					this->sigma[counter0].setElement(counter1 + 1, counter2 + 1, 0 );
			}
		}
	}
}

/*
*输出某一类的均值（从1开始记）
*/
Matrix&  PE::getMean(int whichClass)
{
	if (whichClass < 1 || whichClass > this->classSize)
	{
		cout << "Error from Matrix&  PE::getMean(int whichClass)\n";
		system("pause");
	}
	return this->means[whichClass - 1];
}

/*
*输出某一类的协方差矩阵(从1开始记）
*/
Matrix&  PE::getSigma(int whichClass)
{
	if (whichClass < 1 || whichClass > this->classSize)
	{
		cout << "Error from Matrix&  PE::getMean(int whichClass)\n";
		system("pause");
	}
	return this->sigma[whichClass - 1];
}

/*
*根据样本数据计算各个类别的均值向量，并存储到私有变量中
*/
void PE::calculateMeans()
{
	if(this->means != NULL)
	{
		delete []means;
		means =NULL;
	}
	//为means申请存放空间
	this->means = new Matrix[this->classSize];

	//将文件指针指向开头
	storage.reset();
	//要读完整个文件
	for (int counter0 = 0; counter0 < this->classSize ; counter0++)
	{
		Matrix vec(this->vecLen,1);
		//计算该类样本之和
		for (int counter1 = 0; counter1 < this->sampleSize; counter1++)
		{
			vec = (vec + this->storage.readData());
		}
		//计算均值并保存下来
		this->means[counter0] = 1/(float)this->sampleSize * vec;
	}
}

/*
*根据样本数据计算各个类别的协方差矩阵，并存储到私有变量中去。
*/
void PE::calculateSigma()
{

	if(this->sigma != NULL)
	{
		delete []sigma;
		sigma =NULL;
	}
	//为sigma申请存放空间
	this->sigma = new Matrix[this->classSize];
	//将文件指针指向开头
	this->storage.reset();
	//要读完整个文件
	for (int counter0 = 0; counter0 < this->classSize; counter0++)
	{
		Matrix newMatrix(this->vecLen, this->vecLen);

		//计算该类样本之和
		for (int counter1 = 0; counter1 < this->sampleSize; counter1++)
		{
			Matrix vec(this->vecLen, 1);
			vec = this->storage.readData() - this->means[counter0];

			//求和
			newMatrix = (newMatrix + vec*vec.trans());
		}
		//计算均值并将协方差矩阵保存到私有变量中
		this->sigma[counter0] = 1 / (float)(this->sampleSize) * newMatrix;
	}
}
