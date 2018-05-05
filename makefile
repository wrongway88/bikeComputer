CC=gcc
CFLAGS= -Wall

LIBS= -lstdc++

# Folders
SRC=src
BIN=bin
OBJ=$(BIN)/obj

#Files
SRC_FILES = main.cpp

# create output directorie
#

all: createDirectories bikeComputer

createDirectories:
	@mkdir -p $(BIN)
	@mkdir -p $(OBJ)

bikeComputer:
	$(CC) -o $(BIN)/bikeComputer $(SRC)/main.cpp $(LIBS)  $(CFLAGS)

clean:
