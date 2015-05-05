#ifndef __STACK_H__
#define __STACK_H__

#include <stdio.h>
#include <assert.h>

#define STACK_BLOCK_SIZE 16

template <class Type>
class Stack{

private:
	Type* data;
	unsigned int allocatedMemory;
	unsigned int numElements;
public:

	Stack() :data(NULL), allocatedMemory(0), numElements(0){ Reallocate(STACK_BLOCK_SIZE); }
	Stack(const unsigned int memSize){ Reallocate(memSize); }

	~Stack(){ if (data != NULL) delete[]data; };

	unsigned int getAllocatedMemory()const{
		return allocatedMemory;
	}

	unsigned int Count() const{
		return numElements;
	}

	void Push(const Type value){

		if (allocatedMemory <= numElements) //We don't have extra memory.
		{
			Reallocate(allocatedMemory + STACK_BLOCK_SIZE);
		}

		data[numElements] = value;
		numElements++;
	}

	bool  Pop(Type &container){
		if (numElements != 0)
		{
			numElements--;
			container = data[numElements];
			return true;
		}
		else
			return false;
	}

	const Type* Peek(unsigned int index) const{
		Type* result = NULL;
		if (numElements > index)
			 result = &data[index];
		
		return result;
	}





	Type& operator[](const unsigned int index){
		assert(index < numElements);

		return data[index];

	}
	const Type& operator[](const unsigned int index) const{
		assert(index < numElements);

		return data[index];
	}

	void Reallocate(unsigned int newMemorySize){

		Type* tmp = data;
		allocatedMemory = newMemorySize;
		data = new Type[allocatedMemory];

		if (tmp != NULL)
		{
			for (unsigned int i = 0; i < numElements; i++)
			{
				data[i] = tmp[i];
			}
			delete[] tmp;
		}

	}


};


#endif