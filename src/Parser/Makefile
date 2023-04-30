CXX=g++
CXXFLAGS=-g

OBJ_DIR=./../../obj
SRC_DIR=.


OBJS := $(wildcard $(SRC_DIR)/*.cpp)

all:$(OBJS)

$(OBJS):
	$(CXX) $(CXXFLAGS) $? o $@

clean:
	rm -f $(OBJS) 