/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.tpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timothee <timothee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 15:03:32 by tlafay            #+#    #+#             */
/*   Updated: 2022/07/26 12:35:14 by timothee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"

template <typename T, typename Alloc>
ft::vector<T, Alloc>::vector(const Alloc &alloc):
	array(alloc)
{

}

template <typename T, typename Alloc>
ft::vector<T, Alloc>::vector(std::size_t n, const T& value, const Alloc &alloc):
	array(alloc)
{
	_start = array.allocate(n);
	_end = _start;
	while (n--)
	{
		array.construct(_end, value);
		_end++;
	}
	for (; _start != _end; _start++ )
		std::cout << *_start << std::endl;
}

template <typename T, typename Alloc>
ft::vector<T, Alloc>::vector(const ft::vector<T, Alloc> &other)
{
	*this = other;
}

template <typename T, typename Alloc>
ft::vector<T, Alloc>::~vector()
{
}

template <typename T, typename Alloc>
void	ft::vector<T, Alloc>::operator=(const ft::vector<T, Alloc> &other)
{
	(void)other;
}
