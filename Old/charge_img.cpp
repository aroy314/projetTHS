#include "CImg.h"
#include "iostream"


//Compile with : g++ main.cpp -o main -O2 -L/usr/X11R6/lib -lm -lpthread -lX11


using namespace cimg_library;
using namespace std;


CImg<int> charge_img(const char* file) {
	CImg<int> image (file);
	return image;
}

void save_img(CImg <int> image, const char* file) {
	image.save(file);
}

CImg <int> ecris_img(int** matrice, const int x, const int y) {
	CImg <int> image(x, y, 1, 3);
	
	for(int i=0; i<x; i=i+3){
		for(int j=0; j<y; j++){
			image(i, j, 1, -1) = matrice[i][j];
			image(i, j, 1, 0) = matrice[i+1][j];
			image(i, j, 1, 1) = matrice[i+2][j];
			
		}
	}
	return image;
}

int* Dimensions(CImg<int> image){ //Pour calculer les dimensions de l'image
	int* tab = new int[2];
	tab[0] = image.dimx();
	tab[1] = image.dimy();
	return tab;
}

int** MiseEnMatrice(CImg<int> image, int** matrice, const int x, const int y){
	
	CImg <int> image_test (x*3,y,0,3);
	matrice = new int*[x*3];		//Création matrice
	for (int i=0; i<x*3; i++)
		matrice[i] = new int[y];
	
	for (int i=0; i<x*3; i=i+3){	//Remplissage matrice
		for (int j=0; j<y; j++){
			matrice[i][j]=image(i,j,0,0); 
			matrice[i+1][j]=image(i,j,0,1); 
			matrice[i+2][j]=image(i,j,0,2); 
		}
	}
	return matrice;
}

int** Recalage(int** matrice, const int x, const int y){

	for (int i=0; i<x*3; i++){	
		for (int j=0; j<y; j++){
			if(matrice[i][j]>255)
				matrice[i][j]=255;	
		}
	}
	return matrice;
}

int** Multiple8(int** matrice, int* l, int* L){ //Mise en carré multiple de 8
	int i = (*l) % 8, j = (*L) % 8;
	int x = *l,y = *L;
	cout << x << endl << y << endl;

	if(x > y){
		if (i!=0)
			x += 8 - i;
		*L=x;
		cout << "Cas1" << endl;
	}
	else if(x < y){
		if (j != 0)
			y += 8 - j;
		*l=y;
		cout << "Cas2" << endl;
	}
	int finalX = *l, finalY=*L;
	int** matrice8 = new int*[finalX*3];
	for (int i = 0; i<finalX*3; i++)	//Création nouvelle matrice multiple de 8
		matrice8[i] = new int[finalY];

	for (int i=0; i<finalX*3; i++){	// Remplissage matrice multiple de 8
		for (int j=0; j<finalY; j++){
			if(i<(x*3) && j<y)
				matrice8[i][j] = matrice[i][j];
			if(i>=(x*3) || j>=y)
				matrice8[i][j]=0;
		}
}
	return matrice8;


}

void Free(int** matrice, int* x){ // Libère le tableau
	for (int i=0; i<*x; i++)
		delete[] matrice[i];
	delete[] matrice;
}


int main() 
{	
	CImg<int> image;
	int** matrice = NULL;
	int* l = NULL;
	int* L = NULL;
	
	image = charge_img("lena.jpg");
	int* tab = Dimensions(image);
	cout << "X = " << tab[0] << endl << "Y = " << tab[1] << endl;
	//delete tab;
	
	//int x = image.dimx()*3;
	//int y = image.dimy();
	l = tab;
	L = tab+1;

	matrice = MiseEnMatrice(image, matrice, *l, *L);
	matrice = Multiple8(matrice, l, L);
	matrice = Recalage(matrice, *l, *L);
	

/*	for (int i = 0; i < image.dimx(); i++) {
		for (int j = 0; j < image.dimy(); j++) {
			cout << endl;
			for (int k = 0; k < image.dimv(); k++) {
			cout << image(i,j,0,k);
				}}}
*/
	for (int i = 0; i < (*l)*3; i=i+3){
		for (int j = 0; j < *L; j++){
		//cout << matrice[i+2][j] << " " << matrice[i+1][j]<< " " << matrice[i+2][j]<< " "  << endl;
		/*	if(matrice[i][j] > 255 ||matrice[i+1][j] > 255||matrice[i+2][j] > 255){
			cout << matrice[i][j] << " " << matrice[i+1][j]<< " " << matrice[i+2][j]<< " "  << endl;
			      cout << " ============ ERROR ======== "<<endl << i << " "<<j<<endl;
			}*/
			}}
	
	CImg<int> out = ecris_img(matrice, *l, *L);
	save_img(out, "out2.jpg");

	Free(matrice, l);	

  return 0;
}
