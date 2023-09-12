CXX = g++
CXXFLAGS = -Wall -std=c++11

SRCS = context.cpp main.cpp cpu.cpp operating_system.cpp process.cpp scheduler.cpp read_file.cpp SJF.cpp FCFS.cpp PNP.cpp PPP.cpp RR.cpp
OBJS = $(SRCS:.cpp=.o)
EXEC = my_program

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(EXEC)
	
run: $(EXEC)
	./$(EXEC)

check:
	valgrind --leak-check=summary --show-leak-kinds=all ./$(EXEC)

clean:
	rm -f $(OBJS) $(EXEC)