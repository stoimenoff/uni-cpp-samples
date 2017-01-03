idgenerator.o: idgenerator.cpp idgenerator.h
	g++ -c idgenerator.h idgenerator.cpp -std=c++11

graph.o: graph.h idgenerator.h
	g++ -c graph.h -std=c++11

main.o: main.cpp graph.h
	g++ -c main.cpp -std=c++11

graph: main.o idgenerator.o
	g++ main.o idgenerator.o -o graph

clean:
	rm *.o
	rm *.gch
