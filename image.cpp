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

    void dct_2D(){
        
    }
    
    void Quantification(){
        
    }
    
    void charge_img();
    
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