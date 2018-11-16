#include "bayes.h"
int main()
{
	Bayes bayes;
	bayes.setSampleFile("sample.txt");
	bayes.setClassSize(3);
	bayes.setSampleSize(10);
	bayes.setVectorLen(3);

	cout << "\nMahalanobis :\n";
	cout << "[1,2,1] to w1 " << bayes.mahal("[1,2,1]", 1) << " " << endl;
	cout << "[5,3,2] to w1 " << bayes.mahal("[5,3,2]", 1) << " " << endl;
	cout << "[0,0,0] to w1 " << bayes.mahal("[0,0,0]", 1) << " " << endl;
	cout << "[1,0,0] to w1 " << bayes.mahal("[1,0,0]", 1) << " " << endl << endl;

	cout << "[1,2,1] to w2 " << bayes.mahal("[1,2,1]", 2) << " " << endl;
	cout << "[5,3,2] to w2 " << bayes.mahal("[5,3,2]", 2) << " " << endl;
	cout << "[0,0,0] to w2 " << bayes.mahal("[0,0,0]", 2) << " " << endl;
	cout << "[1,0,0] to w2 " << bayes.mahal("[1,0,0]", 2) << " " << endl << endl;

	cout << "[1,2,1] to w3 " << bayes.mahal("[1,2,1]", 3) << " " << endl;
	cout << "[5,3,2] to w3 " << bayes.mahal("[5,3,2]", 3) << " " << endl;
	cout << "[0,0,0] to w3 " << bayes.mahal("[0,0,0]", 3) << " " << endl;
	cout << "[1,0,0] to w3 " << bayes.mahal("[1,0,0]", 3) << " " << endl<<endl;

	cout << "Prior probability is 0.3 0.3 0.3:\n";
	cout <<"[1,2,1] belong to w"<<bayes.judge("[1,2,1]") << endl;
	cout <<"[5,3,2] belong to w"<<bayes.judge("[5,3,2]") << endl;
	cout <<"[0,0,0] belong to w"<<bayes.judge("[0,0,0]") << endl;
	cout <<"[1,0,0] belong to w"<<bayes.judge("[1,0,0]") << endl;

	
	system("pause");
	return 0;
}