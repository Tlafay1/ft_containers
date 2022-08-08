/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafay <tlafay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 17:17:23 by tlafay            #+#    #+#             */
/*   Updated: 2022/08/08 16:03:18 by tlafay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

#include "random_access_iterator.hpp"

// #include <cstdint>
#include <cstdlib>
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
			explicit vector(size_type n,
				const value_type &value = value_type(),
				const Alloc &alloc = Alloc());
			vector(const vector &other);
			~vector();

			iterator			begin();
			const_iterator			begin() const;
			iterator			end();
			const_iterator			end() const;
			void				push_back(const value_type &val);
			void				pop_back();
			void				reserve(size_type n);
			size_type			capacity();
			size_type			size() const;
			size_type			max_size();
			void				resize(size_type n,
				const value_type &val = value_type());
			value_type&			at(size_type index);
			const value_type&	at(size_type index) const;
			bool				empty() const;
			value_type			&front();
			value_type			&back();
			iterator			insert(iterator position,
				const value_type &val);
			iterator			insert(iterator position, size_type n,
				const value_type &val);
			void				clear();


			void		operator=(const vector &other);
			value_type	operator[](size_type n) const;
			value_type	&operator[](size_type n);


		private:
			Alloc		_alloc;
			value_type	*_array;
			size_type	_size;
			size_type	_capacity;

			void	expand(size_type n);
			void	range_check(std::size_t index);
	};
}

#include "vector.tpp"

#endif