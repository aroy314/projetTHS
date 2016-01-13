//
//  matrix.c
//  projet_ths
//
//  Created by Clément Bissonnier on 03/12/2015.
//  Copyright © 2015 Clement Bissonnier. All rights reserved.
//


#include "matrix.h"




void transposeMatrice( int n, const float matrice[n][n], float matriceTransposee[n][n])
{
    int i,j;
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            matriceTransposee[i][j]=matrice[j][i];      // Transpose la matrice
}

void tailleMatrice(int*l, int*k)
{
    int i=0;
    
    if(((*l)%8)==0 && ((*k)%8)==0 )                 // Test pour savoir si les dimensions de la matrice sont multiples de 8
        i++;
    else
    {
        do{
            if(((*l)%8)!=0)
                *l+=1;
            if(((*k)%8)!=0)
                *k+=1;
        }while(((*l)%8)!=0 || ((*k)%8)!=0 );        // Incrementation des indices de dimensions jusqu a ce qu ils soient multiples de 8
        
    }
    
}

void saveMatrix(float** const matrix, float** newMatrix)
{
    int i,j;
    for(i=0;i<8;i++)
        for(j=0;j<8;j++)
            newMatrix[i][j]=matrix[i][j];                   // Sauvegarde des valeurs dans une matrice tampon
}

float** alloueMatrice(int n, int m)
{
    int i,j;
    float** matrix=NULL;
    matrix=(float**)malloc(n*sizeof(float*));                   // Allocation memoire du tableau
    if(matrix==NULL)
        printf("Erreur d allocation memoire\n");                // Message d erreur si echec de l allocation
    for(i=0;i<n;i++)
    {
        matrix[i]=(float*)malloc(m*sizeof(float));              // Allocation memoire des elements du tableau
        if(matrix[i]==NULL)
            printf("Erreur d allocation memoire 2\n");          // Message d erreur si echec de l allocation
    }
    
    for(i=0;i<n;i++)
        for(j=0;j<m;j++)
            matrix[i][j]=0;                                     // Mise a 0 de toutes les valeurs du tableau
    
    return matrix;                                              // On retourne le tableau
} 

short int ** alloueMatriceInt(int n, int m)
{
    int i,j;
    short int** matrix=NULL;
    matrix=(short int**)malloc(n*sizeof(short int*));           // Allocation memoire du tableau
    if(matrix==NULL)
        printf("Erreur d allocation memoire\n");                // Message d erreur si echec de l allocation
    for(i=0;i<n;i++)
    {
        matrix[i]=(short int*)malloc(m*sizeof(short int));      // Allocation memoire des elements du tableau
        if(matrix[i]==NULL)
            printf("Erreur d allocation memoire 2\n");          // Message d erreur si echec de l allocation
    }
    
    for(i=0;i<n;i++)
        for(j=0;j<m;j++)
            matrix[i][j]=0;                                     // Mise a 0 de toutes les valeurs du tableau
    
    return matrix;                                              // On retourne le tableau
}

void Matrice(int m, float** matrice)
{
    int i,j;
    for(i=0;i<m;i++)
        for(j=0;j<m;j++)
            matrice[i][j]=rand()%255;                    // Remplissage de la matrice par des valeurs comprises entre 0 et 255
}

void affichageMatrice( int n, float** const matrice)
{
    int i,j;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
            printf("M[%d][%d]=%.0f\t",i,j,matrice[i][j]); // Affichage des valeurs de la matrice
        printf("\n");
    }
    
}

void affichageMatriceInt( int n, short int** const matrice)
{
    int i,j;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
            printf("M[%d][%d]=%d\t",i,j,matrice[i][j]); // Affichage des valeurs de la matrice
        printf("\n");
    }
    
}
void remplissageMatrice( int n, int m, float** const matrice,int k, float** matrice2)
{
    int i,j=0,b,a;
    
    
    for(i=0,a=0;a<n;a++)
        for(b=0;b<m;b++,j++)
        {
            matrice2[i][j]=0.;          // Mise a 0 de la matrice aux dimensions multiples de 8
            if(j==k && i<k-1)
            {
                j=0;
                i++;                // Incrementation des indices pour avoir toutes les valeurs d affilee
            }
            matrice2[i][j]=matrice[a][b];   // La matrice aux dimensions multiples de 8 recoit les valeurs de la matrice initiale
        }
    for(i=n;i<k;i++)
        for(j=m;j<k;j++)
            matrice2[i][j]=0;           // Remplissage du reste de la bonne matrice par des 0
    matrice2[15][8]=0;
    
}

