CFLAGS = -O3
cc=g++

kpartiteparaclique: main.o enumerate.o helper.o inputprep.o paraclique.o 
	$(cc)  $(CFLAGS) -o kpartiteparaclique main.o enumerate.o helper.o inputprep.o paraclique.o 

main.o: main.cpp paraclique.cpp enumerate.cpp helper.cpp inputprep.cpp
	$(cc)  $(CFLAGS) -c main.cpp 

paraclique.o: paraclique.cpp
	$(cc)  $(CFLAGS) -c paraclique.cpp

enumerate.o: enumerate.cpp
	$(cc)  $(CFLAGS) -c enumerate.cpp

helper.o: helper.cpp
	$(cc)  $(CFLAGS) -c helper.cpp

inputprep.o: inputprep.cpp
	$(cc)  $(CFLAGS) -c inputprep.cpp

clean: rm -f core *.o 