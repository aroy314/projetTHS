//
//  main.cpp
//  projetTHS
//
//  Created by Alexandre ROY on 16/11/2015.
//  Copyright © 2015 Alexandre ROY. All rights reserved.
//

#include <iostream>
#include <math.h>
#include "image.hpp"
#include "chrg_img.hpp"
#include "OutilsLib.h"
#include "BmpLib.h"
#include "BmpLibfri.h"

using namespace std;

int main(int argc, const char * argv[]) {
    
   //allocation de l'objet image
	
	char *nom_image = NULL;
	if(strlen(argv[1]) == 0){
		cout << "entrez un nom d'image : ";
		cin >> nom_image;
	}else{
		nom_image = (char*) argv[1];
	}
	
	//test
	static DonneesImageRGB *poney = NULL;
	poney = lisBMPRGB(nom_image);
	
    Image *image = new Image(nom_image);
	
    image->compression();
	
    cout << "fin du traitement\n" ;
	
	delete image;

	return 0;
}
