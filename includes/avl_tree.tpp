#include "avl_tree.hpp"

namespace ft
{
	template <class Key, class T, class Compare, class Allocator>
	AvlTree<Key, T, Compare, Allocator>::AvlTree(): _root(NULL) {}

	template <class Key, class T, class Compare, class Allocator>
	AvlTree<Key, T, Compare, Allocator>::AvlTree(avl_node<Key, T, Compare, Allocator> *root):
		_root(root)
	{}

	template <class Key, class T, class Compare, class Allocator>
	AvlTree<Key, T, Compare, Allocator>::~AvlTree()
	{
		this->clear();
	}

	template <class Key, class T, class Compare, class Allocator>
	int	AvlTree<Key, T, Compare, Allocator>::height()
	{
		if (_root)
			return (max(heigth(_root->left), heigth(_root->right)) + 1);
		return (0);
	}

	template <class Key, class T, class Compare, class Allocator>
	int	AvlTree<Key, T, Compare, Allocator>::diff()
	{
		return (heigth(_root->left) - heigth(_root->right));
	}

	template <class Key, class T, class Compare, class Allocator>
	typename AvlTree<Key, T, Compare, Allocator>::iterator
		AvlTree<Key, T, Compare, Allocator>::begin()
	{
		if (!_size)
			return (end());
		return (iterator(_root, min()));
	}

	// Quand const_iterator sera fait

	// typename AvlTree<Key, T, Compare, Allocator>::const_iterator begin()
	// {
	// 	if (!_size)
	// 		return (end());
	// 	return (const_iterator(_root, min()));
	// }

	template <class Key, class T, class Compare, class Allocator>
	typename AvlTree<Key, T, Compare, Allocator>::iterator
		AvlTree<Key, T, Compare, Allocator>::end()
	{
		return (iterator(_root, NULL));
	}

	// Pareil

	// typename AvlTree<Key, T, Compare, Allocator>::const_iterator end()
	// {
	// 	return (const_iterator(_root, NULL));
	// }

	template <class Key, class T, class Compare, class Allocator>
	typename AvlTree<Key, T, Compare, Allocator>::node_ptr
		AvlTree<Key, T, Compare, Allocator>::min()
	{
		if (!_root)
			throw std::out_of_range("Empty AvlTree");
		return (node::min(_root));
	}

	template <class Key, class T, class Compare, class Allocator>
	typename AvlTree<Key, T, Compare, Allocator>::node_ptr
		AvlTree<Key, T, Compare, Allocator>::max()
	{
		if (!_root)
			throw std::out_of_range("Empty AvlTree");
		return (node::max(_root));
	}

	template <class Key, class T, class Compare, class Allocator>
	typename AvlTree<Key, T, Compare, Allocator>::size_type
		AvlTree<Key, T, Compare, Allocator>::size() const
	{
		return (_size);
	}
	
	template <class Key, class T, class Compare, class Allocator>
	bool	AvlTree<Key, T, Compare, Allocator>::insert(pair_type data)
	{
		if (node::find(_root, data.first))
			return (false);
		_root = node::insert(_root, data, _alloc);
		_size++;
		return (true);
	}

	template <class Key, class T, class Compare, class Allocator>
	void	AvlTree<Key, T, Compare, Allocator>::erase(const key_type &key)
	{
		if (!node::find(_root, key))
			return;
		_root = node::erase(_root, key);
		_size--;
	}

	template <class Key, class T, class Compare, class Allocator>
	void	AvlTree<Key, T, Compare, Allocator>::swap(AvlTree<Key,T,
		Compare, Allocator> &other)
	{
		std::swap(_alloc, other._alloc);
		std::swap(_root, other._root);
		std::swap(_size, other._size);
	}
	template <class Key, class T, class Compare, class Allocator>
	void	AvlTree<Key, T, Compare, Allocator>::clear()
	{
		size_type size = _size;
		for (size_type i = 0; i < size; ++i)
			erase(_root->_data.first);
		_size = 0;
	}

	template <class Key, class T, class Compare, class Allocator>
	typename AvlTree<Key, T, Compare, Allocator>::const_pair_type
		&AvlTree<Key, T, Compare, Allocator>::find(const key_type &key)
	{
		node_ptr node = node::find(_root, key);
		if (!node)
			throw std::out_of_range("Key doesn't exist");
		return (reinterpret_cast<const_pair_type&>(node->key_value_pair()));
	}

	template <class Key, class T, class Compare, class Allocator>
	typename AvlTree<Key, T, Compare, Allocator>::node_ptr
		AvlTree<Key, T, Compare, Allocator>::upper(const key_type& key) const
	{
		return (node::upper(this->_root, key));
	}

	template <class Key, class T, class Compare, class Allocator>
	typename AvlTree<Key, T, Compare, Allocator>::node_ptr
		AvlTree<Key, T, Compare, Allocator>::find_node(const key_type& key) const
	{
		node_ptr node = node::find(this->_root, key);
		return (node);
	}
}