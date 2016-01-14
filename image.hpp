//
//  image.hpp
//  projetTHS
//
//  Created by Alexandre ROY on 16/11/2015.
//  Copyright © 2015 Alexandre ROY. All rights reserved.
//

#ifndef image_hpp
#define image_hpp

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
#include "chrg_img.hpp"
#include "OutilsLib.h"
#include "BmpLib.h"
#include "BmpLibfri.h"

using namespace std;

class Image {
	
	// ------------------- PRIVATE ----------------------
	private :
	// ------------------- ATTRIBUTS --------------------
	int largeur;            //largeur (i)
	int hauteur;			//hauteur (j)
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
	
	// ------------------- FONCTIONS ----------------------
	
	void initQ(int q);
	
	// Application de la phase de quantification sur chacune des matrices
	void quantification(int ** Obj);
	
	// Application de la phase de quantification inverse sur chacune des matrices
	void quantification_inv(int ** Obj);
	
	void dct_2D(int **Matrice8x8);
	
	void dct_2D_Inverse(int **Matrice8x8);
	
	//fonction de recup d'une matrice NxN et allocation de la 8x8 selon des paramètres x,y (haut gauche de la matrice)
	void compression8x8(int x, int y, int **matriceNN, int *Vecteur, int *nbV);
	
	void decompression8x8(int x, int y, int **matriceNN, int* Vecteur, int *nbElem);
	
	void concatVect(int *V1, int *nb_val1, int *V2, int *nb_val2);
	
	void deconcatVect(int *V1, int *nb_val1, int *V2, int *nb_val2);
	
	void suppression_zeros(int *V1, int **V2, int *nb_elem);
	
	void fuuusion(int *R, int nbR, int *G, int nbG, int *B, int nbB, int *V);
	
	void unfuuusion(int *V, int *R, int *nbR, int *G, int *nbG, int *B, int *nbB);
	
	void zigzag(int **Matrice8x8, int *Vect);
	
	void compression_zigzag (int *V1, int *V2, int *nb_elem);
	
	void decompression_zigzag (int *V1, int *V2, const int nb_elem);
	
	void EcritureFinal_jpg(int *Vecteur);
	
	void zigzag_inverse (int ** Obj,int * linea);
	
	void writeVect(int *Vect);
	
	void readVect(int *Vect);
	
	// ------------------- PUBLIC ----------------------
	
	public :
	
	Image(char *nom_fichier);
	
	~Image();
	
	void compression();
	
	void decompression();
};


#endif /* image_hpp */
