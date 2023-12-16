#include <iostream>
#define DEFAULT_CAPACITY 5

using namespace std;

template<class Type>
class Node
{
	public:
		Type _data;
		Node *_next;
};

template<class Type>
class list
{
    private:
        Node<Type> *_head;
        int _size;
    public:
        list();
        ~list();
        int size() const;
        void insert(const Type &item);
        bool remove(const Type &item);
        void print();
};

// LinkedList<Type>::

template<class Type>
list<Type>::list()
{
	_head = NULL;
	_size = 0;
}

template<class Type>
list<Type>::~list()
{
	
}

template<class Type>
int list<Type>::size() const
{
	return _size;
}

template<class Type>
void list<Type>::insert(const Type &item)
{
	Node<Type> *temp = new Node<Type>;
	temp->_data = item;

	// if the list is empty
	if (_size == 0)
	{
		_head = temp;
	}
	// if the list has one element
	else if (_size == 1)
	{
		_head->_next = temp;
	}
	else
	{
		// if the list has more than one element
		Node<Type> *current = _head;
		while (current->_next != NULL)
			current = current->_next;

		current->_next = temp;
	}

	_size++;
}

template<class Type>
bool list<Type>::remove(const Type &item)
{
	if (_size == 0)
		return false;

	// bool found = false;

	// remove head element
	if (_head->_data == item)
	{
		_head = _head->_next;
		_size--;
		return true;
	}

	// remove non-head element
	Node<Type> *current = _head;
	while (current->_next != NULL)
	{
		if (current->_next->_data == item)
		{
			current->_next = current->_next->_next;
			_size--;
			return true;
		}

		current = current->_next;
	}

	return false;
}

template<class Type>
void list<Type>::print()
{
	Node<Type> *current = _head;
	while (current != NULL)
	{
		cout << current->_data << " ";
		current = current->_next;
	}
	cout << endl;
}