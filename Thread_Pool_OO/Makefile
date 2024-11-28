.PHONY: all clean

# 指定目标文件
TARGET = main

# 指定源文件
SRCS = main.cc Thread_Class.cc ThreadPool.cc

# 指定编译器和编译选项
CXX = g++
CXXFLAGS = -std=c++11

# 生成目标文件
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

# 清理生成的文件
clean:
	rm -rf $(TARGET)