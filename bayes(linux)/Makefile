main:BayesTest.o bayes.o matrix.o storage.o
	g++ -g BayesTest.o bayes.o matrix.o storage.o -o main
BayesTest.o:BayesTest.cpp bayes.h storage.h matrix.h
	g++ -c -g BayesTest.cpp bayes.h storage.h matrix.h
bayes.o:bayes.cpp bayes.h storage.h matrix.h
	g++ -c -g bayes.cpp bayes.h storage.h matrix.h
matrix.o:matrix.cpp matrix.h
	g++ -c -g matrix.cpp matrix.h
storage.o:storage.cpp storage.h matrix.h
	g++ -c -g storage.cpp storage.h matrix.h

clean:
	rm *.o
	rm *.gch
	rm main
