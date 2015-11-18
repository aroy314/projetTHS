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

using namespace std;

class Image {
	
	// ------------------- PRIVATE ----------------------
	// ------------------- ATTRIBUTS --------------------
    private :
    int taille;             //img squared size
    int **image = NULL;     //image de base
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
    
    void initQ(int q){			// Création de la matrice de quantification
        int k,l;
        for(k=0;k<8;k++){        // parcourt lignes
            for (l=0;l<8;l++){   // parcourt colonnes
                this->Q[k][l] = 1 + ( k + l + 1 ) * q;  // this-> permet de rentrer dans l'objet Q ( q = paramètre de compression )
			}
        }
        cout << "Q initialisée\n";
    }
  
    // Application de la phase de quantification sur chacune des matrices
    void quantification(int ** Obj) {					   // on récupère notre matrice 8x8
        int k,l;
        for(k=0;k<8;k++)					 // parcourt lignes
            for (l=0;l<8;l++)				// parcourt colonnes
                Obj[k][l] = Obj[k][l]/this->Q[k][l];    // divise notre matrice 8x8 par l'objet Q, membre à membre
        cout << "quantification faite\n";
    }
    
        // Application de la phase de quantification inverse sur chacune des matrices
    void quantification_inv(int ** Obj) {					   // on récupère notre matrice 8x8
        int k,l;
        for(k=0;k<8;k++)					 // parcourt lignes
            for (l=0;l<8;l++)				// parcourt colonnes
                Obj[k][l] = Obj[k][l]*this->Q[k][l];    // multiplie notre matrice 8x8 par l'objet Q, membre à membre
        std::cout << "quantification inverse faite\n";
    }
    
    void charge_img(const char * nom_image[], int *taille){
        //lecture du fichier et attribution dans image NN, et envoi de la taille dans *taille
		cout << "image chargée \n";
    }
	
    void dct_2D(int **Matrice8x8){
		
		//allocation d'une matrice de travail
        int **Matrice_dct = new int*[8];
        for (int i = 0; i < 8; i++)
            Matrice_dct[i] = new int[8];
        
        float Ci;
        float Cj;
        
        for (int i=0; i<8; i++)
            for (int j=0; j<8; j++){
				Matrice_dct[i][j] = 0;
                for (int x=0; x<8; x++)
                    for (int y=0; y<8; y++){
                        if (i==0)
                            Ci=1/sqrt(2);
                        else Ci=1;
                        if (j==0)
                            Cj=1/sqrt(2);
                        else Cj=1;
                        
                        Matrice_dct[i][j] += Matrice8x8[x][y]*(Ci*Cj)/4*cos(((2*x+1)*i*M_PI)/16)*cos(((2*y+1)*j*M_PI)/16);
                    }
            }
		
        for (int i=0; i<8; i++)
            for (int j=0; j<8; j++)
                Matrice8x8[i][j] = Matrice_dct[i][j];
		
		cout << "DCT2D faite\n";
    }
	
	void dct_2D_Inv(int **Matrice8x8){//dosda
	}
	
	//fonction de recup d'une matrice NxN et allocation de la 8x8 selon des paramètres x,y (haut gauche de la matrice)
	void compression8x8(int x, int y, int **matriceNN, int *Vecteur, int *nbV){
		//recup de la 8x8
		for(int i=0;i<8;i++)
			for(int j=0;j<8;j++)
				this->Matrice8x8[i][j] = matriceNN[x+i][y+j];
		
		//traitement et compression
		dct_2D(this->Matrice8x8);
		quantification(this->Matrice8x8);
		
		//nb d'elements dans le vecteur compressé
		int nbOut = 0;
		
		int *Vect_temp = new int[64];
		zigzag(this->Matrice8x8, Vect_temp);
		compression_zigzag(Vect_temp, this->Vecteur128, &nbOut);
		delete Vect_temp;
		
		//suppression des 0 et raccourcissement du vecteur, le tout dans Vect_out
		int *Vect_out = NULL;
		suppression_zeros(this->Vecteur128, Vect_out, &nbOut);//nbOut doit réduire de 2 si on enlève les 0
		//on a le resultat final dans Vect_out
		
		//on concatène Vecteur out au bout de VecteursR/G/B
		concatVect(Vecteur, nbV, Vect_out, &nbOut);
		delete Vect_out;
	}
	
