// ----------------------------------------------------
// Quadtree implementation --
// ----------------------------------------------------

#ifndef __P2QUADTREE_H__
#define __P2QUADTREE_H__

#include "Collider.h"
#include "p2DynArray.h"

#define QUADTREE_MAX_ITEMS 2

// Helper function to check if one rectangle complately contains another
bool Contains(const SDL_Rect& a, const SDL_Rect& b);
bool Intersects(const SDL_Rect& a, const SDL_Rect& b);

// Tree node -------------------------------------------------------
class p2QuadTreeNode
{

public:

	SDL_Rect				rect;
	p2DynArray<Collider*>	objects;
	p2QuadTreeNode*			parent;
	p2QuadTreeNode*			childs[4];

public:

	p2QuadTreeNode(SDL_Rect r) :
		rect(r),
		objects(QUADTREE_MAX_ITEMS)
	{
		parent = childs[0] = childs[1] = childs[2] = childs[3] = NULL;
	}

	~p2QuadTreeNode()
	{
		for (int i = 0; i < 4; ++i)
			if (childs[i] != NULL) delete childs[i];
	}
	
	void Insert(Collider* col)
	{
		// TODO: Insertar un nou Collider al quadtree
		// En principi cada node por enmagatzemar QUADTREE_MAX_ITEMS nodes (encara que podrien ser més)
		// Si es detecten més, el node s'ha de tallar en quatre
		// Si es talla, a de redistribuir tots els seus colliders pels nous nodes (childs) sempre que pugui
		// Nota: un Collider pot estar a més de un node del quadtree
		// Nota: si un Collider intersecciona als quatre childs, deixar-lo al pare

		if (childs[0] == NULL) //Childs are not created.
		{
			if (objects.Count() >= QUADTREE_MAX_ITEMS)
				CutQuad(col);
			else
				objects.PushBack(col);
		}
		else
		{
			if (IntersectAllChilds(col))  
			{
				objects.PushBack(col);
				
			}
			else
			{
				for (int i = 0; i < 4; i++) //Put the collider in the right child
				{
					if (Intersects(col->rect, childs[i]->rect))
						childs[i]->Insert(col);
				}
			}
			
		}
			
		
	

	}

	int CollectCandidates(p2DynArray<Collider*>& nodes, const SDL_Rect& r) const
	{
		
		// TODO:
		// Omplir el array "nodes" amb tots els colliders candidats
		// de fer intersecció amb el rectangle r
		// retornar el número de intersección calculades en el procés
		// Nota: és una funció recursiva

		int candidates = 0;

		for (int i = 0; i < objects.Count(); i++)
		{
			nodes.PushBack(objects[i]);
			candidates++;
		}
		if (childs[0] != NULL)
		{
			for (int i = 0; i < 4; i++)
			{
				if (Intersects(childs[i]->rect, r))
					candidates += childs[i]->CollectCandidates(nodes, r);
			}
		}

		return candidates;
	}

	void CollectRects(p2DynArray<p2QuadTreeNode*>& nodes)
	{
		nodes.PushBack(this);

		for (int i = 0; i < 4; ++i)
			if (childs[i] != NULL) childs[i]->CollectRects(nodes);
	}

private:
	void CutQuad(Collider* col)
	{
		childs[0] = new p2QuadTreeNode(SDL_Rect{ rect.x, rect.y, rect.w / 2, rect.h / 2 });
		childs[1] = new p2QuadTreeNode(SDL_Rect{ rect.x + (rect.w / 2), rect.y, rect.w / 2, rect.h / 2 });
		childs[2] = new p2QuadTreeNode(SDL_Rect{ rect.x, rect.y + (rect.h / 2), rect.w / 2, rect.h / 2 });
		childs[3] = new p2QuadTreeNode(SDL_Rect{ rect.x + (rect.w / 2), rect.y + (rect.h / 2), rect.w / 2, rect.h / 2 });

		childs[0]->parent = this;
		childs[1]->parent = this;
		childs[2]->parent = this;
		childs[3]->parent = this;

		p2DynArray<Collider*> container = objects;
		objects.Clear(); //We need to clear first because if not crashes.
		for (int i = 0; i < container.Count(); i++)
		{
			Insert(container[i]);
		}
		Insert(col);

	}
	bool IntersectAllChilds(Collider* col)const{
		int counter = 0;
		for (int i = 0; i < 4; i++)
		{
			if (Intersects(col->rect, childs[i]->rect))
				counter++;
		}
		return (counter == 4) ? true : false;
	}

};

// Tree class -------------------------------------------------------
class p2QuadTree
{
public:

	// Constructor
	p2QuadTree() : root(NULL)
	{}

	// Destructor
	virtual ~p2QuadTree()
	{
		Clear();
	}

	void SetBoundaries(const SDL_Rect& r)
	{
		if (root != NULL)
			delete root;

		root = new p2QuadTreeNode(r);
	}

	void Insert(Collider* col)
	{
		if (root != NULL)
		{
			if (Intersects(root->rect, col->rect))
				root->Insert(col);
		}
	}

	void Clear()
	{
		if (root != NULL)
		{
			delete root;
			root = NULL;
		}
	}

	int CollectCandidates(p2DynArray<Collider*>& nodes, const SDL_Rect& r) const
	{
		int tests = 1;
		if (root != NULL && Intersects(root->rect, r))
			tests = root->CollectCandidates(nodes, r);
		return tests;
	}

	void CollectRects(p2DynArray<p2QuadTreeNode*>& nodes) const
	{
		if (root != NULL)
			root->CollectRects(nodes);
	}

public:

	p2QuadTreeNode*	root;

};

#endif // __p2QuadTree_H__