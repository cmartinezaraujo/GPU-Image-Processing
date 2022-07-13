EXECUTABLE=myPaint
CXX = g++
NVCC = nvcc

#here are all the objects
GPUOBJS = pgmProcessUtility.o pgmProcess.o
OBJS = main.o 

#make and compile
myPaint: $(OBJS) $(GPUOBJS)
	$(NVCC) -arch=sm_30 -o myPaint $(OBJS) $(GPUOBJS)
	
pgmProcessUtility.o: pgmProcessUtility.cu
	$(NVCC) -arch=sm_30 -c pgmProcessUtility.cu
	
pgmProcess.o: pgmProcess.cu
	$(NVCC) -arch=sm_30 -c pgmProcess.cu
	
main.o: main.cu
	$(NVCC) -arch=sm_30 -c main.cu
	
pgmProcessUtility.o: pgmUtility.h

clean:
	rm -f *.o
	rm -f myPaint
	
