BIN=./bin
SRC=./src
OBJ=./obj
INC=./include
DAT=./data
CXX = -std=gnu++0x -g -I$(INC)

all: clean build

build: $(BIN)/tsp_insercion $(BIN)/tsp_cercania $(BIN)/gasolineras $(BIN)/tsp_otro

$(BIN)/tsp_otro: $(OBJ)/tsp_otro.o $(OBJ)/matriz.o
	g++ $(CXX) -no-pie -o $@ $^

$(BIN)/tsp_insercion: $(OBJ)/tsp_insercion.o $(OBJ)/matriz.o
	g++ $(CXX) -no-pie -o $@ $^
	
$(BIN)/tsp_cercania: $(OBJ)/tsp_cercania.o $(OBJ)/matriz.o
	g++ $(CXX) -no-pie -o $@ $^

$(BIN)/gasolineras: $(OBJ)/gasolineras.o $(OBJ)/matriz.o
	g++ $(CXX) -no-pie -o $@ $^

$(OBJ)/tsp_otro.o: $(SRC)/tsp_otro.cpp $(INC)/matriz.h
	g++ $(CXX) -c $< -o $@

$(OBJ)/tsp_insercion.o: $(SRC)/tsp_insercion.cpp $(INC)/matriz.h
	g++ $(CXX) -c $< -o $@
	
$(OBJ)/tsp_cercania.o: $(SRC)/tsp_cercania.cpp $(INC)/matriz.h
	g++ $(CXX) -c $< -o $@

$(OBJ)/gasolineras.o: $(SRC)/gasolineras.cpp $(INC)/matriz.h
	g++ $(CXX) -c $< -o $@

$(OBJ)/matriz.o: $(SRC)/matriz.cpp
	g++ $(CXX) -c $< -o $@


clean:
	rm -rf $(BIN)/* $(OBJ)/* $(DAT)/output/* practica3.zip 
	
zip: clean
	zip -r practica3.zip bin include README.md makefile obj src data memo_practica3.pdf
