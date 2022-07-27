/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timothee <timothee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 10:25:35 by timothee          #+#    #+#             */
/*   Updated: 2022/07/27 10:39:38 by timothee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOM_ACCESS_ITERATOR_HPP
# define RANDOM_ACCESS_ITERATOR_HPP

struct random_access_iterator
{
	int	z;

	void	sayHello() {std::cout << "Hello" << std::endl;}
	// random_access_iterator();
	// random_access_iterator(const random_access_iterator &f);
	// ~random_access_iterator();

	// void	operator=(const random_access_iterator &f);
};

#endif