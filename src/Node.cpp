#include "../header/Node.h"

Node::Node(){
	left = nullptr;
	right = nullptr;
	parent = nullptr;

	data = "";
}

Node::Node(string data){
	left = nullptr;
	right = nullptr;
	parent = nullptr;

	this->data = data;
}

void Node::setLeft(Node* left){
	this-> left = left;
}

void Node::setRight(Node* right){
	this->right = right;
}

void Node::setParent(Node* parent){
	this->parent = parent;
}

void Node::setData(string data){
	this->data = data;
}

Node* Node::getLeft(){
	return left;
}

Node* Node::getRight(){
	return right;
}

Node* Node::getParent(){
	return parent;
}

string Node::str(){
	return data;
}

//bool Node::execute(Node* curr){
//	if(curr->left){
//		execute(curr->left);
//	} 
//
//	if(curr->right){
//		execute(cur 
// return true;
//}
bool Node::execute(){

	if(left){
		left->execute();
	}

	if(this->data == ";"){}
//		Semicolon* semi = new Semicolon(this

	if(right){
		right->execute();
	}

}


	
