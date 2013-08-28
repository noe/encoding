GTEST_LIBS=/usr/local/lib/libgtest.a /usr/local/lib/libgtest_main.a

all: test

test: test_enum.cpp test_integer.cpp test_float.cpp test_streams.cpp
	g++-4.7 -I../include/ -I. -std=c++0x -o $@ $^ ${GTEST_LIBS} -lpthread 
