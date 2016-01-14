//
//  matrix.h
//  projet_ths
//
//  Created by Clément Bissonnier on 03/12/2015.
//  Copyright © 2015 Clement Bissonnier. All rights reserved.
//

#ifndef matrix_h
#define matrix_h

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "OutilsLib.h"
#include "BmpLib.h"
#include "imageIO.h"


typedef struct tabMatrice tabMatrice;

typedef struct tabVector tabVector;

struct tabMatrice{
    float** tab;                    // Structure pour les tableaux de matrices
};

struct tabVector{
    float vector[64];
    float RLEVector[128];               // Structure pour les tableaux de vecteurs
};



void transposeMatrice( int n, const float matrice[n][n], float matriceTransposee[n][n]);

void tailleMatrice(int*l, int*k);

void saveMatrix(float** const matrix, float** newMatrix);

float** alloueMatrice(int n, int m);

short int ** alloueMatriceInt(int n, int m);

void Matrice(int m, float** matrice);

void affichageMatrice( int n, float** const matrice);

void affichageMatriceInt( int n, short int** const matrice);

void remplissageMatrice( int n, int m, float** const matrice,int k, float** matrice2);

void remplissageMatrice2( int n, int m, const float matrice[n][m],int k, int l, float matrice2[k][l]);

void affichageVector(int n, const float vector[n]);

void affichageTableauMatrice( int n, tabMatrice* matrice, int length);

void decoupeMatrice( int departabs, int departord, float** const matrice, float** petiteMatrice);

void DCT(float** const in, float** out);

void remplissageQ( float Q[8][8], float q);

void quantification(int n, const float Q[8][8], float** matrix);

tabMatrice* rangementMatrice(int n, float** const tab, int* length, const float Q[8][8]);

void readZigzag(int n, float** const matrix, int l, float vector[l]);

void RLEfunction2( int l, const float vector[l], float RLEvector[2*l]);

void reverseRLE( int l, float vector[l], const float RLEvector[2*l]);

void reverseReadZigzag(int n, float** matrix, int l, const float vector[l]);

void reverseQuantification(int n, const float Q[8][8], float** matrix);

void iDCTFunction(float** const in, float** out);

void reverseSegmentation(int n, float** const matrix, float** bigMatrix,int departabs, int departord);

void changeVector( int length, tabVector* myVector, int l, int m, float** bigMatrix, const float Q[8][8]);

void returnBeginning(int m,float** const Matrix, int k, int l, float** OutMatrix);

tabVector* rangementVector( int n, tabMatrice* myMatrix, int length);

int stockData( tabVector* myVector, int n);

tabVector* openData(void);

void freeTab(float** tab, int k);

void freeTabInt2(short int**, int k);

void convert( int n, int m, short int** const matriceDepart, float ** matriceFin);

void convert2( int n, int m, short int** matricefin, float ** const matriceDepart);

void staticToDynamic( int n, int m, short int** const staticMatrix, short int** dynamicMatrix);

float saisieQuantification(void); 

void traitement(int n, int m, short int** matrice, float q);

void copyImage( char* name, float q);

#endif /* matrix_h */
