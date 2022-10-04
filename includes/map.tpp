#include "map.hpp"

namespace ft
{
	template <class Key, class T, class Compare, class Alloc>
	map<Key, T, Compare, Alloc>::map(): _tree(tree())
	{}

	template <class Key, class T, class Compare, class Alloc>
	map<Key, T, Compare, Alloc>::map(const Compare &comp, const allocator_type &alloc):
		_tree(tree(alloc))
	{
		(void) comp;
	}

	template <class Key, class T, class Compare, class Alloc>
	template <class InputIterator>
	map<Key, T, Compare, Alloc>::map(InputIterator first, InputIterator last,
		const Compare &comp, const allocator_type &alloc):
		_tree(tree(alloc))
	{
		(void) comp;
		for (; first != last; first++)
			_tree.insert(*first);
	}

	template <class Key, class T, class Compare, class Alloc>
	map<Key, T, Compare, Alloc>::map(const map &other): _tree(tree())
	{
		*this = other;
	}

	template <class Key, class T, class Compare, class Alloc>
	map<Key, T, Compare, Alloc>::~map()
	{}

	template <class Key, class T, class Compare, class Alloc>
	map<Key, T, Compare, Alloc>	&map<Key, T, Compare, Alloc>::operator=(const map &other)
	{
		clear();
		for (const_iterator it = other.begin(); it != other.end(); ++it)
			_tree.insert(*it);
		return (*this);
	}

	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::allocator_type
		map<Key, T, Compare, Alloc>::get_allocator() const
	{
		return (allocator_type());
	}

	template <class Key, class T, class Compare, class Alloc>
	T	&map<Key, T, Compare, Alloc>::at(const Key &key)
	{
		return (_tree.find(key).second);
	}

	template <class Key, class T, class Compare, class Alloc>
	const T	&map<Key, T, Compare, Alloc>::at(const Key &key) const
	{
		return (_tree.find(key).second);
	}

