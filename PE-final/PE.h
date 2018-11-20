#include "storage.h"
class PE
{
public:
	PE();
	~PE();

	/*
	*设置样本文件，该样本呢应该具有固定格式，详细会在实验报告中说明
	*/
	void setSampleFile(string fileName_in);

	/*
	*设置有多少个类别
	*/
	void setClassSize(int classSize_in);

	/*
	*设置样本数据中向量的长度
	*向量一般是指列向量
	*/
	void setVectorLen(int vecLen_in);

	/*
	*设置样本大小
	*/
	void setSampleSize(int sampleSize_in);


	/*
	*call the calculate function
	*/
	void estimate();

	/*
	*call the calculate function
	*it will be used in chapter4 problem 1_d
	*/
	void estimate_d();

	/*
	*输出某一类的均值（从1开始记）
	*/
	Matrix& getMean(int whichClass);

	/*
	*输出某一类的协方差矩阵(从1开始记）
	*/
	Matrix& getSigma(int whichClass);

private:
	Storage storage;//负责样本文件的读取
	Matrix* means;//存储均值向量的数组，下标即类别代号
	Matrix* sigma;//存储协方差矩阵的数组，下标即类别代号
	float * priorPro;
	int classSize;//表示有多少个类别
	int vecLen;//样本中向量的长度
	int sampleSize;//每个类别中样本容量应该相同

	/*
	*根据样本数据计算各个类别的均值向量，并存储到私有变量中
	*/
	void calculateMeans();

	/*
	*根据样本数据计算各个类别的协方差矩阵，并存储到私有变量中去。
	*/
	void calculateSigma();
};
