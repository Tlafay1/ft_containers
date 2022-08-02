/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafay <tlafay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 16:59:54 by tlafay            #+#    #+#             */
/*   Updated: 2022/07/28 16:24:15 by tlafay           ###   ########.fr       */
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

int main(void)
{
	std::vector<Test> test(5, Test());
	// std::cout << test.capacity() << std::endl;
	// std::cout << test.size() << std::endl;
	// test.resize(10);
	// std::cout << test.size() << std::endl;
	return 0;
}