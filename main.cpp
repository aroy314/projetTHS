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

using namespace std;

int main(int argc, const char * argv[]) {
	
    Image *image = new Image();
	
    image->compression();
	
    cout << "fin du traitement\n" ;
	
	delete image;

	return 0;
}
