
# Explications Projet THS

## Compression d'images

###Premiere etape : Chargement de l'image

L’image JPEG est chargee dans un objet X qui comporte une matrice de pointeurs sur des objets de classe Y.
On considere une matrice NxN dont le nombre de lignes et de colones est un multiple de 8.
Si l'image n'est pas décomposable en blocs de 8x8, on complète la matrice de 0 à la fin de chaque ligne et chaque colonne.

![GitHub Logo](/images/Complet0.jpg)
Format: ![Alt Text](https://github.com/aroy314/projetTHS/)

###Deuxieme etape : Recuperation RGB

Pour faciliter les operations, nous privilegeons la separation de notre matrice de base NxN en trois sous matrices NxN. Celles-ci correspondent à 3 composantes d'un pixel : Rouge Vert et Bleu.

###Troisieme etape : Operations sur les blocs 8x8

####**Discret Cosin Transform**

On filtre les informations grace à la transformee en cosinus qui donne accès aux fréquences. Le calcul de la DCT permet la transformation de notre image, la compression. Il contient 4 boucles de 0 = M − 1. Ici l’algorithme considere des matrices M = 8.  Il suffit de leur appliquer la formule de la DCT. 

##### **Quantification** 

On va diminuer la precision des frequences elevees, en divisant chaque element DCT par l’element correspondant.


##### **Zig Zag** 

La methode Zigzag permet de regrouper les eleéments, en suite d'octets et effectuer une linearisation. Elle nous permet d'ecrire la matrice dans un fichier.


![GitHub Logo](/images/zigzag.jpg)
Format: ![Alt Text](https://github.com/aroy314/projetTHS/)


