#include "PE.h"
int main()
{
	PE pe;
	pe.setSampleFile("a.txt");
	pe.setClassSize(3);
	pe.setSampleSize(10);
	pe.setVectorLen(1);

	pe.estimate();
	cout<<"ch3_1_a:\n";
	for(int counter = 1; counter <= 3; counter++)
	{
		cout<<"clo "<<counter<<" means :"<<pe.getMean(counter).matrixToFloat()
		<<" variance :"<<pe.getSigma(counter).matrixToFloat()<<endl;
	}

	pe.setSampleFile("b.txt");
	pe.setClassSize(3);
	pe.setSampleSize(10);
	pe.setVectorLen(2);

	pe.estimate();
	cout<<"\nch3_1_b:\n";
	for(int counter = 1; counter <= 3; counter++)
	{
		cout<<"pair "<<counter<<"\nmeans :";
		pe.getMean(counter).printMatrix();
		cout<<"variance :";
		pe.getSigma(counter).printMatrix();
	}

	pe.setSampleFile("c.txt");
	pe.setClassSize(1);
	pe.setSampleSize(10);
	pe.setVectorLen(3);

	pe.estimate();
	cout<<"\nch3_1_c:\n";
	cout<<"means :";
	pe.getMean(1).printMatrix();
	cout<<"variance :";
	pe.getSigma(1).printMatrix();


  pe.setSampleFile("d.txt");
	pe.estimate_d();
	cout<<"\nch3_1_d:\n";
	cout<<"means :";
	pe.getMean(1).printMatrix();
	cout<<"variance :";
	pe.getSigma(1).printMatrix();



	return 0;
}
