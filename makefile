tgt/run.exe: obj/main.o obj/Patient.o obj/util.o obj/Binary_classifier.o
	g++ -o run.exe obj/*.o
	mv run.exe tgt/run.exe

obj/main.o: src/main.cpp
	g++ -g -c -DDEBUG -std=c++11 src/main.cpp
	mv main.o obj/main.o

obj/Binary_classifier.o: src/Binary_classifier.cpp lib/Binary_classifier.h
	g++ -g -c -DDEBUG -std=c++11 src/Binary_classifier.cpp
	mv Binary_classifier.o obj/Binary_classifier.o

obj/util.o: src/util.cpp lib/util.h
	g++ -g -c -DDEBUG -std=c++11 src/util.cpp
	mv util.o obj/util.o

obj/Patient.o: src/Patient.cpp lib/Patient.h
	g++ -g -c -DDEBUG -std=c++11 src/Patient.cpp
	mv Patient.o obj/Patient.o