	template <class Key, class T, class Compare, class Alloc>
	T	&map<Key, T, Compare, Alloc>::operator[](const Key &key)
	{
		_tree.insert(make_pair(key, T()));
		return (_tree.find(key).second);
	}

	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::iterator	map<Key, T, Compare, Alloc>::begin()
	{
		return (_tree.begin());
	}

	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::const_iterator
		map<Key, T, Compare, Alloc>::begin() const
	{
		return (_tree.begin());
	}

	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::iterator	map<Key, T, Compare, Alloc>::end()
	{
		return (_tree.end());
	}

	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::const_iterator
		map<Key, T, Compare, Alloc>::end() const
	{
		return (_tree.end());
	}

	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::reverse_iterator
		map<Key, T, Compare, Alloc>::rbegin()
	{
		return (reverse_iterator(end()));
	}

	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::const_reverse_iterator
		map<Key, T, Compare, Alloc>::rbegin() const
	{
		return (const_reverse_iterator(end()));
	}

	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::reverse_iterator
		map<Key, T, Compare, Alloc>::rend()
	{
		return (reverse_iterator(begin()));
	}

	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::const_reverse_iterator
		map<Key, T, Compare, Alloc>::rend() const
	{
		return (const_reverse_iterator(begin()));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	map<Key, T, Compare, Alloc>::empty() const
	{
		return (!size());
	}

	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::size_type
		map<Key, T, Compare, Alloc>::size() const
	{
		return (_tree.size());
	}

	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::size_type
		map<Key, T, Compare, Alloc>::max_size() const
	{
		return (std::min(_tree.get_allocator().max_size(),
			static_cast<size_type>(std::numeric_limits<difference_type>::max())));
	}

	template <class Key, class T, class Compare, class Alloc>
	void	map<Key, T, Compare, Alloc>::clear()
	{
		_tree.clear();
	}

	template <class Key, class T, class Compare, class Alloc>
	pair<typename map<Key, T, Compare, Alloc>::iterator, bool>
		map<Key, T, Compare, Alloc>::insert(const value_type &value)
	{
		bool result = this->_tree.insert(value); // Well, sometimes just create the f****** variable
		iterator it = iterator(_tree.root(), _tree.find_node(value.first));
		return (ft::make_pair(it, result));
	}

	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::iterator
		map<Key, T, Compare, Alloc>::insert(iterator hint, const value_type &value)
	{
		(void)hint;
		_tree.insert(value);
		return iterator(_tree.root(), _tree.find_node(value.first));
	}
	
	template <class Key, class T, class Compare, class Alloc>
	template <class InputIt>
	void	map<Key, T, Compare, Alloc>::insert(InputIt first, InputIt last)
	{
		while (first != last)
			_tree.insert(*first++);
	}

	template <class Key, class T, class Compare, class Alloc>
	void	map<Key, T, Compare, Alloc>::erase(iterator pos)
	{
		_tree.erase(pos->first);
	}


	template <class Key, class T, class Compare, class Alloc>
	void	map<Key, T, Compare, Alloc>::erase(iterator first, iterator last)
	{
		iterator save;
		while (first != iterator(_tree.root(), last.base()))
		{
			save = first + 1;
			erase(first);
			first = iterator(_tree.root(), save.base());
		}

	}
	
	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::size_type
		map<Key, T, Compare, Alloc>::erase(const Key &key)
	{
		return (_tree.erase(key));
	}

	template <class Key, class T, class Compare, class Alloc>
	void	map<Key, T, Compare, Alloc>::swap(map<Key, T, Compare, Alloc> &other)
	{
		_tree.swap(other._tree);
	}

	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::size_type
		map<Key, T, Compare, Alloc>::count(const Key &key) const
	{
		try
		{
			_tree.find(key);
			return (1);
		}

		catch (const std::exception &e)
		{
			return (0);
		}
	}

	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::iterator
		map<Key, T, Compare, Alloc>::find(const Key &key)
	{
		return (iterator(_tree.root(), _tree.find_node(key)));
	}

	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::const_iterator
		map<Key, T, Compare, Alloc>::find(const Key &key) const
	{
		return (const_iterator(_tree.root(), _tree.find_node(key)));
	}

	template <class Key, class T, class Compare, class Alloc>
	pair<typename map<Key, T, Compare, Alloc>::iterator,
		typename map<Key, T, Compare, Alloc>::iterator>
		map<Key, T, Compare, Alloc>::equal_range(const Key &key)
	{
		return (ft::make_pair(lower_bound(key), upper_bound(key)));
	}

	template <class Key, class T, class Compare, class Alloc>
	pair<typename map<Key, T, Compare, Alloc>::const_iterator,
		typename map<Key, T, Compare, Alloc>::const_iterator>
		map<Key, T, Compare, Alloc>::equal_range(const Key &key) const
	{
		return (ft::make_pair(lower_bound(key), upper_bound(key)));
	}

	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::iterator
		map<Key, T, Compare, Alloc>::lower_bound(const Key &key)
	{
		return ((find(key) == end()) ? iterator(_tree.root(), _tree.upper(key)) : find(key));
	}

	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::const_iterator
		map<Key, T, Compare, Alloc>::lower_bound(const Key &key) const
	{
		return ((find(key) == end()) ? const_iterator(_tree.root(), _tree.upper(key)) : find(key));
	}

	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::iterator
		map<Key, T, Compare, Alloc>::upper_bound(const Key &key)
	{
		return (iterator(_tree.root(), _tree.upper(key)));
	}

	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::const_iterator
		map<Key, T, Compare, Alloc>::upper_bound(const Key &key) const
	{
		return (const_iterator(_tree.root(), _tree.upper(key)));
	}

	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::key_compare
		map<Key, T, Compare, Alloc>::key_comp() const
	{
		return (key_compare());
	}

	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::value_compare
		map<Key, T, Compare, Alloc>::value_comp() const
	{
		return (value_compare());
	}

	template <class Key, class T, class Compare, class Alloc>
	void	swap(map<Key,T,Compare,Alloc>& lhs, map<Key,T,Compare,Alloc>& rhs)
	{
		lhs.swap(rhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	operator==(const map<Key, T, Compare, Alloc>& lhs,
		const map<Key, T, Compare, Alloc>& rhs)
	{
		if (lhs.size() != lhs.size())
			return (false);
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	operator!=(const map<Key, T, Compare, Alloc>& lhs,
		const map<Key, T, Compare, Alloc>& rhs)
	{
		return (!(lhs == rhs));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	operator<(const map<Key, T, Compare, Alloc>& lhs,
		const map<Key, T, Compare, Alloc>& rhs)
	{
		return (std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	operator<=(const map<Key, T, Compare, Alloc>& lhs,
		const map<Key, T, Compare, Alloc>& rhs)
	{
		return (!(lhs > rhs));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	operator>(const map<Key, T, Compare, Alloc>& lhs,
		const map<Key, T, Compare, Alloc>& rhs)
	{
		return (rhs < lhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	operator>=(const map<Key, T, Compare, Alloc>& lhs,
		const map<Key, T, Compare, Alloc>& rhs)
	{
		return (!(lhs < rhs));
	}


}