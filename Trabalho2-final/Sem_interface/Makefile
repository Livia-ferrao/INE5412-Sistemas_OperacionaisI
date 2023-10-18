CC=g++
CFLAGS=-std=c++14
TARGET=main
SRC=main.cpp FIFO.cpp LRU.cpp OPT.cpp memory.cpp simulador.cpp page.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)

run-exemplo: $(TARGET)
	./$(TARGET) 4 < vsim-exemplo.txt

run-belady: $(TARGET)
	./$(TARGET) 4 < vsim-belady.txt

run-gcc: $(TARGET)
	./$(TARGET) 4 < vsim-gcc.txt