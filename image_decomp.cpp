//
//  image_decomp.cpp
//  projetTHS
//
//  Created by Alexandre ROY on 16/11/2015.
//  Copyright © 2015 Alexandre ROY. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "image_decomp.hpp"

#define FMATRIX "/Volumes/Macintosh HD/Users/AlexandreROY/CloudStation/ISEN/M1/Projet THS/projetTHS/gestionImage/fichier.txt"
#define FMATRIX2 "/Volumes/Macintosh HD/Users/AlexandreROY/CloudStation/ISEN/M1/Projet THS/projetTHS/gestionImage/fichier2.txt"
#define FVECTOR "/Volumes/Macintosh HD/Users/AlexandreROY/CloudStation/ISEN/M1/Projet THS/projetTHS/CompressedVector.txt"

using namespace std;
	// ------------------- FONCTIONS ----------------------
    
	void Image_decomp::initQ(int q){			// Création de la matrice de quantification
        int k,l;
        for(k=0;k<8;k++){        // parcourt lignes
            for (l=0;l<8;l++){   // parcourt colonnes
                this->Q[k][l] = 1 + ( k + l + 1 ) * q;  // this-> permet de rentrer dans l'objet Q ( q = paramètre de compression )
			}
        }
        cout << "Q initialisée\n";
    }

    // Application de la phase de quantification inverse sur chacune des matrices
    void Image_decomp::quantification_inv(int ** Obj) {	// on récupère notre matrice 8x8
        int k,l;
        for(k=0;k<8;k++)					// parcourt lignes
            for (l=0;l<8;l++)				// parcourt colonnes
                Obj[k][l] = (int) (Obj[k][l]*this->Q[k][l]);    // multiplie notre matrice 8x8 par l'objet Q, membre à membre
        //cout << "quantification inverse faite\n";
    }

    void Image_decomp::dct_2D_Inverse(int **Matrice8x8){
        float **Matrice_dct = new float*[8];
        for (int i = 0; i < 8; i++)
            Matrice_dct[i] = new float[8];
		
        float Cx;
        float Cy;
		
        for (int i=0; i<8; i++)
            for (int j=0; j<8; j++){
				Matrice_dct[i][j] = 0;
                for (int x=0; x<8; x++)
                  for (int y=0; y<8; y++){
                        (x==0) ? Cx=1/sqrt(2): Cx=1;
                        (y==0) ? Cy=1/sqrt(2): Cy=1;
                        Matrice_dct[i][j]+=(1/sqrt(16))*(Matrice8x8[x][y]*Cx*Cy*cos(((2*i+1)*x*M_PI)/16)*cos(((2*j+1)*y*M_PI)/16));
                    }
            }
		
        for (int i=0; i<8; i++)
            for (int j=0; j<8; j++)
                Matrice8x8[i][j] = Matrice_dct[i][j];
		
		//cout << "DCT2D inverse faite\n";

    }

	void Image_decomp::zigzag_inverse (int ** Obj,int * linea) {
		
		int pos=0;
		int k=0,l=0;	// k indices lignes, l indice colonnes
		
		for (int i=0 ; i<8 ;i++)
			for ( int j=0 ; j<8 ; j++)
				Obj[i][j] = 0;		// on rempli notre tableau de 0
		
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
		//cout << "ZigZag Inverse fait\n";
	}

	void Image_decomp::decompression_zigzag (int *V1, int *V2, const int nb_elem)//V1 compressé, V2 décompressé de taille 64, nombre d'elem dans le vecteur
	{
		int p = 0;
		
		for (int i=0; i<nb_elem ; i++) //Reatribue les valeurs de base de la matrice 64
			if (i%2==0)
				for (int j=0; j<V2[i]; j++)
					V1[p++]=V2[i+1];
	}

	void Image_decomp::decompression8x8(int x, int y, int **matriceNN, int* Vecteur, int *nbElem){
		int *Vect_temp = new int[64];
		int nbIn = 0;
		//on recupère this->vecteur128 compressé issu de vecteurRGB
		deconcatVect(Vecteur, nbElem, this->Vecteur128, &nbIn);
		
		//on decompresse this->Vecteur128
		decompression_zigzag(this->Vecteur128, Vect_temp, nbIn);
		
		//on le met dans une matrice avec zigzag et on complete de 0
		zigzag_inverse(this->Matrice8x8, Vect_temp);
		delete Vect_temp;
		
		//on effectue la quantif inverse + la dct inverse
		dct_2D_Inverse(this->Matrice8x8);
		quantification_inv(this->Matrice8x8);
		
		//on écrit la 8x8 au bon endroit dans la NxN
		for(int i=0;i<8;i++)
			for(int j=0;j<8;j++)
				matriceNN[x+i][y+j] = this->Matrice8x8[i][j];
	}

    void Image_decomp::deconcatVect(int *V1, int *nb_val1, int *V2, int *nb_val2){ //on attribue un vecteur issu de V1 à V2, et on slide le V1 vers la gauche du nb de valeurs récupérées
		
		int i=1, cpt=0;//compteur de case et compteur cumulé
		//check du bon nombre de valeurs à prendre
		*nb_val2 = V1[0];
		
		while(cpt < *nb_val2){
			V2[i] = V1[i];
			V2[i+1] = V1[i+1];
			cpt += V1[i];
			i += 2;
		}
		//on décale V1 vers la gauche de i cases en arithmétique de pointeur
		V1 = V1+i;
	}
	
	void Image_decomp::unfuuusion(int *V, int **R, int *nbR, int **G, int *nbG, int **B, int *nbB){	//Separation de V en R/G/B
		
		int i=0, j=1, cpt=0;//compteur de case V, de cases RGB et compteur cumulé

		//check du bon nombre de valeurs à prendre
		*nbR = V[0];
		//recup de R
		while(cpt < *nbR){
			copy(V+j, V+j+2, *R+i);
//			(*R[i])	= V[j];
//			(*R[i+1]) = V[j+1];
			//test
//			if(*R[i] != V[j] || *R[i+1] != V[j+1]){
//				cout << "Erreur egalité : " << i << "," << j << " " << *R[i] << "!=" << V[j] << " et " << *R[i+1] << "!=" << V[j+1] << endl;
//			}
			//fintest
			cpt += V[j];
			i += 2;
			j += 2;
		}
		//reinit de cpt
		cpt = 0;
		//réinit de i
		i = 0;
		//check du bon nombre de valeurs à prendre
		*nbG = V[j];
		j++;
		//recup de G
		while(cpt < *nbG){
			copy(V+j, V+j+2, *G+i);
			//test
//			if(*G[i]	!= V[j] || *G[i+1] != V[j+1])
//				cout << "Erreur egalité : " << i << "," << j << endl;
			//fintest
			cpt	+= V[j];
			i += 2;
			j += 2;
		}
		//reinit de cpt
		cpt = 0;
		//réinit de i
		i = 0;
		//check du bon nombre de valeurs à prendre
		*nbB = V[j];
		j++;
		//recup de G
		while(cpt < *nbB){
			copy(V+j, V+j+2, *B+i);
			//test
//			if(*B[i]	!= V[j] || *B[i+1] != V[j+1])
//				cout << "Erreur egalité : " << i << "," << j << endl;
			//fintest
			cpt += V[j];
			i += 2;
			j += 2;
		}
		
		cout << "unfuuusion fait" << endl;
	}

