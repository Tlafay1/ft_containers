/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafay <tlafay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 17:17:23 by tlafay            #+#    #+#             */
/*   Updated: 2022/07/27 11:21:31 by tlafay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

namespace ft
{
	template <typename T, typename Alloc = std::allocator<T> >
	class vector
	{
		public:
			typedef T			value_type;
			typedef value_type* iterator;

			vector(const Alloc &alloc = Alloc());
			vector(std::size_t n, const T& value = T(),
				const Alloc &alloc = Alloc());
			vector(const vector &other);
			~vector();

			iterator	begin();
			iterator	end();
			void		push_back (const value_type& val);

			void	operator=(const vector &other);

		private:
			Alloc		_array;
			T			*_start;
			T			*_end;
			std::size_t	_num;
	};
}

#include "vector.tpp"

#endif