# 定义变量
CC = g++
CFLAGS = -Wall -std=c++11
LDFLAGS = -pthread
INCLUDES = -Iinc
SRCDIR = src
INCDIR = inc
BUILDDIR = build
BINDIR = bin

# 获取所有.cpp文件和对应的.o文件
SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SRCS))

# 目标：生成可执行文件
TARGET = $(BINDIR)/my_executable

# 默认目标
all: $(TARGET)

# 生成可执行文件
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

# 生成.o文件
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# 清理生成的文件
clean:
	rm -f $(BUILDDIR)/*.o $(TARGET)
