#ifndef AVL_NODE_HPP
# define AVL_NODE_HPP

#include "avl_tree.hpp"

namespace ft
{
	template <class Key, class T>
	struct avl_node
	{
		pair<Key, T>	data;
		int				height;
		struct avl_node	*left;
		struct avl_node	*right;
		
		avl_node*		rr_rotation(avl_node* root);
		avl_node*		ll_rotation(avl_node* root);
		avl_node*		lr_rotation(avl_node* root);
		avl_node*		rl_rotation(avl_node* root);
		avl_node*		balance(avl_node* root);
		avl_node*		balanceTree(avl_node* root);
		avl_node*		insert(avl_node* root, pair<Key, T> value);
	};
}

#include "avl_node.tpp"

#endif