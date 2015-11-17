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
    int taille;             //img squared size
    int **image = NULL;     //image de base
    int **R = NULL;         //two dimension matrix
    int **G = NULL;
    int **B = NULL;
    int *Vecteur = NULL;    //Final 1D Vector
    int **Matrice8x8 = NULL;//8x8 matrix we work with
    int **Q = NULL;         //quantification matrix
    
    void initQ(int q) { // Création de la matrice de quantification
        int k,l;
        for(k=0;k<8;k++){        // parcourt lignes
            for (l=0;l<8;l++){   // parcourt colonnes
                this->Q[k][l] = 1 + ( k + l + 1 ) * q;  // this-> permet de rentrer dans l'objet Q ( q = paramètre de compression )
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
    
        // Application de la phase de quantification inverse sur chacune des matrices
    void Quantification_inv(int ** Obj) {					   // on récupère notre matrice 8x8
        int k,l;
        for(k=0;k<8;k++)					 // parcourt lignes
            for (l=0;l<8;l++)				// parcourt colonnes
                Obj[k][l] = Obj[k][l]*this->Q[k][l];    // multiplie notre matrice 8x8 par l'objet Q, membre à membre
        std::cout << "quantification inverse faite\n";
    }
    
    void charge_img(const char * nom_image[], int *taille){
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
        
        charge_img(nom_image,&this->taille);
        
        //allocation des attributs
        this->image = new int *[this->taille];
        this->R     = new int *[this->taille];
        this->G     = new int *[this->taille];
        this->B     = new int *[this->taille];
		
        for (int i=0;i<this->taille;i++) {
            this->image[i] = new int[this->taille];
            this->R[i]     = new int[this->taille];
            this->G[i]     = new int[this->taille];
            this->B[i]     = new int[this->taille];
        }
		
        this->Matrice8x8 = new int *[8];
        this->Q = new int *[8];
        for (int i=0;i<8;i++) {
            this->Matrice8x8[i] = new int[8];
            this->Q[i] = new int[8];
        }
		this->Vecteur = new int[this->taille * this->taille];

		//attribution des matrices RGB selon la matrice image
		
		
        //calcul de Q
        int q;
        std::cout << "Entrez le paramètre de compression : ";
        std::cin >> q;
        initQ(q);
        
        std::cout << "construction faite\n";
    }
    
    ~Image(){ //DESTRUCTEUR
		//destruction des attributs
		
		for (int i=0;i<this->taille;i++) {
			delete this->image[i];
			delete this->R[i];
			delete this->G[i];
			delete this->B[i];
		}
		
		delete this->image;
		delete this->R;
		delete this->G;
		delete this->B;
		
		for (int i=0;i<8;i++) {
			delete this->Matrice8x8[i];
			delete this->Q[i];
		}
		
		delete this->Matrice8x8;
		delete this->Q;
		delete this->Vecteur;
		
		std::cout << "destruction faite\n";
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