void remplissageMatrice2( int n, int m, const float matrice[n][m],int k, int l, float matrice2[k][l])
{
    int i=0,j=0,b,a;
    
    
    for(a=0;a<n;a++)
        for(b=0;b<m;b++)
        {
            matrice2[i][j]=0.;          // Mise a 0 de la matrice aux dimensions multiples de 8
            
            matrice2[a][b]=matrice[a][b];   // La matrice aux dimensions multiples de 8 recoit les valeurs de la matrice initiale
        }
    for(i=n;i<k;i++)
        for(j=m;j<l;j++)
            if(matrice2[i][j]!=0)
                matrice2[i][j]=0;           // Remplissage du reste de la bonne matrice par des 0
    
}

void affichageVector(int n, const float vector[n])
{
    int i;
    for(i=0;i<n;i++)
        printf("V[%d]=%.0f\n",i,vector[i]);     // Affichage des valeurs du vecteur
    printf("\n");
}

void affichageTableauVector(int n, tabVector* vector, int length, int a)
{
    int i;
    for(i=0;i<length;i++)                               // Affichage des vecteurs contenus dans la structure
    {
        if(a==1)
            affichageVector(n, vector[i].vector);       // Affichage du vecteur apres zigzag
        else
            affichageVector(n, vector[i].RLEVector);   // Affichage du vecteur apres RLE
        printf("\n");
    }
}



void affichageTableauMatrice( int n, tabMatrice* matrice, int length)
{
    int i;
    for(i=0;i<length;i++)
    {
        affichageMatrice(n, matrice[i].tab);         // Affichage des matrices contenues dans la structure
        printf("\n");
    }
    
}

void decoupeMatrice(int departabs, int departord, float** const matrice, float** petiteMatrice)
{
    int i, j,k,l;
    for(i=departabs, k=0;i<departabs+8;i++,k++)
        for(j=departord,l=0;j<departord+8;j++,l++)
            petiteMatrice[k][l]=matrice[i][j];          // On sectionne la grande matrice en petites matrices [8][8]
    
}



/*void remplissageP(int n, int m, float P[n][m])
 {
 int i, j, N=8;
 float a;
 for(i=0;i<n;i++)
 for(j=0;j<m;j++)
 {
 if(i==0)                            // condition pour savoir la valeur de a
 a=1/sqrt(2);
 else
 a=1.;
 P[i][j]=sqrt(0.25)*a*cos((2*j+1)*i*pi/(2*N)); // Calcul des valeurs de P
 }
 }
 
 void ProduitMatriciel(int n, int m, const float A[n][m], const float B[m][n], float C[n][n])
 {
 int i, j, k;
 for(i=0; i<n;i++)
 for(j=0;j<m;j++)
 for(k=0;k<m;k++)
 C[i][j]+=A[i][k]*B[k][j];       // Produit matriciel de 2 matrices
 }*/

void DCT(float** const in, float** out)
{
    int i, j, u, v;
    float s;
    
    for (i=0;i<8;i++)
        for (j=0;j<8;j++)
        {
            s=0;
            
            for (u=0;u<8;u++)
                for (v=0;v<8;v++)
                    s+=in[u][v]*cos((2*u+1)*i*M_PI/16)*      // Calcul de la DCT
                    cos((2*v+1)*j*M_PI /16)*
                    ((i==0) ? 1 / sqrt(2) : 1)*             // On multiplie par 1 / sqrt(2) si i=0, 1 sinon
                    ((j==0) ? 1 / sqrt(2) : 1);             // On multiplie par 1 / sqrt(2) si j=0, 1 sinon
            
            out[i][j]=s/4;
        }
    
}

