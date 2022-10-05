#include "avl_node.hpp"

namespace ft
{
	template <class Key, class T, class Compare, class Alloc>
	avl_node<Key, T, Compare, Alloc>::avl_node(pair_type data):
		_data(data),
		_height(1),
		_left(NULL),
		_right(NULL)
	{

	}

	template <class Key, class T, class Compare, class Alloc>
	typename avl_node<Key, T, Compare, Alloc>::pair_type
		&avl_node<Key, T, Compare, Alloc>::key_value_pair()
	{
		return (_data);
	}

	template <class Key, class T, class Compare, class Alloc>
	int	avl_node<Key, T, Compare, Alloc>::height(node_ptr node)
	{
		if (node)
			return (node->_height);
		return (0);
	}

	template <class Key, class T, class Compare, class Alloc>
	int	avl_node<Key, T, Compare, Alloc>::diff(node_ptr node)
	{
		if (!node)
			return (0);
		return (height(node->_left) - height(node->_right));
	}

	template <class Key, class T, class Compare, class Alloc>
	typename avl_node<Key, T, Compare, Alloc>::node_ptr
		avl_node<Key, T, Compare, Alloc>::createNode(pair<Key, T> value, node_allocator &alloc)
	{
		node_ptr ret = alloc.allocate(1);
		alloc.construct(ret, value);
		return (ret);
	}

	template <class Key, class T, class Compare, class Alloc>
	typename avl_node<Key, T, Compare, Alloc>::node_ptr
		avl_node<Key, T, Compare, Alloc>::balanceTree(node_ptr &node, pair_type data)
	{
		node->_height = std::max(height(node->_left), height(node->_right)) + 1;
		int bal = diff(node);
		if (bal > 1 && data.first < node->_left->_data.first)
			return right_rotate(node);
		else if (bal < -1 && data.first > node->_right->_data.first)
			return left_rotate(node);
		else if (bal > 1 && data.first > node->_left->_data.first)
		{
			node->_left = left_rotate(node->_left);
			return right_rotate(node);
		}
		else if (bal < -1 && data.first < node->_right->_data.first)
		{
			node->_right = right_rotate(node->_right);
			return left_rotate(node);
		}
		return (node);
}

	template <class Key, class T, class Compare, class Alloc>
	typename avl_node<Key, T, Compare, Alloc>::node_ptr
		avl_node<Key, T, Compare, Alloc>::insert(node_ptr root,
			pair_type value, node_allocator &alloc)
	{
		if (!root)
			return (createNode(value, alloc));

		if (value.first < root->_data.first)
			root->_left = insert(root->_left, value, alloc);
		else if (value.first > root->_data.first)
			root->_right = insert(root->_right, value, alloc);
		else
			return (root);
		return (balanceTree(root, value));
	}

	template <class Key, class T, class Compare, class Alloc>
	typename avl_node<Key, T, Compare, Alloc>::node_ptr
		avl_node<Key, T, Compare, Alloc>::right_rotate(node_ptr node)
	{
		node_ptr ret = node->_left;
		node_ptr t2 = ret->_right;
		ret->_right = node;
		node->_left = t2;
		node->_height = std::max(height(node->_left), height(node->_right)) + 1;
		ret->_height = std::max(height(ret->_left), height(ret->_right)) + 1;
		return (ret);
	}

	template <class Key, class T, class Compare, class Alloc>
	typename avl_node<Key, T, Compare, Alloc>::node_ptr
		avl_node<Key, T, Compare, Alloc>::left_rotate(node_ptr node)
	{
		node_ptr ret = node->_right;
		avl_node *t2 = ret->_left;
		ret->_left = node;
		node->_right = t2;
		node->_height = std::max(height(node->_left), height(node->_right)) + 1;
		ret->_height = std::max(height(ret->_left), height(ret->_right)) + 1;
		return (ret);
	}

	template <class Key, class T, class Compare, class Alloc>
	typename avl_node<Key, T, Compare, Alloc>::node_ptr
		avl_node<Key, T, Compare, Alloc>::erase(avl_node<Key, T, Compare, Alloc> *root,
			Key key, node_allocator &alloc)
	{
		if (!root)
			return (root);
		if (key < root->_data.first)
			root->_left = erase(root->_left, key, alloc);
		else if(key > root->_data.first)
			root->_right = erase(root->_right, key, alloc);
		else
		{
			if (!root->_left || !root->_right)
			{
				node_ptr tmp = root->_left
					? root->_left : root->_right;
				if (!tmp)
				{
					tmp = root;
					root = NULL;
				}
				else
					*root = *tmp;
				alloc.destroy(tmp);
				alloc.deallocate(tmp, 1);
			}
			else
			{
				node_ptr tmp = min(root->_right);
				root->_data = tmp->_data;
				root->_right = erase(root->_right, tmp->_data.first, alloc);
			}
		}

		if (!root)
			return root;
		root->_height =	std::max(height(root->_left), height(root->_right)) + 1;
		int bal = diff(root);
		if (bal > 1 && diff(root->_left) >= 0)
			return right_rotate(root);
		else if (bal > 1 && diff(root->_left) < 0)
		{
			root->_left = left_rotate(root->_left);
			return right_rotate(root);
		}
		else if (bal < -1 && diff(root->_right) <= 0)
			return left_rotate(root);
		else if (bal < -1 && diff(root->_right) > 0)
		{
			root->_right = right_rotate(root->_right);
			return left_rotate(root);
		}
		return (root);
	}

