#include "avl_tree.hpp"

namespace ft
{
	template <class Key, class T, class Compare, class Alloc>
	AvlTree<Key, T, Compare, Alloc>::AvlTree(const allocator_type &alloc):
		_root(NULL),
		_alloc(alloc)
	{}

	template <class Key, class T, class Compare, class Alloc>
	AvlTree<Key, T, Compare, Alloc>::AvlTree(avl_node<Key, T, Compare, Alloc> *root):
		_root(root)
	{}

	template <class Key, class T, class Compare, class Alloc>
	AvlTree<Key, T, Compare, Alloc>::~AvlTree()
	{
		this->clear();
	}

	template <class Key, class T, class Compare, class Alloc>
	typename AvlTree<Key, T, Compare, Alloc>::iterator
		AvlTree<Key, T, Compare, Alloc>::begin()
	{
		if (!_size)
			return (end());
		return (iterator(_root, min()));
	}

	template <class Key, class T, class Compare, class Alloc>
	typename AvlTree<Key, T, Compare, Alloc>::const_iterator
		AvlTree<Key, T, Compare, Alloc>::begin() const
	{
		if (!_size)
			return (end());
		return (const_iterator(_root, min()));
	}

	template <class Key, class T, class Compare, class Alloc>
	typename AvlTree<Key, T, Compare, Alloc>::iterator
		AvlTree<Key, T, Compare, Alloc>::end()
	{
		return (iterator(_root, NULL));
	}

	template <class Key, class T, class Compare, class Alloc>
	typename AvlTree<Key, T, Compare, Alloc>::const_iterator
		AvlTree<Key, T, Compare, Alloc>::end() const
	{
		return (const_iterator(_root, NULL));
	}

	template <class Key, class T, class Compare, class Alloc>
	const typename AvlTree<Key, T, Compare, Alloc>::node_ptr
		AvlTree<Key, T, Compare, Alloc>::min() const
	{
		if (!_root)
			throw std::out_of_range("Empty AvlTree");
		return (node::min(_root));
	}

	template <class Key, class T, class Compare, class Alloc>
	const typename AvlTree<Key, T, Compare, Alloc>::node_ptr
		AvlTree<Key, T, Compare, Alloc>::max() const
	{
		if (!_root)
			throw std::out_of_range("Empty AvlTree");
		return (node::max(_root));
	}

	template <class Key, class T, class Compare, class Alloc>
	typename AvlTree<Key, T, Compare, Alloc>::size_type
		AvlTree<Key, T, Compare, Alloc>::size() const
	{
		return (_size);
	}
	
	template <class Key, class T, class Compare, class Alloc>
	bool	AvlTree<Key, T, Compare, Alloc>::insert(pair_type data)
	{
		if (node::find(_root, data.first))
			return (false);
		_root = node::insert(_root, data, _alloc);
		_size++;
		return (true);
	}

	template <class Key, class T, class Compare, class Alloc>
	int	AvlTree<Key, T, Compare, Alloc>::erase(const key_type &key)
	{
		if (!node::find(_root, key))
			return 0;
		_root = node::deleteNode(_root, key);
		_size--;
		return (1);
	}

	template <class Key, class T, class Compare, class Alloc>
	void	AvlTree<Key, T, Compare, Alloc>::swap(AvlTree<Key,T,
		Compare, Alloc> &other)
	{
		std::swap(_alloc, other._alloc);
		std::swap(_root, other._root);
		std::swap(_size, other._size);
	}
	template <class Key, class T, class Compare, class Alloc>
	void	AvlTree<Key, T, Compare, Alloc>::clear()
	{
		size_type size = _size;
		for (size_type i = 0; i < size; ++i)
			erase(_root->key_value_pair().first);
		_size = 0;
	}

	template <class Key, class T, class Compare, class Alloc>
	typename AvlTree<Key, T, Compare, Alloc>::const_pair_type
		&AvlTree<Key, T, Compare, Alloc>::find(const key_type &key) const
	{
		node_ptr node = node::find(_root, key);
		if (!node)
			throw std::out_of_range("Key doesn't exist");
		return (reinterpret_cast<const_pair_type&>(node->key_value_pair()));
	}

	template <class Key, class T, class Compare, class Alloc>
	typename AvlTree<Key, T, Compare, Alloc>::node_ptr
		AvlTree<Key, T, Compare, Alloc>::upper(const key_type& key) const
	{
		return (node::upper(this->_root, key));
	}

	template <class Key, class T, class Compare, class Alloc>
	typename AvlTree<Key, T, Compare, Alloc>::node_ptr
		AvlTree<Key, T, Compare, Alloc>::find_node(const key_type& key) const
	{
		node_ptr node = node::find(this->_root, key);
		return (node);
	}

	template <class Key, class T, class Compare, class Alloc>
	typename AvlTree<Key, T, Compare, Alloc>::allocator_type
		AvlTree<Key, T, Compare, Alloc>::get_allocator() const
	{
		return (_alloc);
	}

	template <class Key, class T, class Compare, class Alloc>
	typename AvlTree<Key, T, Compare, Alloc>::node_ptr
		AvlTree<Key, T, Compare, Alloc>::root() const
	{
		return (_root);
	}

}