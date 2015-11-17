//
//  image.cpp
//  projetTHS
//
//  Created by Alexandre ROY on 16/11/2015.
//  Copyright © 2015 Alexandre ROY. All rights reserved.
//

#include "image.hpp"
#include <math.h>

//using namespace std;

class Image {
    
    private :
    int N;  //img squared size
    int **R;//two dimension matrix
    int **G;
    int **B;
    int *Vecteur;//Final 1D Vector
    int **Matrice8x8;
    
    public :
    
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

    
};






















