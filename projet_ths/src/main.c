//
//  main.c
//  projet_ths
//
//  Created by Clément Bissonnier on 10/11/2015.
//  Copyright © 2015 Clement Bissonnier. All rights reserved.
//


#include "../lib/matrix.h"
#include "../lib/OutilsLib.h"
#include "../lib/BmpLib.h"
#include "../lib/imageIO.h"



int main(int argc, char * argv[])
{
    float q=0;
    q=saisieQuantification();
    copyImage(argv[1],q);
    argc=1;
    return 0;
}