	template <class Key, class T, class Compare, class Alloc>
	typename avl_node<Key, T, Compare, Alloc>::node_ptr
		avl_node<Key, T, Compare, Alloc>::next(node_ptr node, node_ptr root)
	{
		if (node->_right)
			return min(node->_right);
		return upper(root, node->_data.first);
	}

	template <class Key, class T, class Compare, class Alloc>
	typename avl_node<Key, T, Compare, Alloc>::node_ptr
		avl_node<Key, T, Compare, Alloc>::prev(node_ptr node, node_ptr root)
	{
		if (!node)
			return max(root);
		if (node->_left)
			return max(node->_left);
		return lower(root, node->_data.first);
	}

	template <class Key, class T, class Compare, class Alloc>
	typename avl_node<Key, T, Compare, Alloc>::node_ptr
		avl_node<Key, T, Compare, Alloc>::min(node_ptr node)
	{
		node_ptr	current = node;

		while (current->_left)
			current = current->_left;
		return current;
	}

	template <class Key, class T, class Compare, class Alloc>
	typename avl_node<Key, T, Compare, Alloc>::node_ptr
		avl_node<Key, T, Compare, Alloc>::max(node_ptr node)
	{
		node_ptr	current = node;

		while (current->_right)
			current = current->_right;
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
				if (current->_right)
					return min(current->_right);
				break ;
			}
			if (root->_key_compare(key, current->_data.first))
			{
				last_valid = current;
				current = current->_left;
			} 
			else
				current = current->_right;
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
				if (current->_left)
					return max(current->_left);
				break;
			}
			if (root->_key_compare(key, current->_data.first))
				current = current->_left;
			else
			{
				last_valid = current;
				current = current->_right;
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
			if (node->_key_compare(key, node->_data.first))
				node = node->_left;
			else if (key > node->_data.first)
				node = node->_right;
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
	avl_tree_iterator<Key, T, Compare, Alloc>::avl_tree_iterator(node_ptr root, node_ptr current):
		_root(root),
		_current(current)
	{}

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
		return (avl_tree_iterator(this->_root, ret));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool avl_tree_iterator<Key, T, Compare, Alloc>::operator==(const avl_tree_iterator &other)
	{
		return ((_root == other._root) && (_current == other._current));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool avl_tree_iterator<Key, T, Compare, Alloc>::operator==(const avl_tree_const_iterator<Key,
					T, Compare, Alloc> &other) const
	{
		return ((_root == other.root()) && (_current == other.base()));
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
	avl_tree_iterator<Key, T, Compare, Alloc>
		avl_tree_iterator<Key, T, Compare, Alloc>::operator+(difference_type n) const
	{
		avl_tree_iterator ret(_root, _current);
		while (n--)
			ret++;
		return (ret);
	}

	template <class Key, class T, class Compare, class Alloc>
	const typename avl_tree_iterator<Key, T, Compare, Alloc>::node_ptr
		avl_tree_iterator<Key, T, Compare, Alloc>::base() const
	{
		return (_current);
	}

	template <class Key, class T, class Compare, class Alloc>
	const typename avl_tree_iterator<Key, T, Compare, Alloc>::node_ptr
		avl_tree_iterator<Key, T, Compare, Alloc>::root() const
	{
		return (_root);
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
	avl_tree_const_iterator<Key, T, Compare, Alloc>::avl_tree_const_iterator(node_ptr root, node_ptr current):
		_root(root),
		_current(current)
	{}

	template <class Key, class T, class Compare, class Alloc>
	avl_tree_const_iterator<Key, T, Compare, Alloc>
		::avl_tree_const_iterator(const avl_tree_iterator<Key, T, Compare, Alloc>& non_const):
		_root(non_const.root()),
		_current(non_const.base())
	{}

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

	template <class Key, class T, class Compare, class Alloc>
	const typename avl_tree_const_iterator<Key, T, Compare, Alloc>::node_ptr
		avl_tree_const_iterator<Key, T, Compare, Alloc>::base() const
	{
		return (_current);
	}

	template <class Key, class T, class Compare, class Alloc>
	const typename avl_tree_const_iterator<Key, T, Compare, Alloc>::node_ptr
		avl_tree_const_iterator<Key, T, Compare, Alloc>::root() const
	{
		return (_root);
	}

	// avl_tree_const_iterator operator+(difference_type n) const
	// {
	// 	avl_tree_const_iterator ret(_root, _current);
	// 	while (n--)
	// 		ret++;
	// 	return (ret);
	// }
}
