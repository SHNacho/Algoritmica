BIN=./bin
SRC=./src
OBJ=./obj
INC=./include
CXX = -std=gnu++0x -g -I$(INC)


build: $(BIN)/traspuesta_DyV $(BIN)/traspuesta_secuencial

$(BIN)/traspuesta_secuencial: $(OBJ)/traspuesta_secuencial.o $(OBJ)/matriz.o
	g++ $(CXX) -no-pie -o $@ $^
	
$(BIN)/traspuesta_DyV: $(OBJ)/traspuesta_DyV.o $(OBJ)/matriz.o
	g++ $(CXX) -no-pie -o $@ $^

$(OBJ)/traspuesta_secuencial.o: $(SRC)/traspuesta_secuencial.cpp $(INC)/matriz.h
	g++ $(CXX) -c $< -o $@

$(OBJ)/traspuesta_DyV.o: $(SRC)/traspuesta_DyV.cpp $(INC)/matriz.h
	g++ $(CXX) -c $< -o $@

$(OBJ)/matriz.o: $(SRC)/matriz.cpp
	g++ $(CXX) -c $< -o $@


clean:
	rm -rf $(BIN)/* $(OBJ)/* traspuesta.zip
	
zip: clean
	zip -r traspuesta.zip bin include Makefile obj README src
	

