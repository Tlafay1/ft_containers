#include "avl_node.hpp"

namespace ft
{
	template <class Key, class T>
	avl_node<Key, T>	*avl_node<Key, T>::insert(avl_node<Key, T> *root, pair<Key, T> value)
	{
		if (!root)
		{
			root = new avl_node;
			root->data = value;
			root->left = NULL;
			root->right = NULL;
			return (root);
		}
		if (value < root->data)
			root->left = insert(root->left, value);
		else if (value > root->data)
			root->right = insert(root->left, value);
		return (root);
	}

	template <class Key, class T>
	avl_node<Key, T>	*avl_node<Key, T>::rr_rotation(avl_node<Key, T> *root)
	{
		avl_node	*tmp;
		tmp = root->right;
		root->right = tmp->left;
		tmp->left = root;
		return (tmp);
	}

	template <class Key, class T>
	avl_node<Key, T>	*avl_node<Key, T>::ll_rotation(avl_node<Key, T> *root)
	{
		avl_node	*tmp;
		tmp = root->right;
		root->right = tmp->left;
		tmp->left = root;
		return (tmp);
	}

	template <class Key, class T>
	avl_node<Key, T>	*avl_node<Key, T>::lr_rotation(avl_node<Key, T> *root)
	{
		avl_node	*tmp;
		tmp = root->left;
		root->left = rr_rotation(tmp);
		return (ll_rotation(root));
	}

	template <class Key, class T>
	avl_node<Key, T>	*avl_node<Key, T>::rl_rotation(avl_node<Key, T> *root)
	{
		avl_node	*tmp;
		tmp = root->right;
		root->left = ll_rotation(tmp);
		return (rr_rotation(root));
	}

	template <class Key, class T>
	avl_node<Key, T>	*avl_node<Key, T>::balance(avl_node<Key, T> *root)
	{
		int	balance_factor = avl_tree(root).diff();

		if (balance_factor > 1)
		{
			if (avl_tree(root->left).diff() > 0)
				root = ll_rotation(root);
			else
				root = lr_rotation(root);
		}
		else if (balance_factor < -1)
		{
			if (avl_tree(root->right).diff() > 0)
				root = rl_rotation(root);
			else
				root = rr_rotation(root);
		}
		return (root);
	}

	template <class Key, class T>
	avl_node<Key, T>	*avl_node<Key, T>::balanceTree(avl_node<Key, T> *root)
	{
		if (!root)
			return NULL;
		root->left = balanceTree(root->left);
		root->right = balanceTree(root->right);
		root = balance(root);
		return root;
	}	
}