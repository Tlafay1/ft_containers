/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timothee <timothee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 17:17:23 by tlafay            #+#    #+#             */
/*   Updated: 2022/08/02 10:27:06 by timothee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

#include "random_access_iterator.hpp"

// #include <cstdint>
#include <stdexcept>
#include <limits>

namespace ft
{
	template < typename T, typename Alloc = std::allocator<T> >
	class vector
	{
		public:
			typedef T			value_type;
			typedef T*			iterator;
			typedef const T*	const_iterator;
			typedef std::size_t	size_type;

			explicit vector(const Alloc &alloc = Alloc());
			// explicit vector(size_type n, const Alloc &alloc = Alloc());
			explicit vector(size_type n, const T &value = T(),
				const Alloc &alloc = Alloc());
			vector(const vector &other);
			~vector();

			iterator	begin();
			iterator	end();
			void		push_back(const value_type &val);
			void		reserve(size_type n);
			size_type	capacity();
			size_type	size();
			size_type	max_size();
			void		resize(size_type n, const value_type &val);

			void	operator=(const vector &other);

		private:
			Alloc		_alloc;
			value_type	*_array;
			size_type	_size;
			size_type	_capacity;

			void	expand(size_type n);
	};
}

#include "vector.tpp"

#endif