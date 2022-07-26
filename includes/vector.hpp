/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timothee <timothee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 17:17:23 by tlafay            #+#    #+#             */
/*   Updated: 2022/07/26 12:37:56 by timothee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

// #include <memory>

namespace ft
{
	template <typename T, typename Alloc = std::allocator<T> >
	class vector
	{
		public:
			vector(const Alloc &alloc = Alloc());
			vector(std::size_t n, const T& value = T(), const Alloc &alloc = Alloc());
			vector(const vector &other);
			~vector();

			void	operator=(const vector &other);

		private:
			Alloc	array;
			T		*_start;
			T		*_end;
	};
}

#include "vector.tpp"

#endif