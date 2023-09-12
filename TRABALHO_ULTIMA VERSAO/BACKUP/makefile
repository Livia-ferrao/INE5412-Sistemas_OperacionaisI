CXX = g++
CXXFLAGS = -Wall -std=c++11

SRCS = context.cpp main.cpp scheduler.cpp cpu.cpp operating_system.cpp process.cpp read_file.cpp
OBJS = $(SRCS:.cpp=.o)
EXEC = my_program

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(EXEC)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)