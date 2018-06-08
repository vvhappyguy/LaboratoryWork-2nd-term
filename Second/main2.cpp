#include "Canvas.h"
#include "GItem.h"
#include <iostream>
int main() 
{
	Canvas c(70 , 70);
	GPixel* pix = new GPixel ( 5, 40 , 45);
	GLine* L = new GLine(10,20,30,40);
	GCircle* cr = new GCircle(35, 35, 20);
	GPicture pic;
	pic.push_back(cr);
	pic.push_back(L);
	pic.push_back(pix);
	pic.draw(c);
	c.draw(std::cout);
	pic.save("text.txt");
	c.clear();

	GPicture Pic2;
	Pic2.load("text.txt");
	Pic2.draw(c);
	c.draw(std::cout);
	
	return 0;

}
