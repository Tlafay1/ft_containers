/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafay <tlafay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 10:25:35 by timothee          #+#    #+#             */
/*   Updated: 2022/08/09 11:42:47 by tlafay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOM_ACCESS_ITERATOR_HPP
# define RANDOM_ACCESS_ITERATOR_HPP

#include "iterator.hpp"

namespace ft
{
	template <typename T>
	class random_access_iterator: ft::iterator<ft::random_access_iterator_tag, T>
	{
		public:
			random_access_iterator(): _ptr(nullptr){}
			random_access_iterator(T *rhs) : _ptr(rhs) {}
			random_access_iterator(const random_access_iterator &rhs) : _ptr(rhs._ptr){}

			random_access_iterator& operator=(T *rhs)
			{
				_ptr = rhs;
				return *this;
			}
			random_access_iterator& operator=(const random_access_iterator &rhs)
			{
				_ptr = rhs._ptr;
				return *this;
			}
			random_access_iterator& operator+=(const int& rhs)
			{
				_ptr += rhs;
				return *this;
			}
			random_access_iterator& operator-=(const int& rhs)
			{
				_ptr -= rhs;
				return *this;
			}
			T	&operator*()
			{
				return *_ptr;
			}
			T	*operator->()
			{
				return _ptr;
			}
			T	&operator[](const int& rhs)
			{
				return _ptr[rhs];
			}

	    	// Operators : arithmetic
			random_access_iterator& operator++()
			{
				++_ptr;
				return *this;
			}
			random_access_iterator& operator--()
			{
				--_ptr;
				return *this;
			}
			random_access_iterator& operator++(int)
			{
				random_access_iterator tmp(*this);
				++_ptr;
				return tmp;
			}
			random_access_iterator& operator--(int)
			{
				random_access_iterator tmp(*this);
				--_ptr;
				return tmp;
			}
			random_access_iterator operator+(const random_access_iterator& rhs)
			{
				return random_access_iterator(_ptr+rhs._ptr);
			}
			random_access_iterator operator-(const random_access_iterator& rhs)
			{
				return random_access_iterator(_ptr-rhs._ptr);
			}
			random_access_iterator operator+(const int& rhs)
			{
				return random_access_iterator(_ptr+rhs);
			}
			random_access_iterator operator-(const int& rhs)
			{
				return random_access_iterator(_ptr-rhs);
			}
			// random_access_iterator operator+(const int& lhs,
			// 	const random_access_iterator& rhs)
			// {
			// 	return random_access_iterator(lhs+_ptr);
			// }
			// random_access_iterator operator-(const int& lhs,
			// 	const random_access_iterator& rhs)
			// {
			// 	return random_access_iterator(lhs-_ptr);
			// }

	    	// Operators : comparison
			bool operator==(const random_access_iterator& rhs)
			{
				return _ptr == rhs._ptr;
			}
			bool operator!=(const random_access_iterator& rhs)
			{
				return _ptr != rhs._ptr;
			}
			bool operator>(const random_access_iterator& rhs)
			{
				return _ptr > rhs._ptr;
			}
			bool operator<(const random_access_iterator& rhs)
			{
				return _ptr < rhs._ptr;
			}
			bool operator>=(const random_access_iterator& rhs)
			{
				return _ptr >= rhs._ptr;
			}
			bool operator<=(const random_access_iterator& rhs)
			{
				return _ptr <= rhs._ptr;
			}
		protected:
			T	*_ptr;
	};
}

#endif