stringtokenizer.o: stringtokenizer.cpp stringtokenizer.h
	g++ -c stringtokenizer.h stringtokenizer.cpp -std=c++11

filetokenizer.o: filetokenizer.cpp filetokenizer.h stringtokenizer.o
	g++ -c filetokenizer.h filetokenizer.cpp -std=c++11

main.o: main.cpp filetokenizer.o
	g++ -c main.cpp -std=c++11

tokensearch: main.o
	g++ main.o filetokenizer.o stringtokenizer.o -o tokensearch

clean:
	rm *.o
	rm *.gch
