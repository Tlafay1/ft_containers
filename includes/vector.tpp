/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.tpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timothee <timothee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 15:03:32 by tlafay            #+#    #+#             */
/*   Updated: 2022/07/27 16:00:21 by timothee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"

template <typename T, typename Alloc>
ft::vector<T, Alloc>::vector(const Alloc &alloc):
	_array(alloc),
	_start(NULL),
	_end(NULL),
	_num(0)
{

}

template <typename T, typename Alloc>
ft::vector<T, Alloc>::vector(std::size_t n, const T& value, const Alloc &alloc):
	_array(alloc),
	_num(n)
{
	_start = _array.allocate(_num);
	_end = _start;
	while (n--)
	{
		_array.construct(_end, value);
		_end++;
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
	T	*tmp = _start;

	for (; tmp != _end; tmp++)
		_array.destroy(tmp);
	_array.deallocate(_start, _num);
}

template <typename T, typename Alloc>
T	*ft::vector<T, Alloc>::begin()
{
	return	_start;
}

template <typename T, typename Alloc>
T	*ft::vector<T, Alloc>::end()
{
	return	_end;
}

template <typename T, typename Alloc>
void		ft::vector<T, Alloc>::push_back (const value_type& val)
{
	/** TO REMOVE **/
	std::size_t	diff = 0;
	T	*tmp = _start;

	for (; tmp != _end; ++tmp, ++diff);
	/** END TO REMOVE **/
	
	if (_num == diff)
	{
		_num *= 2;
		tmp = _array.allocate(_num);
		_end = tmp;
		for (std::size_t i = 0; i < _num; i++, _end++)
			*_end = *_start + i;
		_array.deallocate(_start, _num / 2);
		_start = tmp;
	}
	*_end++ = val;
}

template <typename T, typename Alloc>
void	ft::vector<T, Alloc>::operator=(const ft::vector<T, Alloc> &other)
{
	(void)other;
}
