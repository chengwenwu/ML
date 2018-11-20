main:NPETest.o NPE.o matrix.o storage.o
	g++ -g NPETest.o NPE.o matrix.o storage.o -o main
BayesTest.o:NPETest.cpp NPE.h storage.h matrix.h
	g++ -c -g NPETest.cpp NPE.h storage.h matrix.h
bayes.o:NPE.cpp NPE.h storage.h matrix.h
	g++ -c -g NPE.cpp NPE.h storage.h matrix.h
matrix.o:matrix.cpp matrix.h
	g++ -c -g matrix.cpp matrix.h
storage.o:storage.cpp storage.h matrix.h
	g++ -c -g storage.cpp storage.h matrix.h

clean:
	rm *.o
	rm *.gch
	rm main
