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

		for (int i = 0; i < size; i++)//������ѵ�����ݻ��ǲ�����������ֻ��Ҫ1000��
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
@training_set��ѵ������
@labels��ѵ�����ݱ�ǩ
@start����ѵ�����ݵ��ĸ�λ�ÿ�ʼ��Ϊ��KNN��������ѵ�����ݿ�ʼ���±�
@size:�������ݴ�С
@k:�����k������
@test:����һ����������
*/
unsigned char KNN(unsigned char training_set[1000][784], unsigned char labels[1000], int start, int size, int k, unsigned char test[784])
{
	multimap<int, int> dis_inedx;//������֮��ľ�����±��������
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

	//�ҵ���test�����k����������ͳ�����ǵı�ǩ����
	int count[10] = { 0 };
	int counter1 = 0;
	for (std::multimap<int, int>::iterator it = dis_inedx.begin(); it != dis_inedx.end()&& counter1 < k; ++it, counter1++)
	{
		count[labels[it->second]]++;
	}

	//�ҵ���ǩ�����Ǹ����֣����س�����
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
	unsigned char train_images[1000][784];//��ȡ1000��ѵ������
	unsigned char train_labels[1000];//��ȡ1000��ѵ�����ݵı�ǩ

	read_Mnist_Images("tarin_data", train_size, train_images);
	read_Mnist_Label("train_data", train_size, train_labels);

	int test_size = 100;
	unsigned char test_images[100][784];//��ȡ1000����������
	unsigned char test_labels[100];//��ȡ1000���������ݵı�ǩ

	read_Mnist_Images("test_data", test_size, test_images);
	read_Mnist_Label("test_data", test_size, test_labels);

	int test_number = 100;
	int correct = 0;
	for (int counter0 = 0; counter0 < test_number;counter0++ )//����ѭ��
	{
		//ͳ��ÿ�������������
		int count[10] = { 0 };
		for (int counter1 = 0; counter1 < 5; counter1++)
		{
			count[(int)(KNN(train_images, train_labels, counter1 * 200, 200, 20, test_images[counter0]))]++;//ÿ200��ѵ��������Ϊһ����������ѵ����
		}

		//����ͶƱ
		unsigned char index = 0, max = 0;
		for (int counter2 = 0; counter2 < 10; counter2++)
		{
			if (count[counter2] > max)
			{
				max = count[counter2];
				index = counter2;
			}
		}
		//�жϷ����Ƿ���ȷ
		if (index == test_labels[counter0])
			correct++;
	}
	cout << "��ȷ�ʣ� " << (double)correct / (double)test_number<<endl;
	system("pause");
	return 0;
}