void remplissageQ( float Q[8][8], float q)
{
    int i,j;
    for(i=0;i<8;i++)
        for(j=0;j<8;j++)
            Q[i][j]=(1+2*(i+j))*q;                      // Remplissage de la matrice de quantification
}

void quantification(int n, const float Q[8][8], float** matrix)
{
    int i, j;
    float temp;
    for(i=0; i<n;i++)
        for(j=0;j<n;j++)
        {
            temp=matrix[i][j];
            temp/=Q[i][j];
            matrix[i][j]=temp;                      // Division de chaque element de la matrice DCT par la valeur de quantification
            
        }
    

}

tabMatrice* rangementMatrice(int n, float** const tab, int* length, const float Q[8][8])
{
    int i,j,value,l,size=0;
    float** saveTab=alloueMatrice(8,8);
    value=n*n;
    size=value/64;                                                          // Calcul du nombre de matrices necessaires
    *length=size;
    tabMatrice* myMatrice=(tabMatrice*)malloc(size*sizeof(tabMatrice));     // Creation d un tableau de matrices pouvant contenir toutes les valeurs de la grosse matrice
    if(myMatrice==NULL)
        printf("Erreur d allocation memoire/n");
    
    for(i=0,l=0;i<n;i+=8)
        for(j=0;j<n;j+=8,l++)
        {
            myMatrice[l].tab=alloueMatrice(8,8);
            decoupeMatrice(i, j, tab, myMatrice[l].tab);          // decoupage de la grosse matrice dans les petites matrices
            saveMatrix(myMatrice[l].tab, saveTab);                   // Utilisation d une matrice tampon
            DCT(saveTab, myMatrice[l].tab);                          // Calcul de la DCT
            quantification(8, Q, myMatrice[l].tab);
        }
    
    freeTab(saveTab,8);
    return myMatrice;
}
 
void readZigzag(int n, float** const matrix, int l, float vector[l])
{
    int i=0, j=0,k=0, flag=0;
    
    if(j==0 && i==0)
    {
        vector[k]=matrix[i][j];         // Premiere case
        j++;
        k++;
        vector[k]=matrix[i][j];
    }
    while(j<n)
    {
        while(j!=0)                         // Descente diagonale
        {
            i++;
            j--;
            k++;
            vector[k]=matrix[i][j];
        }
        if(j==0 && i<n)
        {
            if(i!=n-1)
            {
                i++;                        // Decalage d une case vers le bas quand on arrive au bout de la diagonale et qu on n est pas dans un coin
                k++;
                vector[k]=matrix[i][j];
            }
            else
            {
                j++;                    // Decalage d une case vers la droite sinon
                k++;
                vector[k]=matrix[i][j];
            }
        }
        while(i!=0 && flag==0)
        {
            if(j!=n-1)                  // Montee diagonale si l on n est pas dans un coin
            {
                i--;
                j++;
                k++;
                vector[k]=matrix[i][j];
                
            }
            else
            {
                
                vector[k]=matrix[i][j];         // Decalage d une case vers le bas si l on est dans un coin
                flag=1;
                i++;
                k++;
                vector[k]=matrix[i][j];
                
            }
        }
        if(flag==1)                             // Remise a zero du flag pour la boucle
            flag=0;
        if(j==n-1 && i<n)                       // Si l on a passe la grande diagonale
        {
            while(k<n*n)
            {
                while(i!=n-1)                   // Descente diagonale
                {
                    j--;
                    i++;
                    k++;
                    vector[k]=matrix[i][j];
                }
                if(i==n-1 && j<n)
                {
                    j++;                        // Decalage d une case vers la droite
                    k++;
                    vector[k]=matrix[i][j];
                }
                while(j!=n-1)
                {
                    i--;                        // Montee diagonale
                    j++;
                    k++;
                    vector[k]=matrix[i][j];
                }
                if(j==n-1 && i<n)
                {
                    i++;                        // Decalage d une case vers le bas
                    k++;
                    vector[k]=matrix[i][j];
                    if(i==n-2)
                    {
                        i++;
                        vector[k]=matrix[i][j];
                        k=n*n;
                        j++;
                    }
                }
            }
            j=n;
        }
        if(i==0 && j<n)
        {
            j++;                                    // Decalage d une case vers la droite
            k++;
            vector[k]=matrix[i][j];
        }
        
    }
    
}


