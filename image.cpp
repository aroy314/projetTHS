//
//  image.cpp
//  projetTHS
//
//  Created by Alexandre ROY on 16/11/2015.
//  Copyright © 2015 Alexandre ROY. All rights reserved.
//

#include <iostream>
#include "image.hpp"
#include <math.h>

using namespace std;

class Image {
    
    private :
    int taille;             //img squared size
    int **image = NULL;     //image de base
    int **R = NULL;         //two dimensions matrix
    int **G = NULL;
    int **B = NULL;
    int *VecteursR = NULL;  //Vector R G and B compressed
	int *VecteursG = NULL;
	int *VecteursB = NULL;
	int *Vecteur	= NULL; // FINAL VECTOR TO WRITE ON DISK
	int *Vecteur128 = NULL; // Vector compressed from Matrix8x8
    int **Matrice8x8 = NULL;//8x8 matrix we work with
    int **Q = NULL;         //quantification matrix

    
    void initQ(int q){			// Création de la matrice de quantification
        int k,l;
        for(k=0;k<8;k++){        // parcourt lignes
            for (l=0;l<8;l++){   // parcourt colonnes
                this->Q[k][l] = 1 + ( k + l + 1 ) * q;  // this-> permet de rentrer dans l'objet Q ( q = paramètre de compression )
			}
        }
        cout << "Q initialisée\n";
    }
    
    // Application de la phase de quantification sur chacune des matrices
    void quantification(int ** Obj) {					   // on récupère notre matrice 8x8
        int k,l;
        for(k=0;k<8;k++)					 // parcourt lignes
            for (l=0;l<8;l++)				// parcourt colonnes
                Obj[k][l] = Obj[k][l]/this->Q[k][l];    // divise notre matrice 8x8 par l'objet Q, membre à membre
        
        std::cout << "quantification faite\n";

    }
    
        // Application de la phase de quantification inverse sur chacune des matrices
    void Quantification_inv(int ** Obj) {					   // on récupère notre matrice 8x8
        int k,l;
        for(k=0;k<8;k++)					 // parcourt lignes
            for (l=0;l<8;l++)				// parcourt colonnes
                Obj[k][l] = Obj[k][l]*this->Q[k][l];    // multiplie notre matrice 8x8 par l'objet Q, membre à membre
        std::cout << "quantification inverse faite\n";
    }
    

    
    
//    void dct_2D(int **Matrice8x8)
//    {
//        void charge_img(const char * nom_image[], int *taille){
//        //lecture du fichier et attribution dans image NN, et envoi de la taille dans *taille
//		cout << "image chargée \n";
//    }
	
    void dct_2D(int **Matrice8x8){
		
		//allocation d'une matrice de travail
        int **Matrice_dct = new int*[8];
        for (int i = 0; i < 8; i++)
            Matrice_dct[i] = new float[8];
        
        float Ci;
        float Cj;
        
        for (int i=0; i<8; i++)
            for (int j=0; j<8; j++){
				Matrice_dct[i][j] = 0;
                for (int x=0; x<8; x++)
                    for (int y=0; y<8; y++)
                    {
                        (i==0) ? Ci=1/sqrt(2): Ci=1;
                        (j==0) ? Cj=1/sqrt(2): Cj=1;
                        
                        Matrice_dct[i][j] += Matrice8x8[x][y]*(Ci*Cj)/4*cos(((2*x+1)*i*M_PI)/16)*cos(((2*y+1)*j*M_PI)/16);
                    }
            }
        
        
        for (int i=0; i<8; i++)//arondicement des valeurs
            for (int j=0; j<8; j++)
            {
                Matrice8x8[i][j]=Matrice_dct[i][j];
            }
        
//        for (int i=0; i<8; i++)//arondicement des valeurs
//            for (int j=0; j<8; j++)
//            {
//                if(Matrice_dct[i][j]>0)
//                    (Matrice_dct[i][j]-(int)Matrice_dct[i][j]>0.5)?Matrice8x8[i][j]=(int)Matrice_dct[i][j]+1:
//                        Matrice8x8[i][j]=Matrice_dct[i][j];
//                else
//                    (Matrice_dct[i][j]-(int)Matrice_dct[i][j]>-0.5)?Matrice8x8[i][j]=(int)Matrice_dct[i][j]+1:
//                    Matrice8x8[i][j]=Matrice_dct[i][j];
//            }
    
        }
    
    
    
