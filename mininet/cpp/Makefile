# MiniNet makefile

CC := g++
JSON_INC = $(shell pkg-config jsoncpp --cflags)
JSON_LIB = $(shell pkg-config jsoncpp --libs)
ARMADILLO_INC = -I/usr/include
ARMADILLO_LIB = -larmadillo
CXXFLAG = -I./include -std=c++11 -g
CXXFLAG += $(JSON_INC)
CXXFLAG += $(JSON_LIB)
CXXFLAG += $(ARMADILLO_INC)
CXXFLAG += $(ARMADILLO_LIB)

vpath %.hpp include
vpath %.cpp src
vpath %.cpp example

.PHONY : all
all : ofsmall mnist
	-mkdir build
	mv *.o *.a mnist ofsmall build

ofsmall : ofsmall.o libmnet.a
	$(CC) -o ofsmall ofsmall.o libmnet.a $(CXXFLAG)

ofsmall.o : mini_net.hpp ofsmall.cpp
	$(CC) -c  src/ofsmall.cpp $(CXXFLAG)

mnist : mnist.o libmnet.a
	$(CC) -o mnist mnist.o libmnet.a $(CXXFLAG)

mnist.o : mini_net.hpp mnist.cpp
	$(CC) -c example/mnist.cpp $(CXXFLAG)

libmnet.a : blob.o layer.o net.o 
	ar r libmnet.a blob.o layer.o net.o

blob.o layer.o net.o : blob.hpp layer.hpp net.hpp test.hpp blob.cpp layer.cpp net.cpp
	$(CC) -c src/blob.cpp src/layer.cpp src/net.cpp $(CXXFLAG)

.PHONY: clean
clean:
	-rm -r build/
	-rm *.o *.a mnist ofsmall 
