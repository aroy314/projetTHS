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

//using namespace std;

class Image {
    
    private :
    int N;  //img squared size
    int **image; //image de base
    int **R;//two dimension matrix
    int **G;
    int **B;
    int *Vecteur;//Final 1D Vector
    int **Matrice8x8;//8x8 matrix we work with
    int **Q;//quantification matrix

    void dct_2D(){//dosda
        
    }
    
    void initQ(int q) { // Création de la matrice de quantification
        int k,l;
        for(k=0;k<8;k++){					 // parcourt lignes
            for (l=0;l<8;l++){				// parcourt colonnes
                this->Q[k][l] = 1 + ( k + l + 1 ) * q;  // this. permet de rentrer dans l'objet Q ( q = paramètre de compression )
                std::cout << this->Q[k][l] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << "Q initialisée\n";
    }
  
    // Application de la phase de quantification sur chacune des matrices
    void Quantif(int ** Obj) {					   // on récupère notre matrice 8x8
        int k,l;
        for(k=0;k<8;k++)					 // parcourt lignes
            for (l=0;l<8;l++)				// parcourt colonnes
                Obj[k][l] = Obj[k][l]/this->Q[k][l];    // divise notre matrice 8x8 par l'objet Q, membre à membre
        std::cout << "quantification faite\n";
    }
    
    void charge_img(){
        //lecture du fichier et attribution dans image NN
    }
    
    
    
    
    void dct_2D_V1(int **Matrice8x8)
    {
        int **Matrice_dct = new int*[8];
        for (int i = 0; i < 8; i++)
            Matrice_dct[i] = new int[8];
        
        float Ci;
        float Cj;
        
        for (int i=0; i<8; i++)
            for (int j=0; j<8; j++)
            {    Matrice_dct[i][j] = 0;
                for (int x=0; x<8; x++)
                    for (int y=0; y<8; y++)
                    {
                        if (i==0)
                            Ci=1/sqrt(2);
                        else Ci=1;
                        
                        if (j==0)
                            Cj=1/sqrt(2);
                        else Cj=1;
                        
                        Matrice_dct[i][j]+=Matrice8x8[x][y]*(Ci*Cj)/4*cos(((2*x+1)*i*M_PI)/16)*cos(((2*y+1)*j*M_PI)/16);
                    }
                
            }
        
        for (int i=0; i<8; i++)
            for (int j=0; j<8; j++)
                Matrice8x8[i][j]=Matrice_dct[i][j];
        
        
    }
    
    
    
    public :
    Image(const char * nom_image[]){ //CONSTRUCTEUR
        
        //allocation
/*
        exemple d'allocation de tableau 2D
        int **R = new int*[8];
        for (int i = 0; i < 8; i++)
            Matrice[i] = new int[8];
        */
        
        //charge_img() et allocation RGB
        //calcul de Q
        int q;
        std::cout << "Entrez le paramètre de compression : ";
        std::cin >> q;
        initQ(q);
        
        std::cout << "construction faite\n";
    }
    
    void traitement(){
        //pour R :
            //separation de la NN en 8x8 dans matrice8x8
            //dct2D + quantification
            //reecriture dans la NN
        //pour G :
            //separation de la NN en 8x8 dans matrice8x8
            //dct2D + quantification
            //reecriture dans la NN
        //pour B :
            //separation de la NN en 8x8 dans matrice8x8
            //dct2D + quantification
            //reecriture dans la NN
        //reunion des 3 matrices dans image
        
        std::cout << "traitement fait\n";
        
    }
    void zigzag(){//poisson
        //lecture de la NN image
        //ecriture de Vecteur avec la lecture en zigzag
        
        std::cout << "ZigZag fait\n";
        
    }
    

    
};






