void RLEfunction2( int l, const float vector[l], float RLEvector[2*l])
{
    int i,j=0,k,cpt=1;
    int test[l];
    float saveVector[l];
    int occurence[l];
    for(i=0;i<l;i++)
        test[i]=vector[i];              // Cast int
    for(i=0;i<l;i++)
    {
        if(test[i]==test[i+1] && cpt<64)    // test d egalite de 2 valeurs successives
            cpt++;
        else
        {
            saveVector[j]=test[i];
            occurence[j]=cpt;           // Sauvegarde de la valeur et de la valeur du compteur si valeurs plus egales
            cpt=1;
            j++;
        }
        
    }
    for(i=0,k=0;i<2*j;i+=2,k++)
    {
        RLEvector[i]=occurence[k];
        RLEvector[i+1]=saveVector[k];       // Injection des valeurs dans le vecteur RLE
    }
}

void reverseRLE( int l, float vector[l], const float RLEvector[2*l])
{
    int i, j, k, cpt;
    for(i=0,j=0,k=1;i<l;i++,j+=2,k+=2)
    {
        cpt=RLEvector[j];
        while(cpt!=0)
        {
            vector[i]=RLEvector[k];     // Tant que le compteur n est pas nul, on stocke la meme valeur dans le veteur
            cpt--;
        }
    }
}

void reverseReadZigzag(int n, float** matrix, int l, const float vector[l])
{
    int i=0, j=0,k=0, flag=0;
    
    if(j==0 && i==0)
    {
        matrix[i][j]=vector[k];         // Premiere case
        j++;
        k++;
        matrix[i][j]=vector[k];
    }
    while(j<n)
    {
        while(j!=0)                         // Descente diagonale
        {
            i++;
            j--;
            k++;
            matrix[i][j]=vector[k];
        }
        if(j==0 && i<n)
        {
            if(i!=n-1)
            {
                i++;                        // Decalage d une case vers le bas quand on arrive au bout de la diagonale et qu on n est pas dans un coin
                k++;
                matrix[i][j]=vector[k];
            }
            else
            {
                j++;                    // Decalage d une case vers la droite sinon
                k++;
                matrix[i][j]=vector[k];
            }
        }
        while(i!=0 && flag==0)
        {
            if(j!=n-1)                  // Montee diagonale si l on n est pas dans un coin
            {
                i--;
                j++;
                k++;
                matrix[i][j]=vector[k];
                
            }
            else
            {
                
                matrix[i][j]=vector[k];         // Decalage d une case vers le bas si l on est dans un coin
                flag=1;
                i++;
                k++;
                matrix[i][j]=vector[k];
                
            }
        }
        if(flag==1)                             // Remise a zero du flag pour la boucle
            flag=0;
        if(j==n-1 && i<n)                       // Si l on a passe la grande diagonale
        {
            while(k<n*n)
            {
                while(i!=n-1)                   // Descente diagonale
                {
                    j--;
                    i++;
                    k++;
                    matrix[i][j]=vector[k];
                }
                if(i==n-1 && j<n)
                {
                    j++;                        // Decalage d une case vers la droite
                    k++;
                    matrix[i][j]=vector[k];
                }
                while(j!=n-1)
                {
                    i--;                        // Montee diagonale
                    j++;
                    k++;
                    matrix[i][j]=vector[k];
                }
                if(j==n-1 && i<n)
                {
                    i++;                        // Decalage d une case vers le bas
                    k++;
                    matrix[i][j]=vector[k];
                    if(i==n-2)
                    {
                        i++;
                        matrix[i][j]=vector[k];
                        k=n*n;
                        j++;
                    }
                }
            }
            j=n;
        }
        if(i==0 && j<n)
        {
            j++;                                    // Decalage d une case vers la droite
            k++;
            matrix[i][j]=vector[k];
        }
        
    }
    
}

