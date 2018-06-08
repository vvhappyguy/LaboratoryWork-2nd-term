#ifndef __CANVAS_H__
#define __CANVAS_H__

#include <iostream>
#include <fstream>

class Canvas
{
	private:
		Canvas(const Canvas&); // Copy-tor
		Canvas& operator = (const Canvas&); // ":=" = copy-tor
	public:
		Canvas(int rows, int cols); // Basic Canvas C-tor
		~Canvas(); // D-tor

		void clear(); // Clear Canvas
		void draw(std::ostream& ostr = std::cout); // Draw to Console

		int rows() const; // Getter for rows
		int cols() const; // Getter for cols
		char& pixel(int row, int col); // Get and change pixel
		//char pixel(int row, int col) const; // Get pixel
	private:
		char* ROW(size_t r); // Get row
		const char* ROW(size_t r) const; // Get row
		void checkBounds(int row, int cols) const; // Проверка на вхождение пикселя в рамки
		int _rows, _cols; // Rows and Cols
		char* _canvas; // All Canvas
};

#endif // __CANVAS_H__
