
all:
	mkdir -p bin
	g++ -Wall -Werror -ansi -pedantic src/rshell.cpp -o bin/rshell
rshell:
	mkdir -p bin
	g++ -Wall -Werror -ansi -pedantic src/rshell.cpp -o bin/rshell
clean:
	rm bin/rshell
	rm -rf bin