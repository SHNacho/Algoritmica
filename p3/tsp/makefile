BIN=./bin
SRC=./src
OBJ=./obj
INC=./include
CXX = -std=gnu++0x -g -I$(INC)

build: $(BIN)/tsp_insercion $(BIN)/tsp_cercania


	
$(BIN)/tsp_insercion: $(OBJ)/tsp_insercion.o $(OBJ)/matriz.o
	g++ $(CXX) -no-pie -o $@ $^
	
$(BIN)/tsp_cercania: $(OBJ)/tsp_cercania.o $(OBJ)/matriz.o
	g++ $(CXX) -no-pie -o $@ $^

$(OBJ)/tsp_insercion.o: $(SRC)/tsp_insercion.cpp $(INC)/matriz.h
	g++ $(CXX) -c $< -o $@
	
$(OBJ)/tsp_cercania.o: $(SRC)/tsp_cercania.cpp $(INC)/matriz.h
	g++ $(CXX) -c $< -o $@

$(OBJ)/matriz.o: $(SRC)/matriz.cpp
	g++ $(CXX) -c $< -o $@


clean:
	rm -rf $(BIN)/* $(OBJ)/* traspuesta.zip
	
zip: clean
	zip -r tsp.zip bin include makefile obj src data
