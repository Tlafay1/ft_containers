#include "avl_node.hpp"

namespace ft
{
	template <class Key, class T, class Compare, class Alloc>
	avl_node<Key, T, Compare, Alloc>::avl_node(const Alloc &alloc):
		_height(0),
		_left(NULL),
		_right(NULL),
		_alloc(alloc)
	{

	}

	template <class Key, class T, class Compare, class Alloc>
	typename avl_node<Key, T, Compare, Alloc>::node_ptr avl_node<Key, T, Compare, Alloc>::createNode(pair<Key, T> value)
	{
		node_ptr ret = _alloc.allocate(1);
		_alloc.construct(ret, value);
		ret->_left = NULL;
		ret->_right = NULL;
		return (ret);
	}

	template <class Key, class T, class Compare, class Alloc>
	typename avl_node<Key, T, Compare, Alloc>::node_ptr minValueNode(avl_node<Key, T, Compare, Alloc> *node)
	{
		avl_node<Key, T, Compare, Alloc>* current = node;
		while (current->_left)
			current = current->_left;
		return current;
	}

	template <class Key, class T, class Compare, class Alloc>
	typename avl_node<Key, T, Compare, Alloc>::node_ptr avl_node<Key, T, Compare, Alloc>::insert(avl_node<Key, T, Compare, Alloc> *root, pair<Key, T> value)
	{
		if (!root)
		{
			root = createNode(value);
			return (root);
		}
		if (value < root->_data.first)
			root->_left = insert(root->_left, value);
		else if (value > root->_data.first)
			root->_right = insert(root->_left, value);
		return (root);
	}

	template <class Key, class T, class Compare, class Alloc>
	typename avl_node<Key, T, Compare, Alloc>::node_ptr avl_node<Key, T, Compare, Alloc>::rr_rotation(avl_node<Key, T, Compare, Alloc> *root)
	{
		avl_node	*tmp;
		tmp = root->_right;
		root->_right = tmp->_left;
		tmp->_left = root;
		return (tmp);
	}

	template <class Key, class T, class Compare, class Alloc>
	typename avl_node<Key, T, Compare, Alloc>::node_ptr avl_node<Key, T, Compare, Alloc>::ll_rotation(avl_node<Key, T, Compare, Alloc> *root)
	{
		avl_node	*tmp;
		tmp = root->_right;
		root->_right = tmp->_left;
		tmp->_left = root;
		return (tmp);
	}

	template <class Key, class T, class Compare, class Alloc>
	typename avl_node<Key, T, Compare, Alloc>::node_ptr avl_node<Key, T, Compare, Alloc>::lr_rotation(avl_node<Key, T, Compare, Alloc> *root)
	{
		avl_node	*tmp;
		tmp = root->_left;
		root->_left = rr_rotation(tmp);
		return (ll_rotation(root));
	}

	template <class Key, class T, class Compare, class Alloc>
	typename avl_node<Key, T, Compare, Alloc>::node_ptr avl_node<Key, T, Compare, Alloc>::rl_rotation(avl_node<Key, T, Compare, Alloc> *root)
	{
		avl_node	*tmp;
		tmp = root->_right;
		root->_left = ll_rotation(tmp);
		return (rr_rotation(root));
	}

	template <class Key, class T, class Compare, class Alloc>
	typename avl_node<Key, T, Compare, Alloc>::node_ptr avl_node<Key, T, Compare, Alloc>::balance(avl_node<Key, T, Compare, Alloc> *root)
	{
		int	balance_factor = avl_tree(root).diff();

		if (balance_factor > 1)
		{
			if (avl_tree(root->_left).diff() > 0)
				root = ll_rotation(root);
			else
				root = lr_rotation(root);
		}
		else if (balance_factor < -1)
		{
			if (avl_tree(root->_right).diff() > 0)
				root = rl_rotation(root);
			else
				root = rr_rotation(root);
		}
		return (root);
	}

	template <class Key, class T, class Compare, class Alloc>
	typename avl_node<Key, T, Compare, Alloc>::node_ptr avl_node<Key, T, Compare, Alloc>::balanceTree(avl_node<Key, T, Compare, Alloc> *root)
	{
		if (!root)
			return NULL;
		root->_left = balanceTree(root->_left);
		root->_right = balanceTree(root->_right);
		root = balance(root);
		return root;
	}

	template <class Key, class T, class Compare, class Alloc>
	avl_node<Key, T, Compare, Alloc> *deleteNode(avl_node<Key, T, Compare, Alloc> *root, Key key)
	{
		if (!root)
			return (root);
		if (key < root->key)
			root->_left = deleteNode(root->_left, key);
		else if(key > root->key)
			root->_right = deleteNode(root->_right, key);
		else
		{
			if (!root->_left || !root->_right)
			{
				avl_node<Key, T, Compare, Alloc> *tmp = root->_left ? root->_left : root->_right;
				if (!tmp)
				{
					tmp = root;
					root = NULL;
				}
				else
					*root = *tmp;
				delete tmp;
			}
			else
			{
				avl_node<Key, T, Compare, Alloc> *tmp = minValueNode(root->_right);
				root->key = tmp->key;
				root->_right = deleteNode(root->_right, tmp->key);
			}
		}

		if (!root)
			return root; 
		root->_height = std::max(height(root->_left), height(root->_right)) + 1;
		balanceTree(root);
		return (root);
	}

	
}
