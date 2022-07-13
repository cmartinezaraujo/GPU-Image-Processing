EXECUTABLE=myPaint
CXX = g++
NVCC = nvcc

#here are all the object files
OBJS = main.o pgmUtility_CPU.o

#make and compile
myPaint: $(OBJS)
	$(CXX) -o myPaint $(OBJS)

pgmUtility_CPU.o: pgmUtility_CPU.c
	$(CXX) -c pgmUtility_CPU.c
	
main.o: main.c
	$(CXX) -c main.c
	
pgmUtility_CPU.o: pgmUtility.h

clean:
	rm -f *.o
	rm -f myPaint
	
