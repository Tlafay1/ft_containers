/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.tpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafay <tlafay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 15:03:32 by tlafay            #+#    #+#             */
/*   Updated: 2022/07/25 10:46:36 by tlafay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"

template <typename T>
ft::vector<T>::vector(): array(new T[10])
{

}

template <typename T>
ft::vector<T>::vector(std::size_t n, const T& value): array(new T[n])
{
	while (n--)
	{
		array[n] = value;
	}
}

template <typename T>
ft::vector<T>::vector(const ft::vector<T> &f)
{
	*this = f;
}

template <typename T>
ft::vector<T>::~vector()
{
}

template <typename T>
void	ft::vector<T>::operator=(const ft::vector<T> &f)
{
	(void)f;
}
