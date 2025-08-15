CFLAGS=-I/opt/homebrew/include/SDL2 -I../Ramparty/headers
LDFLAGS=-L/opt/homebrew/lib -lSDL2 -lSDL2_image -stdlib=libc++
EXE=Ramparty
SRC_DIR=src/
FILES=$(SRC_DIR)*.cpp

clean:
	rm $(EXE) *.o

game:
	clang++ -v -o $(EXE) $(FILES) $(CFLAGS) $(LDFLAGS) -std=c++17

