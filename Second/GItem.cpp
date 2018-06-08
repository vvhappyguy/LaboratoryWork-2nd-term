#include "Canvas.h"
#include "GItem.h"
#include "logger.h"
#include <string>
#include <cstring>
#include <cstdlib>

//GItem realisation
GItem::GItem()
{
	logger(LOG_INFO,"Default C-tor of GItem");
}
GItem::GItem(int x, int y): _x(x), _y(y)
{
	logger(LOG_INFO,"C-tor with values: %d, %d",x,y);
}
GItem::~GItem()
{
	logger(LOG_INFO,"D-tor of GItem");
}
int GItem::x() const{return this->_x;}
int& GItem::x(){return this->_x;}
int GItem::y() const{return this->_y;}
int& GItem::y(){return this->_y;}


//GFactory realisation
GFactory::GFactory():_types(0)
{
	logger(LOG_INFO,"Default C-tor of GFactory");
}

GFactory::GFactory(const GFactory& other)
{
	for(size_t i = 0;i < this->_types; i++)
	{
		strcpy(this->GTypes[i].TypeId, other.GTypes[i].TypeId);
		this->GTypes[i].factory = other.GTypes[i].factory;
	}
	this->_types = other._types;
	logger(LOG_INFO,"Copy C-tor of GFactory");
}

GFactory & GFactory::operator = (const GFactory& other)
{
	for(size_t i = 0;i < this->_types;i++)
	{
		strcpy(this->GTypes[i].TypeId, other.GTypes[i].TypeId);
		this->GTypes[i].factory = other.GTypes[i].factory;
	}
	this->_types = other._types;
	logger(LOG_INFO,"Operator = of GFactory");
	return *this;
}

void GFactory::registerType(const char* typeID, Factory* factory)
{
	//logger(LOG_INFO,"Registered New Type %s",typeID);
	//strncpy(this->GTypes[this->_types].TypeId,typeID,20);
	for(int i = 0; i < 20; i++)
		this->GTypes[this->_types].TypeId[i] = typeID[i];
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
		if(strcmp(this->GTypes[i].TypeId,typeID) == 0)
		{
			return GTypes[i].factory;
		}
	}
	logger(LOG_WARN,"No such type resgistered");
	return NULL;
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
	logger(LOG_INFO,"Draw Pixel at(%d,%d)",this->x(),this->y());
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
{logger(LOG_INFO,"C-tor GLine with values:(%d,%d) to (%d,%d)",x,y,dx,dy);}

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

void GLine::draw(Canvas& canvas)
{
	int x1 = this->x();
	int y1 = this->y();
	int delX = abs(this->dx() - this->x());
	int delY = abs(this->dy() - this->y());
	int zX = this->x() < this->dx() ? 1 : -1;
	int zY = this->y() < this->dy() ? 1 : -1;
	int error = delX - delY;
	canvas.pixel(_dx, _dy) = '*';
	while(x1!=this->dx() || y1!=this->dy())
	{
		canvas.pixel(x1,y1) = '*';
		int error2 = error*2;
		if(error2 > -delY)
		{
			error -= delY;
			x1 += zX;
		}
		error += delX;
		y1 += zY;
	}
	logger(LOG_INFO,"Draw line from (%d,%d) to (%d,%d)",this->x(),this->y(),this->dx(),this->dy());
}

//GCircle realisation
GCircle::GCircle(){logger(LOG_INFO,"Default C-tor of GCircle");}

GCircle::GCircle(int x, int y, int r):GItem(x,y), _r(r)
{logger(LOG_INFO,"C-tor GCircle with values %d, %d, %d",x,y,r);}

void GCircle::draw(Canvas& canvas)
{
	int x = 0;
	int y = _r;
   int del = 1-2*_r;
	int error = 0;
	while(y >= 0)
	{
		canvas.pixel(_x + x, _y + y) = '*';
		canvas.pixel(_x + x, _y - y) = '*';
		canvas.pixel(_x - x, _y + y) = '*';
		canvas.pixel(_x - x, _y - y) = '*';
		error = 2 * (del + y) - 1;
		if( (del < 0) && (error <= 0))
			del += 2*++x + 1;
		error = 2*(del - x) - 1;
		if((del > 0) && (error >0))
			del += 1-2*--y;
		x++;
		del +=2*(x-y);
		y--;
	}
	logger(LOG_INFO,"Drawing circle. R = %d with center:(%d, %d)",this->r(), this->x(), this->y());

}

void GCircle::save(std::ostream& ostr)
{
	ostr << "GCircle " << this->x() << " " << this->y() << " " << this->r() << std::endl;
	logger(LOG_INFO,"Circle saved");
}

void GCircle::restore(std::istream& istr)
{
	if(istr)
	{
		istr >> _x >> _y >> _r;
		logger(LOG_INFO, "Restored GCircle");
	}
	else
	{
		logger(LOG_ERROR, "ERROR in GCircle.restore()");
		throw 10;
	}
}

GItem* GCircle::clone()
{
	logger(LOG_INFO, "Cloned GCircle");
	return new GCircle(_x,_y,_r);
}

GItem* GCircle::factory()
{
	logger(LOG_INFO, "GCircle Factory");
	return new GCircle();
}
	 
int GCircle::r() const{return this->_r;}
int& GCircle::r(){return this->_r;}

//GPicture realisation
GPicture::GPicture():_head(NULL){logger(LOG_INFO,"Default C-tor of Picture");}
GPicture::GPicture(const GPicture& other):_head(other._head){logger(LOG_INFO,"Copy C-tor");}

void GPicture::save(const char * filename) const
{
	std::ofstream ostr(filename);
	if(!ostr.is_open())
	{
		logger(LOG_WARN, "Can't open filename for GPict.save() : %s",filename);
		throw 11;
	}
	Node* it = _head;
	while(it != NULL)
	{
		it->item->save(ostr);
		it = it->next;
	}
	ostr.close();
	logger(LOG_INFO, "Saved GPicture to file: %s", filename);
}

void GPicture::draw(Canvas& canvas) const
{
	Node* it = _head;
	while(it != NULL)
	{
		it->item->draw(canvas);
		it = it->next;
	}
	logger(LOG_INFO, "Draw GPicture to Canvas(%d)", &canvas);
}

size_t GPicture::numItems()const
{
	size_t count = 0;
	if(this->_head)
	{
		Node* it = this->_head;
		while(it->next)
		{
			it = it->next;
			count++;
		}
	logger(LOG_INFO, "Counted len %d of GPicture list", count);
	return count;
	}
}

GItem*& GPicture::at(size_t pos)
{
	Node* it = this->_head;
	for(size_t i = 0; i < pos; ++i)
		it = it-> next;
	return it->item;
}

const GItem* GPicture::at(size_t pos) const
{
	Node* it = this->_head;
	for(size_t i = 0; i < pos; ++i)
		it = it->next;
	return it->item;
}

void GPicture::push_back(GItem* Item)
{
	Node* tmp = new Node();
	tmp->item = Item;
	tmp->next = NULL;
   Node* iter = _head;

	if(_head != NULL)
	{
		while(iter->next != NULL)
			iter = iter->next;
		iter->next = tmp;
	}
	if(_head == NULL)
	{
		_head = tmp;
	}
	logger(LOG_INFO, "PushBack GItem to GPicture");
}

void GPicture::load(const char* filename)
{
	std::ifstream istr(filename);
	if(!istr) throw 13;

	GFactory::instance().registerType("GPixel", GPixel::factory);
	GFactory::instance().registerType("GLine",GLine::factory);
	GFactory::instance().registerType("GCircle",GCircle::factory);
	char* typeID = new char[20];
	while(!istr.eof())
	{
		istr >> typeID;
		if(istr.eof()) break;
		GItem* factory = GFactory::instance().getFactory(typeID)();
		if(factory != NULL)
		{
			factory->restore(istr);
			push_back(factory);
			istr.get();
		}
		else
			throw 14;
	}
	istr.close();
	logger(LOG_INFO,"Loaded from file %s", filename);
}

GPicture::~GPicture()
{
	while(this->_head != NULL)
	{
		Node* it = _head->next;
		delete _head;
		_head = it;
	}
	logger(LOG_INFO,"GPicture D-tor");
}

// void GPicture::add(GItem* Item, size_t pos)
// {
// 	if(pos < 0 || pos > this->numItems())
// 	{
// 		logger(LOG_WARN,"Bad value %d in GPicture.add()",pos);
// 		throw 15;
// 	}
// 	if(pos == 0)
// 	{
// 		Node* node = new Node();
// 		node->next = this->_head;
// 		this->_head = node;
// 	}
// 	else
// 	{
// 		int count = 0;
// 		Node* tmp = this->_head;
// 		while(count < pos)
// 		{
// 			if(count != pos - 1)
// 			{
// 				tmp = tmp->next;
// 				count++;
// 			}
// 			else
// 			{
// 				Node* node = new Node();
// 				Node* tmp1 = tmp->next;
// 				tmp->next = node;
// 				node->next = tmp1;
// 			}
// 		}
// 	}
// 	logger(LOG_INFO,"Added GItem to pos(%d)",pos);
// }

void GPicture::del(size_t pos)
{
    if (pos > this->numItems())
        throw 19;
    Node * it = _head;
    if (pos == 0)
    {
        if (it->next)
        {
            _head = it->next;
            delete it;
            return;
        }
        else
        {
            _head = NULL;
            return;
        }
    }
    for (int i = 0; i < pos - 1; i++)
    {
        it = it->next;
    }
    Node * it1 = it->next;
    if (it1->next)
    {
        Node * it2 = it1->next;
        delete it1;
        it->next = it2;
    }
    else
    {
        delete it1;
        it->next = NULL;
    }
}
