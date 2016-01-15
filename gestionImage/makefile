CC = g++
CFLAGS = -Wall -Os -lm
LDFLAGS = -lm
EXEC = chrg_img

all : $(EXEC)

chrg_img: chrg_img.o BmpLibfri.o OutilsLib.o
	$(CC) -o $@ $^ $(LDFLAGS)

chrg_img.o: chrg_img.cpp BmpLibfri.h OutilsLib.h
	$(CC) -c $< $(CFLAGS)

OutilsLib.o: OutilsLib.c OutilsLib.h
	$(CC) -c $< $(CFLAGS)

BmpLibfri.o: BmpLibfri.c BmpLibfri.h OutilsLib.h
	$(CC) -c $< $(CFLAGS)

clean:
	rm -f *~ *.o

deepclean: clean
	rm -f $(EXEC) out fichier.txt
