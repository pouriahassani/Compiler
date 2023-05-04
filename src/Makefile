CXX=g++
CXXFLAGS=-Wall
SRC_DIR=./
OBJ_DIR=./../obj
BIN_DIR=./../bin
TARGET=$(BIN_DIR)/Compiler
OBJS=$(wildcard $(OBJ_DIR)/*.o)

.PHONY: all clean

all: Compiler

Compiler: $(OBJS) Compiler.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) $^

clean:
	rm -f $(TARGET) $(OBJS)

