#ifndef __TREE__H_
#define __TREE__H_

#include "p2List.h"
#include "Stack.h"


template <class Type>
class NodeTree{
public:
	Type data;
	NodeTree* parent;
	p2List<NodeTree*> child;

	NodeTree(){}

	void PreOrderRecursive(p2List<NodeTree<Type>*>* list) {
		list->add(this);

		
		p2List_item<NodeTree*>* tmp = child.start;
		while (tmp)
		{
			tmp->data->PreOrderRecursive(list);
			tmp = tmp->next;
		}

	}

	void PostOrderRecursive(p2List<NodeTree<Type>*>* list){

		p2List_item<NodeTree*>* tmp = child.start;
		
		while (tmp){
			tmp->data->PostOrderRecursive(list);
			tmp = tmp->next;
		}

		list->add(this);
	}

	
	void InOrderRecursive(p2List<NodeTree<Type>*>* list){

		int firstChilds = (child.count() != 1) ? child.count()/2 : 1;
	
		for (int i = 0; i < firstChilds; i++)
		{
			NodeTree<Type>* thisChild;
			child.at(i, thisChild);
			thisChild->InOrderRecursive(list);
		}
			
		
		list->add(this);

		for (int i = firstChilds; i < child.count(); i++)
		{
			NodeTree<Type>* thisChild;
			child.at(i, thisChild);
			thisChild->InOrderRecursive(list);
		}

	}

};


template <class Type>
class Tree{
public:
	NodeTree<Type> rootNode;

	Tree(){ rootNode = NULL; }
	Tree(const Type& _data){ rootNode.data = _data; rootNode.parent = NULL; }

	NodeTree<Type>* Add(const Type& _data){
		NodeTree<Type>* item = new NodeTree<Type>;

		item->parent = &rootNode;
		item->data = _data;

		rootNode.child.add(item);

		return item;
	}

	NodeTree<Type>* Add(const Type& data, NodeTree<Type>* _parent){
		NodeTree<Type>* item = new NodeTree<Type>;
		item->data = data;
		

		if (_parent)
		{
			item->parent = _parent;
			_parent->child.add(item);
		}
		else
		{
			rootNode.child.add(item);
			item->parent = &rootNode;
		}

		return item;
		
	}

	void PostOrderIterative(p2List<NodeTree<Type>*>* list){
		
		Stack<NodeTree<Type>*> stack;

		NodeTree<Type>* node = &rootNode;

		while (node || stack.Pop(node))
		{
			p2List_item<NodeTree<Type>*>* tmp = node->child.end;
			if (tmp && list->find(tmp->data) == -1)
			{
				stack.Push(node);
				while (tmp != node->child.start)
				{
					stack.Push(tmp->data);
					tmp = tmp->prev;
				}
				node = tmp->data;
			}
			else
			{
				list->add(node);
				node = NULL;
			}
		}
	}


	void InOrderIterative(p2List<NodeTree<Type>*>* list){
		Stack<NodeTree<Type>*> stack;
		NodeTree<Type>* node = &rootNode;

		bool done = false;
		while (!done)
		{
			if (node != NULL)
			{
				if (list->find(node) == -1)
					stack.Push(node);
				if (node->child.count() != 0)
					node = node->child.start->data;
				else
					node = NULL;
				
			}
			else
			{
				if (stack.Count() > 0)
				{
					stack.Pop(node);
					list->add(node);
					if (node->child.count() != 0)
						node = node->child.end->data;
					else
						node = NULL;
				}
				else
					done = true;
			}
			
		}

		

	}
	void PreOrderIterative(p2List<NodeTree<Type>*>* list){

		Stack<NodeTree<Type>*> stack;

		NodeTree<Type>* node = &rootNode;

		while (node || stack.Pop(node))
		{
			list->add(node);
			p2List_item<NodeTree<Type>*>* tmp = node->child.end;
			while (node->child.start != tmp)
			{
				stack.Push(tmp->data);
				tmp = tmp->prev;
			}
			if (tmp == NULL)
				node = NULL;
			else
				node = tmp->data;
		}
	}

	


	void PostOrderRecursive(p2List<NodeTree<Type>*>* list){
		rootNode.PostOrderRecursive(list);
	}



	void PreOrderRecursive(p2List<NodeTree<Type>*>* list){

		rootNode.PreOrderRecursive(list);
	}

	void InOrderRecursive(p2List<NodeTree<Type>*>* list){
		rootNode.InOrderRecursive(list);
	}
	

	void Clear(){
		Clear(&rootNode);
	}
	

	void Clear(NodeTree<Type>* node){

		NodeTree<Type>* deleteNode = node;
	
		if (deleteNode == NULL)
			return;

		if (deleteNode->parent)
		{
			if (deleteNode->child.count() != 0)
			{
				p2List_item<NodeTree<Type>*>* tmp = deleteNode->parent->child.start;
				while (tmp)
				{
					if (tmp->data == deleteNode)
					{
						deleteNode->parent->child.del(tmp);
						return;
					}

					tmp = tmp->next;
				}
			}
			
		}

		if (deleteNode->child.count() != 0)
		{
			if (deleteNode->child.end->data)
				Clear(deleteNode->child.end->data);
			if (deleteNode->child.start->data)
				Clear(deleteNode->child.start->data);
		}
		
			
		
		delete deleteNode;

	}

	

};


#endif // !__TREE__H_

