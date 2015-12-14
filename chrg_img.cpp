#include "iostream"
#include <stdio.h>
#include <stdlib.h>
#include "OutilsLib.h"
#include "BmpLib.h"
#define NBLIG 300
#define NBCOL 200

using namespace std;


void alloueMatrice(int** rouge, int** vert, int** bleu){
	//Allocation matrices
	rouge = new int*[NBLIG];
	for (int i=0; i<NBLIG; i++)
		rouge[i] = new int[NBCOL];

	vert = new int*[NBLIG];
	for (int i=0; i<NBLIG; i++)
		vert[i] = new int[NBCOL];
	
	bleu = new int*[NBLIG];
	for (int i=0; i<NBLIG; i++)
		bleu[i] = new int[NBCOL];
}

void cree3matrices(DonneesImageRGB *image, int** rouge, int** vert, int** bleu)
{
	int i,j,k=0;
	for (i=0; i<image->largeurImage; i++)
		for (j=0; j<image->hauteurImage;j++)
		{
			bleu[i][j]=image->donneesRGB[k];
			k++;
			vert[i][j]=image->donneesRGB[k];
			k++;
			rouge[i][j]=image->donneesRGB[k];
			k++;
		}
}

void creeImage(DonneesImageRGB *image, int** rouge, int** vert, int** bleu, int* largeur, int* hauteur)
{
	int i,j,k=0;
	for (i=0; i<*largeur; i++)
		for (j=0; j<*hauteur;j++)
		{
			image->donneesRGB[k]=bleu[i][j];
			k++;
			image->donneesRGB[k]=vert[i][j];
			k++;
			image->donneesRGB[k]=rouge[i][j];
			k++;
		}
}

//Mise en carré multiple de 8
int** multiple8(DonneesImageRGB *image, int**  matrice, int* largeur, int* hauteur){	
	int i = (image->largeurImage) % 8, j = (image->hauteurImage) % 8;

	if(*largeur > *hauteur){
		if (i!=0)
			*largeur += 8 - i;
		*hauteur=*largeur;
		cout << "Cas 1" << endl;
		cout << "Largeur : " << *largeur << endl << "Hauteur : " << *hauteur << endl << endl;
	}
	else if(*largeur < *hauteur){
		if (j != 0)
			*hauteur += 8 - j;
		*largeur=*hauteur;
		cout << "Cas 2" << endl;
		cout << "Largeur : " << *largeur << endl << "Hauteur : " << *hauteur << endl << endl;
	}

	int** matrice8=NULL;
	
	matrice8 = new int*[*largeur];
	for (int i=0; i<*largeur; i++)
		matrice8[i] = new int[*hauteur];

	int m,n;
	for (m=0; m<*largeur; m++)
		for (n=0; n<*hauteur;n++)
		{
			matrice8[m][n]=0;
		}
	int p,q;
	for (p=0; p<image->largeurImage; p++)
		for (q=0; q<image->hauteurImage;q++)
		{
			matrice8[p][q]=matrice[p][q];
		}	

	return matrice8;
}

int main(void)
{
	DonneesImageRGB *image=NULL;
	DonneesImageRGB *image8=NULL;
    	
	//Déclaration matrices
   	int** rouge=NULL; 
	int** vert=NULL; 
	int** bleu=NULL;

	//Déclarations nouvelles dimensions
	int* largeur=NULL;
	int* hauteur=NULL;
	int* tab = new int[2];
	
	cout << "========== Lecture de l'image =========" << endl << endl;
    	
	image = lisBMPRGB("champ.bmp");
	cout << "Largeur : " << image->largeurImage << endl << "Hauteur : " << image->hauteurImage << endl << endl;	
	
	tab[0]=image->largeurImage;
	tab[1]=image->hauteurImage;
	largeur=tab;
	hauteur=tab+1;


	//Allocation matrices
	rouge = new int*[image->largeurImage];
	for (int i=0; i<image->largeurImage; i++)
		rouge[i] = new int[image->hauteurImage];

	vert = new int*[image->largeurImage];
	for (int i=0; i<image->largeurImage; i++)
		vert[i] = new int[image->hauteurImage];
	
	bleu = new int*[image->largeurImage];
	for (int i=0; i<image->largeurImage; i++)
		bleu[i] = new int[image->hauteurImage];
	
	cout << "test1" << endl;
	
	cree3matrices(image, rouge, vert, bleu);
	
	cout << "test2" << endl;
	
	rouge = multiple8(image, rouge, largeur, hauteur);
	vert = multiple8(image, vert, largeur, hauteur);
	bleu = multiple8(image, bleu, largeur, hauteur);
	
	cout << "test3" << endl;

	creeImage(image8,rouge, vert, bleu, largeur, hauteur);
	
	cout << "========== Ecriture de l'image =========" << endl << endl;
	
	ecrisBMPRGB_Dans(image,"out.bmp");

}
