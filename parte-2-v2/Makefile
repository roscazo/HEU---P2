CC = g++

CFLAGS = -std=c++14 -Wall
TARGET = main

all: $(TARGET)

$(TARGET): $(TARGET).cpp 
	$(CC) $(CFLAGS) $(TARGET).cpp include/mapa.cpp include/node.cpp include/state.cpp -o $(TARGET) 

clean:
	$(RM) $(TARGET)