	void decompression8x8(int x, int y, int **matriceNN, int* Vecteur, int *nbElem){
		int *Vect_temp = new int[64];
		int nbIn = 0;
		//on recupère this->vecteur128 compressé issu de vecteurRGB
		
		//on le decompresse
		decompression_zigzag(this->Vecteur128, Vect_temp, nbIn);
		
		//on le met dans une matrice avec zigzag
		zigzag_inverse(this->Matrice8x8, Vect_temp);
		delete Vect_temp;
		
		//on effectue la quantif inverse + la dct inverse
		dct_2D_Inv(this->Matrice8x8);
		quantification_inv(this->Matrice8x8);
		
		//on écrit la 8x8 au bon endroit dans la NxN
		for(int i=0;i<8;i++)
			for(int j=0;j<8;j++)
				matriceNN[x+i][y+j] = this->Matrice8x8[i][j];
	}
	
	void concatVect(int *V1, int *nb_val1, int *V2, int *nb_val2){
		//on met this->Vecteur128 au bout de V
		//on cherche la bonne case
		int i=0, cpt=0;//compteur de case et compteur cumulé
		while(cpt < *nb_val1){
			cpt += V1[i];
			i += 2;
		}
		//i est à la bonne position, on remplit
		while(cpt <= (*nb_val1 + *nb_val2)){
			V1[i]=V2[i];
			V1[i+1]=V2[i+1];
			cpt+=V2[i+1];
			i+=2;
		}
		//on met à jour nb_val1
		*nb_val1 = cpt;
	}

	void suppression_zeros(int *V1, int *V2, int *size_vect){
		if(V1[*size_vect]==0)
			*size_vect -= 2;
		//creation du nouveau vecteur
		V2 = new int[*size_vect];
		for(int i=0;i<*size_vect;i++)
			V2[i] = V1[i];
	}
	
	void fuuusion(int *R, int nbR, int *G, int nbG, int *B, int nbB, int *V){
		
		int i=1;//notre compteur
		int cpt=0;//compteur cumulé
		int cptVect=0;//compteur cumulé des 3 vect
		//RED
		V[0]=nbR;
		while(cpt<nbR){
			V[i] = R[i];	//qté
			V[i+1] = V[i+1];//valeur
			i+=2;
			cpt+=V[i+1];
		}
		//GREEN
		V[i]=nbG;
		i++;
		cptVect+=cpt;
		cpt=0;//réinit du compteur cumulé
		while(cpt<nbG){
			V[i] = R[i];	//qté
			V[i+1] = V[i+1];//valeur
			i+=2;
			cpt+=V[i+1];
		}
		//BLUE
		V[i]=nbB;
		i++;
		cpt=0;//réinit du compteur cumulé
		while(cpt<nbB){
			V[i] = R[i];	//qté
			V[i+1] = V[i+1];//valeur
			i+=2;
			cpt+=V[i+1];
		}
		cptVect+=cpt;
		cout << "Vecteur Final : " << "nb de cases : " << i << endl << "nb de valeurs : " << cptVect << endl;
	}
	
	void unfuuusion(int *V, int *R, int *nbR, int *G, int *nbG, int *B, int *nbB){
		
	}
	
	void zigzag(int **Matrice8x8, int *Vect){//poisson
		//lecture de la 88 image
		//ecriture de Vecteur avec la lecture en zigzag
		
		cout << "ZigZag fait" << endl;
		
	}
	
	void zigzag_inverse(int **Matrice8x8, int *Vect){//mathilde
		//lecture du vecteur compressé
		//ecriture d'une matrice 88
		
		cout << "ZigZag Inverse fait" << endl;
		
	}
	
	void compression_zigzag(int *V1, int* V2, int *nb_elem){//V1 vecteur non compressé, V2 vecteur compressé, nombre d'elem dans le vecteur
		
	}
	
	void decompression_zigzag(int *V1, int* V2, const int nb_elem){//V1 compressé, V2 décompressé de taille 64, nombre d'elem dans le vecteur
		
	}
	

