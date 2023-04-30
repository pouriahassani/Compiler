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


$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(TARGET)

