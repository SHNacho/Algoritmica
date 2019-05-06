BIN=./bin
SRC=./src
OBJ=./obj
INC=./include
CXX = -std=gnu++0x -g -I$(INC)

all: clean build

build: $(BIN)/tsp_insercion_1 $(BIN)/tsp_insercion_2 $(BIN)/tsp_cercania

$(BIN)/tsp_insercion_2: $(OBJ)/tsp_insercion_2.o $(OBJ)/matriz.o
	g++ $(CXX) -no-pie -o $@ $^
	
$(BIN)/tsp_insercion_1: $(OBJ)/tsp_insercion_1.o $(OBJ)/matriz.o
	g++ $(CXX) -no-pie -o $@ $^
	
$(BIN)/tsp_cercania: $(OBJ)/tsp_cercania.o $(OBJ)/matriz.o
	g++ $(CXX) -no-pie -o $@ $^

$(OBJ)/tsp_insercion_2.o: $(SRC)/tsp_insercion_2.cpp $(INC)/matriz.h
	g++ $(CXX) -c $< -o $@

$(OBJ)/tsp_insercion_1.o: $(SRC)/tsp_insercion_1.cpp $(INC)/matriz.h
	g++ $(CXX) -c $< -o $@
	
$(OBJ)/tsp_cercania.o: $(SRC)/tsp_cercania.cpp $(INC)/matriz.h
	g++ $(CXX) -c $< -o $@

$(OBJ)/matriz.o: $(SRC)/matriz.cpp
	g++ $(CXX) -c $< -o $@


clean:
	rm -rf $(BIN)/* $(OBJ)/* tsp.zip
	
zip: clean
	zip -r tsp.zip bin include makefile obj src data
