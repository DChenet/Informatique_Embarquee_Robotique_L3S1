reconnaissance: couleur.o barycentre.o serial.o reconnaissance.o 
	g++ reconnaissance.o couleur.o barycentre.o serial.o -o reconnaissance -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_videoio

reconnaissance.o: couleur.h serial.h barycentre.h reconnaissance.cpp
	g++ -c reconnaissance.cpp  -o reconnaissance.o

couleur.o: couleur.h couleur.cpp
	g++ -c couleur.cpp  -o couleur.o

barycentre.o: barycentre.h barycentre.cpp
	g++ -c barycentre.cpp -o barycentre.o

serial.o: serial.h serial.cpp
	g++ -c serial.cpp -o serial.o

clean:
	rm -f reconnaissance.o couleur.o barycentre.o  serial.o
