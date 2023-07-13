
all: main.o 
	g++ build/main.o -o bin/programa.exe

main.o: 
	g++ -c source/main.cpp -o build/main.o 

clean: 
	rm build/*.o bin/programa.exe

run: 
	./bin/programa.exe

