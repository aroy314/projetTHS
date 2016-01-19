//
//  image.cpp
//  projetTHS
//
//  Created by Alexandre ROY on 16/11/2015.
//  Copyright © 2015 Alexandre ROY. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "image_comp.hpp"

#define FNAME "/Volumes/Macintosh HD/Users/AlexandreROY/CloudStation/ISEN/M1/Projet THS/projetTHS/gestionImage/fichier.txt"

using namespace std;
	// ------------------- FONCTIONS ----------------------
    
	void Image_comp::initQ(int q){			// Création de la matrice de quantification
        int k,l;
        for(k=0;k<8;k++){        // parcourt lignes
            for (l=0;l<8;l++){   // parcourt colonnes
                this->Q[k][l] = 1 + ( k + l + 1 ) * q;  // this-> permet de rentrer dans l'objet Q ( q = paramètre de compression )
			}
        }
        cout << "Q initialisée\n";
    }
    
    // Application de la phase de quantification sur chacune des matrices
	void Image_comp::quantification(int ** Obj) {		// on récupère notre matrice 8x8
		int k,l;
		for(k=0;k<8;k++)					// parcourt lignes
			for (l=0;l<8;l++)				// parcourt colonnes
				Obj[k][l] = (int) (Obj[k][l]/this->Q[k][l]);    // divise notre matrice 8x8 par l'objet Q, membre à membre
		
		cout << endl << "quantification faite\n";
		
	}
	void Image_comp::dct_2D(int **Matrice8x8){
		
		//allocation d'une matrice de travail
		float **Matrice_dct = new float*[8];
		for (int i = 0; i < 8; i++)
			Matrice_dct[i]= new float[8];
		
		float Ci;
		float Cj;
		
		for (int i=0; i<8; i++)
			for (int j=0; j<8; j++){
				Matrice_dct[i][j] = 0;
				for (int x=0; x<8; x++)
					for (int y=0; y<8; y++)
					{
						(i==0) ? Ci=1/sqrt(2): Ci=1;
						(j==0) ? Cj=1/sqrt(2): Cj=1;
						
						Matrice_dct[i][j] += Matrice8x8[x][y]*(Ci*Cj)/4*cos(((2*x+1)*i*M_PI)/16)*cos(((2*y+1)*j*M_PI)/16);
					}
			}
		
		for (int i=0; i<8; i++)
			for (int j=0; j<8; j++)
				Matrice8x8[i][j]=Matrice_dct[i][j];//reatribution de la matrice de travail
	}

	//fonction de recup d'une matrice NxN et allocation de la 8x8 selon des paramètres x,y (haut gauche de la matrice)
	void Image_comp::compression8x8(int x, int y, int **matriceNN, int *Vecteur, int *nbV){
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
		suppression_zeros(this->Vecteur128, &Vect_out, &nbOut);//nbOut doit réduire si on enlève les 0
		//on a le resultat final dans Vect_out
		
		//on concatène Vect_out au bout de Vecteur, précédé d'un marqueur indiquant le nombre de valeurs par vecteur
		concatVect(Vecteur, nbV, Vect_out, &nbOut);
		delete Vect_out;
	}

	void Image_comp::concatVect(int *V1, int *nb_val1, int *V2, int *nb_val2){ //on met V2 au bout de V1
		
		int test=0;
		int i=0;
		while (test < *nb_val1) {
			test+=V1[i];
			i+=2;
		}
		
		test=0;
		int j=0;
		while (test < *nb_val2) {
			test+=V2[j];
			j+=2;
		}
		
		for (int k=0; k<j; k++)
			V1[i+k]=V2[k];
		
		*nb_val1=*nb_val1+*nb_val2;
	}

	void Image_comp::suppression_zeros(int *V1, int **V2, int *nb_elem){
		int i=0;
		int cpt=0;
		int size=0;
		while (cpt<*nb_elem) {
			cpt+=V1[size];
			size+=2;
		}
		if(V1[size-1]==0){
			size -= 2;
			*nb_elem-=V1[size];
		}
		//creation du nouveau vecteur
		*V2 = new int[size];
		cpt=0;i=0;
		while(cpt<*nb_elem){
			(*V2)[i] = V1[i];
			(*V2)[i+1] = V1[i+1];
			cpt+=V1[i];
			i+=2;
		}
	}
	
    void Image_comp::fuuusion(int *R, int nbR, int *G, int nbG, int *B, int nbB, int *V){
		
        int i=1;//notre compteur
        int j=0;
        int cpt=0;//compteur cumulé
        int cptVect=0;//compteur cumulé des 3 vect
        //RED
        V[0]=nbR;
        while(cpt<nbR){
            V[i] = R[j];	//qté
            V[i+1] = R[j+1];//valeur
            cpt+=R[j];
            i+=2;
            j+=2;
        }
        //GREEN
        V[i]=nbG;
        i++;
        cptVect+=cpt;
        cpt=0; j=0;//réinit du compteur cumulé
        while(cpt<nbG){
            V[i] = G[j];	//qté
            V[i+1] = G[j+1];//valeur
            cpt+=G[j];
            i+=2;
            j+=2;
        }
        //BLUE
        V[i]=nbB;
        i++;
        cptVect+=cpt;
        cpt=0; j=0;//réinit du compteur cumulé
        while(cpt<nbB){
            V[i] = B[j];	//qté
            V[i+1] = B[j+1];//valeur
            cpt+=B[j];
            i+=2;
            j+=2;
        }
        
        cptVect+=cpt;
        cout << "Vecteur Final : " << "nb de cases : " << i << endl << "nb de valeurs : " << cptVect << endl;
    }

	void Image_comp::zigzag(int **Matrice8x8, int *Vect){
		//lecture de la 88 image
		//ecriture de Vecteur avec la lecture en zigzag
		
		int k=0;
		int l=0;
		int i=0;
		
		while ((k!=7)||(l!=7)){
			while((k!=0)&&(l!=7)){
				Vect[i++]=Matrice8x8[k][l];
				k--;
				l++;
			}
			Vect[i++]=Matrice8x8[k][l];
			if(l==7)
				k++;
			else
				l++;
			while((k!=7)&&(l!=0)){
				Vect[i++]=Matrice8x8[k][l];
				k++;
				l--;
			}
			Vect[i++]=Matrice8x8[k][l];
			if(k==7)
				l++;
			else
				k++;
		}
		Vect[i]=Matrice8x8[k][l];
		cout << endl << "ZigZag fait" << endl;
	}

	void Image_comp::compression_zigzag (int *V1, int *V2, int *nb_elem){//V1 vecteur non compressé, V2 vecteur compressé, nombre d'elem dans le vecteur
		int a = 1, cpt=0;
		
		for (int pos=0; pos<64 ; pos++){ // parcours le tableau
			if (V1[pos+1]==V1[pos] && pos!=63) // compte le nombre de chiffre similaire
				a++;
			else {
				V2[cpt] = a ;// attribut les valleurs a la matrice de sortie
				V2[cpt+1] = V1[pos];
				a = 1 ;
				cpt+=2; // recupere taille matrice
			}
		}
		//on inscrit dans nb_elem la somme des cases paires (nombre d'elements compressés)
		for (int i=0;i<cpt;i+=2)
			*nb_elem += V2[i];
		
		cout << "compression de Vecteur faite" << endl << "Nb d'elements : " << *nb_elem << endl;
	}
	
    void Image_comp::decompression_zigzag (int *V1, int *V2, const int nb_elem)//V1 compressé, V2 décompressé de taille 64, nombre d'elem dans le vecteur
    {
        int p = 0;
        
        for (int i=0; i<nb_elem ; i++) //Reatribue les valeurs de base de la matrice 64
            if (i%2==0)
                for (int j=0; j<V2[i]; j++)
                    V1[p++]=V2[i+1];
    }

	void Image_comp::writeVect(int *Vect){
		
		ofstream fichier; //alloc d'un fichier
		fichier.open("/Volumes/Macintosh HD/Users/AlexandreROY/CloudStation/ISEN/M1/Projet THS/projetTHS/CompressedVector.txt");//ouverture du fichier
		
		int i=1;//notre compteur
		int cpt=0;//compteur cumulé
		
		//RED
		int nbelem = Vect[0];
		fichier << Vect[0] << " ";
		while(cpt<nbelem){
			//cout << i << " " << cpt << " " << Vect[i] << endl;
			fichier << Vect[i] << " " << Vect[i+1] << " ";//on ecrit deux cases
			cpt+=Vect[i];
			i+=2;//on tape 2 cases plus loin au prochain tour
			
		}
		//cout << i << " " << cpt << " " << Vect[i] << endl;
		//GREEN
		nbelem = Vect[i];
		fichier << Vect[i] << " ";
		i++;cpt=0;//réinit du compteur cumulé
		while(cpt<nbelem){
			//cout << i << " " << cpt << " " << Vect[i] << endl;
			fichier << Vect[i] << " " << Vect[i+1] << " ";
			cpt+=Vect[i];
			i+=2;
		}
		//cout << i << " " << cpt << " " << Vect[i] << endl;
		//BLUE
		nbelem = Vect[i];
		fichier << Vect[i] << " ";
		i++;cpt=0;//réinit du compteur cumulé
		while(cpt<nbelem){
			//cout << i << " " << cpt << " " << Vect[i] << endl;
			fichier << Vect[i] << " " << Vect[i+1] << " ";
			cpt+=Vect[i];
			i+=2;
		}
		
		fichier.close();//fermeture du fichier
	}
	
	// ------------------- PUBLIC ----------------------

    Image_comp::Image_comp(){ //CONSTRUCTEUR
		
		//Fichier --> Matrice
		FILE *fichier2 = fopen (FNAME, "r" );
		if (fichier2 == NULL){
			perror (FNAME);
			printf("impossible de lire gestionImage/fichier.txt\n");
			exit(1);
		}
		else {
			int i=0;
			int j=0;
			fscanf(fichier2, "%d,%d,\n", &this->largeur, &this->hauteur);

			//allocation des attributs
			this->R     = new int *[this->largeur];
			this->G     = new int *[this->largeur];
			this->B     = new int *[this->largeur];
			for (int i=0;i<this->largeur;i++) {
				this->R[i]     = new int[this->hauteur];
				this->G[i]     = new int[this->hauteur];
				this->B[i]     = new int[this->hauteur];
			}

			for(i = 0; i < this->largeur; i++){
				for(j = 1; j < this->hauteur; j++){
					if (!fscanf(fichier2, "%d,%d,%d,", &this->R[i][j],&this->G[i][j],&this->B[i][j]))
						break;
				}
			}
			fclose(fichier2);
	    }
		
        this->Matrice8x8 = new int *[8];
        this->Q = new int *[8];
        for (int i=0;i<8;i++) {
            this->Matrice8x8[i] = new int[8];
            this->Q[i] = new int[8];
        }
		
		this->Vecteur128	= new int[128];
		this->VecteursR		= new int[2*this->largeur*this->hauteur];
		this->VecteursG		= new int[2*this->largeur*this->hauteur];
		this->VecteursB		= new int[2*this->largeur*this->hauteur];
		this->Vecteur		= new int[6*this->largeur*this->hauteur+3]; //contient les vect RGB + nb de val dans chacun à chaque debut de vect
		
        //calcul de Q
        int q;
        
        this->Q = new int*[8]; //init Matrice Q
        for (int i = 0; i < 8; i++)
            Q[i] = new int[8];
        
        
        cout << "Entrez le paramètre de compression : ";
        cin >> q;
        initQ(q);
        
        cout << "construction faite\n";

    }
    
    Image_comp::~Image_comp(){ //DESTRUCTEUR
		//destruction des attributs
		
		for (int i=0;i<this->largeur;i++) {
			delete this->R[i];
			delete this->G[i];
			delete this->B[i];
		}
		
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
	
    void Image_comp::compression(){
		
		if(this->largeur%8!=0 || this->hauteur%8!=0)//test tout bête
			cout << "Erreur dans la taille des matrices : pas multiple de 8" << endl;
		else {
			//entier indiquant le nb de val de chaque vecteur
			int nbR=0, nbG=0, nbB=0;
		
			//pour R, G et B :
			for(int i=0;i<this->largeur/8;i++)
				for(int j=0;j<this->hauteur/8;j++){
					compression8x8(i*8,j*8,this->R,this->VecteursR,&nbR);
					compression8x8(i*8,j*8,this->G,this->VecteursG,&nbG);
					compression8x8(i*8,j*8,this->B,this->VecteursB,&nbB);
				}

			//mise bout à bout des 3 vecteurs RGB dans Vecteur, séparé par une case indiquant le nb de valeurs dans chacun
			fuuusion(this->VecteursR,nbR,this->VecteursG,nbG,this->VecteursB,nbB,this->Vecteur);
		
			//on ecrit Vecteur dans un fichier
			writeVect(this->Vecteur);
			
			cout << "compression faite, fichier ecrit "<< endl;
		}
    }

