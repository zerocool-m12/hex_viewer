CXX = clang++
CXX_FLAGS = -std=c++17 -O3
LD_FLAGS = -static

SRC = main.cpp
TARGET = hex_viewer.o
$(TARGET): $(SRC)
  $(CXX) $(CXX_FLAGS) $(SRC) $(LD_FLAGS) -o $(TARGET)
.PHONEY: clean
clean:
  rm -f $(TARGET)
