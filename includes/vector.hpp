/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timothee <timothee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 17:17:23 by tlafay            #+#    #+#             */
/*   Updated: 2022/07/27 16:23:48 by timothee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

#include "random_access_iterator.hpp"

namespace ft
{
	template <typename T, typename Alloc = std::allocator<T> >
	class vector
	{
		public:
			typedef T			value_type;
			typedef value_type* iterator;

			vector(const Alloc &alloc = Alloc());
			vector(std::size_t n, const value_type& value = value_type(),
				const Alloc &alloc = Alloc());
			vector(const vector &other);
			~vector();

			iterator	begin();
			iterator	end();
			void		push_back(const value_type& val);

			void	operator=(const vector &other);

		private:
			Alloc		_array;
			value_type	*_start;
			value_type	*_end;
			std::size_t	_num;
	};
}

#include "vector.tpp"

#endif