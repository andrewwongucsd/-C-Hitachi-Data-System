#ifndef AVLTREE_H
#define AVLTREE_H

#include <cstdio>
/*
 * Namespace called AVL
 */
namespace AVL {

	/*
	 * AVL Node
	 */
  struct AVLNode {
    int elem;			// Element
    int height;			// Height
    AVLNode *left;		// left Node
    AVLNode *right;		// right Node
    AVLNode(int e) : elem(e), height(0), left(0), right(0) {} // constructor
    ~AVLNode() {delete left; delete right;} // destructor
  };

  bool find(const AVLNode *tree, int elem);
  AVLNode *insert(AVLNode *tree, int elem);


}
/*
 * AVLTree with the only root
 * function: AVLTree{AVLNode as the root, AVLNode(s)}
 */
class AVLTree {
private:
  AVL::AVLNode *root; // Namespace(AVL)'s AVLNode called dereference root;
public:
  AVLTree() : root(0) {} 				// root set to 0 as empty tree when constructed.
  ~AVLTree() {delete root;}				// destructed the root.
  bool find(int elem) const {return AVL::find(root, elem);}
  void insert(int elem) {root = AVL::insert(root, elem);}

};

#endif // AVLTREE_H
