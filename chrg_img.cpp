#include "iostream"
#include <stdio.h>
#include <stdlib.h>
#include "OutilsLib.h"
#include "BmpLib.h"
#define NBLIG 300
#define NBCOL 200

using namespace std;


void cree3matrices(DonneesImageRGB *image, int rouge[NBLIG][NBCOL], 
	int vert[NBLIG][NBCOL], int bleu[NBLIG][NBCOL])
{
	int i,j,k=0;
	for (i=0; i<NBLIG; i++)
		for (j=0; j<NBCOL;j++)
		{
			bleu[i][j]=image->donneesRGB[k];
			k++;
			vert[i][j]=image->donneesRGB[k];
			k++;
			rouge[i][j]=image->donneesRGB[k];
			k++;
		}
}

void creeImage(DonneesImageRGB *image, int rouge[NBLIG][NBCOL], 
	int vert[NBLIG][NBCOL], int bleu[NBLIG][NBCOL])
{
	int i,j,k=0;
	for (i=0; i<NBLIG; i++)
		for (j=0; j<NBCOL;j++)
		{
			image->donneesRGB[k]=bleu[i][j];
			k++;
			image->donneesRGB[k]=vert[i][j];
			k++;
			image->donneesRGB[k]=rouge[i][j];
			k++;
		}
}

/*short int Multiple8(short int  matrice[NBLIG][NBCOL]){ //Mise en carré multiple de 8
	int i = (NBLIG) % 8, j = (NBCOL) % 8;
	int x = NBLIG,y = NBCOL;
	cout << x << endl << y << endl;

	if(x > y){
		if (i!=0)
			x += 8 - i;
		y=x;
		cout << "Cas1" << endl;
	}
	else if(x < y){
		if (j != 0)
			y += 8 - j;
		x=y;
		cout << "Cas2" << endl;
	}
	short int matrice8[x][y];
	
	int m,n;
	for (i=0; i<x; i++)
		for (j=0; j<y;j++)
		{
			matrice8[i][j]=0;
		}
	int i,j;
	for (i=0; i<NBLIG; i++)
		for (j=0; j<NBCOL;j++)
		{
			matrice8[i][j]=matrice[i][j];
		}	

	return matrice8;
}*/

int main(void)
{
	

	DonneesImageRGB *image=NULL;
    
   	int rouge[NBLIG][NBCOL]; 
	int vert[NBLIG][NBCOL]; 
	int bleu[NBLIG][NBCOL];
    

    	cout << "========== Lecture de l'image =========" << endl;
    	
	image = lisBMPRGB("cascade.bmp");
	cout << image->largeurImage << endl << image->hauteurImage << endl;	
	cree3matrices(image, rouge, vert, bleu);
	creeImage(image,rouge, vert, bleu);
	
	cout << "========== Ecriture de l'image =========" << endl;
	
	ecrisBMPRGB_Dans(image,"out.bmp");

}
