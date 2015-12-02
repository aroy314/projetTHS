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
    
/*    //allocation de l'objet image
        //le constructeur charge l'img et alloue les 3 matrices
    Image *image = new Image(argv);
	
	//lancement de la conversion
	//division en matrices 8x8 et pour chacune :
	//DCT_2D();
	//Quantification();
	//réécriture dans la matrice NxN
    image->compression();
	
	
    cout << "fin du traitement\n" ;
   */
    

 //   delete image; //liberation memoire
    /*
    int a=1;
    int **Matrice = new int*[8];
    for (int i = 0; i < 8; i++)
        Matrice[i] = new int[8];
    
    
    */
 
    
    
//==============================================================================
//    int **Matrice = new int*[8];
//    for (int i = 0; i < 8; i++)
//        Matrice[i] = new int[8];
//    
//    Matrice[0][0]=140;
//    Matrice[0][1]=144;
//    Matrice[0][2]=147;
//    Matrice[0][3]=140;
//    Matrice[0][4]=140;
//    Matrice[0][5]=155;
//    Matrice[0][6]=179;
//    Matrice[0][7]=175;
//    
//    Matrice[1][0]=144;
//    Matrice[1][1]=152;
//    Matrice[1][2]=140;
//    Matrice[1][3]=147;
//    Matrice[1][4]=140;
//    Matrice[1][5]=148;
//    Matrice[1][6]=167;
//    Matrice[1][7]=179;
//    
//    Matrice[2][0]=152;
//    Matrice[2][1]=155;
//    Matrice[2][2]=136;
//    Matrice[2][3]=167;
//    Matrice[2][4]=163;
//    Matrice[2][5]=162;
//    Matrice[2][6]=152;
//    Matrice[2][7]=172;
//    
//    Matrice[3][0]=168;
//    Matrice[3][1]=145;
//    Matrice[3][2]=156;
//    Matrice[3][3]=160;
//    Matrice[3][4]=152;
//    Matrice[3][5]=155;
//    Matrice[3][6]=136;
//    Matrice[3][7]=160;
//    
//    Matrice[4][0]=162;
//    Matrice[4][1]=148;
//    Matrice[4][2]=156;
//    Matrice[4][3]=148;
//    Matrice[4][4]=140;
//    Matrice[4][5]=136;
//    Matrice[4][6]=147;
//    Matrice[4][7]=162;
//    
//    Matrice[5][0]=147;
//    Matrice[5][1]=167;
//    Matrice[5][2]=140;
//    Matrice[5][3]=155;
//    Matrice[5][4]=155;
//    Matrice[5][5]=140;
//    Matrice[5][6]=136;
//    Matrice[5][7]=162;
//    
//    Matrice[6][0]=136;
//    Matrice[6][1]=156;
//    Matrice[6][2]=123;
//    Matrice[6][3]=167;
//    Matrice[6][4]=162;
//    Matrice[6][5]=144;
//    Matrice[6][6]=140;
//    Matrice[6][7]=147;
//    
//    Matrice[7][0]=148;
//    Matrice[7][1]=155;
//    Matrice[7][2]=136;
//    Matrice[7][3]=155;
//    Matrice[7][4]=152;
//    Matrice[7][5]=147;
//    Matrice[7][6]=147;
//    Matrice[7][7]=136;
//    
//    int **R = new int*[8];
//    for (int i = 0; i < 8; i++)
//        R[i] = new int[8];
//    
//    int **G = new int*[8];
//    for (int i = 0; i < 8; i++)
//        G[i] = new int[8];
//    
//    int **B = new int*[8];
//    for (int i = 0; i < 8; i++)
//        B[i] = new int[8];
//    
//
//    image->separate_RGB(Matrice, 8, R, G, B);
//    
//    
//    for (int i=0; i<8; i++)
//        for (int j=0; j<8; j++)
//        {
//            printf("%d ", R[i][j]);
//            if(j==7)
//            {
//                printf("\n");
//            }
//            
//        }
//     printf("\n");
//     printf("\n");
//    
//    for (int i=0; i<8; i++)
//        for (int j=0; j<8; j++)
//        {
//            printf("%d ", G[i][j]);
//            if(j==7)
//            {
//                printf("\n");
//            }
//            
//        }
//    
//     printf("\n");
//     printf("\n");
//    for (int i=0; i<8; i++)
//        for (int j=0; j<8; j++)
//        {
//            printf("%d ", B[i][j]);
//            if(j==7)
//            {
//                printf("\n");
//            }
//            
//        }
//    
//    
    
    
//==============================================================================
  
    Image *image = new Image(argv);
    int *x=new int;
    
    
    int *comp=new int[128];
    int matrice[64]={1,1,1,4,5,3,3,7,10,5,5,5,5,5,5,5,5,5,5,5,0,0,0,2,2,1,1,1,4,5,3,3,7,10,5,5,5,5,5,5,5,5,5,5,5,0,0,0,2,2,0,0,0,2,2,0,0,0,2,2,0,0,0,2};
    int *matrice2=new int[64];
    
    image->compression_zigzag(matrice, comp, x);
    printf("X ------->  %d", *x);
    printf("X ------->  %d", *comp);
    for (int i=0;i<x[0]; i++)
    printf("  %d  ", comp[i]);
    image->decompression_zigzag(matrice2, comp, x);
    
    printf("\n x----->   %d  \n ", x[0]);
 //==============================================================================
    
    return 0;
}