void Image_decomp::readVect(int** Vect, int* largeur, int* hauteur, int* q){
	
	//Vector --> Matrice
	FILE *vector = fopen (FVECTOR, "r" );
	if (vector == NULL){
		perror (FVECTOR);
	}
	else
	{
		int i=0;
		fscanf(vector, "%d %d %d\n", largeur, hauteur, q);
		*Vect = new int[6*(*largeur)*(*hauteur)+3];
		cout << "l,h,q : " << *largeur << " " << *hauteur << " " << *q << endl;
		cout << 6*(*largeur)*(*hauteur) << endl;
		for(i = 0; i < 6*(*largeur)*(*hauteur)+3; i++){
			if (!fscanf(vector, "%d ", *Vect+i))
				break;
			if(i%2==0 && *(*Vect+i)!=0)
				cout << *(*Vect+i) << " " << *(*Vect+i+1) << " ";
		}
		cout << endl;
	}
	fclose(vector);
}

	// ------------------- PUBLIC ----------------------

    Image_decomp::Image_decomp(){ //CONSTRUCTEUR
		cout << "construction de Image_decomp...\n";
		//lecture du fichier, alloc de Vecteur, largeur, hauteur et q
		readVect(&this->Vecteur,&this->largeur,&this->hauteur,&this->q);
		
		//alloc des paramètres
		this->R     = new int *[this->largeur];
		this->G     = new int *[this->largeur];
		this->B     = new int *[this->largeur];
		for (int i=0;i<this->largeur;i++) {
			this->R[i]     = new int[this->hauteur];
			this->G[i]     = new int[this->hauteur];
			this->B[i]     = new int[this->hauteur];
		}

		this->Matrice8x8 = new int *[8];
		this->Q = new int *[8];
		for (int i=0;i<8;i++) {
			this->Matrice8x8[i] = new int[8];
			this->Q[i] = new int[8];
		}
		
		this->Vecteur128	= new int[128];
		this->VecteursR		= new int[2*this->largeur*this->hauteur];
		this->VecteursG		= new int[2*this->largeur*this->hauteur];
		this->VecteursB		= new int[2*this->largeur*this->hauteur];

        this->Q = new int*[8]; //init Matrice Q
        for (int i = 0; i < 8; i++)
            Q[i] = new int[8];
		
        initQ(this->q);
        cout << "construction faite\n";
    }
    
    Image_decomp::~Image_decomp(){ //DESTRUCTEUR
		//destruction des attributs
		
		for (int i=0;i<this->largeur;i++) {
			delete this->R[i];
			delete this->G[i];
			delete this->B[i];
		}
		
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

	void Image_decomp::decompression(){	//compression à l'envers avec fonctions inverses
		
		//Separation de this->vecteur en vecteurs R/G/B
		//entier indiquant le nb de val de chaque vecteur
		int nbR=0, nbG=0, nbB=0;
		unfuuusion(this->Vecteur,&this->VecteursR,&nbR,&this->VecteursG,&nbG,&this->VecteursB,&nbB);
		
		//test affichage de Vect R G et B
		cout << endl << "nb cases R G B : " <<  nbR << " " << nbG << " " << nbB << endl;
		int cpt1=0;
		int cpt2=0;
		cout << endl << "Vecteur R : " << endl;
		while(cpt2<nbR){
			cout << this->VecteursR[cpt1] << " " << this->VecteursR[cpt1] << " ";
			cpt2+=this->VecteursR[cpt1];
			cpt1+=2;
		}
		cpt1=0;
		cpt2=0;
		cout << endl << "Vecteur G : " << endl;
		while(cpt2<nbG){
			cout << this->VecteursG[cpt1] << " " << this->VecteursG[cpt1] << " ";
			cpt2+=this->VecteursG[cpt1];
			cpt1+=2;
		}
		cpt1=0;
		cpt2=0;
		cout << endl << "Vecteur B : " << endl;
		while(cpt2<nbB){
			cout << this->VecteursB[cpt1] << " " << this->VecteursB[cpt1] << " ";
			cpt2+=this->VecteursB[cpt1];
			cpt1+=2;
		}

		//fin test affichage
		
		//repartition de chaque vecteursRGB dans des vecteurs 88 puis mise en matrice et traitement
		for(int i=0;i<this->largeur/8;i++)
			for(int j=0;j<this->hauteur/8;j++){
				decompression8x8(i*8,j*8,this->R,this->VecteursR,&nbR);
				decompression8x8(i*8,j*8,this->G,this->VecteursG,&nbG);
				decompression8x8(i*8,j*8,this->B,this->VecteursB,&nbB);
			}
		
		//ecriture de la matrice dans un fichier
		//Matrice --> Fichier
		FILE *fmatrix2 = fopen (FMATRIX2, "w" );
		if (fmatrix2 == NULL){
			perror (FMATRIX2);
		}
		else {
			int i=0;
			int j=0;
			//ecriture entete
			fprintf (fmatrix2, "%d,%d,\n", this->largeur,this->hauteur);
			for (i = 0; i < this->largeur; i++)	{
				for (j = 1; j < this->hauteur; j++)	{
					fprintf (fmatrix2, "%d,", this->R[i][j]);
					fprintf (fmatrix2, "%d,", this->G[i][j]);
					fprintf (fmatrix2, "%d,", this->B[i][j]);
				}
				fprintf (fmatrix2, "\n" );
			}
			fclose(fmatrix2);
		}
		cout << "decompression faite" << endl;
	}

