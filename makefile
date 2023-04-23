# Compile all the .cpp code needed for the compiler

all:Compiler

Compiler:Compiler.o Lexical_analyzer.o Parser.o NFA.o Utils.o Exception.o NFA_Simulation.o RegularExpressionOperations.o
	g++ -o Compiler Compiler.o Lexical_analyzer.o Parser.o NFA.o Utils.o Exception.o NFA_Simulation.o RegularExpressionOperations.o
Compiler.o: Compiler.cpp
	g++ -c Compiler.cpp

Lexical_analyzer.o: Lexical_analyzer.cpp
	g++ -c Lexical_analyzer.cpp

Parser.o: Parser.cpp
	g++ -c Parser.cpp

NFA.o: NFA.cpp	
	g++ -c -g NFA.cpp

Exception.o: Exception.cpp	
	g++ -c Exception.cpp

Utils.o: Utils.cpp	
	g++ -c Utils.cpp

NFA_Simulation.o: NFA_Simulation.cpp
	g++ -c -g NFA_Simulation.cpp

RegularExpressionOperations.o: RegularExpressionOperations.cpp
	g++ -c -g RegularExpressionOperations.cpp

clean:
	rm -rf *.o Compiler