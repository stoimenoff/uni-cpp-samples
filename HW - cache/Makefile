all:
	g++ -std=c++11 test.cpp mystring.cpp vector.h movie.cpp moviestaff.cpp date.cpp \
	 role.cpp user.cpp review.cpp dispatcher.cpp -o test
reader:
	g++ -std=c++11 read.cpp mystring.cpp vector.h movie.cpp moviestaff.cpp date.cpp \
	 role.cpp user.cpp review.cpp dispatcher.cpp -o read
headers:
	g++ mystring.h vector.h movie.h moviestaff.h date.h role.h user.h \
	 review.h dispatcher.h -std=c++11
system:
	g++ -std=c++11 sys.cpp mystring.cpp vector.h movie.cpp moviestaff.cpp \
	 date.cpp role.cpp user.cpp review.cpp dispatcher.cpp -o sys
clean:
	find . -name "*.h.gch" -type f -delete
