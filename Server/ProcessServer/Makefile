CC = g++
CFLAGS = -lssl -lcrypto
TARGET = main
SRC = main.cpp

all: $(TARGET)


$(TARGET):$(SRC)
	$(CC) -o $(TARGET) $(SRC) $(CFLAGS)

clean:
	rm -f $(TARGET)
