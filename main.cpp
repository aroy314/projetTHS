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
	
    image->compression();
	
    cout << "fin du traitement\n" ;

	return 0;
}
