# tool macros
CXX := g++
#CXXFLAGS := -funsafe-math-optimizations -Ofast -flto=auto  -funroll-all-loops -pipe -march=native -std=c++20 -Wall -Wextra `pkg-config --cflags --libs opencv4`
CXXFLAGS := -funsafe-math-optimizations -Ofast -flto=auto  -funroll-all-loops -pipe -march=native -std=c++20 -Wall -Wextra
DBGFLAGS := -g
CXXOBJFLAGS := $(CXXFLAGS) -c
LFLAGS := -lncnn -lstdc++ -pthread -Wl,--gc-sections -flto -fopt-info-vec-optimized

# path macros
BIN_PATH := bin
OBJ_PATH := obj
SRC_PATH := src
DBG_PATH := debug

# compile macros
TARGET_NAME := stablencnn
ifeq ($(OS),Windows_NT)
	TARGET_NAME := $(addsuffix .exe,$(TARGET_NAME))
endif
TARGET := $(BIN_PATH)/$(TARGET_NAME)
TARGET_DEBUG := $(DBG_PATH)/$(TARGET_NAME)

# src files & obj files
SRC := $(foreach x, $(SRC_PATH), $(wildcard $(addprefix $(x)/*,.cpp)))
OBJ := $(addprefix $(OBJ_PATH)/, $(addsuffix .o, $(notdir $(basename $(SRC)))))
OBJ_DEBUG := $(addprefix $(DBG_PATH)/, $(addsuffix .o, $(notdir $(basename $(SRC)))))

# clean files list
DISTCLEAN_LIST := $(OBJ) \
                  $(OBJ_DEBUG)
CLEAN_LIST := $(TARGET) \
			  $(TARGET_DEBUG) \
			  $(DISTCLEAN_LIST)

# default rule
default: makedir all

# non-phony targets
$(TARGET): $(OBJ)
	$(CXX) -o $@ $(OBJ) $(CXXFLAGS) $(LFLAGS)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.cpp
	$(CXX) $(CXXOBJFLAGS) -o $@ $<

$(DBG_PATH)/%.o: $(SRC_PATH)/%.cpp
	$(CXX) $(CXXOBJFLAGS) $(DBGFLAGS) -o $@ $<

$(TARGET_DEBUG): $(OBJ_DEBUG)
	$(CXX) $(CXXFLAGS) $(DBGFLAGS) $(OBJ_DEBUG) -o $@ $(LFLAGS)

# phony rules
.PHONY: makedir
makedir:
	@mkdir -p $(BIN_PATH) $(OBJ_PATH) $(DBG_PATH)

.PHONY: all
all: $(TARGET)

.PHONY: debug
debug: $(TARGET_DEBUG)

.PHONY: clean
clean:
	@echo CLEAN $(CLEAN_LIST)
	@rm -f $(CLEAN_LIST)

.PHONY: distclean
distclean:
	@echo CLEAN $(DISTCLEAN_LIST)
	@rm -f $(DISTCLEAN_LIST)
