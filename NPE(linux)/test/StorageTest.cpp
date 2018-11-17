#include "storage.h"
int main()
{
	Storage storage;
	storage.setfile("sample.txt");

	storage.setVectorLen(3);
	//先读开头的先验概率
	storage.readPostPro();
	storage.readPostPro();
	storage.readPostPro();
	//读30次到文件末尾
	for(int counter = 0; counter < 30; counter++)
		(storage.readData()).printMatrix();
	//返回开头
	storage.reset();

	//这里应该是先验概率
	(storage.readData()).printMatrix();
	system("pause");
	return 0;
}