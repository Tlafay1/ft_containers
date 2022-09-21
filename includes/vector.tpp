/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.tpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafay <tlafay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 15:03:32 by tlafay            #+#    #+#             */
/*   Updated: 2022/09/21 11:06:02 by tlafay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"

namespace ft
{
	template <typename T, typename Alloc>
	vector<T, Alloc>::vector(const Alloc &alloc):
		_alloc(alloc),
		_array(pointer()),
		_size(0),
		_capacity(0)
	{}

	template <typename T, typename Alloc>
	vector<T, Alloc>::vector(size_type n, const T& value, const Alloc &alloc):
		_alloc(alloc),
		_array(pointer()),
		_size(n),
		_capacity(n)
	{
		_array = _alloc.allocate(n);
		for (T *it = _array; it != _array + _size; ++it)
		{
			_alloc.construct(it, value);
		}
	}

	template <typename T, typename Alloc>
	template <class InputIterator>
	vector<T, Alloc>::vector (InputIterator first, InputIterator last,
		const allocator_type& alloc,
		typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type*):
		_alloc(alloc),
		_array(pointer()),
		_size(0),
		_capacity(0)
	{
		this->assign(first, last);
	}

	template <typename T, typename Alloc>
	vector<T, Alloc>::vector(const vector<T, Alloc> &other)
	{
		*this = other;
	}

	template <typename T, typename Alloc>
	vector<T, Alloc>::~vector()
	{
		this->clear();
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::iterator	vector<T, Alloc>::begin()
	{
		return	(_array);
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::const_iterator	vector<T, Alloc>::begin() const
	{
		return	(_array);
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::iterator	vector<T, Alloc>::end()
	{
		return	(_array + _size);
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::const_iterator	vector<T, Alloc>::end() const
	{
		return	(_array + _size);
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::reverse_iterator	vector<T, Alloc>::rbegin()
	{
		return (reverse_iterator(this->end()));
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::const_reverse_iterator	vector<T, Alloc>::rbegin() const
	{
		return ((const_reverse_iterator)this->end());
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::reverse_iterator	vector<T, Alloc>::rend()
	{
		return (reverse_iterator(this->begin()));
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::const_reverse_iterator	vector<T, Alloc>::rend() const
	{
		return ((const_reverse_iterator)this->begin());
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::size_type	vector<T, Alloc>::capacity()
	{
		return (_capacity);
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::value_type	*vector<T, Alloc>::data()
	{
		if (_size == 0)
			return (NULL);
		return (_array);
	}

	template <typename T, typename Alloc>
	const typename vector<T, Alloc>::value_type	*vector<T, Alloc>::data() const
	{
		if (_size == 0)
			return (NULL);
		return (_array);
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::iterator	vector<T, Alloc>::erase(iterator position)
	{
		if (position + 1 != end())
			std::copy(position + 1, end(), position);
		_alloc.destroy(position);
		_size--;
		_array = position;
		return position;
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::iterator	vector<T, Alloc>::erase(iterator first, iterator last)
	{
		if (first != last)
		{
			if (last != end())
				std::copy(last, end(), first);
			for (iterator it = first; it != last; it++)
				_alloc.destroy(it);
			_size = first - _array;
		}
		return first;
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::allocator_type vector<T, Alloc>::get_allocator() const
	{
		return (_alloc);
	}

	template <typename T, typename Alloc>
	void	vector<T, Alloc>::reserve(size_type n)
	{
		if (n <= _capacity)
			return ;

		size_type i = 0;
		for (const_iterator it = begin(); it != end(); ++it)
			i++;
		if (i != _size)
			std::cerr << "Size is not good !" << std::endl;
		
		pointer			new_array = _alloc.allocate(n);

		for (size_type i = 0; i < _size; ++i)
		{
			_alloc.construct(new_array + i, _array[i]);
		}

		std::swap(new_array, _array);

		for (size_type i = 0; i < _size; ++i)
		{
			_alloc.destroy(new_array + i);
		}
		_alloc.deallocate(new_array, _capacity);
		_capacity = n;
	}

	template <typename T, typename Alloc>
	void	vector<T, Alloc>::expand(size_type n)
	{
		size_t	new_capacity;
		
		if (!_capacity)
			new_capacity = 1;
		else if (_capacity < std::numeric_limits<std::size_t>::max() / 2)
			new_capacity = 2 * _capacity;
		else
			new_capacity = std::numeric_limits<std::size_t>::max();
		if (n > new_capacity)
			new_capacity = n;
		reserve(new_capacity);
	}

	template <typename T, typename Alloc>
	void	vector<T, Alloc>::resize(size_type n, const value_type& val)
	{
		if (n < _size)
		{
			for (pointer it = _array + n; it != _array + _size; it++)
				_alloc.destroy(it);
			_size = n;
			return ;
		}
		if (n > _size)
		{
			if (n > _capacity)
				expand(n);
		}
		for (pointer it = _array + _size;
			it != _array + n; it++)
		{
			_alloc.construct(it, val);
		}
		_size = n;
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::size_type	vector<T, Alloc>::size() const
	{
		size_type i = 0;
		for (const_iterator it = begin(); it != end(); ++it)
			i++;
		if (i != _size)
			std::cerr << "Size is not good !" << std::endl;
		return (_size);
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::size_type	vector<T, Alloc>::max_size()
	{
		return (std::numeric_limits<typename
			std::iterator_traits<iterator>::difference_type>::max());
	}

	template <typename T, typename Alloc>
	void	vector<T, Alloc>::push_back (const value_type& val)
	{
		resize(_size + 1, val);
	}

	template <typename T, typename Alloc>
	void	vector<T, Alloc>::pop_back()
	{
		resize(_size - 1);
	}

	template <typename T, typename Alloc>
	void	vector<T, Alloc>::range_check(std::size_t index)
	{
		if (index >= _size)
			throw std::out_of_range("vector");
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::value_type	&vector<T, Alloc>::at(std::size_t index)
	{
		range_check(index);
		return (_array[index]);
	}

	template <typename T, typename Alloc>
	const typename vector<T, Alloc>::value_type
		&vector<T, Alloc>::at(std::size_t index) const
	{
		range_check(index);
		return (_array[index]);
	}

	template <typename T, typename Alloc>
	bool	vector<T, Alloc>::empty() const
	{
		return ((_size == 0) ? true : false);
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::value_type	&vector<T, Alloc>::front()
	{
		return (*_array);
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::value_type	&vector<T, Alloc>::back()
	{
		return (*(_array + _size - 1));
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::pointer	vector<T, Alloc>::insert(const_iterator position,
		const value_type &val)
	{
		value_type	tmp = val;
		value_type	tmp2;
		size_type	size = position - this->begin();

		resize(_size + 1);
		for (iterator it = this->begin()+ size; it != this->end();)
		{
			tmp2 = *it;
			*it = tmp;
			tmp = tmp2;
			it++;
		}
		return (this->begin() + size);
	}

	template <typename T, typename Alloc>
	void	vector<T, Alloc>::insert(const_iterator position,
		size_type count, const value_type &val)
	{
		size_type	size = position - this->begin();

		resize(_size + 1);
		vector<T, Alloc> tmp(this->size() - size);
		for (iterator it1 = this->begin() + size, it2 = tmp.begin();
			it1 != this->end(); it1++, it2++)
			*it2 = *it1;
		for (size_type i = 0; i < tmp.size(); i++)
			this->pop_back();
		while (count--)
			this->push_back(val);
		for (iterator it = tmp.begin();
			it != tmp.end() - 1; it++)
			this->push_back(*it);
	}

	template <typename T, typename Alloc>
	template< class InputIterator >
	void	vector<T, Alloc>::insert(const_iterator position,
		InputIterator first, InputIterator last,
		typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type*)
	{
		size_type idx = position - _array;
		size_type cnt = std::distance(first, last);

		this->reserve(_size + cnt);

		for (size_type i = 0; i < cnt; ++i) {
			_alloc.construct(_array + _size + i, *first);
		}
		for (difference_type i = _size - 1; i >= 0 && i >= (difference_type)idx; --i) {
			_array[i + cnt] = _array[i];
		}
		for (size_type i = idx; i < idx + cnt; ++i) {
			_array[i] = *first++;
		}
		_size += cnt;
	}

	template <typename T, typename Alloc>
	void	vector<T, Alloc>::clear()
	{
		resize(0);
	}

	template <typename T, typename Alloc>
	void	vector<T, Alloc>::swap(vector<T, Alloc> &other)
	{
		std::swap(this->_alloc, other._alloc);
		std::swap(this->_array, other._array);
		std::swap(this->_size, other._size);
		std::swap(this->_capacity, other._capacity);
	}

	template <typename T, typename Alloc>
	template <typename InputIterator>
	void	vector<T, Alloc>::assign(InputIterator first, InputIterator last,
		typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type*)
	{
		this->clear();
		for (; first != last; first++)
			this->push_back(*first);
	}

	template <typename T, typename Alloc>
	void	vector<T, Alloc>::assign (size_type n, const value_type& val)
	{
		this->clear();
		this->reserve(n);
		for (size_type i = 0; i < n; i++)
			_alloc.construct(this->_array + i, val);
	}

	template <typename T, typename Alloc>
	vector<T, Alloc>
		&vector<T, Alloc>::operator=(const vector<T, Alloc> &other)
	{
		this->_alloc = other._alloc;
		this->reserve(other._size);
		this->assign(other.begin(), other.end());
		return (*this);
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::value_type
		vector<T, Alloc>::operator[](size_type n) const
	{
		return (*(_array + n));
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::value_type
		&vector<T, Alloc>::operator[](size_type n)
	{
		return (*(_array + n));
	}

	template <class T, class Alloc>
	bool	operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
				return (false);
		return (equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class T, class Alloc>
	bool	operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return (!(lhs == rhs));
	}

	template <class T, class Alloc>
	bool	operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return (std::lexicographical_compare(lhs.begin(),lhs.end(),
			rhs.begin(), rhs.end()));
	}

	template <class T, class Alloc>
	bool	operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return ((lhs == rhs) || (lhs < rhs));
	}

	template <class T, class Alloc>
	bool	operator>(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return (!(lhs <= rhs));
	}

	template <class T, class Alloc>
	bool	operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return (!(lhs < rhs));
	}

	template <class T, class Alloc>
	void	swap( std::vector<T, Alloc>& lhs, std::vector<T, Alloc>& rhs )
	{
		lhs.swap(rhs);
	}
}