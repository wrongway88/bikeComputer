CC=gcc
CFLAGS= -Wall

LIBS= -lstdc++

# Folders
SRC=src
BIN=bin
OBJ=$(BIN)/obj

#Files
SRC_FILES = \
	$(SRC)/main.cpp \
	$(SRC)/data/ISensor.h \
	$(SRC)/data/ISensorData.h \
	$(SRC)/data/sensorWrappers/GPSData.cpp \
	$(SRC)/data/sensorWrappers/GPSData.h \
	$(SRC)/data/sensorWrappers/GPSWrapper.cpp \
	$(SRC)/data/sensorWrappers/GPSWrapper.h

# create output directorie
#

all: createDirectories bikeComputer

createDirectories:
	@mkdir -p $(BIN)
	@mkdir -p $(OBJ)

bikeComputer:
	$(CC) -o $(BIN)/bikeComputer $(SRC_FILES) $(LIBS)  $(CFLAGS)

clean:
