#include "avl_tree.hpp"

namespace ft
{
	template <class Key, class T>
	AvlTree<Key, T>::AvlTree(): _root(NULL) {}

	template <class Key, class T>
	AvlTree<Key, T>::AvlTree(avl_node<Key, T> *root): _root(root) {}

	template <class Key, class T>
	int	AvlTree<Key, T>::height()
	{
		if (_root)
			return (max(heigth(_root->left), heigth(_root->right)) + 1);
		return (0);
	}

	template <class Key, class T>
	int	AvlTree<Key, T>::diff()
	{
		return (heigth(_root->left) - heigth(_root->right));
	}

}