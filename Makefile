CXX=g++
CFLAGS=-std=c++14 -O2 -Wall -g

TARGET=Server
OBJS=./log/*.cpp ./pool/*.cpp ./timer/*.cpp\
		./http/*.cpp ./server/*.cpp\
		./buffer/*.cpp ./main.cpp

all:$(OBJS)
	$(CXX) $(CFLAGS) $(OBJS) -o $(TARGET) -pthread -lmysqlclient

clean:
	rm -rf $(OBJS) $(TARGET)