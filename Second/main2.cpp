#include "Canvas.h"
#include "GItem.h"
#include <iostream>
int main() 
{
	Canvas c(70 , 70);
	
	
	GPixel* pix = new GPixel ( 20, 20 , 40);
	GLine* L = new GLine(50,54,32,3);
	GCircle* cr = new GCircle(35, 35, 10);
	GPixel* pix2 = new GPixel(22,22,32);
	GPicture pic;
	pic.push_back(cr);
	pic.push_back(L);		
	pic.push_back(pix);
	pic.del(0);
	pic.draw(c);
	c.draw(std::cout);
	pic.save("txt.txt");
	c.clear();
	

	GPicture Pic2;
	Pic2.load("txt.txt");
	Pic2.draw(c);
	c.draw(std::cout);
	
	return 0;

}
