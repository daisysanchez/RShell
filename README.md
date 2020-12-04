# CS 100 Programming Project

# Project Information
  Quarter: Winter 2020
  
  Partners: 
    Rachel Lau (862039557) and 
    Daisy Sanchez (862119715)
    
    Daisy Sanchez: Author of all src files. Contributions to README and tests
    Rachel Lau: Author of README and tests. Contributions to parser

# Introduction
  This project is a command shell capable of executing standard BASH commands. It prompts the user, reads a line of command(s) (and connector(s)), executes the command(s), and repeats this process until the `exit` command is executed.
  To execute the appropriate commands, the shell implements `fork`, `execvp`, and `waitpid` system calls to create and control the flow of new processes. 
  
  `fork` is used to create a child process in order to run different commands.
  
  `execvp` is used to execute the appropriate commands from the `bin/` folder.
  
  `waitpid` is used to suspend the execution of a parent process to wait for a child process to execute.
  
  The commands will be in the following format, with no limit to the number of commands on a single line:
  
 > `$ executable [arugmentList] [connector] [executable] ...`
  
  where `[executable]` is an executable program located at one of the `PATH` environment variable locations and `[connector]` is any of `||`, `&&`, or `;`.
  
  To develop the project, we are implementing a factory method and prototype design pattern


# Diagram
![alt-text](https://github.com/cs100/assignment-weareconfusion/blob/master/images/Assignment3%20Diagram.png?raw=true)

# Classes
In this assignment, we will have 10 classes: 
1. Rshell (main)::  
  The Main function is where the rshell is implemented and ran. It firsts parses the command into commands and connectors. In this function, we implemented the Shunting Yard algorithm to help decide on the order of the commands because we implemented the parser to break up parentheses for precedence testing. The Shunting Yard algorithm will convert the commands from infix to postfix order. After it converts it from infix to postfix, it then executes the trees, traversing left to right. 
2. Tree Class ::
  The Tree class has an empty constructor, a constructor set with a Node* from the Node class, a void execute, a boolean function for inorder Traversal, and a helper function for the inorder traversal function. Each tree that is created with this class is either a full command or a portion of a full command. A tree is a partial command if there are semicolons in the command to separate the user inputs. Each root is a Node* from the Node class. This means that the Tree class and Node class interact by aggregating with each other. One has to be created for the other one to be created. The inorder traversal function traverses the tree when it sees a node for the second time or knows that it is the last node. It executes by using a Command* from the Command class. The void execute function calls the inorder Traversal function for it to execute.  
3. Node Class ::
  The Node class has an empty constructor, a constructor with a string, a few mutator functions, a few accessor functions, and a boolean execute function. The mutator functions are used to set the right child, left child, parent node, and the data within the node. The accessor functions are used to retrieve the right child, left child, parent node, and the data within the nodes. The purpose of the Node class is to make the tree, and break the commands into left or right childs, or hold the string that with has command literals or connector. This class interactions with Tree class through aggregatio and interacts with the Command class through association. 
4. Parse Class :: 
  The Parse class includes the parsing function, converter function, and two removing space functions. The parsing function is a vector of string function that takes in a string, which will be the command, and then parses it by the connectors and special characters. The parsing function traverses the string and as it traverses it, it collects the characters into a string. Then it sees a connector or special character, it pushes it into a temporary vector that will be returned at the end of the function. Then it collects the connector or special character. It continues to do this until the command ends. After this I traverse that temporary vector for the test commands that I need to convert and change it, then add it onto the vector that will be returned. It is called in the main function to parse the command, so it is associated with the main class. This class is used to help implement rshell (main).
5. Command Class ::
  The Command class has an empty constructor, a constructor with a string, destructor, a converter, and a virtual boolean function. The constructors help build the item while the destructor erases it after going through a scope. The converter converts the vector of strings from the parser into a double char argument to become executables. Since the class has a virtual boolean, this becomes an abstract class and indicates that the child class will implement this function as well. The boolean execute function for this class is also where the syscalls are used to execute functions as well. This is also where the forking occurs. This class is parent to Test Class. This class also interacts with the Node class through association. 
6. Test Class ::
  The Test class is subclass of the Command class, meaning it inherits all the properties of the Command class but also has more functions within itself. This class implements the test and [] functions that are used in the test cases. This is implemented using stat, S_ISREG, and S_ISIDIR. The reason to implement this is so that it is unlike normal bash behavior as it will output (true) or (false) depending on whether the executions are true or false. 

# Prototypes / Research
Prototypes for different functions can be found in the `prototypes/` directory.

The `prototype-syscalls.c` experiments with forking processes and waiting for child processes to finish. It also includes a sample of `execvp` function, by runnning ls. 

The `main.cpp` experiments with parsing. It is a simple parsing technique that parses between spaces and stores the strings i vector. This does not tell about the order of executions, so it will not be the actual parsing function for the assignment, but it does show the idea of separating the words and storing them somewhere else. 

## Connector behavior

`echo ls -a && ls -a` will output
    ls -a
    [files] 
    
 `echo && &&`  `echo ; && echo hello` will both output an error. It can be concluded that in order to output a connecor, it must be surrounded by "".
 
 `echo hello &&` and `echo hello ||` will continue to wait for the user to finish the command (rhs of &&)
 

# Development and Testing Roadmap

SEE ISSUES
1. Rshell (main)  
2. Tree Class 
3. Node Class
4. Parsing Class
5. Parentheses in Parsing 
6. Test Bracket in Parsing
7. Update Connector Classes 
8. Update Command Class
9. Update Unit Tests
10. Update Integration Tests
11. Update ReadMe and OML Diagram
