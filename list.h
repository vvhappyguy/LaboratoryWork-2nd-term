#pragma once

class ListInt
{
  private:
	class Node // класс узла списка - полностью инкапсулирован и недоступен снаружи класса ListInt
	{
	  private:
		int _value;
		Node *_prev, *_next;
		Node();

	  public:
		Node(int value);
		int &value();
		int value() const;
		Node *&prev();
		Node *&next();
	};
	Node *_head, *_tail; // Указатели на голову и хвост списка
	size_t _size;		 // количество элементов
  public:
	ListInt();  // default c-tor
	~ListInt(); // d-tor

	size_t size() const; // получить количество
	bool empty() const;  // предикат пустого списка

	void reverse();						 // поменять порядок на обратный
	void grab_and_append(ListInt &from); // забрать все элементы у другого списка и добавить их в конец этого
	void sort();						 // отсортировать по возрастанию (потом, когда пройдем перегрузку операторов, можно
										 // добавить сюда параметр - функтор сравнения на меньше для любого порядка сортировки)

	class iterator // класс итератора списка
	{
	  private:
		Node *_current;
		iterator(Node *node); // основной конструктор: запрещен для использования вне списка
		friend class ListInt; // чтобы воспользоваться этим конструктором из ListInt он должен быть объявлен дружественным
	  public:
		iterator(const iterator &); // copy c-tor
		~iterator();

		bool valid() const; // true если _current != NULL

		// получить данные
		int &get();
		int get() const;

		void prev(); // перейти к _current->next()
		void next(); // перейти к _current->prev()

		bool equal(const iterator &other) const;
	};

	// фабрики итераторов
	iterator head();
	iterator tail();

	iterator insert(iterator pos, int value); // возвращает позицию после вставленной
	iterator erase(iterator &pos);			  // Обратить внимание: после удаления узла итератор позиции должен стать инвалидным
											  // возвращает итератор указывающий на узел следующий после удаленного

	void push_back(int val); // добавление в конец
	void pop_back();		 // выкинуть последний элемент
							 //...
};