#include "storage.h"
class NPE
{
public:
	NPE();
	~NPE();

	/*
	*设置样本文件，该样本应该具有固定格式，详细会在实验报告中说明
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
	*输出parzen窗判别结果
	*/
	int judgePar(string vec_str_in, float h);

	/*
	@vec_str:用户输入的x,各个元素之间用逗号隔开
	*输出KNN概率
	*/
	float* knnProbability(string vec_str_in,int k);



private:
	Storage storage;//负责样本文件的读取
	int classSize;//表示有多少个类别
	int vecLen;//样本中向量的长度
	int sampleSize;//每个类别中样本容量应该相同

	/*
	*用户输入处理
	*将用户输入形如[1,2,3,4,5]的向量转化为一个Matrix对象输出
	*/
	Matrix userInputProcess(string vec_str_in);
};
