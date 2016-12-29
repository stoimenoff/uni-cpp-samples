tokenizer.o: tokenizer.cpp tokenizer.h
	g++ -c tokenizer.h tokenizer.cpp -std=c++11

operator.o: operator.cpp operator.h
	g++ -c operator.h operator.cpp -std=c++11

operatorregistry.o: operatorregistry.cpp operatorregistry.h operator.o
	g++ -c operatorregistry.h operatorregistry.cpp -std=c++11

expressionparser.o: expressionparser.cpp expressionparser.h operatorregistry.o tokenizer.o
	g++ -c expressionparser.cpp -std=c++11

main.o: main.cpp
	g++ -c main.cpp -std=c++11

rpn: main.o expressionparser.o
	g++ main.o expressionparser.o operatorregistry.o operator.o tokenizer.o -o rpn

clean:
	rm *.o
	rm *.gch
