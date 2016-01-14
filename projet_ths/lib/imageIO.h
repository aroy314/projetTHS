#define NBLIG 200
#define NBCOL 300


void cree3matrices(DonneesImageRGB *image, short int** rouge,
                   short int** vert, short int** bleu, int n, int m);
// convertit DonneesImageRGB *image en trois matrices rouge, vert, bleu

void matricesVersImage(DonneesImageRGB *image, short int** rouge,
                       short int** vert, short int** bleu, int n, int m);
// convertit trois matrices rouge, vert, bleu en DonneesImageRGB *image
// attention : image doit être correctement alloue pour etre utilise
                       
void sauveImage1composante(char *nom, DonneesImageRGB *image, short int** gris);
// permet de sauvegarder le contenu de la matrice gris dans un fichier BMP code sur 24 bits
// attention : image doit être correctement alloue pour etre utilise

void dupliqueImageCouleur(short int rouge[NBLIG][NBCOL], short int vert[NBLIG][NBCOL], short int bleu[NBLIG][NBCOL], 
                          short int rouge2[NBLIG][NBCOL], short int vert2[NBLIG][NBCOL], short int bleu2[NBLIG][NBCOL]);
// copie l'image rouge, vert, bleu dans l'image rouge2, vert2, bleu2 

void dupliqueImage1composante(short int gris[NBLIG][NBCOL], short int gris2[NBLIG][NBCOL]);
// copie l'image 1 composante gris dans l'image 1 composante gris2 
