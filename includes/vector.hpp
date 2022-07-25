/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafay <tlafay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 17:17:23 by tlafay            #+#    #+#             */
/*   Updated: 2022/07/25 13:32:01 by tlafay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

#include "test.hpp"

template <typename T>
class ft::vector
{
	public:
		vector();
		vector(std::size_t n, const T& value = T());
		vector(const vector &other);
		~vector();

		void	operator=(const vector &other);

	private:
		T	*array;
};

#include "vector.tpp"

#endif