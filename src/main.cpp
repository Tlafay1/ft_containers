/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timothee <timothee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 16:59:54 by tlafay            #+#    #+#             */
/*   Updated: 2022/08/06 11:00:32 by timothee         ###   ########.fr       */
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
	ft::vector<Test> test(5, Test());
	Test a = test.at(10);
	std::cout << test.capacity() << std::endl;
	std::cout << test.size() << std::endl;
	test.resize(10);
	std::cout << test.size() << std::endl;
	return 0;
}