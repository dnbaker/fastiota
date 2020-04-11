CXX?=g++
CC?=gcc
CXXFLAGS+=-march=native -O3

fastiota.o: fastiota.c
	$(CC) -march=native -O3 $< -c -o $@ -fpic

testfastiota: testfastiota.cpp fastiota.o
	$(CXX) $(CXXFLAGS) $< -o $@ fastiota.o


testfastiotaho: testfastiota.cpp fastiota.c
	$(CXX) $(CXXFLAGS) $< -o $@ -DSINGLE_HEADER_FAST_IOTA



