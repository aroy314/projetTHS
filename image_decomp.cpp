//
//  image.cpp
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

#define FNAME "/Volumes/Macintosh HD/Users/AlexandreROY/CloudStation/ISEN/M1/Projet THS/projetTHS/gestionImage/fichier.txt"

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
        std::cout << "quantification inverse faite\n";
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
		
		cout << "DCT2D inverse faite\n";

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
	
	void Image_decomp::unfuuusion(int *V, int *R, int *nbR, int *G, int *nbG, int *B, int *nbB){	//Separation de V en R/G/B
		
		int i=1, cpt=0;//compteur de case et compteur cumulé
		//sauvegarde de pointeur
		int *SVG = V;

		//check du bon nombre de valeurs à prendre
		*nbR = V[0];
		//recup de R
		while(cpt < *nbR){
			R[i]	= V[i];
			R[i+1]	= V[i+1];
			cpt += V[i];
			i += 2;
		}
		//reinit de cpt
		cpt = 0;
		//decalage de V puis réinit de i
		V = V+i;
		i = 1;
		//check du bon nombre de valeurs à prendre
		*nbG = V[0];
		//recup de G
		while(cpt < *nbG){
			G[i]	= V[i];
			G[i+1]	= V[i+1];
			cpt	+= V[i];
			i	+= 2;
		}
		//reinit de cpt
		cpt = 0;
		//decalage de V puis réinit de i
		V = V+i;
		i = 1;
		//check du bon nombre de valeurs à prendre
		*nbB = V[0];
		//recup de G
		while(cpt < *nbB){
			B[i]	= V[i];
			B[i+1]	= V[i+1];
			cpt += V[i];
			i += 2;
		}
		//recup du bon pointeur sur V
		V = SVG;
		
		cout << "unfuuusion fait" << endl;
	}

	// ------------------- PUBLIC ----------------------

    Image_decomp::Image_decomp(){ //CONSTRUCTEUR
	    //faire le constructeur ici
        

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

	void Image_decomp::decompression(){	//compression à l'envers
		//readVect(this->Vecteur);
		cout << " chargé en mémoire" << endl;
		
		//Separation de this->vecteur en vecteurs R/G/B
		//entier indiquant le nb de val de chaque vecteur
		int nbR=0, nbG=0, nbB=0;
		unfuuusion(this->Vecteur,this->VecteursR,&nbR,this->VecteursG,&nbG,this->VecteursB,&nbB);
		
		//repartition de chaque vecteursRGB dans des vecteurs 88 puis mise en matrice et traitement
		for(int i=0;i<this->largeur/8;i++)
			for(int j=0;j<this->hauteur/8;j++){
				decompression8x8(i*8,j*8,this->R,this->VecteursR,&nbR);
				decompression8x8(i*8,j*8,this->G,this->VecteursG,&nbG);
				decompression8x8(i*8,j*8,this->B,this->VecteursB,&nbB);
			}
		
		cout << "decompression faite" << endl;
	}

