#ifndef __QEUE_H__
#define __QEUE_H__

template<class Type>
struct node{
	Type value;
	node<Type>* next;
	node<Type>* prev;
};

template<class Type>
class Qeue{

public:
	node<Type>* start;
	node<Type>* end;

private:
	unsigned int size;

public:

	//Constructor

	Qeue()
	{
		start = end = NULL;
		size = 0;
	}

	//Destructor

	~Qeue()
	{
	}

	//Methods

	

	void Push(const Type data){

		node<Type>* item;
		item = new node <Type>;
		item->value = data;

		if (start != NULL)
		{
			item->prev = end;
			end->next = item;
			end = item;
			item->next = NULL;
		}
		else
		{
			start = end = item;
			item->prev = item->next = NULL;
		}

		size++;

	}

	bool Pop(Type& value){
		
		if (start)
		{

			value = start->value;
			Delete(start);
			return true;
		}
		else
		{
			return false;
		}
			
		
		
	}


	
private:

	bool Delete(node<Type>* item){

		if (item == NULL)
			return false;

		if (item->prev != NULL)
		{
			item->prev->next = item->next;
			if (item->next != NULL)
			{
				item->next->prev = item->prev;
			}
			else
			{
				end = item->prev;
			}

		}
		else
		{
			if (item->next == NULL)
			{
				start = end = NULL;
			}
			else
			{
				start = item->next;
				item->next->prev = NULL;
			}
		}

		delete item;
		size--;
		return true;
	}

	unsigned int Count()
	{
		return size;
	}



};


#endif