    void dct_2D_Inverse(int **Matrice8x8)
    {
        float **Matrice_dct = new float*[8];
        for (int i = 0; i < 8; i++)
            Matrice_dct[i] = new float[8];
        
        float Cx;
        float Cy;
        
        for (int i=0; i<8; i++)
            for (int j=0; j<8; j++)
            {    Matrice_dct[i][j] = 0;
                for (int x=0; x<8; x++)
                  for (int y=0; y<8; y++)
                    {
                        (x==0) ? Cx=1/sqrt(2): Cx=1;
                        (y==0) ? Cy=1/sqrt(2): Cy=1;
                        
                        Matrice_dct[i][j]+=(1/sqrt(16))*(Matrice8x8[x][y]*Cx*Cy*cos(((2*i+1)*x*M_PI)/16)*cos(((2*j+1)*y*M_PI)/16));
                    }
            }
        
        
//        
//        for (int i=0; i<8; i++)//arondicement des valeurs
//            for (int j=0; j<8; j++)
//            {
//                if(Matrice_dct[i][j]>0)
//                    (Matrice_dct[i][j]-(int)Matrice_dct[i][j]>0.5)?Matrice8x8[i][j]=(int)Matrice_dct[i][j]+1:
//                    Matrice8x8[i][j]=Matrice_dct[i][j];
//                else
//                    (Matrice_dct[i][j]-(int)Matrice_dct[i][j]>-0.5)?Matrice8x8[i][j]=(int)Matrice_dct[i][j]+1:
//                    Matrice8x8[i][j]=Matrice_dct[i][j];
//            }
		
		//à optimiser et garder seulement la matrice passée en paramètre
        for (int i=0; i<8; i++)
            for (int j=0; j<8; j++)
                Matrice8x8[i][j] = Matrice_dct[i][j];
		
		cout << "DCT2D faite\n";

    }

    
    
    public :
    Image(const char * nom_image[]){ //CONSTRUCTEUR
		
		//chargement de l'image et attribution de la taille de la matrice NN
		charge_img(nom_image,&this->taille);
		
        //allocation des attributs
        this->image = new int *[3*this->taille];
        this->R     = new int *[this->taille];
        this->G     = new int *[this->taille];
        this->B     = new int *[this->taille];
		
		for (int i=0;i<3*this->taille;i++) {
			this->image[i] = new int[this->taille];
		}
		
        for (int i=0;i<this->taille;i++) {
            this->R[i]     = new int[this->taille];
            this->G[i]     = new int[this->taille];
            this->B[i]     = new int[this->taille];
        }
		
        this->Matrice8x8 = new int *[8];
        this->Q = new int *[8];
        for (int i=0;i<8;i++) {
            this->Matrice8x8[i] = new int[8];
            this->Q[i] = new int[8];
			
        }
		
		this->Vecteur128	= new int[128];
		this->VecteursR		= new int[2*this->taille*this->taille];
		this->VecteursG		= new int[2*this->taille*this->taille];
		this->VecteursB		= new int[2*this->taille*this->taille];
		this->Vecteur		= new int[6*this->taille*this->taille+3]; //contiens les vect RGB + nb de val dans chacun à chaque debut de vect
		
		//attribution des matrices RGB selon la matrice image
		
        //calcul de Q
        int q;
        
        this->Q = new int*[8]; //init Matrice Q
        for (int i = 0; i < 8; i++)
            Q[i] = new int[8];
        
        
        cout << "Entrez le paramètre de compression : ";
        cin >> q;
        initQ(q);
        
        cout << "construction faite\n";

    }
    
    ~Image(){ //DESTRUCTEUR
		//destruction des attributs
		
		for (int i=0;i<this->taille;i++) {
			delete this->R[i];
			delete this->G[i];
			delete this->B[i];
		}
		
		for (int i=0;i<this->taille*3;i++) {
			delete this->image[i];
		}
		
		delete this->image;
		delete this->R;
		delete this->G;
		delete this->B;
		
		for (int i=0;i<8;i++) {
			delete this->Matrice8x8[i];
			delete this->Q[i];
		}
		
		delete this->Matrice8x8;
		delete this->Q;
		
		delete this->VecteursR;
		delete this->VecteursG;
		delete this->VecteursB;
		delete this->Vecteur;
		delete this->Vecteur128;

		
		cout << "destruction faite\n";
		}
	
	//fonction de recup d'une matrice NxN et allocation de la 8x8 selon des paramètres x,y (haut gauche de la matrice)
	void compression8x8(int x, int y, int **matriceNN, int* Vecteur){
		//recup de la 8x8
		for(int i=0;i<8;i++)
			for(int j=0;j<8;j++)
				this->Matrice8x8[i][j] = matriceNN[x+i][y+j];
		
		//traitement et compression
		dct_2D(this->Matrice8x8);
		quantification(this->Matrice8x8);
		
		//besoin d'un int pour savoir ou on en est dans le vecteur global R/G/B qu'on nomme position
		int position = 0;
		int *Vect_temp = new int[128];
		zigzag(this->Matrice8x8, Vect_temp);
		compression_zigzag(Vect_temp,this->Vecteur128,&position);
		delete Vect_temp;
		
		//suppression des 0 et raccourcissement du vecteur de taille size
		int size_vect = 0;
		int *Vect_temp2 = new int[size_vect];
		//raccourcissement(&size_vect, );
		
		//ecriture du vecteur128 dans le vecteur correspondant
		
		for(int i=0;i<size_vect;i++)
			Vecteur[position + i] = Vect_temp2[i];
		
	}
	
