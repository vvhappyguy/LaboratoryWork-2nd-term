#ifndef __GITEM_H__
#define __GITEM_H__

#include <Canvas.h>

class GItem 
{
	protected:
		int _x,_y; 
	public:
		GItem();
		GItem(int x, int y);
		virtual ~GItem();
		virtual void draw(Canvas&) = 0;
		virtual void save(std::ostream&);
		virtual void restore(std::istream&);

		virtual GItem* clone() = 0;

		int x() const;
		int& x();

		int y() const;
		int& y();
};

class GFactory
{
	public:
		typedef GItem* (Factory)();
	private:
	struct Registry
	{
		char TypeId[20];
		GItem* (factory)();
	} GTypes[100];
	size_t _types;

	GFactory();
	GFactory(const GFactory&);
	GFactory& operator=(const GFactory& other);

	public:

	void registerType(const char* typeId, Factory factory);
	Factory* getFactory(const char* typeId) const;

	static GFactory& instance() { static GFactory _instance; return _instance; }
};


class GPixel : public GItem
{
	protected:
		char _c;
	public:
		GPixel();
		GPixel(int x, int y, int c);

		void draw(Canvas&);
		void save(std::ostream&);
		void restore(std::istream&);
		GItem* clone();

		static GItem* factory();

		char c() const;
		char& c();
};

class GLine : public GItem
{
	protected:
		int _dx, _dy;
	public:
		GLine();
		GLine(int x, int y, int dx, int dy);

		void draw(Canvas&);
		void save(std::ostream&);
		void restore(std::istream&);
		GItem* clone();

		static GItem* factory();

		int dx() const;
		int& dx();
		int dy() const;
		int& dy();
};

class GCircle : public GItem
{
	protected:
		int _r;
	public:
		GCircle();
		GCircle(int x, int y, int r);

		void draw(Canvas&);
		void save(std::ostream&);
		void restore(std::istream&);
		GItem* clone();

		static GItem* factory();

		int r() const;
		int& r();
};


class GPicture
{
	private:
		struct Node
		{
			GItem* item;
			Node* next;
		} *_head;
	public:
		GPicture();
		GPicture(const GPicture& other);
		GPicture& operator=(const GPicture& other);
		~GPicture();

		void load(const char* filename);
		void save(const char* filename) const;
		void draw(Canvas& canvas) const;

		size_t numItems() const;
		GItem*& at(size_t pos);
		const GItem* at(size_t pos) const;

		void add(GItem* item, size_t pos = 0);
		void del(size_t pos = 0);
};

#endif 
