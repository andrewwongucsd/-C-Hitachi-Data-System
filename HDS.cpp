//============================================================================
// Name        : HDS.cpp, AVLTree.cpp, AVLTree.h
// Author      : Andrew Wong
// Version     :
// Description : The class is to let users prompt an integer to be evaluated
//				 under two test: Parity and Divisibility Test between 2 and 9
//				Each operation is required to record the input into the AVL Tree.
//				Its look-up cost is O(log(n)) due to the nature of the data struture
//				(Self balancing Binary Search Tree).
//				1) Parity Test: return true if even, false if odd.
//				2) Divisibility Test between 2 and 9:
//					The for loop iterates the given integer around the factors (2-9)
//				1A/2A) Insert Element function:
//					AVL Tree-based Search function.
//					Self-balancing in term of rotation operations takes place
//					when a balance factor of a node is more than pos/neg 1 once
//					an integer is being inserted.
//					The integer traverses the tree according to the rules as follows:
//					the integer is less than the examined node, goes left.
//					otherwise, goes right. until the integer reaches to the right
//					spot. (duplicated integer will be ignored).
//					As the integer traverses the tree, route in list<AVLNode*>
//					captures the route from the root to the right spot.
//					the route starts traversal from the right spot to the root.
//					If a node is out of balance (+-2), then read the height of
// 					its next left or right node (+-1). There're 4 situations.
//					1) Right/Left (double rotation[-1]),
//					2) Left/Left (single rotation[+1]),
//					3) Left/Right (double rotation[-1]),
//					4) Right/Right (single roatation[+1])
//				3) Look-Up function (Complexity: O(log(n)))
//					The integer traverses the tree according to the rules as follows:
//					the integer is less than the examined node, goes left.
//					otherwise, goes right. until the integer reaches to the right
//					spot, then found, then return true. if not found, then return false.
//============================================================================

#include <iostream>
#include <assert.h>
#include "AVLTree.h"
#include "sstream"

using namespace std;

/**
 * isInteger(String str)
 * See if successfully converted from string to integer
 */
bool isInteger(string str, int* integer){
	std::istringstream iss(str);
	iss >> *integer;
	if (iss.eof() == false ||  str != std::to_string(*integer)){
		return false;
	}
	return true;
}


/**
 * The wrapper function of isEven
 * The wrapper is to insert the integer into the tree
 * and print the message and finally returns true if even, returns false if odd.
 */
int parityTest(string str, AVLTree* tree){
	int integer;
	if(!isInteger(str, &integer)){
		std::cout << str << " is not an integer." << std::endl;
		return -1;
	}
	(*tree).insert(integer);
	if(integer % 2 == 0){
		std::cout << integer << " is even." << std::endl;
		return 1;
	}else{
		std::cout << integer << " is odd." << std::endl;
		return 0;
	}
}

/**
 * The real meat of isDivisibleBy function
 * it returns 1 for divisible by factor;
 * otherwise returns 0 for non divisible by factor
 */
int isDivisibleBy(int integer, int factor){
	if(integer%factor == 0){
		return 1;
	}else{
		return 0;
	}
}

/**
 * The wrapper of int isDivisibleBy(int integer, int factor)
 * it returns what the function overloading returns, plus
 * it returns -1 for non-integer or overflown integer.
 */
int isDivisibleBy(string str, int factor, AVLTree* tree){
	int integer;
	if(!isInteger(str, &integer)){
		std::cout << str << " is not an integer or overflown." << std::endl;
		return -1;
	}
	(*tree).insert(integer);
	return isDivisibleBy(integer, factor);
}


/**
 * The wrapper function of isDivisibleBy
 * This wrapper is to insert the integer into the tree.
 * and to print the message.
 */
void divisibilityTest(string str,  AVLTree* tree ){
	int integer;
	if(!isInteger(str, &integer)){
		std::cout << str << " is not an integer or overflown." << std::endl;
		return;
	}
	(*tree).insert(integer);
	int idx;
	for(idx = 2; idx < 10; idx++){
		if(isDivisibleBy(integer,idx) == 1){
			std::cout << integer << " is divisible by "<< idx << std::endl;
		}else if(isDivisibleBy(integer,idx) == -1){
			std::cout << str << " is not an integer or overflown." << std::endl;
		}else if(isDivisibleBy(integer,idx) == 0){
			std::cout << integer << " is NOT divisible by "<< idx << std::endl;
		}else{
			std::cout << " ERROR " << std::endl;
		}
	}
}



/**
 * The wrapper function of isEvaluated
 * This wrapper is to print message and then return true is found
 * 											return false is not found.
 */
bool foundTest(string str, AVLTree* tree){
	int integer;
	if(!isInteger(str, &integer)){
		std::cout << str << " is not an integer." << std::endl;
		return false;
	}
	if((*tree).find(integer)){
		std::cout << integer << " is found." << std::endl;
		return true;
	}else{
		std::cout << integer << " is NOT found." << std::endl;
		return false;
	}
}

int main( )
{
	AVLTree tree;
	int option;
	string integer;
	do{
		std::cout << "================================" << std::endl;
		std::cout << " 1) Parity Test " << std::endl;
		std::cout << " 2) Divisibility by 2 - 9 " << std::endl;
		std::cout << " 3) Recent Being Search Look-up" << std::endl;
		std::cout << " 4) Unit Testing" << std::endl;
		std::cout << "================================" << std::endl;

		std::cin >> option;
		if(option < 4 && option > 0){
			std::cout << "Number? " <<std::endl;
			std::cin >> integer;
		}
		if(option == 1){
			parityTest(integer, &tree);
		}else if(option == 2){
			divisibilityTest(integer,&tree);
		}else if(option == 3){
			foundTest(integer, &tree);
		}else if(option == 4){
			assert(parityTest("-1", &tree)==0);
			assert(parityTest("1", &tree)==0);
			assert(parityTest("0", &tree)==1);
			assert(parityTest("2147483649", &tree)==-1);
			assert(parityTest("-2147483649", &tree)==-1);
			assert(parityTest("e", &tree)==-1);
			assert(parityTest(")", &tree)==-1);
			assert(isDivisibleBy("-1",2, &tree)==0);
			assert(isDivisibleBy("1", 2, &tree)==0);
			assert(isDivisibleBy("0", 2, &tree)==1);
			assert(isDivisibleBy("2147483649", 2,&tree)==-1);
			assert(isDivisibleBy("-2147483649", 2,&tree)==-1);
			assert(isDivisibleBy("e", 2, &tree)==-1);
			assert(isDivisibleBy(")", 2, &tree)==-1);
			assert(foundTest("-1", &tree)==true);
			assert(foundTest("1", &tree)==true);
			assert(foundTest("0", &tree)==true);
			assert(foundTest("2147483649", &tree)==false);
			assert(foundTest("-2147483649", &tree)==false);
			assert(foundTest("e", &tree)==false);
			assert(foundTest(")", &tree)==false);
			assert(foundTest("3", &tree)==false);
			std::cout << "All Unit Test passed."<< std::endl;
		}else{
			break;
		}
	}while(option);

	return 0;
}
