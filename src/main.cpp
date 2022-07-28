/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafay <tlafay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 16:59:54 by tlafay            #+#    #+#             */
/*   Updated: 2022/07/28 12:59:15 by tlafay           ###   ########.fr       */
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
	// std::allocator<std::string> myAllocator;

	// std::string* arr = myAllocator.allocate(5);

	// for (int i = 0; i < 5; ++i)
	// {
	// 	myAllocator.construct(arr + i, "Test()");
	// }

	// for (int i = 0; i < 5; ++i)
	// {
	// 	myAllocator.destroy(arr + i);
	// }
	// myAllocator.deallocate(arr, 5);
	ft::vector<Test> test(5);
	return 0;
}