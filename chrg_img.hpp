//
//  chrg_img.hpp
//  projetTHS
//
//  Created by Alexandre ROY on 04/01/2016.
//  Copyright © 2016 Alexandre ROY. All rights reserved.
//


#ifndef chrg_img_h
#define chrg_img_h

#include "OutilsLib.h"
#include "BmpLib.h"
#include "BmpLibfri.h"

void cree3matrices(DonneesImageRGB *image, int** rouge, int** vert, int** bleu);

void creeImage(tabRVB tabRVB, int** rouge, int** vert, int** bleu, int x, int y);

//Mise en carré multiple de 8
int** multiple8(DonneesImageRGB *image, int**  matrice, int* largeur, int* hauteur, int* eps);
void charge_img(char *nom_fichier, int ***rouge, int ***vert, int ***bleu, int *largeur, int *hauteur);

#endif /* chrg_img_h */