	// ------------------- PUBLIC ----------------------
    public :
    Image(const char * nom_image[]){ //CONSTRUCTEUR
		
		//chargement de l'image et attribution de la taille de la matrice NN
		charge_img(nom_image,&this->taille);
		
        //allocation des attributs
        this->image = new int *[3*this->taille];
        this->R     = new int *[this->taille];
        this->G     = new int *[this->taille];
        this->B     = new int *[this->taille];
		
		for (int i=0;i<3*this->taille;i++) {
			this->image[i] = new int[this->taille];
		}
		
        for (int i=0;i<this->taille;i++) {
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
		
		this->Vecteur128	= new int[128];
		this->VecteursR		= new int[2*this->taille*this->taille];
		this->VecteursG		= new int[2*this->taille*this->taille];
		this->VecteursB		= new int[2*this->taille*this->taille];
		this->Vecteur		= new int[6*this->taille*this->taille+3]; //contiens les vect RGB + nb de val dans chacun à chaque debut de vect
		
		//attribution des matrices RGB selon la matrice image
		
        //calcul de Q
        int q;
        cout << "Entrez le paramètre de compression : ";
        cin >> q;
        initQ(q);
        
        cout << "construction faite\n";
    }
    
    ~Image(){ //DESTRUCTEUR
		//destruction des attributs
		
		for (int i=0;i<this->taille;i++) {
			delete this->R[i];
			delete this->G[i];
			delete this->B[i];
		}
		
		for (int i=0;i<this->taille*3;i++) {
			delete this->image[i];
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
		
		delete this->VecteursR;
		delete this->VecteursG;
		delete this->VecteursB;
		delete this->Vecteur;
		delete this->Vecteur128;

		
		cout << "destruction faite\n";
		}
	
	
    void compression(){
		
		if(this->taille%8==0)//test tout bête
			cout << "Erreur dans la taille des matrices : pas multiple de 8" << endl;
		else {
		
			//entier indiquant le nb de val de chaque vecteur
			int nbR=0, nbG=0, nbB=0;
		
			//pour R, G et B :
			for(int i=0;i<this->taille/8;i++)
				for(int j=0;j<this->taille/8;j++){
					compression8x8(i*8,j*8,this->R,this->VecteursR,&nbR);
					compression8x8(i*8,j*8,this->G,this->VecteursG,&nbG);
					compression8x8(i*8,j*8,this->B,this->VecteursB,&nbB);
				}
			
			//mise bout à bout des 3 vecteurs RGB dans Vecteur, séparé par une case indiquant le nb de valeurs dans chacun
			fuuusion(this->VecteursR,nbR,this->VecteursG,nbG,this->VecteursB,nbB,this->Vecteur);
		
			//on ecrit Vecteur dans un fichier
			char *nom_fichierVect = new char[50];
			//ecrit_Vect(this->Vecteur, nomfichierVect);
        
			cout << "compression faite, fichier ecrit : " << nom_fichierVect << endl;
		}
	}
	
	void decompression(){	//compression à l'envers
		char *nom_fichierVect = new char[50];
		//lecture_Vect(nomfichierVect, this->Vecteur);
		cout << nom_fichierVect << " chargé en mémoire" << endl;
		
		//Separation de this->vecteur en vecteurs R/G/B
		//entier indiquant le nb de val de chaque vecteur
		int nbR=0, nbG=0, nbB=0;
		unfuuusion(this->Vecteur,this->VecteursR,&nbR,this->VecteursG,&nbG,this->VecteursB,&nbB);
		
		//repartition de chaque vecteursRGB dans des vecteurs 88 puis mise en matrice et traitement
		for(int i=0;i<this->taille/8;i++)
			for(int j=0;j<this->taille/8;j++){
				decompression8x8(i*8,j*8,this->R,this->VecteursR,&nbR);
				decompression8x8(i*8,j*8,this->G,this->VecteursG,&nbG);
				decompression8x8(i*8,j*8,this->B,this->VecteursB,&nbB);
			}
		
		cout << "decompression faite" << endl;
	}
};
