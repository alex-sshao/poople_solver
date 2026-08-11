.PHONY=default clean
CC := g++
PNAME := poosolve

default: 
	@$(CC) main.cpp -o $(PNAME)
clean:
	rm -rf $(PNAME)
