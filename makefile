# Compile all the .cpp code needed for the compiler

all:Compiler

Compiler:Compiler.o Lexical_analyzer.o
	g++ -o Compiler Compiler.o Lexical_analyzer.o

Compiler.o: Compiler.cpp
	g++ -c Compiler.cpp

Lexical_analyzer.o: Lexical_analyzer.cpp
	g++ -c Lexical_analyzer.cpp

clean:
	rm -rf *.o Compiler