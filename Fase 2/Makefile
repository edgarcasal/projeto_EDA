OBJ = src/funcoes.o
LIB = lib/libfuncoes.a
BIN = prog

all: $(BIN)

$(LIB): $(OBJ)
	mkdir -p lib
	ar rcs $(LIB) $(OBJ)

$(OBJ): src/funcoes.c src/funcoes.h
	gcc -c src/funcoes.c -o $(OBJ)

$(BIN): src/main.c $(LIB)
	gcc src/main.c -Llib -lfuncoes -o $(BIN)

clean:
	rm -f $(OBJ) $(LIB) $(BIN)