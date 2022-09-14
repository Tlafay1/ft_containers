/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.tpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafay <tlafay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 15:03:32 by tlafay            #+#    #+#             */
/*   Updated: 2022/08/09 13:14:42 by tlafay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"

template <typename T, typename Alloc>
ft::vector<T, Alloc>::vector(const Alloc &alloc):
	_alloc(alloc),
	_array(NULL),
	_size(0),
	_capacity(0)
{

}

template <typename T, typename Alloc>
ft::vector<T, Alloc>::vector(size_type n, const T& value, const Alloc &alloc):
	_alloc(alloc),
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
ft::vector<T, Alloc>::vector(const ft::vector<T, Alloc> &other)
{
	*this = other;
}

template <typename T, typename Alloc>
ft::vector<T, Alloc>::~vector()
{
	if (!_array)
		return;

	T	*tmp = _array;
	for (; tmp != _array + _size; tmp++)
		_alloc.destroy(tmp);
	_alloc.deallocate(_array, _capacity);
}

template <typename T, typename Alloc>
typename ft::random_access_iterator<T> ft::vector<T, Alloc>::begin()
{
	return	_array;
}

template <typename T, typename Alloc>
const typename ft::random_access_iterator<T> ft::vector<T, Alloc>::begin() const
{
	return	_array;
}

template <typename T, typename Alloc>
typename ft::random_access_iterator<T> ft::vector<T, Alloc>::end()
{
	return	_array + _size;
}

template <typename T, typename Alloc>
const typename ft::random_access_iterator<T> ft::vector<T, Alloc>::end() const
{
	return	_array + _size;
}

template <typename T, typename Alloc>
std::size_t	ft::vector<T, Alloc>::capacity()
{
	return (_capacity);
}

template <typename T, typename Alloc>
void	ft::vector<T, Alloc>::reserve(size_type n)
{
	if (n <= _capacity)
		return ;
	
	size_type	new_capacity = n;
	size_type	new_size = _size;
	T			*new_array = _alloc.allocate(n);

	for (size_type i = 0; i < _size; ++i)
	{
		_alloc.construct(new_array + i, _array[i]);
	}

	std::swap(new_capacity, _capacity);
	std::swap(new_size, _size);
	std::swap(new_array, _array);

	for (size_type i = 0; i < new_size; ++i)
	{
		_alloc.destroy(new_array + i);
	}
	_alloc.deallocate(new_array, new_capacity);
}

template <typename T, typename Alloc>
void	ft::vector<T, Alloc>::expand(size_type n)
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
void	ft::vector<T, Alloc>::resize(size_type n, const value_type& val)
{
	if (n < _size)
	{
		for (T *it = _array + n; it != _array + _size; it++)
			_alloc.destroy(it);
		_size = n;
		return ;
	}
	if (n > _size)
	{
		if (n > _capacity)
			expand(n);
	}
	for (T *it = _array + _size;
		it != _array + n; it++)
	{
		_alloc.construct(it, val);
	}
	_size = n;
}

template <typename T, typename Alloc>
std::size_t	ft::vector<T, Alloc>::size() const
{
	return (_size);
}

template <typename T, typename Alloc>
std::size_t	ft::vector<T, Alloc>::max_size()
{
	return (std::numeric_limits<typename
		std::iterator_traits<iterator>::difference_type>::max());
}

template <typename T, typename Alloc>
void	ft::vector<T, Alloc>::push_back (const value_type& val)
{
	resize(_size + 1, val);
}

template <typename T, typename Alloc>
void	ft::vector<T, Alloc>::pop_back()
{
	resize(_size - 1);
}

template <typename T, typename Alloc>
void	ft::vector<T, Alloc>::range_check(std::size_t index)
{
	if (index >= _size)
		throw std::out_of_range("vector");
}

template <typename T, typename Alloc>
T	&ft::vector<T, Alloc>::at(std::size_t index)
{
	range_check(index);
	return (_array[index]);
}

template <typename T, typename Alloc>
const T	&ft::vector<T, Alloc>::at(std::size_t index) const
{
	range_check(index);
	return (_array[index]);
}

template <typename T, typename Alloc>
bool	ft::vector<T, Alloc>::empty() const
{
	return ((_size == 0) ? true : false);
}

template <typename T, typename Alloc>
T	&ft::vector<T, Alloc>::front()
{
	return (*_array);
}

template <typename T, typename Alloc>
T	&ft::vector<T, Alloc>::back()
{
	return (*(_array + _size - 1));
}

template <typename T, typename Alloc>
typename ft::random_access_iterator<T> ft::vector<T, Alloc>::insert(iterator position,
	const value_type &val)
{
	value_type	tmp = val;
	value_type	tmp2;
	std::size_t	size = position - this->begin();

	resize(_size + 1);
	for (typename ft::vector<T>::iterator it = this->begin()+ size; it != this->end();)
	{
		tmp2 = *it;
		*it = tmp;
		tmp = tmp2;
		it++;
	}
	return (this->begin() + size);
}

template <typename T, typename Alloc>
typename ft::random_access_iterator<T> ft::vector<T, Alloc>::insert(iterator position,
	size_type n, const value_type &val)
{
	int	size = position - this->begin();

	resize(_size + 1);
	ft::vector<T, Alloc> tmp(this->size() - size);
	for (typename ft::vector<T>::iterator it1 = this->begin() + size, it2 = tmp.begin();
		it1 != this->end(); it1++, it2++)
		*it2 = *it1;
	for (std::size_t i = 0; i < tmp.size(); i++)
		this->pop_back();
	while (n--)
		this->push_back(val);
	for (typename ft::vector<T>::iterator it = tmp.begin();
		it != tmp.end() - 1; it++)
		this->push_back(*it);
	return (this->begin() + size);
}

template <typename T, typename Alloc>
void	ft::vector<T, Alloc>::clear()
{
	resize(0);
}


template <typename T, typename Alloc>
void	ft::vector<T, Alloc>::operator=(const ft::vector<T, Alloc> &other)
{
	(void)other;
}

template <typename T, typename Alloc>
T	ft::vector<T, Alloc>::operator[](size_type n) const
{
	return (*(_array + n));
}

template <typename T, typename Alloc>
T	&ft::vector<T, Alloc>::operator[](size_type n)
{
	return (*(_array + n));
}

template <class T, class Alloc>
bool operator==(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
{
	if (lhs.size() != rhs.size())
		return (false);
	// for (typename ft::vector<T>::const_iterator it1 = lhs.begin(), it2 = rhs.begin();
	// 	it1 != lhs.end() && it2 != rhs.end(); ++it1, ++it2)
	// {
	// 	if (*it1 != *it2)
	// 		return (false);
	// }
	return (true);
}

template <class T, class Alloc>
bool operator!=(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
{
	return (!(lhs == rhs));
}

template <class T, class Alloc>
bool operator<(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
{
	(void)rhs, (void)lhs;
	return (true);
}

template <class T, class Alloc>
bool operator<=(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
{
	(void)rhs, (void)lhs;
	return (true);
}

template <class T, class Alloc>
bool operator>(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
{
	(void)rhs, (void)lhs;
	return (true);
}

template <class T, class Alloc>
bool operator>=(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
{
	(void)rhs, (void)lhs;
	return (true);
}