void reverseQuantification(int n, const float Q[8][8], float** matrix)
{
    int i, j;
    float temp;
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
        {
            temp=matrix[i][j];              // Utilisation d une variable tampon
            temp*=Q[i][j];                  // Multiplication de cette variable par la matrice de quantification
            matrix[i][j]=temp;              // On injecte la valeur dans la matrice
            
        }
}

void iDCTFunction(float** const in, float** out)
{
    int i, j, u, v;
    float s;
    
    for (i=0;i<8;i++)
        for (j=0;j<8;j++)
        {
            s=0;
            
            for (u=0;u<8;u++)
                for (v=0;v<8;v++)
                    s+=in[u][v]*cos((2*i+1)*u*M_PI/16)*       // Calcul IDCT
                    cos((2*j+1)*v*M_PI/16)*
                    ((u==0) ? 1 / sqrt(2) : 1.)*              // On multiplie par 1 / sqrt(2) si i=0, 1 sinon
                    ((v==0) ? 1 / sqrt(2) : 1.);              // On multiplie par 1 / sqrt(2) si i=0, 1 sinon
            
            out[i][j]=s/4;
        }
    
}

void reverseSegmentation(int n, float** const matrix, float** bigMatrix,int departabs, int departord)
{
    int i, j,k,p;
    for(i=departabs, k=0;k<n;i++,k++)
        for(j=departord, p=0;p<n;j++,p++)
            bigMatrix[i][j]=matrix[k][p];                       // Stockage des valeurs des petites matrices dans la grande matrice

}

void changeVector( int length, tabVector* myVector, int l, int m, float** bigMatrix, const float Q[8][8])
{
    int i,j,op;
    float** saveTab=alloueMatrice(8,8);
    
    tabMatrice* myMatrix=(tabMatrice*)malloc(length*sizeof(tabMatrice));        // Creation d un tableau de matrices
    if(myMatrix==NULL)
        printf("Erreur d allocation memoire/n");
    
    for(i=0;i<length;i++)
    {
        myMatrix[i].tab=alloueMatrice(8,8);
        reverseRLE(l, myVector[i].vector, myVector[i].RLEVector);               // RLE inverse
        reverseReadZigzag(8, myMatrix[i].tab, l, myVector[i].vector);           // Zigzag inverse
        reverseQuantification(8, Q, myMatrix[i].tab);                         // Quantification inverse
        saveMatrix(myMatrix[i].tab, saveTab);
        iDCTFunction(saveTab, myMatrix[i].tab);                                 // IDCT
        
    }

    for(i=0,op=0;i<m;i+=8)
        for(j=0;j<m;j+=8,op++)
            reverseSegmentation(8, myMatrix[op].tab, bigMatrix,i,j);         // Segmentation inverse

    freeTab(saveTab,8);
    for(i=0;i<length;i++)
        freeTab(myMatrix[i].tab, 8);
    free(myMatrix);                                                             // Liberation de la memoire allouee
}

void returnBeginning(int m,float** const Matrix, int k, int l, float** OutMatrix)
{
    int i, j,a,b=0;
    for(i=0,a=0;i<k;i++)
        for(j=0;j<l;j++,b++)
        {
            OutMatrix[i][j]=Matrix[a][b];                                   // Concatenation des petites matrices dans la grande
            if(OutMatrix[i][j]<1)
                OutMatrix[i][j]=0;
            if(OutMatrix[i][j]>255)
                OutMatrix[i][j]=255;                                    // Correction des underflow et overflow
            if(b==m-1)
            {
                b=-1;
                a++;
            }
        }
}

tabVector* rangementVector( int n, tabMatrice* myMatrix, int length)
{
    int i;
    tabVector* myVector=(tabVector*)malloc(length*sizeof(tabVector));       // Creation d un tableau de vecteurs
    if(myVector==NULL)
        printf("Erreur d allocation memoire/n");

    for(i=0;i<length;i++)
    {
        readZigzag(n, myMatrix[i].tab, n*n, myVector[i].vector);
        RLEfunction2(n*n, myVector[i].vector, myVector[i].RLEVector);        // Remplissage du tableau de vecteurs
    }
    return myVector;
}

