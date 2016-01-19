//
//  main.cpp
//  projetTHS
//
//  Created by Alexandre ROY on 16/11/2015.
//  Copyright © 2015 Alexandre ROY. All rights reserved.
//

#include <iostream>
#include <math.h>
#include "image_comp.hpp"
#include "image_decomp.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
	
    Image_comp *image_comp = new Image_comp();
    image_comp->compression();
	
	Image_decomp *image_decomp = new Image_decomp();
	image_decomp->decompression();
	
    cout << "fin du traitement\n" ;
	
	delete image_comp;
	delete image_decomp;


	return 0;
}
