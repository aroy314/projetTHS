#include <stdio.h>
#include <stdlib.h>
#include "OutilsLib.h"
#include "BmpLib.h"
#include "imageIO.h"

void cree3matrices(DonneesImageRGB *image, short int** rouge,
                   short int** vert, short int** bleu, int n, int m)
// convertit DonneesImageRGB *image en trois matrices rouge, vert, bleu
{
    int i,j,k=0;

    for (i=0; i<n; i++)
        for (j=0; j<m; j++)
        {
            bleu[i][j]=image->donneesRGB[k];
            k++;
            vert[i][j]=image->donneesRGB[k];
            k++;
            rouge[i][j]=image->donneesRGB[k];
            k++;
        }
}

void matricesVersImage(DonneesImageRGB *image, short int** rouge,
                       short int** vert, short int** bleu, int n, int m)
// convertit trois matrices rouge, vert, bleu en DonneesImageRGB *image
// attention : image doit être correctement alloue pour etre utilise
{
    int i,j,k=0;
    for (i=0; i<n; i++)
        for (j=0; j<m; j++)
        {
            image->donneesRGB[k]=bleu[i][j];
            k++;
            image->donneesRGB[k]=vert[i][j];
            k++;
            image->donneesRGB[k]=rouge[i][j];
            k++;
        }
}

void sauveImage1composante(char *nom,DonneesImageRGB *image, short int** gris)
// permet de sauvegarder le contenu de la matrice gris dans un fichier BMP code sur 24 bits
// attention : image doit être correctement alloue pour etre utilise
{
    matricesVersImage(image,gris,gris,gris,NBLIG,NBCOL);
    ecrisBMPRGB_Dans(image,nom);
}

void dupliqueImageCouleur(short int rouge[NBLIG][NBCOL], short int vert[NBLIG][NBCOL], short int bleu[NBLIG][NBCOL], 
                          short int rouge2[NBLIG][NBCOL], short int vert2[NBLIG][NBCOL], short int bleu2[NBLIG][NBCOL])
// copie l'image rouge, vert, bleu dans l'image rouge2, vert2, bleu2 
{
     int i,j;

     for (i=0; i<NBLIG; i++)
        for (j=0; j<NBCOL; j++)
        {
            rouge2[i][j] = rouge[i][j];
            vert2[i][j] = vert[i][j];
            bleu2[i][j] = bleu[i][j];
        }                             
}

void dupliqueImage1composante(short int gris[NBLIG][NBCOL], short int gris2[NBLIG][NBCOL])
// copie l'image 1 composante gris dans l'image 1 composante gris2 
{
     int i,j;

     for (i=0; i<NBLIG; i++)
        for (j=0; j<NBCOL; j++)
            gris2[i][j] = gris[i][j];
}
