#include "NPE.h"
#include <cstring>
#include <algorithm>
#include <math.h>
#include <float.h>
#define PI 3.141592654
NPE::NPE()
{
	this->classSize = -1;
	this->sampleSize = -1;
	this->vecLen = -1;
}

NPE::~NPE()
{
}

/*
*设置样本文件，该样本应该具有固定格式，详细会在实验报告中说明
*/
void NPE::setSampleFile(string fileName_in)
{
	this->storage.setfile(fileName_in);
}

/*
*设置有多少个类别
*/
void NPE::setClassSize(int classSize_in)
{
	this->classSize = classSize_in;
}

/*
*设置样本数据中向量的长度
*/
void NPE::setVectorLen(int vecLen_in)
{
	//设置数据存储层次向量维度，在读取数据时会使用到
	this->storage.setVectorLen(vecLen_in);
	this->vecLen = vecLen_in;
}

/*
*设置样本大小
*/
void NPE::setSampleSize(int sampleSize_in)
{
	this->sampleSize = sampleSize_in;
}


/*
@vec_str:用户输入将要判别的向量,各个元素之间用逗号隔开
*输出判别结果
*/
int NPE::judgePar(string vec_str_in, float h)
{
	this->storage.reset();
	Matrix vec1 = this->userInputProcess(vec_str_in);
	float g = - FLT_MAX, temp = 0;//将g赋值为最小浮点数
	int victory = -1;
	for (int counter1 = 1; counter1 <= this->classSize; counter1++)
	{
		temp = 0;
		for (int counter2 = 0; counter2 < this->sampleSize; counter2++)
		{
			Matrix vec2 = vec1 - this->storage.readData();
			temp += exp(-(vec2.trans()*vec2).matrixToFloat()/(2*pow(h,2)));
		}
		if (temp > g)
		{
			g = temp;
			victory = counter1;
		}
	}
	return victory;
}

/*
@vec_str:用户输入的x,各个元素之间用逗号隔开
*输出KNN概率,最后不要忘了释放指针空间
*/
float* NPE::knnProbability(string vec_str_in, int k)
{
	if (k > this->sampleSize || k < 0)
	{
		cout << "K is error from float NPE::knnProbability(string vec_str_in, int k)\n";
		system("pause");
	}
	Matrix newVec = this->userInputProcess(vec_str_in);
	float* knn = new float[this->classSize];
	float* dis = new float[this->sampleSize];
	this->storage.reset();//文件指针回到文件开始位置
	for (int counter0 = 0; counter0 < this->classSize; counter0++)
	{
		for (int counter1 = 0; counter1 < this->sampleSize; counter1++)
		{
			dis[counter1] = eDist(newVec, this->storage.readData());
		}
		sort(dis, dis + this->sampleSize);//从小到大排序
		float V = 0;
		//第k-1个就是KNN中离他最远的那个，然后在以那个为中心，做圆或球
		switch (this->vecLen)
		{
		case 1:
			V = 2 * dis[k - 1];
			break;
		case 2:
			V = PI * pow(dis[k - 1], 2);
			break;
		case 3:
			V = 4 * PI*pow(dis[k - 1], 3) / 3;
			break;
		default:
			cout << "Vector Length Error from float NPE::knnProbability(string vec_str_in, int k)\n";
			system("pause");
		}
		cout << V << endl;
		knn[counter0] = k / this->sampleSize / V;
	}
	delete []dis;
	return knn;
}
/*
*用户输入处理
*将用户输入形如[1,2,3,4,5]的向量转化为一个Matrix对象输出
*/
Matrix NPE::userInputProcess(string vec_str_in)
{
	if (!(vec_str_in[0] == '[' && vec_str_in[vec_str_in.length() - 1] == ']' && vec_str_in.length() > 2))
	{
		cout << "Input format error from Matrix NPE::userInputProcess(string vec_str_in)\n";
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
		cout << "Input format error from Matrix NPE::userInputProcess(string vec_str_in)\n";
		system("pause");
	}
	Matrix vec(this->vecLen, 1);
	vec.setElement(1, 1, atof(xc[0]));
	for (int counter = 2; counter <= this->vecLen ; counter++)
	{
		xc[counter-1] = strtok(NULL, seg);
		if (xc[counter-1] == NULL)
		{
			cout << "Input format error from Matrix NPE::userInputProcess(string vec_str_in)\n";
			system("pause");
		}
		vec.setElement(counter, 1, atof(xc[counter-1]));
	}
	delete[] subchar;
	return vec;
}
