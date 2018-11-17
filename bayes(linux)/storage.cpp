#include "storage.h"
Storage::Storage()
{
	this->vectorLen = -1;
}

Storage::~Storage()
{
	if (this->infile)
		this->infile.close();
}
/*
*打开文件
*/
void Storage::setfile(string fileName)
{
	this->infile.open(fileName);
	if (!this->infile)
	{
		cout << "File open error!\n";
		system("pause");
	}
}

/*
*设置样本数据中向量的长度
*/
void  Storage::setVectorLen(int vectorLen_in)
{
	this->vectorLen = vectorLen_in;
	this->matrix = Matrix(this->vectorLen, 1);
}

/*
*从文件中读取后验概率
*/
float Storage::readPostPro()
{
	float a;
	this->infile >> a;
	return a;
}

/*
*只支持顺序读取
*/
Matrix& Storage::readData()
{
	float data;
	for(int counter = 1; counter <= this->vectorLen && this->infile >> data; counter++)
	{
		//cout << data;
		this->matrix.setElement(counter, 1, data);
	}
	return this->matrix;
}

/*
*让文件指针回到文件开始的地方
*/
void Storage::reset()
{
	this->infile.seekg(0, ios::beg);
}