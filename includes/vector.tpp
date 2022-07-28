/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.tpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafay <tlafay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 15:03:32 by tlafay            #+#    #+#             */
/*   Updated: 2022/07/28 17:13:32 by tlafay           ###   ########.fr       */
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
ft::vector<T, Alloc>::vector(size_type n, const Alloc &alloc):
	_alloc(alloc),
	_size(n),
	_capacity(n)
{
	_array = _alloc.allocate(n);
	for (iterator it = _array; it != _array + _size; ++it)
	{
		_alloc.construct(it);
	}
}

template <typename T, typename Alloc>
ft::vector<T, Alloc>::vector(size_type n, const T& value, const Alloc &alloc):
	_alloc(alloc),
	_size(n),
	_capacity(n)
{
	_array = _alloc.allocate(n);
	for (iterator it = _array; it != _array + _size; ++it)
	{
		_alloc.construct(it, value());
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
T	*ft::vector<T, Alloc>::begin()
{
	return	_array;
}

template <typename T, typename Alloc>
T	*ft::vector<T, Alloc>::end()
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
void	ft::vector<T, Alloc>::resize(size_type n)
{
	if (n < _size)
	{
		for (iterator it = _array + n; it != _array + _size; it++)
			_alloc.destroy(it);
		_size = n;
	}
	// else if (n > _size)
	// {
	// 	if 
	// }
}

template <typename T, typename Alloc>
void	ft::vector<T, Alloc>::resize(size_type n, const value_type& val)
{
	(void)n, val;
}

template <typename T, typename Alloc>
std::size_t	ft::vector<T, Alloc>::size()
{
	return (_size);
}

template <typename T, typename Alloc>
std::size_t	ft::vector<T, Alloc>::max_size()
{
	return (std::numeric_limits<typename std::iterator_traits<iterator>::difference_type>::max());
}

template <typename T, typename Alloc>
void	ft::vector<T, Alloc>::push_back (const value_type& val)
{
	(void)val;
}

template <typename T, typename Alloc>
void	ft::vector<T, Alloc>::operator=(const ft::vector<T, Alloc> &other)
{
	(void)other;
}
