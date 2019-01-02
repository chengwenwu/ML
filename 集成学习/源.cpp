#include <iostream>  
#include <fstream>  
#include <string>   
#include <map>
#include <cmath>
using namespace std;

int ReverseInt(int i)
{
	unsigned char ch1, ch2, ch3, ch4;
	ch1 = i & 255;
	ch2 = (i >> 8) & 255;
	ch3 = (i >> 16) & 255;
	ch4 = (i >> 24) & 255;
	return((int)ch1 << 24) + ((int)ch2 << 16) + ((int)ch3 << 8) + ch4;
}

void read_Mnist_Label(string data_type, int size,unsigned char labels[1000])
{
	string filename = "train-labels.idx1-ubyte";
	if (data_type == "test_data")
	{
		filename = "t10k-labels.idx1-ubyte";
	}
	ifstream file(filename, ios::binary);
	if (file.is_open())
	{
		int magic_number = 0;
		int number_of_images = 0;
		file.read((char*)&magic_number, sizeof(magic_number));
		file.read((char*)&number_of_images, sizeof(number_of_images));
		magic_number = ReverseInt(magic_number);
		number_of_images = ReverseInt(number_of_images);
		cout << "magic number = " << magic_number << endl;
		cout << "number of images = " << number_of_images << endl;


		for (int i = 0; i < size; i++)
		{
			unsigned char label = 0;
			file.read((char*)&label, sizeof(label));
			labels[i] = label;
		}

	}
}

void read_Mnist_Images(string data_type,int size, unsigned char images[][784])
{
	string filename = "train-images.idx3-ubyte";
	if (data_type == "test_data")
	{
		filename = "t10k-images.idx3-ubyte";
	}
	ifstream file(filename, ios::binary);
	if (file.is_open())
	{
		int magic_number = 0;
		int number_of_images = 0;
		int n_rows = 0;
		int n_cols = 0;
		file.read((char*)&magic_number, sizeof(magic_number));
		file.read((char*)&number_of_images, sizeof(number_of_images));
		file.read((char*)&n_rows, sizeof(n_rows));
		file.read((char*)&n_cols, sizeof(n_cols));
		magic_number = ReverseInt(magic_number);
		number_of_images = ReverseInt(number_of_images);
		n_rows = ReverseInt(n_rows);
		n_cols = ReverseInt(n_cols);

		cout << "magic number = " << magic_number << endl;
		cout << "number of images = " << number_of_images << endl;
		cout << "rows = " << n_rows << endl;
		cout << "cols = " << n_cols << endl;

		for (int i = 0; i < size; i++)//无论是训练数据还是测试数据我们只需要1000个
		{
			for (int r = 0; r < n_rows; r++)
			{
				for (int c = 0; c < n_cols; c++)
				{
					unsigned char image = 0;
					file.read((char*)&image, sizeof(image));
					images[i][r * 28 + c] = image;
				}
			}
		}
		
	}
}

/*
@training_set：训练数据
@labels：训练数据标签
@start：从训练数据的哪个位置开始作为该KNN分类器的训练数据开始的下标
@size:样本数据大小
@k:最近的k个样本
@test:传入一个测试数据
*/
unsigned char KNN(unsigned char training_set[1000][784], unsigned char labels[1000], int start, int size, int k, unsigned char test[784])
{
	multimap<int, int> dis_inedx;//把向量之间的距离和下标关联起来
	for (int counter0 = start; counter0 < start + size; counter0++)
	{
		int temp = 0;
		for (int counter1 = 0; counter1 < 784; counter1++)
		{
			temp += pow(training_set[counter0][counter1] - test[counter1], 2);
		}
		temp = sqrt(temp);
		dis_inedx.insert(pair<int, int>(temp, counter0));
	}

	//找到离test最近的k个向量，并统计他们的标签数量
	int count[10] = { 0 };
	int counter1 = 0;
	for (std::multimap<int, int>::iterator it = dis_inedx.begin(); it != dis_inedx.end()&& counter1 < k; ++it, counter1++)
	{
		count[labels[it->second]]++;
	}

	//找到标签最多的那个数字，返回出来。
	unsigned char index = 0, max = 0;
	for (int counter = 0; counter < 10; counter++)
	{
		if (count[counter] > max)
		{
			max = count[counter];
			index = counter;
		}
	}
	return index;
}

int main()
{
	int train_size = 1000;
	unsigned char train_images[1000][784];//读取1000个训练数据
	unsigned char train_labels[1000];//读取1000个训练数据的标签

	read_Mnist_Images("tarin_data", train_size, train_images);
	read_Mnist_Label("train_data", train_size, train_labels);

	int test_size = 100;
	unsigned char test_images[100][784];//读取1000个测试数据
	unsigned char test_labels[100];//读取1000个测试数据的标签

	read_Mnist_Images("test_data", test_size, test_images);
	read_Mnist_Label("test_data", test_size, test_labels);

	int test_number = 100;
	int correct = 0;
	for (int counter0 = 0; counter0 < test_number;counter0++ )//测试循环
	{
		//统计每个分类器的输出
		int count[10] = { 0 };
		for (int counter1 = 0; counter1 < 5; counter1++)
		{
			count[(int)(KNN(train_images, train_labels, counter1 * 200, 200, 20, test_images[counter0]))]++;//每200个训练数据作为一个分类器的训练数
		}

		//进行投票
		unsigned char index = 0, max = 0;
		for (int counter2 = 0; counter2 < 10; counter2++)
		{
			if (count[counter2] > max)
			{
				max = count[counter2];
				index = counter2;
			}
		}
		//判断分类是否正确
		if (index == test_labels[counter0])
			correct++;
	}
	cout << "正确率： " << (double)correct / (double)test_number<<endl;
	system("pause");
	return 0;
}
