//
//  main.cpp
//  projetTHS
//
//  Created by Alexandre ROY on 16/11/2015.
//  Copyright © 2015 Alexandre ROY. All rights reserved.
//

#include <iostream>
#include <math.h>
#include "image.cpp"

using namespace std;

int main(int argc, const char * argv[]) {
    
    //allocation de l'objet image
        //le constructeur charge l'img et alloue les 3 matrices
    Image *image = new Image(argv);
    
    image->traitement();
    
    image->zigzag();
    
    //lancement de la conversion
        //division en matrices 8x8 et pour chacune :
            //DCT_2D();
            //Quantification();
            //réécriture dans la matrice NxN
    
        //ZigZag de la matrice NxN pour obtenir vecteur N^2
    cout << "fin du traitement\n" ;
    delete image;
    
    int a=1;
    int **Matrice = new int*[8];
    for (int i = 0; i < 8; i++)
        Matrice[i] = new int[8];
    
    Image* image= new Image();
    
    
    for (int i=0; i<8; i++)
        for (int j=0; j<8; j++)
            Matrice[i][j]=((i+a));
    
    
    image->dct_2D_V1(Matrice);
    
    
    for (int i=0; i<8; i++)
        for (int j=0; j<8; j++)
        {
            printf("%d ", Matrice[i][j]);
            if(j==7)
            {
                printf("\n");
            }
            
        }
    
    
    return 0;
}
