/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.tpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafay <tlafay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 15:03:32 by tlafay            #+#    #+#             */
/*   Updated: 2022/09/22 13:32:13 by tlafay           ###   ########.fr       */
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
	vector<T, Alloc>::vector(const vector<T, Alloc> &other):
		_array(pointer()),
		_size(0),
		_capacity(0)
	{
		*this = other;
	}

	template <typename T, typename Alloc>
	vector<T, Alloc>::~vector()
	{
		this->clear();
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
	template <typename InputIterator>
	void	vector<T, Alloc>::assign(InputIterator first, InputIterator last,
		typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type*)
	{
		this->clear();
		for (; first != last; ++first)
			this->push_back(*first);
	}

	template <typename T, typename Alloc>
	void	vector<T, Alloc>::assign (size_type n, const value_type& val)
	{
		this->clear();
		this->reserve(n);
		for (size_type i = 0; i < n; i++)
			_alloc.construct(this->_array + i, val);
		_size = n;
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::allocator_type vector<T, Alloc>::get_allocator() const
	{
		return (_alloc);
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

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::value_type	&vector<T, Alloc>::front()
	{
		return (*_array);
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::value_type	&vector<T, Alloc>::back()
	{
		return (*(end() - 1));
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::value_type	*vector<T, Alloc>::data()
	{
		return (_array);
	}

	template <typename T, typename Alloc>
	const typename vector<T, Alloc>::value_type	*vector<T, Alloc>::data() const
	{
		return (_array);
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
	bool	vector<T, Alloc>::empty() const
	{
		return ((_size == 0) ? true : false);
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::size_type	vector<T, Alloc>::size() const
	{
		return (_size);
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::size_type	vector<T, Alloc>::max_size()
	{
		return (std::min(_alloc.max_size(),
			static_cast<size_type>(std::numeric_limits<difference_type>::max())));
	}

	template <typename T, typename Alloc>
	void	vector<T, Alloc>::reserve(size_type n)
	{
		if (n == 0 || this->_capacity >= n)
		{
			return ;
		}
		pointer	tmp;
		if (n == 0)
			tmp = pointer();
		else
			tmp = this->_alloc.allocate(n);
		for (size_type i = 0; i < this->_size; i++){
			this->_alloc.construct(tmp + i, _array[i]);
			this->_alloc.destroy(_array + i);
		}
		_alloc.deallocate(this->_array, this->_capacity);
		this->_array = tmp;
		this->_capacity = n;
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::size_type	vector<T, Alloc>::capacity()
	{
		return (_capacity);
	}

	template <typename T, typename Alloc>
	void	vector<T, Alloc>::clear()
	{
		resize(0);
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::pointer	vector<T, Alloc>::insert(const_iterator position,
		const value_type &val)
	{
		size_type	size = position - this->begin();

		if (position == this->end())
			this->push_back(val);
		else
			this->insert(position, 1, val);
		return (iterator(_array + size));
	}

	template <typename T, typename Alloc>
	void	vector<T, Alloc>::insert(const_iterator position,
		size_type n, const value_type &val)
	{
		size_type	size = position - _array;

		reserve(_size + n);
		iterator src = end() - 1;
		for (iterator dest = src + n; src >= _array + size; src--, dest--)
		{
			_alloc.construct(dest, *src);
			_alloc.destroy(src);
		}
		src++;
		for (size_type i = 0; i < n; ++i, ++src)
			_alloc.construct(src, val);
		_size += n;
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
	typename vector<T, Alloc>::iterator	vector<T, Alloc>::erase(iterator position)
	{
		if (position + 1 != end())
			std::copy(position + 1, end(), position);
		_size--;
		_alloc.destroy(_array + _size);
		return (position);
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::iterator	vector<T, Alloc>::erase(iterator first, iterator last)
	{
		if (first != last)
		{
			if (last != end())
				std::copy(last, end(), first);
			for (iterator it = first + (this->end() - last); it != end(); it++)
				_alloc.destroy(it);
			_size = first + (this->end() - last) - _array;
		}

		return first;
	}

	template <typename T, typename Alloc>
	void	vector<T, Alloc>::push_back (const value_type& val)
	{
		if (_capacity == _size)
			expand(_capacity + 1);
		_alloc.construct(_array + _size, val);
		_size++;
	}

	template <typename T, typename Alloc>
	void	vector<T, Alloc>::pop_back()
	{
		resize(_size - 1);
	}

	template <typename T, typename Alloc>
	void	vector<T, Alloc>::resize(size_type n, const value_type& val)
	{
		if (n > this->_size)
			this->insert(this->end(), n - this->_size, val);
		else
		{
			iterator tmp = _array + n;
			for (iterator it = tmp; it != this->end(); it++) {
				_alloc.destroy(it);
			}
			this->_size = tmp - this->_array;
		}
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
	void	vector<T, Alloc>::expand(size_type n)
	{
		size_t	new_capacity;
		
		if (!_capacity)
			new_capacity = 1;
		else if (_capacity < max_size() / 2)
			new_capacity = 2 * _capacity;
		else
			new_capacity = max_size();
		if (n > new_capacity)
			new_capacity = n;
		reserve(new_capacity);
	}

	template <typename T, typename Alloc>
	void	vector<T, Alloc>::range_check(std::size_t index)
	{
		if (index >= _size)
			throw std::out_of_range("vector");
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
	void	swap(vector<T, Alloc>& lhs, vector<T, Alloc>& rhs)
	{
		lhs.swap(rhs);
	}
}