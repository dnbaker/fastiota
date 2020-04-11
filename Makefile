CXX?=g++
CC?=gcc
CXXFLAGS+=-march=native -O3

all: testfastiota testfastiotaho testfastiota_c testfastiota_cho

fastiota.o: fastiota.c
	$(CC) -march=native -O3 $< -c -o $@ -fpic

testfastiota: testfastiota.cpp fastiota.o
	$(CXX) $(CXXFLAGS) $< -o $@ fastiota.o

testfastiota_c: testfastiota_c.c fastiota.o
	$(CC) -march=native -O3 $< -o $@ fastiota.o

testfastiota_cho: testfastiota_c.c fastiota.o
	$(CC) -march=native -O3 $< -o $@ -DSINGLE_HEADER_FAST_IOTA -I.


testfastiotaho: testfastiota.cpp fastiota.c
	$(CXX) $(CXXFLAGS) $< -o $@ -DSINGLE_HEADER_FAST_IOTA -I.

testsse2:
	$(MAKE) clean && $(MAKE) CXXFLAGS="-mno-avx2 -msse2" && ./testfastiota && ./testfastiotaho && ./testfastiota_c && ./testfastiota_cho

clean:
	rm -f testfastiota testfastiotaho testfastiota_c testfastiota_cho fastiota.o
