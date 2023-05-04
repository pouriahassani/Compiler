CXX=g++
CXXFLAGS=-Wall
SRC_DIR=./
OBJ_DIR=./../obj
BIN_DIR=./../bin
TARGET=$(BIN_DIR)/Compiler

SRCS=$(wildcard $(SRC_DIR)/*.cpp)
OBJS=$(wildcard $(OBJ_DIR)/*.o)

.PHONY: all clean

all: $(TARGET)


$(TARGET): $(OBJS) Compiler.o
	echo "in the src Makefile"
	@$(CXX) $(CXXFLAGS) -o $@ $^

Compiler.o: Compiler.cpp 
	$(CXX) $(CXXFLAGS)  $@ -c $^

clean:
	rm -f $(TARGET) $(OBJS)