int stockData( tabVector* myVector, int n)
{
    FILE*myFile=NULL;
    myFile=fopen("resultats/result.txt", "w+");                                       // Ouverture d un fichier en ecriture et lecture
    if(myFile==NULL)
    {
        printf("Erreur d ouverture du fichier\n");                          // Si le fichier ne s ouvre pas on print une erreur et renvoie -1
        return -1;
    }
    
    int i,j;
    
    for(i=0;i<n;i++)
    {
        for(j=0;j<128;j++)
            fprintf(myFile,"%.0f\n",myVector[i].RLEVector[j] );             // Les valeurs des vecteurs RLE sont ecrites dans le fichier
        fprintf(myFile," \n");
    }
    
    fclose(myFile);                                                         // Fermeture du fichier
    return 0;
}


tabVector* openData(void)
{
    FILE* myFile=fopen("resultats/result.txt","r+");                                  // Ouverture du fichier en lecture
    char c;
    int i=0,j=0,length=0;
    
    if(myFile==NULL)
        printf("Erreur d'ouverture du fichier\n");                          // On print une erreur si le fichier ne s est pas ouvert
    
    while((c=getc(myFile))!=EOF)
        if(c==' ')
            if((c=getc(myFile))=='\n')                                      // Comptage du nombre de \n pour savoir le nombre de vecteurs
                length++;
    
    rewind(myFile);                                                         // On se remet au debut du fichier
    
    tabVector*myVector=(tabVector*)malloc((length)*sizeof(tabVector));     // Creation du tableau de vecteur
    if(myVector==NULL)
        printf("Erreur d allocation memoire/n");
    
    for(i=0;i<length;i++)
        for(j=0;j<128;j++)
            fscanf(myFile,"%f",&(myVector[i].RLEVector[j]));                // Copie des valeur du fichier vers le vecteur
    
    fclose(myFile);                                                         // Fermeture du fichier
    return myVector;
}

void freeTab(float** tab, int k)
{
    int i;
    for(i=0;i<k;i++)
        free(tab[i]);                                                   // Liberation des elements alloues
    free(tab);                                                          // Liberation du tableau alloue
}

void freeTabInt2(short int** tab, int k)
{
    int i;
    for(i=0;i<k;i++)
        free(tab[i]);                                               // Liberation des elements alloues
    free(tab);                                                      // Liberation du tableau alloue
}

void convert( int n, int m, short int** const matriceDepart, float ** matriceFin)
{
    int i,j;
    for(i=0;i<n;i++)
        for(j=0;j<m;j++)
            matriceFin[i][j]=matriceDepart[i][j];                   // Stockage des valeurs du tableau en int dans un tableau en float
}

void convert2( int n, int m, short int** matricefin, float ** const matriceDepart)
{ 
    int i,j;
    for(i=0;i<n;i++)
        for(j=0;j<m;j++)
            matricefin[i][j]=matriceDepart[i][j];                   // Stockage des valeurs du tableau en float dans un tableau en int
}

void staticToDynamic( int n, int m, short int** const staticMatrix, short int** dynamicMatrix)
{
    int i,j;
    for(i=0;i<n;i++)
        for(j=0;j<m;j++)
            dynamicMatrix[i][j]=staticMatrix[i][j];             // Stockage des valeurs du tableau statique au tableau dynamique
}

float saisieQuantification(void)
{
    float q=0;
    do{
        printf("Entrez le parametre de quantification :");
        scanf("%f",&q);                                     // Demande le parametre de quantification
    }while(q<1 || q>25);                                    // Repetition de l operation tant que q n est pas compris entre 1 et 25 inclus
    return q;
        
}


