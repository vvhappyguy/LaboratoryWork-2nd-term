#include "Canvas.h"
#include "GItem.h"
#include <iostream>
#include "logger.h"
#include <string>
#include <cstring>
#include <exception>
#include <stdexcept>

using namespace std;

char* Canvas::ROW(size_t r){return this->_canvas + r * (cols() + 1);}
const char* Canvas::ROW(size_t r) const{return this->_canvas + r * (cols() + 1);}

Canvas::Canvas(int rows, int cols):_rows(rows),_cols(cols)
{
	logger(LOG_INFO,"Canvas(%d) C-tor with values(rows:%d, cols:%d).",this, rows, cols);

	this->_canvas = new char[rows*(cols + 1)];
	
	for(size_t r = 0; r < rows; ++r)
	{
		char* row = ROW(r);  // Get pointer to new ROW
		memset(row, ' ', cols);  // Set space symbol all row
		row[cols] = '\0';  // Last symbol for row
	}
}

Canvas::~Canvas()
{
	delete [] this->_canvas;
}

void Canvas::clear()
{
	logger(LOG_INFO,"Canvas(%d) cleared",this);
	for(int i = 0; i < rows(); i++)
	{
		char* row = ROW(i);
		memset(row, ' ', cols());
		row[cols()] = '\0';
	}
}

int Canvas::rows() const{return this->_rows;}
int Canvas::cols() const{return this->_cols;}

void Canvas::draw(ostream& ostr)
{
	logger(LOG_INFO,"Draw Canvas(%d) to some stream", this);
	for(int i = 0; i < rows(); i++)
	{
		char* row = ROW(i);
		ostr << row << endl;
	}
}

void Canvas::checkBounds(int row, int col) const
{
	try
	{
		if(row < 0 || col < 0)
		{
			logger(LOG_WARN,"Got minus value(s): (%d, %d)", row, col);
			throw 2;
		}
		else if(row > rows() || col > cols())
		{
			logger(LOG_WARN,"Value(s)(%d, %d)  out if canvas.", row, col);
			//cout <<  "Bad value(s) " << row << ", " << col << endl;
			throw 1;
		}
		else
		{
			//logger(LOG_INFO,"Good checked values(%d, %d)", row, col);
		}
	}
	catch(int i)
	{
		//cout << "Error = " << i << endl;
	}
}

char& Canvas::pixel(int row, int col)
{
	checkBounds(row, col);
	char* Line = ROW(row);
	return Line[col];
}

Canvas::Canvas(const Canvas & copy)
{
	this->_rows = copy.rows();
	this->_cols = copy.cols();
	memcpy(this->_canvas, copy._canvas, copy._rows * (copy.cols() + 1));
}

Canvas& Canvas::operator=(const Canvas& copy)
{
	this->_rows = copy.rows();
	this->_cols = copy.cols();
	memcpy(this->_canvas, copy._canvas, copy._rows * (copy.cols() + 1));

	return *this;
}

