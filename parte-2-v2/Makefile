CC = g++

CFLAGS = -std=c++14 -Wall 
TARGET = main

all: $(TARGET)

$(TARGET): $(TARGET).cpp 
	$(CC) $(CFLAGS) $(TARGET).cpp mapa.cpp -o $(TARGET) 

clean:
	$(RM) $(TARGET)