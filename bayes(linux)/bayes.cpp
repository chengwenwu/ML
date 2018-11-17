#include "bayes.h"
#include <string.h>
#include <float.h>
#include <cmath>
Bayes::Bayes()
{
	this->means = NULL;
	this->sigma = NULL;
	this->classSize = -1;
	this->sampleSize = -1;
	this->vecLen = -1;
	this->priorPro = NULL;
}

Bayes::~Bayes()
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
void Bayes::setSampleFile(string fileName_in)
{
	this->storage.setfile(fileName_in);
}

/*
*设置有多少个类别
*/
void Bayes::setClassSize(int classSize_in)
{
	this->classSize = classSize_in;
}

/*
*设置样本数据中向量的长度
*/
void Bayes::setVectorLen(int vecLen_in)
{
	//设置数据存储层次向量维度，在读取数据时会使用到
	this->storage.setVectorLen(vecLen_in);
	this->vecLen = vecLen_in;
}

/*
*设置样本大小
*/
void Bayes::setSampleSize(int sampleSize_in)
{
	this->sampleSize = sampleSize_in;
}


/*
@vec_str:用户输入将要判别的向量,各个元素之间用逗号隔开
*输出判别结果
*/
int Bayes::judge(string vec_str_in)
{
	//判断之前要做好准备工作，计算好相关参数
	//下面三个if语句不可交换次序
	if (this->means == NULL)
		this->calculateMeans();
	if (this->sigma == NULL)
		this->calculateSigma();

	float g = - FLT_MAX, temp = 0;//将g赋值为最小浮点数
	int victory = -1;
	for (int counter = 1; counter <= this->classSize; counter++)
	{

		//cout<<mahal(vec_str_in, counter)<<endl;
		//sigma[counter - 1].printMatrix();
		temp = (-0.5)*mahal(vec_str_in, counter) - 0.5*log(this->sigma[counter - 1].det()) + log(this->priorPro[counter - 1]);
		//cout << temp << endl;
		if (temp > g)
		{
			g = temp;
			victory = counter;
			//cout << temp;
		}
	}
	return victory;
}

/*
	*输出某一类的均值（从1开始记）
	*/
Matrix&  Bayes::getMean(int whichClass)
{
	if (whichClass < 1 || whichClass > this->classSize)
	{
		cout << "Error from Matrix&  Bayes::getMean(int whichClass)\n";
		system("pause");
	}
	return this->means[whichClass - 1];
}

/*
*输出某一类的协方差矩阵(从1开始记）
*/
Matrix&  Bayes::getSigma(int whichClass)
{
	if (whichClass < 1 || whichClass > this->classSize)
	{
		cout << "Error from Matrix&  Bayes::getMean(int whichClass)\n";
		system("pause");
	}
	return this->sigma[whichClass - 1];
}

/*
*计算马氏距离
@vec_str_in:字符串形式的向量，应该具有如下形式
[1,2,3,4,5],即开头必须是‘[’结尾必须是‘]’,中间数字用‘,’隔开
@whichclass:输入的向量和哪个类之间的马氏距离(从1开始）
*/
float Bayes::mahal(string vec_str_in, int whichclass)
{
	if (whichclass < 1 || whichclass > this->classSize)
	{
		cout << "Error: Class does not exist. from float Bayes::mahal(string vec_str_in, int whichclass)\n";
		system("pause");
	}
	// 下面三个if语句不可交换次序
	if (this->means == NULL)
		this->calculateMeans();
	if (this->sigma == NULL)
		this->calculateSigma();
	Matrix newVec = userInputProcess(vec_str_in);
	Matrix tempVec = newVec - this->means[whichclass - 1];
	return (tempVec.trans()*(sigma[whichclass - 1].inverse()) * tempVec).matrixToFloat();
}

/*
*根据样本数据计算各个类别的均值向量，并存储到私有变量中
*/
void Bayes::calculateMeans()
{
	//为means申请存放空间
	this->means = new Matrix[this->classSize];

	//将文件指针指向开头
	storage.reset();
	this->setPostPro();
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
void Bayes::calculateSigma()
{
	//为sigma申请存放空间
	this->sigma = new Matrix[this->classSize];
	//将文件指针指向开头
	this->storage.reset();
	this->setPostPro();
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
		this->sigma[counter0] = 1 / (float)(this->sampleSize-1) * newMatrix;
	}
}

/*
*用户输入处理
*将用户输入形如[1,2,3,4,5]的向量转化为一个Matrix对象输出
*/
Matrix Bayes::userInputProcess(string vec_str_in)
{
	if (!(vec_str_in[0] == '[' && vec_str_in[vec_str_in.length() - 1] == ']' && vec_str_in.length() > 2))
	{
		cout << "Input format error from Matrix Bayes::userInputProcess(string vec_str_in)\n";
		system("pause");
	}
	//去掉开头和结尾的方括号，方便后续字符串分割
	string sub = vec_str_in.substr(1, vec_str_in.length() - 2);
	//字符串分割函数参数必须是char*类型
	char  *subchar = new char[sub.length() + 1];
	strcpy(subchar, sub.c_str());
	const char seg[] = ",";//用逗号进行分割
	//分割出第一个元素
	char *xc[8];
	xc[0] = strtok(subchar, seg);
	if (xc[0] == NULL)
	{
		cout << "Input format error from Matrix Bayes::userInputProcess(string vec_str_in)\n";
		system("pause");
	}
	Matrix vec(this->vecLen, 1);
	vec.setElement(1, 1, atof(xc[0]));
	for (int counter = 2; counter <= this->vecLen ; counter++)
	{
		xc[counter-1] = strtok(NULL, seg);
		if (xc[counter-1] == NULL)
		{
			cout << "Input format error from Matrix Bayes::userInputProcess(string vec_str_in)\n";
			system("pause");
		}
		vec.setElement(counter, 1, atof(xc[counter-1]));
	}
	delete[] subchar;
	return vec;
}

/*
*从文件中读取后验概率,放到内存中
*/
void  Bayes::setPostPro()
{
	if (this->priorPro != NULL)
	{
		delete[]priorPro;
		priorPro = NULL;
	}

	this->priorPro = new float[this->classSize];
	for (int counter = 0; counter < this->classSize; counter++)
	{
		this->priorPro[counter] = this->storage.readPostPro();
		//cout << this->postPro[counter] << "hhh\n";
	}
}
