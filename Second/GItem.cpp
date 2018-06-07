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
