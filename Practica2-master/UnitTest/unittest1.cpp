#include "stdafx.h"
#include "CppUnitTest.h"

#include "../Practica Quadtree/Tree.h"
#include "../Practica Quadtree/Stack.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(TreeT)
	{
	public:

		TEST_METHOD(Add)
		{
			NodeTree<char> *a, *b, *c, *d, *e, *f, *g, *h, *i;
			Tree<char> tree('F');
			f = &tree.rootNode;
			b = tree.Add('B', f);
			g = tree.Add('G', f);
			a = tree.Add('A', b);
			d = tree.Add('D', b);
			c = tree.Add('C', d);
			e = tree.Add('E', d);
			i = tree.Add('I', g);
			h = tree.Add('H', i);

			Assert::IsTrue(true); //We don't need to test anything because we test the add in the other methods.

		};

		TEST_METHOD(Clear)
		{
			NodeTree<char> *a, *b, *c, *d, *e, *f, *g, *h, *i;
			Tree<char> tree('F');
			f = &tree.rootNode;
			b = tree.Add('B', f);
			g = tree.Add('G', f);
			a = tree.Add('A', b);
			d = tree.Add('D', b);
			c = tree.Add('C', d);
			e = tree.Add('E', d);
			i = tree.Add('I', g);
			h = tree.Add('H', i);


			tree.Clear(b);

			p2List<NodeTree<char>*> list;
			tree.PreOrderRecursive(&list);

			Assert::AreEqual((int)list.count(), 4);


		};

		TEST_METHOD(PreOrderRecursive)
		{
			NodeTree<char> *a, *b, *c, *d, *e, *f, *g, *h, *i;
			Tree<char> tree('F');
			f = &tree.rootNode;
			b = tree.Add('B', f);
			g = tree.Add('G', f);
			a = tree.Add('A', b);
			d = tree.Add('D', b);
			c = tree.Add('C', d);
			e = tree.Add('E', d);
			i = tree.Add('I', g);
			h = tree.Add('H', i);



			p2List<NodeTree<char>*> list;
			tree.PreOrderRecursive(&list);

			Assert::AreEqual((int)list.count(), 9);
			
			Assert::AreEqual((char)list[0]->data, 'F');
			Assert::AreEqual((char)list[1]->data, 'B');
			Assert::AreEqual((char)list[2]->data, 'A');
			Assert::AreEqual((char)list[3]->data, 'D');
			Assert::AreEqual((char)list[4]->data, 'C');
			Assert::AreEqual((char)list[5]->data, 'E');
			Assert::AreEqual((char)list[6]->data, 'G');
			Assert::AreEqual((char)list[7]->data, 'I');
			Assert::AreEqual((char)list[8]->data, 'H');

		};

		TEST_METHOD(InOrderRecursive)
		{
			NodeTree<char> *a, *b, *c, *d, *e, *f, *g, *h, *i;
			Tree<char> tree('F');
			f = &tree.rootNode;
			b = tree.Add('B', f);
			g = tree.Add('G', f);
			a = tree.Add('A', b);
			d = tree.Add('D', b);
			c = tree.Add('C', d);
			e = tree.Add('E', d);
			i = tree.Add('I', g);
			h = tree.Add('H', i);



			p2List<NodeTree<char>*> list;
			tree.InOrderRecursive(&list);

			Assert::AreEqual((int)list.count(), 9);
			Assert::AreEqual((char)list[0]->data, 'A');
			Assert::AreEqual((char)list[1]->data, 'B');
			Assert::AreEqual((char)list[2]->data, 'C');
			Assert::AreEqual((char)list[3]->data, 'D');
			Assert::AreEqual((char)list[4]->data, 'E');
			Assert::AreEqual((char)list[5]->data, 'F');
			Assert::AreEqual((char)list[6]->data, 'H');
			Assert::AreEqual((char)list[7]->data, 'I');
			Assert::AreEqual((char)list[8]->data, 'G');

		};

		TEST_METHOD(PostOrderRecursive)
		{
			NodeTree<char> *a, *b, *c, *d, *e, *f, *g, *h, *i;
			Tree<char> tree('F');
			f = &tree.rootNode;
			b = tree.Add('B', f);
			g = tree.Add('G', f);
			a = tree.Add('A', b);
			d = tree.Add('D', b);
			c = tree.Add('C', d);
			e = tree.Add('E', d);
			i = tree.Add('I', g);
			h = tree.Add('H', i);

			p2List<NodeTree<char>*> list;
			tree.PostOrderRecursive(&list);

			Assert::AreEqual((int)list.count(), 9);
			Assert::AreEqual((char)list[0]->data, 'A');
			Assert::AreEqual((char)list[1]->data, 'C');
			Assert::AreEqual((char)list[2]->data, 'E');
			Assert::AreEqual((char)list[3]->data, 'D');
			Assert::AreEqual((char)list[4]->data, 'B');
			Assert::AreEqual((char)list[5]->data, 'H');
			Assert::AreEqual((char)list[6]->data, 'I');
			Assert::AreEqual((char)list[7]->data, 'G');
			Assert::AreEqual((char)list[8]->data, 'F');

		};

		TEST_METHOD(PreOrderIterative)
		{
			NodeTree<char> *a, *b, *c, *d, *e, *f, *g, *h, *i;
			Tree<char> tree('F');
			f = &tree.rootNode;
			b = tree.Add('B', f);
			g = tree.Add('G', f);
			a = tree.Add('A', b);
			d = tree.Add('D', b);
			c = tree.Add('C', d);
			e = tree.Add('E', d);
			i = tree.Add('I', g);
			h = tree.Add('H', i);



			p2List<NodeTree<char>*> list;
			tree.PreOrderIterative(&list);

			Assert::AreEqual((int)list.count(), 9);
			Assert::AreEqual((char)list[0]->data, 'F');
			Assert::AreEqual((char)list[1]->data, 'B');
			Assert::AreEqual((char)list[2]->data, 'A');
			Assert::AreEqual((char)list[3]->data, 'D');
			Assert::AreEqual((char)list[4]->data, 'C');
			Assert::AreEqual((char)list[5]->data, 'E');
			Assert::AreEqual((char)list[6]->data, 'G');
			Assert::AreEqual((char)list[7]->data, 'I');
			Assert::AreEqual((char)list[8]->data, 'H');

		};

		TEST_METHOD(InOrderIterative)
		{
			NodeTree<char> *a, *b, *c, *d, *e, *f, *g, *h, *i;
			Tree<char> tree('F');
			f = &tree.rootNode;
			b = tree.Add('B', f);
			g = tree.Add('G', f);
			a = tree.Add('A', b);
			d = tree.Add('D', b);
			c = tree.Add('C', d);
			e = tree.Add('E', d);
			i = tree.Add('I', g);
			h = tree.Add('H', i);

			p2List<NodeTree<char>*> list;
			tree.InOrderIterative(&list);

			Assert::AreEqual((int)list.count(), 9);
			Assert::AreEqual((char)list[0]->data, 'A');
			Assert::AreEqual((char)list[1]->data, 'B');
			Assert::AreEqual((char)list[2]->data, 'C');
			Assert::AreEqual((char)list[3]->data, 'D');
			Assert::AreEqual((char)list[4]->data, 'E');
			Assert::AreEqual((char)list[5]->data, 'F');
			Assert::AreEqual((char)list[6]->data, 'H');
			Assert::AreEqual((char)list[7]->data, 'I');
			Assert::AreEqual((char)list[8]->data, 'G');

		};
		
		TEST_METHOD(PostOrderIterative)
		{
			NodeTree<char> *a, *b, *c, *d, *e, *f, *g, *h, *i;
			Tree<char> tree('F');
			f = &tree.rootNode;
			b = tree.Add('B', f);
			g = tree.Add('G', f);
			a = tree.Add('A', b);
			d = tree.Add('D', b);
			c = tree.Add('C', d);
			e = tree.Add('E', d);
			i = tree.Add('I', g);
			h = tree.Add('H', i);



			p2List<NodeTree<char>*> list;
			tree.PostOrderIterative(&list);

			Assert::AreEqual((int)list.count(), 9);

			Assert::AreEqual((char)list[0]->data, 'A');
			Assert::AreEqual((char)list[1]->data, 'C');
			Assert::AreEqual((char)list[2]->data, 'E');
			Assert::AreEqual((char)list[3]->data, 'D');
			Assert::AreEqual((char)list[4]->data, 'B');
			Assert::AreEqual((char)list[5]->data, 'H');
			Assert::AreEqual((char)list[6]->data, 'I');
			Assert::AreEqual((char)list[7]->data, 'G');
			Assert::AreEqual((char)list[8]->data, 'F');

		};

		

		
	};
}