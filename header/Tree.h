#ifndef TREE_H
#define TREE_H

#include "Node.h"
#include "Command.h"
#include "Test.h"
//#iinclude "Connectors.h"

class Tree{
	private:
		Node* root;

	public:
		Tree();
		Tree(Node*);

		void execute();
			//executes tree using in order traversal
		bool inorder(Node* , bool);

		void inorder();
			//helper function for execute
};

#endif
