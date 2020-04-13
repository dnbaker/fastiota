CXX?=g++
CC?=gcc
CXXFLAGS+=-march=native -O3 -Wall -Wextra

all: testfastiota testfastiotaho testfastiota_c testfastiota_cho

fastiota.o: fastiota.c
	$(CC) -march=native -O3 $< -c -o $@ -fpic  -Wall -Wextra -Wc++-compat

testfastiota: testfastiota.cpp fastiota.o
	$(CXX) $(CXXFLAGS) $< -o $@ fastiota.o

testfastiota_c: testfastiota_c.c fastiota.o
	$(CC) -march=native -O3 $< -o $@ fastiota.o  -Wall -Wextra -Wc++-compat

testfastiota_cho: testfastiota_c.c fastiota.o
	$(CC) -march=native -O3 $< -o $@ -DSINGLE_HEADER_FAST_IOTA -I.  -Wall -Wextra -Wc++-compat


testfastiotaho: testfastiota.cpp fastiota.c
	$(CXX) $(CXXFLAGS) $< -o $@ -DSINGLE_HEADER_FAST_IOTA -I.

testsse2:
	$(MAKE) clean && $(MAKE) CXXFLAGS="-mno-avx2 -msse2" && ./testfastiota && ./testfastiotaho && ./testfastiota_c && ./testfastiota_cho

clean:
	rm -f testfastiota testfastiotaho testfastiota_c testfastiota_cho fastiota.o
