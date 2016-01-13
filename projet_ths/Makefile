main: temp/main.o temp/matrix.o temp/OutilsLib.o temp/BmpLib.o temp/imageIO.o
	gcc -o main temp/main.o temp/matrix.o temp/OutilsLib.o temp/BmpLib.o temp/imageIO.o -lm

temp/main.o: lib/matrix.c lib/imageIO.c lib/BmpLib.c lib/OutilsLib.c
	gcc -o temp/main.o -c src/main.c -W -Wall

temp/matrix.o: lib/matrix.c lib/matrix.h lib/imageIO.c lib/imageIO.h lib/BmpLib.c lib/BmpLib.h lib/OutilsLib.c lib/OutilsLib.h
	gcc -o temp/matrix.o -c lib/matrix.c -W -Wall 

temp/OutilsLib.o: lib/OutilsLib.c lib/OutilsLib.h
	gcc -o temp/OutilsLib.o -c lib/OutilsLib.c -W -Wall

temp/BmpLib.o: lib/BmpLib.c lib/BmpLib.h lib/OutilsLib.c lib/OutilsLib.h
	gcc -o temp/BmpLib.o -c lib/BmpLib.c -W -Wall

temp/imageIO.o: lib/imageIO.c lib/imageIO.h lib/BmpLib.c lib/BmpLib.h lib/OutilsLib.c lib/OutilsLib.h
	gcc -o temp/imageIO.o -c lib/imageIO.c -W -Wall

clean:
	rm -rf *.o
	rm main
	rm resultats/ImageTraitee.bmp