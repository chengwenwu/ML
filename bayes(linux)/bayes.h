#include "storage.h"
class Bayes
{
public:
	Bayes();
	~Bayes();

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
	@vec_str:用户输入将要判别的向量,各个元素之间用逗号隔开
	*输出判别结果
	*/
	int judge(string vec_str_in);

	/*
	*输出某一类的均值（从1开始记）
	*/
	Matrix& getMean(int whichClass);

	/*
	*输出某一类的协方差矩阵(从1开始记）
	*/
	Matrix& getSigma(int whichClass);

	/*
	*计算马氏距离,是开方后的结果
	@vec_str_in:字符串形式的向量，应该具有如下形式
	[1,2,3,4,5],即开头必须是‘[’结尾必须是‘]’,中间数字用‘,’隔开
	*/
	float mahal(string vec_str_in, int whichclass);

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

	/*
	*用户输入处理
	*将用户输入形如[1,2,3,4,5]的向量转化为一个Matrix对象输出
	*/
	Matrix userInputProcess(string vec_str_in);

	/*
	*从文件中读取后验概率,放到内存中
	*/
	void setPostPro();
};
