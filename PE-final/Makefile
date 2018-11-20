main:PETest.o PE.o matrix.o storage.o
	g++ -g PETest.o PE.o matrix.o storage.o -o main
PETest.o:PETest.cpp PE.h storage.h matrix.h
	g++ -c -g PETest.cpp PE.h storage.h matrix.h
PE.o:PE.cpp PE.h storage.h matrix.h
	g++ -c -g PE.cpp PE.h storage.h matrix.h
matrix.o:matrix.cpp matrix.h
	g++ -c -g matrix.cpp matrix.h
storage.o:storage.cpp storage.h matrix.h
	g++ -c -g storage.cpp storage.h matrix.h

clean:
	rm *.o
	rm *.gch
	rm main
