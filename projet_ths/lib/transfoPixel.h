void couleur2NG(short int rouge[NBLIG][NBCOL],short int vert[NBLIG][NBCOL],
                short int bleu[NBLIG][NBCOL], short int gris[NBLIG][NBCOL]);
// convertit l'image RVB (matrices rouge, vert et bleu) en niveaux de gris (matrice gris)                

void couleur2NoirBlanc(short int rouge[NBLIG][NBCOL],short int vert[NBLIG][NBCOL],
                short int bleu[NBLIG][NBCOL], short int nb[NBLIG][NBCOL]);
// convertit l'image RVB (matrices rouge, vert et bleu) en noir et blanc (matrice nb)                

void negatifImage(short int rouge[NBLIG][NBCOL],short int vert[NBLIG][NBCOL],
                  short int bleu[NBLIG][NBCOL]);
// calcule le negatif d'une image a partir des 3 matrices rouge, vert et bleu

void quantification(int N, short int gris[NBLIG][NBCOL]);
// quantifie une image en 256 niveaux de gris sur N niveaux de gris

void echantillonnage(int N, short int gris[NBLIG][NBCOL]);
// sous-echantillonne une image en niveaux de gris d'un facteur N

void statistiques(short int gris[NBLIG][NBCOL]);
// calcule et affiche les statistiques de l'image
