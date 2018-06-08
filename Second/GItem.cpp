#include "Canvas.h"
#include "GItem.h"
#include "logger.h"
#include <string>
#include <cstring>

//GItem realisation
GItem::GItem()
{
	logger(LOG_INFO,"Default C-tor of GItem");
}
GItem::GItem(int x, int y): _x(x), _y(x)
{
	logger(LOG_INFO,"C-tor with values: %d, %d",x,y);
}
virtual GItem::~GItem()
{
	logger(LOG_INFO,"D-tor of GItem")
}
int GItem::x() const{return this->_x;}
int& Gitem::x(){return this->_x;}
int GItem::y() const{return this->_y;}
int& GItem::y(){return this->_y;}


//GFactory realisation
GFactory::GFactory():_types(0)
{
	logger(LOG_INFO,"Default C-tor of GFactory");
}

void GFactory::registerType(const char* typeID, Factory* factory)
{
	logger(LOG_INFO,"Registered New Type %s",typeID);
	strncpy(this->GTypes[this->_types].TypeId,typeID,20);
	this->GTypes[this->_types].factory = factory;
	this->_types++;
}

GFactory::Factory* GFactory::getFactory(const char* typeID) const
{
	if(strlen(typeID) < 0)
	{
		throw 6;
		logger(LOG_ERROR,"Getted len=0 name of GItem");
	}
	for(size_t i = 0;i < this->_types;i++)
	{
		if(strcmp(this->GTypes[i].TypeId,typeID)
		{
			return this->GTypes[i].factory;
		}
	}
	logger(LOG_WARN,"No such type resgistered");
	return NULL;
}

GFactory::GFactory(const GFactory& other)
{
	this->_types = other.types;
	for(size_t i = 0;i < this->_types; i++)
	{
		strcpy(this->GTypes[i].TypeId, other.GTypes[i].TypeId);
		this->GTypes[i].factory = other.GTypes[i].factory;
	}
	logger(LOG_INFO,"Copy C-tor of GFactory");
}

GFactory::GFactory & GFactory::operator = (const GFactory& other)
{
	this->_types = other.types;
	for(size_t i = 0;i < this->_types;i++)
	{
		strcpy(this->GTypes[i].TypeId, other.GTypes[i].TypeId);
		this->GTypes[i].factory = other.GTypes[i].factory;
	}
	logger(LOG_INFO,"Operator = of GFactory");
	return *this;
}


//GPixel realisation
GPixel::GPixel()
{
	logger(LOG_INFO,"Default C-tor of GPixel");
}

GPixel::GPixel(int x, int y, int c):GItem(x,y), _c(c)
{
	logger(LOG_INFO,"C-tor of GPixel with values: %d %d %c",x,y,c);
}

void GPixel::save(std::ostream& ostr)
{
	ostr << "GPixel " <<_x << " " << _y << " " << _c << std::endl;
	logger(LOG_INFO,"Save Pixel to file");
}

void GPixel::restore(std::istream& istr)
{
	if(istr)
	{
		istr >> _x >> _y >> _c;
		logger(LOG_INFO, "Restore Pixel from file");	
	}
	else
	{
		throw 7;
		logger(LOG_ERROR, "ERROR in restore() Pixel");
	}
}

void GPixel::draw(Canvas& canvas)
{
	canvas.pixel(this->x(),this->y()) = this->_c;
}

GItem* GPixel::clone()
{
	logger(LOG_INFO,"Cloned pixel");
	return new GPixel(this->x(), this->y(),this->_c);
}

GItem* GPixel::factory()
{
	logger(LOG_INFO,"GPixel factory");
	return new GPixel();
}

char GPixel::c() const{return this->_c;}
char& GPixel::c(){return this->_c;}

//GLine realisation

GLine::GLine(){logger(LOG_INFO,"Default C-tor GLine");}

GLine::GLine(int x, int y, int dx, int dy): GItem(x, y), _dx(dx), _dy(dy)
{logger(LOG_INFO,"C-tor GLine with values:(%d,%d) to (%d,%d)",x,y,dx,dy);

void GLine::save(std::ostream& ostr)
{
	ostr << "GLine " << x() << " " << y() << " " << dx() << " " << dy() << std::endl;
	logger(LOG_INFO,"Save Line to file");
}

void GLine::restore(std::istream& istr)
{
	if(istr)
	{
		istr >> this->x() >> this->y() >> this->dx() >> this->dy();
		logger(LOG_INFO, "Restored GLine from file");
	}
	else
	{
		logger(LOG_ERROR, "ERROR in GLine.restore()");
		throw 8;
	}
}

GItem* GLine::clone()
{
	logger(LOG_INFO,"Clonned line");
	return new GLine(this->x(), this->y(), this->dx(), this->dy());
}

GItem* GLine::factory()
{
	logger(LOG_INFO,"GLine Factory");
	return new GLine();
}

int GLine::dx() const{return this->_dx;}
int& GLine::dx(){return this->_dx;}
int GLine::dy() const{return this->_dy;}
int& GLine::dy(){return this->_dy;}


