/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.tpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafay <tlafay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 15:03:32 by tlafay            #+#    #+#             */
/*   Updated: 2022/06/30 15:10:40 by tlafay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"

template <typename T>
ft::vector<T>::vector()
{
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
