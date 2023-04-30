# CXX=g++


# TARGET=Compiler
# SRC_DIR=srs
# OBJ_DIR=obj
# OBJS=$(wildcard $(OBJ_DIR)/*.o)

# all: SRSMAKE $(TARGET)

# SRSMAKE:
# 	cd $(SRC_DIR); make

# $(TARGET): OBJS
# 	$(CXX) $? -o $@
SRC_DIR := src

SUBDIRS := $(wildcard $(SRC_DIR)/*)
SUBDIRS := $(filter-out $(wildcard $(SRC_DIR)/*.cpp),$(SUBDIRS))
SUBDIRS := $(filter-out $(SRC_DIR)/Makefile,$(SUBDIRS))
SUBDIRS += $(SRC_DIR)
.PHONY: all $(SUBDIRS)

all: $(SUBDIRS) 


$(SUBDIRS):
	$(MAKE) -C $@

.PHONY: clean

clean:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir clean; \
	done