	void decompression8x8(int x, int y, int **matriceNN, int* Vecteur){
		
	}
	
    void compression(){
		
		if(this->taille%8==0)//test tout bête
			cout << "Erreur dans la taille des matrices : pas multiple de 8";
		
        //pour R, G et B :
			for(int i=0;i<this->taille/8;i++)
				for(int j=0;j<this->taille/8;j++){
					compression8x8(i*8,j*8,this->R,this->VecteursR);
					compression8x8(i*8,j*8,this->G,this->VecteursG);
					compression8x8(i*8,j*8,this->B,this->VecteursB);
				}
        
        cout << "compression faite\n";
    }
	
	void decompression(){
		
		cout << "decompression faite\n";
		
	}
	
    void zigzag(int **Matrice8x8, int *Vect){//poisson
        //lecture de la 88 image
        //ecriture de Vecteur avec la lecture en zigzag
        
        cout << "ZigZag fait\n";
        
    }
    
    
    
    void EcritureFinal_jpg(int *Vecteur){//Dosda
        //Ecriture fichier en jpg
        
        std::cout << "ZigZag fait\n";
        
    }
    

    void zigzag_inverse (int * linea, int ** Obj) {

int pos;	
int k,l;	// k indices lignes, l indice colonnes



for (int i=0 ; i<8 ;i++) {
	for ( int j=0 ; j<8 ; j++) {
	
		Obj[i][j] = 0;		// on rempli notre tableau de 0
	}
}


while ((k!=7)||(l!=7))			// tant qu'on n'est pas arrivé au dernier élément de la matrice
{	
	while((k!=0)&&(l!=7))		// tant qu'on n'est pas à la fin de la première ligne de la matrice
	{
		Obj[k][l]=linea[pos++];		// on récupère dans la matrice l'élément correspondant de la linéarisation
		k--;				// on décrémente les lignes
		l++;				// on incrémente les colonnes
	}				// --> diago croissante
	Obj[k][l]=linea[pos++];		// on récupère à nouveau l'élément de linéarisation dans la matrice 
		if(l==7)
		k++;
		else
		l++;
	while((k!=7)&&(l!=0))		// tant qu'on n'est pas au début de la dernière ligne de la matrice
	{	
		Obj[k][l]=linea[pos++];		// on récupère dans la matrice l'élément correspondant de la linéarisation
		k++;				// on décrémente les lignes
		l--;				// on incrémente les colonnes
	}				// --> diago décroissante
	Obj[k][l]=linea[pos++];		// on récupère à nouveau l'élément de linéarisation dans la matrice 
		if(k==7)		
		l++;
		else
		k++;
}

Obj[k][l]=linea[pos];

}

	void zigzag_inverse(int **Matrice8x8, int *Vect){//mathilde
		//lecture du vecteur compressé
		//ecriture d'une matrice 88
		int pos;	
int k,l;	// k indices lignes, l indice colonnes



for (int i=0 ; i<8 ;i++) {
	for ( int j=0 ; j<8 ; j++) {
	
		Obj[i][j] = 0;		// on rempli notre tableau de 0
	}
}


while ((k!=7)||(l!=7))			// tant qu'on n'est pas arrivé au dernier élément de la matrice
{	
	while((k!=0)&&(l!=7))		// tant qu'on n'est pas à la fin de la première ligne de la matrice
	{
		Obj[k][l]=linea[pos++];		// on récupère dans la matrice l'élément correspondant de la linéarisation
		k--;				// on décrémente les lignes
		l++;				// on incrémente les colonnes
	}				// --> diago croissante
	Obj[k][l]=linea[pos++];		// on récupère à nouveau l'élément de linéarisation dans la matrice 
		if(l==7)
		k++;
		else
		l++;
	while((k!=7)&&(l!=0))		// tant qu'on n'est pas au début de la dernière ligne de la matrice
	{	
		Obj[k][l]=linea[pos++];		// on récupère dans la matrice l'élément correspondant de la linéarisation
		k++;				// on décrémente les lignes
		l--;				// on incrémente les colonnes
	}				// --> diago décroissante
	Obj[k][l]=linea[pos++];		// on récupère à nouveau l'élément de linéarisation dans la matrice 
		if(k==7)		
		l++;
		else
		k++;
}

Obj[k][l]=linea[pos];
		
		
		cout << "ZigZag Inverse fait\n";
		
	}
	
	void compression_zigzag(int *V1, int* V2, int *position){//V1 vecteur non compressé, V2 vecteur non compressé, position = nombre de cases
		
	}
	
	void decompression_zigzag(int *V1, int* V2){
		
	}


};

