#include "../header/Tree.h"

#include <iostream>

using std::cout;
using std::endl;

Tree::Tree(){
	root = nullptr;
}

Tree::Tree(Node* root){
	this->root = root;
}

void Tree::execute(){
	inorder(root, true);
}

/*void Tree::execute(Node* curr){
	if(!=nullptr){
		execute(curr->left);
		execute(curr->right);

		if(curr->right){
			curr->execute;
}*/

//void Tree::inorder(){
//	inorder(root, true);

//}

bool Tree::inorder(Node* curr, bool executed){
	if(curr == nullptr){
		return executed;
	}
	
	executed = inorder(curr->getLeft(), executed);

	//Command* currCommand = new Command(curr->str());
	//executed = currCommand->execute();

	if(curr->str() == ";"){
		return true;
	} else if (curr->str() == "||"){
		executed = inorder(curr->getRight(), !executed);
		//if(!executed){
		//	inorder(curr->getRight(), false);
		//}
	} else if(curr->str() == "&&"){
		executed = inorder(curr->getRight(), executed);
		//if(executed){
		//	inorder(curr->getRight(), true);
		//}
	} else {
			//cout << "curr: " << curr->str() << " " << endl;
			if(executed){
				if(curr->str().size() >3 && curr->str().substr(0,4) == "test"){
					Test* currCommand = new Test(curr->str());
					return currCommand->execute();
				} else if(curr->str().size() > 3 && curr->str().substr(0,4) == "exit"){
					exit(0);
				} else {
					Command* currCommand = new Command(curr->str());
					return currCommand->execute();
				}	
			} else {
				return !executed;
			}
	}
	
	//if(curr->getRight()){
	//	inorder(curr->getRight());
	//}

	//cout << "curr: " << curr->str() << " " << endl;
}
