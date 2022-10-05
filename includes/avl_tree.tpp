#include "avl_tree.hpp"

namespace ft
{
	template <class Key, class T, class Compare, class Alloc>
	avl_tree<Key, T, Compare, Alloc>::avl_tree(const allocator_type &alloc):
		_root(NULL),
		_alloc(alloc),
		_size(0)
	{}

	template <class Key, class T, class Compare, class Alloc>
	avl_tree<Key, T, Compare, Alloc>::avl_tree(avl_node<Key, T, Compare, Alloc> *root):
		_root(root)
	{}

	template <class Key, class T, class Compare, class Alloc>
	avl_tree<Key, T, Compare, Alloc>::~avl_tree()
	{
		clear();
	}

	template <class Key, class T, class Compare, class Alloc>
	typename avl_tree<Key, T, Compare, Alloc>::iterator
		avl_tree<Key, T, Compare, Alloc>::begin()
	{
		if (!_size)
			return (end());
		return (iterator(_root, min()));
	}

	template <class Key, class T, class Compare, class Alloc>
	typename avl_tree<Key, T, Compare, Alloc>::const_iterator
		avl_tree<Key, T, Compare, Alloc>::begin() const
	{
		if (!_size)
			return (end());
		return (const_iterator(_root, min()));
	}

	template <class Key, class T, class Compare, class Alloc>
	typename avl_tree<Key, T, Compare, Alloc>::iterator
		avl_tree<Key, T, Compare, Alloc>::end()
	{
		return (iterator(_root, NULL));
	}

	template <class Key, class T, class Compare, class Alloc>
	typename avl_tree<Key, T, Compare, Alloc>::const_iterator
		avl_tree<Key, T, Compare, Alloc>::end() const
	{
		return (const_iterator(_root, NULL));
	}

	template <class Key, class T, class Compare, class Alloc>
	const typename avl_tree<Key, T, Compare, Alloc>::node_ptr
		avl_tree<Key, T, Compare, Alloc>::min() const
	{
		if (!_root)
			throw std::out_of_range("Empty avl_tree");
		return (node::min(_root));
	}

	template <class Key, class T, class Compare, class Alloc>
	const typename avl_tree<Key, T, Compare, Alloc>::node_ptr
		avl_tree<Key, T, Compare, Alloc>::max() const
	{
		if (!_root)
			throw std::out_of_range("Empty avl_tree");
		return (node::max(_root));
	}

	template <class Key, class T, class Compare, class Alloc>
	typename avl_tree<Key, T, Compare, Alloc>::size_type
		avl_tree<Key, T, Compare, Alloc>::size() const
	{
		return (_size);
	}
	
	template <class Key, class T, class Compare, class Alloc>
	bool	avl_tree<Key, T, Compare, Alloc>::insert(pair_type data)
	{
		if (node::find(_root, data.first))
			return (false);
		_root = node::insert(_root, data, _alloc);
		_size++;
		return (true);
	}

	template <class Key, class T, class Compare, class Alloc>
	int	avl_tree<Key, T, Compare, Alloc>::erase(const key_type &key)
	{
		if (!node::find(_root, key))
			return 0;
		_root = node::erase(_root, key, _alloc);
		_size--;
		return (1);
	}

	template <class Key, class T, class Compare, class Alloc>
	void	avl_tree<Key, T, Compare, Alloc>::swap(avl_tree<Key,T,
		Compare, Alloc> &other)
	{
		std::swap(_alloc, other._alloc);
		std::swap(_root, other._root);
		std::swap(_size, other._size);
	}
	template <class Key, class T, class Compare, class Alloc>
	void	avl_tree<Key, T, Compare, Alloc>::clear()
	{
		while (_size > 0)
			erase(_root->key_value_pair().first);
	}

	template <class Key, class T, class Compare, class Alloc>
	typename avl_tree<Key, T, Compare, Alloc>::const_pair_type
		&avl_tree<Key, T, Compare, Alloc>::find(const key_type &key) const
	{
		node_ptr node = node::find(_root, key);
		if (!node)
			throw std::out_of_range("Key doesn't exist");
		return (reinterpret_cast<const_pair_type&>(node->key_value_pair()));
	}

	template <class Key, class T, class Compare, class Alloc>
	typename avl_tree<Key, T, Compare, Alloc>::node_ptr
		avl_tree<Key, T, Compare, Alloc>::upper(const key_type& key) const
	{
		return (node::upper(_root, key));
	}

	template <class Key, class T, class Compare, class Alloc>
	typename avl_tree<Key, T, Compare, Alloc>::node_ptr
		avl_tree<Key, T, Compare, Alloc>::find_node(const key_type& key) const
	{
		node_ptr node = node::find(_root, key);
		return (node);
	}

	template <class Key, class T, class Compare, class Alloc>
	typename avl_tree<Key, T, Compare, Alloc>::allocator_type
		avl_tree<Key, T, Compare, Alloc>::get_allocator() const
	{
		return (_alloc);
	}

	template <class Key, class T, class Compare, class Alloc>
	typename avl_tree<Key, T, Compare, Alloc>::node_ptr
		avl_tree<Key, T, Compare, Alloc>::root() const
	{
		return (_root);
	}


	template <class Key, class T, class Compare, class Alloc>
	typename avl_tree<Key, T, Compare, Alloc>::size_type
		avl_tree<Key, T, Compare, Alloc>::max_size() const
	{
		return std::min(_alloc.max_size(),
			static_cast<size_type>(std::numeric_limits<difference_type>::max()));
	}

}