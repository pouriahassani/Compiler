CXX=g++
CXXFLAGS=-g -c

OBJ_DIR=./../../obj
SRC_DIR=.


SRCS=$(wildcard $(SRC_DIR)/*.cpp)
OBJS=$(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

.PHONY: all clean

all:$(OBJS)
	

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $? -o $@

clean:
	rm -f $(OBJS) 