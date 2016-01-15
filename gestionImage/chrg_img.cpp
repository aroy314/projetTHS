#include "iostream"
#include <stdio.h>
#include <stdlib.h>
#include "OutilsLib.h"
#include "BmpLib.h"
#include "BmpLibfri.h"

#define FNAME "fichier.txt"

using namespace std;

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

void creeImage(tabRVB tabRVB, int** rouge, int** vert, int** bleu, int x, int y)
{
	int i,j,k=0;
	for (i=0; i<x; i++)
		for (j=0; j<y;j++)
		{
			tabRVB[k]=bleu[i][j];
			k++;
			tabRVB[k]=vert[i][j];
			k++;
			tabRVB[k]=rouge[i][j];
			k++;
		}
}

//Mise en carré multiple de 8
int** multiple8(DonneesImageRGB *image, int**  matrice, int* largeur, int* hauteur, int* eps){	
	int i = (*largeur) % 8, j = (*hauteur) % 8;
		if (i != 0){
			*largeur += 8 - i;
			*eps = 8 - i;
		cout << "Cas 1 :" << endl;
		cout << "Largeur : " << *largeur << endl << "Hauteur : " << *hauteur << endl << endl;
	}
		if (j != 0){
			*hauteur += 8 - j;
		cout << "Cas 2 :" << endl;
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
	//Déclaration image
	DonneesImageRGB *image=NULL;
	
	//Déclaration recadrage
	int* eps=NULL;	

	//Déclaration matrices
   	int** rouge=NULL; 
	int** vert=NULL; 
	int** bleu=NULL;

	//Déclarations nouvelles dimensions
	int* largeur=NULL;
	int* hauteur=NULL;
	int* tab = new int[3];
	
	cout << "========== Lecture de l'image =========" << endl << endl;
    	
	image = lisBMPRGB("img/champ.bmp");
	
	cout << "Largeur : " << image->largeurImage << endl << "Hauteur : " << image->hauteurImage << endl << endl;	
	
	int x = tab[0] = image->largeurImage;
	int y = tab[1] = image->hauteurImage;
	tab[2] = 0;
	largeur = tab;
	hauteur = tab+1;
	eps = tab+2;
	
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
	
	cree3matrices(image, rouge, vert, bleu);
	
	rouge = multiple8(image, rouge, largeur, hauteur, eps);
	vert = multiple8(image, vert, largeur, hauteur, eps);
	bleu = multiple8(image, bleu, largeur, hauteur, eps);
	
	//Matrice --> Fichier
	FILE *fichier1 = fopen (FNAME, "w" );
         if (fichier1 == NULL)
         {
            perror (FNAME);
         }
         else
         {
            int i;
            for (i = 0; i < image->largeurImage; i++)
            {
               int j;
               for (j = 0; j < image->hauteurImage; j++)
               {
                  fprintf (fichier1, "%d,", rouge[i][j]);
		  fprintf (fichier1, "%d,", vert[i][j]);
		  fprintf (fichier1, "%d,", bleu[i][j]);

               }
               fprintf (fichier1, "\n" );
            }
         fclose(fichier1);
	 }
	
	//Fichier --> Matrice
	FILE *fichier2 = fopen (FNAME, "r" );
         if (fichier2 == NULL)
         {
            perror (FNAME);
         }
         else
         {
	 int i;
 	 for(i = 0; i < image->largeurImage; i++)
  	 {
      		int j;
	 	for(j = 0; j < image->hauteurImage; j++) 
      		{
       
	 if (!fscanf(fichier2, "%d,%d,%d,", &rouge[i][j],&vert[i][j],&bleu[i][j])) 
        
	     	break;
       
	 printf("%d,%d,%d\n", rouge[i][j],vert[i][j],bleu[i][j]);
      		}

  	 }
	 fclose(fichier2);	 
	 }

	unsigned char* tabRVB=NULL;
	tabRVB = (unsigned char*)calloc(1, sizeof(unsigned char)*(*largeur)*(*hauteur)*3);

	creeImage(tabRVB, rouge, vert, bleu, x, y);
	
	cout << "========== Ecriture de l'image =========" << endl;
	
	ecrisImageRVB("out", tabRVB, largeur, hauteur, eps);
}
