#pragma once
/*
*这个类主要负责样本文件的读取，由
*由于时间比较紧张，所以这个类的功能写的很简单，只能够顺序读取文件中的数据
*然后将数据以向量的形式返回给上层函数
*/
#include <fstream>
#include "matrix.h"
class Storage {
public:
	Storage();
	~Storage();
	/*
	*打开文件
	*/
	void setfile(string fileName);

	/*
	*设置样本数据中向量的长度
	*/
	void setVectorLen(int vectorLen_in);

	/*
	*从文件中读取后验概率
	*/
	float readPostPro();

	/*
	*只支持顺序读取
	*/
	Matrix& readData();

	/*
	*让文件指针回到文件开始的地方
	*/
	void reset();
private:
	Matrix matrix;
	ifstream infile;
	int vectorLen;
};