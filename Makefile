#
#
#

CXX = g++

STD = -std=c++11

CFLAGS = -Wall

HEADERS = state.hpp
SOURCES = main.cpp


all: $(SOURCES) $(HEADERS)
	$(CXX) $(STD) $(CFLAGS) $(SOURCES) -o chain


clean:
	rm -f chain
