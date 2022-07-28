/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafay <tlafay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 17:17:23 by tlafay            #+#    #+#             */
/*   Updated: 2022/07/28 13:48:59 by tlafay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

#include "random_access_iterator.hpp"

namespace ft
{
	template < typename T, typename Alloc = std::allocator<T> >
	class vector
	{
		public:
			typedef T			value_type;
			typedef T*			iterator;
			typedef const T*	const_iterator;

			explicit vector(const Alloc &alloc = Alloc());
			explicit vector(std::size_t n, const Alloc &alloc = Alloc());
			explicit vector(std::size_t n, const T& value,
				const Alloc &alloc = Alloc());
			vector(const vector &other);
			~vector();

			iterator	begin();
			iterator	end();
			void		push_back(const value_type& val);
			void		reserve(std::size_t n);
			std::size_t	capacity();

			void	operator=(const vector &other);

		private:
			Alloc		_alloc;
			value_type	*_array;
			std::size_t	_size;
			std::size_t	_capacity;
	};
}

#include "vector.tpp"

#endif