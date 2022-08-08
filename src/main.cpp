/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafay <tlafay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 16:59:54 by tlafay            #+#    #+#             */
/*   Updated: 2022/08/08 10:42:37 by tlafay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>

#include "vector.hpp"

class Test
{
	public:
		int	*arr;
		Test(): arr(new int[10]) {std::cout << "Constructor called" << std::endl;}
		~Test() {std::cout << "Destructor called" << std::endl; delete[] arr;}
};

namespace N = ft;

int main(void)
{
	N::vector<int> test(5);
	for (std::size_t i = 0; i < test.size(); i++)
	{
		test[i] = i;
	}
	test.insert(test.begin() + 2, 5, 1000);
	N::vector<int> test2(5);
	for (std::size_t i = 0; i < test2.size(); i++)
	{
		test2[i] = i;
	}
	test2.insert(test2.begin() + 2, 5, 1000);
	// for (std::size_t i = 0; i < test.size(); i++)
	// {
	// 	std::cout << test[i] << std::endl;
	// }
	std::cout << (test != test2) << std::endl;
	return 0;
}