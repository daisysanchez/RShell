#ifndef NODE_H
#define NODE_H

#include <string>

using std::string;

class Node{
	private: 
		Node* left;
		Node* right;
		Node* parent;

		string data;

	public:	
		Node();
		Node(string);
		
		//setters
		void setLeft(Node*);
		void setRight(Node*);
		void setParent(Node*);
		void setData(string);

		//getters
		Node* getLeft();
		Node* getRight();
		Node* getParent();
		string str();

		bool execute();
};

#endif
