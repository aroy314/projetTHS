//
//  image.cpp
//  projetTHS
//
//  Created by Alexandre ROY on 16/11/2015.
//  Copyright © 2015 Alexandre ROY. All rights reserved.
//

#include "image.hpp"

//using namespace std;

class Image {
    
    private :
    int N;  //img squared size
    int **R;//two dimension matrix
    int **G;
    int **B;
    int *Vecteur;//Final 1D Vector
    int **Matrice8x8;//8x8 matrix we work with
    int **Q;//quantification matrix

    void dct_2D(){
        
    }
    
    void initQ(int q) { // Création de la matrice de quantification
        int k,l;
        for(k=0;k<8;k++)					 // parcourt lignes
            for (l=0;l<8;l++)				// parcourt colonnes
                this->Q[k][l] = 1 + ( k + l + 1 ) * q;  // this. permet de rentrer dans l'objet Q ( q = paramètre de compression )
    }
  
    // Application de la phase de quantification sur chacune des matrices
    void Quantif(int ** Obj) {					   // on récupère notre matrice 8x8
        int k,l;
        for(k=0;k<8;k++)					 // parcourt lignes
            for (l=0;l<8;l++)				// parcourt colonnes
                Obj[k][l] = Obj[k][l]/this->Q[k][l];    // divise notre matrice 8x8 par l'objet Q, membre à membre
    }
    
    void charge_img(){
        
    }
    
    public :
    Image(const char * nom_image[]){
        //par richard
        //charge_img();
        //allocation RGB
    }
    
    void traitement(){
        //pour R, G et B :
            //separation de la NN en 8x8 dans matrice8x8
            //dct2D + quantification
            //reecriture dans la NN
    }
    void zigzag(){
        
    }
    
    
    
    
};