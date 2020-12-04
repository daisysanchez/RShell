#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <stack>

//#include "../header/Composite.h"
#include "../header/Node.h"
#include "../header/Tree.h"
//#include "../header/Connectors.h"
//#include "../header/Command.h"
//#include "../header/Ampersand.h"
//#include "../header/Bars.h"
//#include "../header/Semicolon.h"
#include "../header/Parse.h"

using std::cout;
using std::vector;
using std::string;
using std::endl;
using std::stack;
using std::queue;

vector<string> toPostFix(vector<string>);
//convert infix to postfix using shunting yard algorithm

vector<string> createExpressionTree(vector<string>);
//creates vector representing abstract arithmetic expression tree

//vector<string> evaluateExpressionTree(vector<string>);
//evaluates postfix expression of command line input

vector<string> toPostFix(vector<string> parsedCommand){
	vector<string> postFixCommand;
	stack<string> operators;
	
	for(int i=0; i<parsedCommand.size(); i++){
		//cout << parsedCommand.at(i) << " " << endl;
		if(parsedCommand.at(i) == "("){ //paranthesis hold highest precedence
			operators.push(parsedCommand.at(i));
		} else if(parsedCommand.at(i) == ")"){
			while(operators.size() != 0){
				if(operators.top() != "("){
					postFixCommand.push_back(operators.top());
					operators.pop();
				} else {
					operators.pop();
				}
			}

		} else if (parsedCommand.at(i) == ";"){ //semicolon has highest connector precedence
			while(operators.size() != 0 && operators.top() != "("){
				postFixCommand.push_back(operators.top());
				operators.pop();
			}
			postFixCommand.push_back(parsedCommand.at(i));
		} else if (parsedCommand.at(i) == "&&" || parsedCommand.at(i) == "||"){
			if(operators.size() != 0){
				if(operators.top() != ";"){  //if current operator has same precedence
					operators.push(parsedCommand.at(i)); //push operator onto stack
				} else { //if current operator has lower precedence
					while(operators.size() != 0 && operators.top() != "("){ //pop off operators unless (
	                                        postFixCommand.push_back(operators.top()); //then push operator onto expression
        	                                operators.pop();
                                	}
					operators.push(parsedCommand.at(i));
				}
			} else {
				 operators.push(parsedCommand.at(i));
			}
		} else { //if current string is a command
			postFixCommand.push_back(parsedCommand.at(i)); //operands can be pushed onto expression whenever encountered
		}

		//cout << "postFixCommand: ";
		//for(int j=0; j<postFixCommand.size(); j++){
		//	cout << postFixCommand.at(j) << " ";
		//}
		//cout << endl;
	}

	while(operators.size() != 0){
		postFixCommand.push_back(operators.top());
		operators.pop();
	}

	return postFixCommand;
}

vector<string> createExpressionTree(vector<string> postFixCommand){
	vector<string> expressionTree;
	
	if(postFixCommand.size() == 0) return expressionTree; //if no commands, return empty tree

	if(postFixCommand.size() == 1){ //if only one element, it must be a command
		expressionTree.push_back(postFixCommand.at(0)); //push back to tree
		return expressionTree;
	}

	//if theres more than one element in the postFixCommand
	string left; 
	string right;

	for(int i=0; i<postFixCommand.size(); i++){
		left = postFixCommand.at(i); //left is first encountered
		i++; //go to connector
		if(postFixCommand.at(i) == ";"){ //if connector is semicolon
			right = ""; //then there is no right
			expressionTree.push_back(postFixCommand.at(i)); //first push back 

		}

	}

	return expressionTree;
}

int main(){
	
	while(true){ //take in input until exit command

		string commandLine;
		
		cout << "$ "; //prompts user

		getline(std::cin, commandLine); //takes in user input
		cin.clear(); //clears bufferA

		Parse* p = new Parse();

		vector<string> parsedCommand = p->parse(commandLine); //parses commandLine input	

//		parsedCommand.push_back(";");

		vector<string> postFixCommand = toPostFix(parsedCommand); //converts parsed expression into postfix
//		for(int i=0; i<postFixCommand.size(); i++){
//			cout << "\"" << postFixCommand.at(i) << "\"" << " ";
//		}

//		cout << endl;

		//create tree	
		stack<Node*> expression;

		for(int i=0; i<postFixCommand.size(); i++){ //goes through postfix command
//			cout << "curr: " << postFixCommand.at(i) << endl;
			if(postFixCommand.at(i) == ";"){
				Node* left = new Node();
				left = expression.top();
				expression.pop();
				
				Node* semicolon = new Node(postFixCommand.at(i));
				semicolon->setLeft(left);
//				cout << "semi left: " << semicolon->getLeft()->str() << endl;
				left->setParent(semicolon);
				expression.push(semicolon);
			} else if(postFixCommand.at(i) == "&&" || postFixCommand.at(i) == "||"){
				Node* right = new Node();
				right = expression.top();
				expression.pop();
				Node* left = new Node();
				left = expression.top();
				expression.pop();

				Node* connector = new Node(postFixCommand.at(i));
				connector->setLeft(left);
//				cout << "conn left: " << connector->getLeft()->str() << endl;
				left->setParent(connector);
				connector->setRight(right);
//				cout << "conn right: " << connector->getRight()->str() << endl;
				right->setParent(connector);

				expression.push(connector);                         
                             
                        } else {
				Node* operand = new Node(postFixCommand.at(i));
				expression.push(operand);
			}

		}
		//bool size = expression.size() == 1;
		//cout << expression.size() << endl;
			//tree will consist of node*
			//each node* has a * to left, right, parent
			//and str containting an element of parsedVector
/*		while(expression.size() != 1){
			Node* left = expression.top();
			expression.pop();
			
			Node* right = expression.top();
			expression.pop();
			Node* command = new Node(";");
			command->setLeft(left);
			left->setParent(command);
			command->setRight(right);
			right->setParent(command);

			expression.push(command);
	
		}
*/
//		cout << expression.size() << endl;

		stack<Node*> expressionTrees;

		while(expression.size()!=0){
			Node* subExpression = new Node();
			subExpression = expression.top();
			expressionTrees.push(subExpression);
			expression.pop();
		}



		while(expressionTrees.size()!=0){
			Tree* expressionTree = new Tree(expressionTrees.top());
			expressionTree->execute();	
			expressionTrees.pop();
		}

		//execute tree
			//as tree is traversed
			//str will be converted to either connector object or command object

	} //end while

	return 0;
}
