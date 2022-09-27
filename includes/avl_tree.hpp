#ifndef AVL_TREE_HPP
# define AVL_TREE_HPP

# include "avl_node.hpp"

namespace ft
{
	template <class Key, class T>
	class AvlTree
	{
		public:
			AvlTree();
			AvlTree(avl_node<Key, T> *root);
			
			int	height();
			int	diff();

		private:
			avl_node<Key, T>	*_root;
	};
}

# include "avl_tree.tpp"

#endif