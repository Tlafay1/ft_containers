/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafay <tlafay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 16:59:54 by tlafay            #+#    #+#             */
/*   Updated: 2022/09/15 16:58:04 by tlafay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>

#include "vector.hpp"
#include "stack.hpp"

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
	// N::vector<int> test(5);
	// for (std::size_t i = 0; i < test.size(); i++)
	// {
	// 	test[i] = i;
	// }
	// test.insert(test.begin() + 2, 5, 1000);
	// N::vector<int> test2(5);
	// for (std::size_t i = 0; i < test2.size(); i++)
	// {
	// 	test2[i] = i;
	// }
	// test2.insert(test2.begin() + 2, 5, 1000);
	// test2.reserve(20);
	// test2.resize(10);
	// std::cout << (test != test2) << std::endl;
	// return 0;
	int (arrInt)[20];
	// int nb = 0;
    std::vector<int> c0;
	// execNonConst(c0, ++nb);

    for (int i = 0; i < 10; i++){
        c0.push_back(arrInt[i]);
        // execNonConst(c0, ++nb);
        
        if (!i%3){
            std::vector<int> tmp(c0);
            // execNonConst(tmp, ++nb);
        }
        if (!i%2){
            std::vector<int> tmp;
            tmp = c0;
            // execNonConst(tmp, ++nb);
        }
    }
}