CXX = g++
CXXFLAGS = -g -std=c++11
RM = rm

all: decoder encoder

clean: 
	$(RM) *.o encoder decoder

encoder: encoder.o pheap.o bheap.o fheap.o
	$(CXX) $(CXXFLAGS) -o encoder encoder.o pheap.o bheap.o fheap.o


encoder.o: encoder.cpp pheap.h bheap.h fheap.h
	$(CXX) $(CXXFLAGS) -c encoder.cpp


pheap.o: pheap.h	

bheap.o: bheap.h

fheap.o: fheap.h

decoder: decoderHuffman.o decoder.o encoder.o
	$(CXX) $(CXXFLAGS) -o decoder decoderHuffman.o decoder.o 

decoderHuffman.o: decoderHuffman.cpp decoder.h 
	$(CXX) $(CXXFLAGS) -c decoderHuffman.cpp

decoder.o: decoder.h
