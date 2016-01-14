#define NBCOL   304
#define NBLIG   304

typedef unsigned char *tabRVB;
typedef char *chaine;

tabRVB lisImageRVB(chaine nom);
/* lit une image BMP de NBCOLxNBLIG points et la stocke dans une variable de type tabRVB (suite d'octets BVR) */
void ecrisImageRVB(chaine nom, tabRVB monImageData, int* largeur, int* hauteur, int* eps);
	/* écrit le contenu d'une variable tabRVB dans une image BMP */
DonneesImageRGB *lisBMPRGB(char *nom);