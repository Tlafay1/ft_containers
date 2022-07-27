/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafay <tlafay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 16:59:54 by tlafay            #+#    #+#             */
/*   Updated: 2022/07/27 11:25:53 by tlafay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>

#include "vector.hpp"

int main(void)
{
	std::cout << "Hello World" << std::endl;
	ft::vector<int> a;
	ft::vector<int> v(5, 10);
	std::cout << *v.begin() << std::endl;
	v.push_back(3);
	std::cout << *(v.end() - 1) << std::endl;
	return 0;
}