#include <list>
#include "AVLTree.h"

using namespace std;
using namespace AVL;

/*
 * Private Namespace
 */
namespace {

/*
 *	Return a max value;
 */
  inline int max(int a, int b) {return (a > b) ? a : b;}

  /*
   * Return a cached height of the given tree.
   */
  inline int height(AVLNode *t) {return t ? t->height : -1;}

  /* {x} head node or return node.
   *		{c}			{b}			[a]			[a]
   *	[b]		==>	[a]		[c] or 		{c}	==>		{b}
   *[a]								[b]					[c]
   *	Update height for each AVLNode pointed node.
   */
  AVLNode *leftRotate(AVLNode *tree) {
    AVLNode *nodeC = tree;
    AVLNode *nodeB = tree->left;
    nodeC->left = nodeB->right;
    nodeB->right = nodeC;
    nodeC->height = 1 + max(height(nodeC->left), height(nodeC->right));
    nodeB->height = 1 + max(height(nodeB->left), height(nodeB->right));
    return nodeB;
  }

  /* {x} head node or return node.
   * 	[c]					[c]		{c}					{b}
   * {a}		==> 	{b}		or		[b]		==>	[a]		[c]
   * 	[b]			[a]						[a]
   * 	Update height for each AVLNode pointed node.
   */
  AVLNode *rightRotate(AVLNode *tree) {
    AVLNode *nodeA = tree;
    AVLNode *nodeB = tree->right;
    nodeA->right = nodeB->left;
    nodeB->left = nodeA;
    nodeA->height = 1 + max(height(nodeA->left), height(nodeA->right));
    nodeB->height = 1 + max(height(nodeB->left), height(nodeB->right));
    return nodeB;
  }

  /*
   * ========= REBALANCE(AVLNode* tree, list<AVLNode*> &route) =========
   * height of the node +-1: OK
   * height of the node +-2:
   * 	if +2: the left subtree is heavier,
   * 		if left->right is heavier, then Right Rotation on the left subtree
   * 			and then right rotation at the head. (double rotation)
   * 		otherwise, just right rotation on the head.
   * 	if -2: the right subtree is heavier,
   * 		if right->left is heavier, then Left Rotation on the right subtree
   * 			and then left rotation at the head. (double rotation).
   * 		otherwise, just left rotation on the head.
   *
   */
  AVLNode *rebalance(AVLNode* tree, list<AVLNode*> &route) {
    while (!route.empty()) {
      AVLNode *head = route.front(); // peek
      route.pop_front();				// pop
      const int rightHeight = height(head->right);
      const int leftHeight = height(head->left);
      const int balance = leftHeight - rightHeight; // balance factor.
      AVLNode **parentOfHead;
      if(balance > 1){ // if the left subtree is heavier, then either Left/Right or Left/Left
    	  if(route.empty()){	// if there's no more, then it must be the tree.
    		  parentOfHead = &tree;
    	  }else if(route.front()->right == head){ // remember the parentOfHead is from the right.
    		  parentOfHead = &route.front()->right;
    	  }else{								// remember the parentOfHead is from the left.
    		  parentOfHead = &route.front()->left;
    	  }
    	  if(height(head->left->right) > height(head->left->left)){ // Left/Right > Left/Left
    		  head->left = rightRotate(head->left);	// double rotation
    	  }
    	  head = leftRotate(head);			// single rotation.
    	  *parentOfHead = head;	// now record the parentOfHead after rotation
      }else if(balance < -1){
    	  if (route.empty()){	// if there's no more, then it must be the tree
    		  parentOfHead = &tree;
    	  }else if (route.front()->right == head){	// remember the parentOfHead is from the right.
    		  parentOfHead = &route.front()->right;
    	  }else{									// remember the parentOfHead is from the left.
    		  parentOfHead = &route.front()->left;
    	  }
    	  if (height(head->right->left) > height(head->right->right)){	// Right/Left > Right/Right
    		  head->right = leftRotate(head->right);	// Double rotation
    	  }
    	  head = rightRotate(head);		// single rotation
    	  *parentOfHead = head;
      }
      head->height = 1 + max(height(head->left), height(head->right)); // update the head
    }
    return tree;
  }


}

namespace AVL {


  /*
   * ===== FIND (const AVLNODE *tree, int key) =====
   * Look for the given elem from the given tree pointer.
   * According to the logic as follows.
   * 	Go Left:	Key < Current Element
   * 	Go Right:	Key > Current Element
   * 	Stay:		Key = Current Element, Found.
   * if tree pointer points to 0, the key is not in Tree.
   */
  bool find(const AVLNode *tree, int key) {
    while (tree)
      if (key < tree->elem)
        tree = tree->left;
      else if (key > tree->elem)
        tree = tree->right;
      else
        break;
    return tree != 0;
  }


  /*
   * ===== INSERT (const AVLNODE *tree, int key) =====
   * if tree is 0, the tree is empty.
   * Route (list<AVLNode*> records the route from node to root
   * Travel
   */
  AVLNode *insert(AVLNode *tree, int elem) {
    if (tree == 0)
      return new AVLNode(elem);

    list<AVLNode*> route;

    AVLNode *curr = tree;
    while (true) {
      route.push_front(curr);
      if (elem < curr->elem) { 	// the element should be less (left)
        if (curr->left == 0) {	// If null, then create a new object with elem.
        	curr->left = new AVLNode(elem);
          break;				// then break while loop
        }
        curr = curr->left;				// still look for a right spot.
      } else if (elem > curr->elem) {	// the element should be more (right)
        if (curr->right == 0) {			// if right is empty.
        	curr->right = new AVLNode(elem);
          break;
        }
        curr = curr->right;
      } else{					// the right spot but previously occupied.
    	  return tree;			// duplicated, so nothing actually is happened.
      }
    }

    // Go to rebalance
    tree = rebalance(tree, route);

    return tree;
  }

}
