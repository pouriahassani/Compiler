CXX=g++
CXXFLAGS=-Wall
SRC_DIR=./
OBJ_DIR=./../../obj
BIN_DIR=./../../bin
TARGET=$(BIN_DIR)/Compiler

SRCS=$(wildcard $(SRC_DIR)/*.cpp)
OBJS=$(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

.PHONY: all clean

all: $(OBJS)


# $(TARGET): $(OBJS)
# 	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(TARGET)

