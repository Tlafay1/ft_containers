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
	typename avl_node<Key, T, Compare, Alloc>::node_ptr
		avl_node<Key, T, Compare, Alloc>::createNode(pair<Key, T> value)
	{
		node_ptr ret = _alloc.allocate(1);
		_alloc.construct(ret, value);
		ret->_left = NULL;
		ret->_right = NULL;
		return (ret);
	}

	template <class Key, class T, class Compare, class Alloc>
	typename avl_node<Key, T, Compare, Alloc>::node_ptr
		avl_node<Key, T, Compare, Alloc>::minValueNode(avl_node<Key, T, Compare, Alloc> *node)
	{
		avl_node<Key, T, Compare, Alloc>* current = node;
		while (current->_left)
			current = current->_left;
		return current;
	}

	template <class Key, class T, class Compare, class Alloc>
	typename avl_node<Key, T, Compare, Alloc>::node_ptr
		avl_node<Key, T, Compare, Alloc>::insert(avl_node<Key, T, Compare, Alloc> *root,
			pair<Key, T> value)
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
	typename avl_node<Key, T, Compare, Alloc>::node_ptr
		avl_node<Key, T, Compare, Alloc>::rr_rotation(avl_node<Key, T, Compare, Alloc> *root)
	{
		avl_node	*tmp;
		tmp = root->_right;
		root->_right = tmp->_left;
		tmp->_left = root;
		return (tmp);
	}

	template <class Key, class T, class Compare, class Alloc>
	typename avl_node<Key, T, Compare, Alloc>::node_ptr
		avl_node<Key, T, Compare, Alloc>::ll_rotation(avl_node<Key, T, Compare, Alloc> *root)
	{
		avl_node	*tmp;
		tmp = root->_right;
		root->_right = tmp->_left;
		tmp->_left = root;
		return (tmp);
	}

	template <class Key, class T, class Compare, class Alloc>
	typename avl_node<Key, T, Compare, Alloc>::node_ptr
		avl_node<Key, T, Compare, Alloc>::lr_rotation(avl_node<Key, T, Compare, Alloc> *root)
	{
		avl_node	*tmp;
		tmp = root->_left;
		root->_left = rr_rotation(tmp);
		return (ll_rotation(root));
	}

	template <class Key, class T, class Compare, class Alloc>
	typename avl_node<Key, T, Compare, Alloc>::node_ptr
		avl_node<Key, T, Compare, Alloc>::rl_rotation(avl_node<Key, T, Compare, Alloc> *root)
	{
		avl_node	*tmp;
		tmp = root->_right;
		root->_left = ll_rotation(tmp);
		return (rr_rotation(root));
	}

	template <class Key, class T, class Compare, class Alloc>
	typename avl_node<Key, T, Compare, Alloc>::node_ptr
		avl_node<Key, T, Compare, Alloc>::balance(avl_node<Key, T, Compare, Alloc> *root)
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
	typename avl_node<Key, T, Compare, Alloc>::node_ptr
		avl_node<Key, T, Compare, Alloc>::balanceTree(avl_node<Key, T, Compare, Alloc> *root)
	{
		if (!root)
			return NULL;
		root->_left = balanceTree(root->_left);
		root->_right = balanceTree(root->_right);
		root = balance(root);
		return root;
	}

	template <class Key, class T, class Compare, class Alloc>
	typename avl_node<Key, T, Compare, Alloc>::node_ptr
		avl_node<Key, T, Compare, Alloc>::deleteNode(avl_node<Key, T, Compare, Alloc> *root,
			Key key)
	{
		ofieqjfoiwj(root);
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
				avl_node<Key, T, Compare, Alloc> *tmp = root->_left
					? root->_left : root->_right;
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
		root->_height = std::max(avl_tree(root->_left).height(),
			avl_tree(root->_right).height() + 1);
		balanceTree(root);
		return (root);
	}

	template <class Key, class T, class Compare, class Alloc>
	typename avl_node<Key, T, Compare, Alloc>::node_ptr
		avl_node<Key, T, Compare, Alloc>::next(node_ptr node, node_ptr root)
	{
		if (node->right)
			return min(node->right);
		return upper(root, node->_data.first);
	}

	template <class Key, class T, class Compare, class Alloc>
	typename avl_node<Key, T, Compare, Alloc>::node_ptr
		avl_node<Key, T, Compare, Alloc>::prev(node_ptr node, node_ptr root)
	{
		if (node == NULL)
			return max(root);
		if (node->left)
			return max(node->left);
		return lower(root, node->_data.first);
	}

	template <class Key, class T, class Compare, class Alloc>
	typename avl_node<Key, T, Compare, Alloc>::node_ptr
		avl_node<Key, T, Compare, Alloc>::min(node_ptr node)
	{
		node_ptr	current = node;

		while (current->left)
			current = current->left;
		return current;
	}

	template <class Key, class T, class Compare, class Alloc>
	typename avl_node<Key, T, Compare, Alloc>::node_ptr
		avl_node<Key, T, Compare, Alloc>::max(node_ptr node)
	{
		node_ptr	current = node;

		while (current->right)
			current = current->right;
		return current;
	}
	
	template <class Key, class T, class Compare, class Alloc>
	typename avl_node<Key, T, Compare, Alloc>::node_ptr
		avl_node<Key, T, Compare, Alloc>::upper(node_ptr root, key_type key)
	{
		node_ptr	current = root;
		node_ptr	last_valid = NULL;
		while (current)
		{
			if (key == current->_data.first)
			{
				if (current->right)
					return min(current->right);
				break ;
			}
			if (root->key_compare(key, current->_data.first))
			{
				last_valid = current;
				current = current->left;
			} 
			else
				current = current->right;
		}
		return (last_valid);
	}

	template <class Key, class T, class Compare, class Alloc>
	typename avl_node<Key, T, Compare, Alloc>::node_ptr
		avl_node<Key, T, Compare, Alloc>::lower(node_ptr root, key_type key)
	{
		node_ptr	current = root;
		node_ptr	last_valid = NULL;
		while (current) {
			if (key == current->_data.first)
			{
				if (current->left)
					return max(current->left);
				break;
			}
			if (root->key_compare(key, current->_data.first))
				current = current->left;
			else
			{
				last_valid = current;
				current = current->right;
			}
		}
		return (last_valid);
	}

	template <class Key, class T, class Compare, class Alloc>
	typename avl_node<Key, T, Compare, Alloc>::node_ptr
		avl_node<Key, T, Compare, Alloc>::find(node_ptr node, key_type key)
	{
		while (node)
		{
			if (node->_data.first == key)
				return node;
			if (node->key_compare(key, node->_data.first))
				node = node->left;
			else if (key > node->_data.first)
				node = node->right;
		}
		return NULL;
	}

	// iterator

	template <class Key, class T, class Compare, class Alloc>
	avl_tree_iterator<Key, T, Compare, Alloc>::avl_tree_iterator():
		_root(NULL),
		_current(NULL)
	{}
	
	template <class Key, class T, class Compare, class Alloc>
	avl_tree_iterator<Key, T, Compare, Alloc>::avl_tree_iterator(const avl_tree_iterator& src)
	{
		*this = src;
	}

	template <class Key, class T, class Compare, class Alloc>
	avl_tree_iterator<Key, T, Compare, Alloc>::~avl_tree_iterator()
	{}

	template <class Key, class T, class Compare, class Alloc>
	avl_tree_iterator<Key, T, Compare, Alloc>&
		avl_tree_iterator<Key, T, Compare, Alloc>::operator=(const avl_tree_iterator& src)
	{
		_root = src._root;
		_current = src._current;
		return (*this);
	}

	template <class Key, class T, class Compare, class Alloc>
	avl_tree_iterator<Key, T, Compare, Alloc>&
		avl_tree_iterator<Key, T, Compare, Alloc>::operator++()
	{
		_current = node::next(_current, _root);
		return (*this);
	}

	template <class Key, class T, class Compare, class Alloc>
	avl_tree_iterator<Key, T, Compare, Alloc>&
		avl_tree_iterator<Key, T, Compare, Alloc>::operator--()
	{
		_current = node::prev(_current, _root);
		return (*this);
	}

	template <class Key, class T, class Compare, class Alloc>
	avl_tree_iterator<Key, T, Compare, Alloc>
		avl_tree_iterator<Key, T, Compare, Alloc>::operator--(int)
	{
		node_ptr ret = _current;
		_current = node::prev(_current, _root);
		return (ret);
	}

	template <class Key, class T, class Compare, class Alloc>
	avl_tree_iterator<Key, T, Compare, Alloc>
		avl_tree_iterator<Key, T, Compare, Alloc>::operator++(int)
	{
		node_ptr ret = _current;
		_current = node::next(_current, _root);
		return (ret);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool avl_tree_iterator<Key, T, Compare, Alloc>::operator==(const avl_tree_iterator &other)
	{
		return ((_root == other._root) && (_current == other._current));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool avl_tree_iterator<Key, T, Compare, Alloc>::operator!=(const avl_tree_iterator &other)
	{
		return (!(*this == other));
	}

	template <class Key, class T, class Compare, class Alloc>
	typename avl_tree_iterator<Key, T, Compare, Alloc>::reference
		avl_tree_iterator<Key, T, Compare, Alloc>::operator*() const
	{
		return (*reinterpret_cast<const_pair_type*>(&_current->key_value_pair()));
	}

	template <class Key, class T, class Compare, class Alloc>
	typename avl_tree_iterator<Key, T, Compare, Alloc>::pointer
		avl_tree_iterator<Key, T, Compare, Alloc>::operator->() const
	{
		return (&(operator*()));
	}

	template <class Key, class T, class Compare, class Alloc>
	avl_tree_iterator<Key, T, Compare, Alloc> avl_tree_iterator<Key, T, Compare, Alloc>::operator+(difference_type n) const
	{
		avl_tree_iterator ret(_root, _current);
		while (n--)
			ret++;
		return (ret);
	}

	// const_iterator

	template <class Key, class T, class Compare, class Alloc>
	avl_tree_const_iterator<Key, T, Compare, Alloc>::avl_tree_const_iterator():
		_root(NULL),
		_current(NULL)
	{}
	
	template <class Key, class T, class Compare, class Alloc>
	avl_tree_const_iterator<Key, T, Compare, Alloc>::avl_tree_const_iterator(const avl_tree_const_iterator& src)
	{
		*this = src;
	}

	template <class Key, class T, class Compare, class Alloc>
	avl_tree_const_iterator<Key, T, Compare, Alloc>::~avl_tree_const_iterator()
	{}

	template <class Key, class T, class Compare, class Alloc>
	avl_tree_const_iterator<Key, T, Compare, Alloc>&
		avl_tree_const_iterator<Key, T, Compare, Alloc>::operator=(const avl_tree_const_iterator& src)
	{
		_root = src._root;
		_current = src._current;
		return (*this);
	}

	template <class Key, class T, class Compare, class Alloc>
	avl_tree_const_iterator<Key, T, Compare, Alloc>&
		avl_tree_const_iterator<Key, T, Compare, Alloc>::operator++()
	{
		_current = node::next(_current, _root);
		return (*this);
	}

	template <class Key, class T, class Compare, class Alloc>
	avl_tree_const_iterator<Key, T, Compare, Alloc>&
		avl_tree_const_iterator<Key, T, Compare, Alloc>::operator--()
	{
		_current = node::prev(_current, _root);
		return (*this);
	}

	template <class Key, class T, class Compare, class Alloc>
	avl_tree_const_iterator<Key, T, Compare, Alloc>
		avl_tree_const_iterator<Key, T, Compare, Alloc>::operator--(int)
	{
		node_ptr ret = _current;
		_current = node::prev(_current, _root);
		return (ret);
	}

	template <class Key, class T, class Compare, class Alloc>
	avl_tree_const_iterator<Key, T, Compare, Alloc>
		avl_tree_const_iterator<Key, T, Compare, Alloc>::operator++(int)
	{
		node_ptr ret = _current;
		_current = node::next(_current, _root);
		return (ret);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool avl_tree_const_iterator<Key, T, Compare, Alloc>::operator==(const avl_tree_const_iterator &other)
	{
		return ((_root == other._root) && (_current == other._current));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool avl_tree_const_iterator<Key, T, Compare, Alloc>::operator!=(const avl_tree_const_iterator &other)
	{
		return (!(*this == other));
	}

	template <class Key, class T, class Compare, class Alloc>
	typename avl_tree_const_iterator<Key, T, Compare, Alloc>::reference
		avl_tree_const_iterator<Key, T, Compare, Alloc>::operator*() const
	{
		return (*reinterpret_cast<const_pair_type*>(&_current->key_value_pair()));
	}

	template <class Key, class T, class Compare, class Alloc>
	typename avl_tree_const_iterator<Key, T, Compare, Alloc>::pointer
		avl_tree_const_iterator<Key, T, Compare, Alloc>::operator->() const
	{
		return (&(operator*()));
	}

	// avl_tree_const_iterator operator+(difference_type n) const
	// {
	// 	avl_tree_const_iterator ret(_root, _current);
	// 	while (n--)
	// 		ret++;
	// 	return (ret);
	// }
}
