# Compile all the .cpp code needed for the compiler

all:Compiler

Compiler:Compiler.o Lexical_analyzer.o Parser.o
	g++ -o Compiler Compiler.o Lexical_analyzer.o Parser.o NFA.cpp

Compiler.o: Compiler.cpp
	g++ -c Compiler.cpp

Lexical_analyzer.o: Lexical_analyzer.cpp
	g++ -c Lexical_analyzer.cpp

Parser.o: Parser.cpp
	g++ -c Parser.cpp

NFA.o: NFA.cpp	
	g++ -c NFA.cpp

clean:
	rm -rf *.o Compiler