void traitement(int n, int m, short int** matrice, float q)
{  
    int k=n,l=m,i;
    float ** tab=alloueMatrice(k,l);
    if(n<m)
        n=m;
    else
        m=n;
    tailleMatrice(&n,&m);                                                  // Allocation memoire des tableaux et calul de la bonne taille des indices de la matrice
    float **tab2=alloueMatrice(n,m), **tab3=alloueMatrice(n,m), Q[8][8];
    
    int length, verif=0;
    remplissageQ(Q, q);                                            // Remplissage matrice quantif en fonction du parametre de quantification
    
    convert(k,l, matrice, tab);                                       // Conversion de la matrice en float
    
    printf("Debut du traitement\n");

    remplissageMatrice(k,l,tab,n,tab2);                           // Remplissage des 0 si la taille de la matrice le necessite
    
    tabMatrice* myMatrice=rangementMatrice(n, tab2, &length, Q);   // Segmentation , DCT , quantification
    
    tabVector*myvector=rangementVector(8, myMatrice, length);       // Zigzag , RLE
    
    verif=stockData(myvector, length);                              // Stockage du vecteur RLE dans un fichier
    
    tabVector*myVector2=openData();                                 // Lecture des donnees stockees et on les met dans un nouveau vecteur RLE
    

    changeVector(length, myVector2, 64, n, tab3, Q);                // RLE inverse, zigzag inverse, quantification inverse, IDCT
    

    returnBeginning(n, tab3, k,l, tab);                               // Segmentation inverse

    printf("Fin de traitement\n");
    convert2(k,l, matrice, tab);                                      // Conversion de la matrice en int
    
    freeTab(tab,k);
    freeTab(tab2,n);
    freeTab(tab3,n);                                                // Liberation memoire de tous les elements alloues dynamiquement
    for(i=0;i<length;i++)
        freeTab(myMatrice[i].tab, 8);
    free(myMatrice);
    free(myvector);
    free(myVector2);
    
    
}

void copyImage(char* name, float q)
{

    DonneesImageRGB* image=NULL;
    image=lisBMPRGB(name);                                                          //lecture de l image passe en parametre
    short int** rouge2=alloueMatriceInt(image->hauteurImage, image->largeurImage);
    
    short int** vert2=alloueMatriceInt(image->hauteurImage, image->largeurImage);
    
    short int** bleu2=alloueMatriceInt(image->hauteurImage, image->largeurImage);   // Declaration des matrices rouge, vert, bleu de maniere dynamique
    
    short int** rouge=alloueMatriceInt(image->hauteurImage, image->largeurImage);
    
    short int** vert=alloueMatriceInt(image->hauteurImage, image->largeurImage);
    
    short int** bleu=alloueMatriceInt(image->hauteurImage, image->largeurImage);                  // Declaration des matrices rouge, vert, bleu de maniere statique
    
    cree3matrices(image, rouge, vert, bleu,image->hauteurImage,image->largeurImage);                        // Stockage des valeurs rouges, vertes et bleues dans les matrices rouge, vert, bleu
    
    staticToDynamic(image->hauteurImage,image->largeurImage,rouge,rouge2);
    staticToDynamic(image->hauteurImage,image->largeurImage,vert,vert2);
    staticToDynamic(image->hauteurImage,image->largeurImage,bleu,bleu2);                // Copie des valeurs des matrices statiques dans les matrices dynamiques
    
    traitement(image->hauteurImage,image->largeurImage, rouge2, q);
    printf("rouge\n");
    traitement(image->hauteurImage,image->largeurImage, vert2, q);
    printf("vert\n");
    traitement(image->hauteurImage,image->largeurImage, bleu2, q);                                    // Traitement des donnees pour chaque matrice
    printf("bleu\n");
    
    matricesVersImage(image, rouge2, vert2, bleu2,image->hauteurImage, image->largeurImage);   // Envoi des donnees traitees dans l image
    ecrisBMPRGB_Dans(image, "resultats/ImageTraitee.bmp");              // Sauvegarde de l image
    
    freeTabInt2(rouge2, image->hauteurImage);
    freeTabInt2(vert2, image->hauteurImage);            // Liberation de tous les elements alloues dynamiquement
    freeTabInt2(bleu2, image->hauteurImage);
    freeTabInt2(rouge, image->hauteurImage);
    freeTabInt2(vert, image->hauteurImage);
    freeTabInt2(bleu, image->hauteurImage);
    free(image);
}