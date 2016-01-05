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
#include "chrg_img.hpp"
#include "OutilsLib.h"
#include "BmpLib.h"
#include "BmpLibfri.h"

using namespace std;

int main(int argc, const char * argv[]) {
    
   //allocation de l'objet image
        //le constructeur charge l'img et alloue les 3 matrices
	char *nom_image = (char*) argv[1];
	DonneesImageRGB *imagemesboules = NULL;
	imagemesboules = lisBMPRGB(nom_image);
	
    Image *image = new Image(imagemesboules);
	
    image->compression();
	
    cout << "fin du traitement\n" ;
	
	delete image;

	return 0;
}
