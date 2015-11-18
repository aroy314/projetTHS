#include "CImg.h"
#include "iostream"


//Compile with : g++ main.cpp -o main -O2 -L/usr/X11R6/lib -lm -lpthread -lX11


using namespace cimg_library;
using namespace std;

CImg<int> charge_img(const char* file) {
	CImg<int> image (file);
	return image;
}

void save_img(CImg <int> image, const char* file) {
	image.save(file);
}

int* Dimensions(CImg<int> image){
	int* tab = new int[1];
	tab[0] = image.dimx();
	tab[1] = image.dimy();
	return tab;
}

int main() 
{	
	CImg<int> image;
 	image = charge_img("lena.jpg");
	int* tab = Dimensions(image);
	cout << "X = " << tab[0] << endl << "Y = " << tab[1] << endl;

/*	for (int i = 0; i < image.dimx(); i++) {
		for (int j = 0; j < image.dimy(); j++) {
			for (int k = 1; k < 2; k++) {
				image(i,j,0,k)=0;
				}}}


	for (int i = 0; i < image.dimx(); i++){
		for (int j = 0; j < image.dimy(); j++){
			cout << endl;
			for (int k = 0; k < 3; k++){
				cout << image(i,j,0,k);
			}}}
*/

		
	save_img(image, "out.jpg");
	

//  CImgDisplay main_disp(image,"Click a point");
//  while (!main_disp.is_closed()){
//    main_disp.wait();
//   }

  return 0;
}
