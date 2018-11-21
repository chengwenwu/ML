#include "NPE.h"
int main()
{
	NPE npe;
	npe.setSampleFile("sample.txt");
	npe.setClassSize(3);
	npe.setSampleSize(10);
	npe.setVectorLen(3);

	cout << "Parzen  h = 1:\n";
	cout <<"[0.5, 1.0, 0.0] belong to w"<<npe.judgePar("[0.5, 1.0, 0.0]", 1) << endl;
	cout <<"[0.31, 1.51, -0.50] belong to w"<<npe.judgePar("[0.31, 1.51, -0.50]", 1) << endl;
	cout <<"[-0.3, 0.44, -0.1] belong to w"<<npe.judgePar("[-0.3, 0.44, -0.1]", 1) << endl;

	cout << "Parzen  h = 0.1:\n";
	cout << "[0.5, 1.0, 0.0] belong to w" << npe.judgePar("[0.5, 1.0, 0.0]", 0.1) << endl;
	cout << "[0.31, 1.51, -0.50] belong to w" << npe.judgePar("[0.31, 1.51, -0.50]", 0.1) << endl;
	cout << "[-0.3, 0.44, -0.1] belong to w" << npe.judgePar("[-0.3, 0.44, -0.1]", 0.1) << endl;

	//三维情况
	cout<<endl<<"while k = 1"<<endl;
	float *knn = npe.knnProbability("[-0.41,0.82,0.88]", 1);
	cout << "[-0.41,0.82,0.88] knn Probability in every class is " << knn[0] <<" "<< knn[1] << " " << knn[2] << " " << endl;
	delete[]knn;
	knn = npe.knnProbability("[0.14,0.72,4.1]", 1);
	cout << "[0.14,0.72,4.1] knn Probability in every class is " << knn[0] << " " << knn[1] << " " << knn[2] << " " << endl;
	delete[]knn;
	knn = npe.knnProbability("[-0.81,0.61,-0.38]", 1);
	cout << "[-0.81,0.61,-0.38] knn Probability in every class is " << knn[0] << " " << knn[1] << " " << knn[2] << " " << endl;
	
	cout << endl << "while k = 3" << endl;
	delete[]knn;
	knn = npe.knnProbability("[-0.41,0.82,0.88]", 3);
	cout << "[-0.41,0.82,0.88] knn Probability in every class is " << knn[0] << " " << knn[1] << " " << knn[2] << " " << endl;
	delete[]knn;
	knn = npe.knnProbability("[0.14,0.72,4.1]", 3);
	cout << "[0.14,0.72,4.1] knn Probability in every class is " << knn[0] << " " << knn[1] << " " << knn[2] << " " << endl;
	delete[]knn;
	knn = npe.knnProbability("[-0.81,0.61,-0.38]", 3);
	cout << "[-0.81,0.61,-0.38] knn Probability in every class is " << knn[0] << " " << knn[1] << " " << knn[2] << " " << endl;
	
	cout << endl << "while k = 5" << endl;
	delete[]knn;
	knn = npe.knnProbability("[-0.41,0.82,0.88]", 5);
	cout << "[-0.41,0.82,0.88] knn Probability in every class is " << knn[0] << " " << knn[1] << " " << knn[2] << " " << endl;
	delete[]knn;
	knn = npe.knnProbability("[0.14,0.72,4.1]", 5);
	cout << "[0.14,0.72,4.1] knn Probability in every class is " << knn[0] << " " << knn[1] << " " << knn[2] << " " << endl;
	delete[]knn;
	knn = npe.knnProbability("[-0.81,0.61,-0.38]", 5);
	cout << "[-0.81,0.61,-0.38] knn Probability in every class is " << knn[0] << " " << knn[1] << " " << knn[2] << " " << endl;
	
	system("pause");
	return 0;
}