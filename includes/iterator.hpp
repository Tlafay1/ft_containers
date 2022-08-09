/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafay <tlafay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 10:42:20 by tlafay            #+#    #+#             */
/*   Updated: 2022/08/09 11:01:02 by tlafay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

namespace ft
{
	template<
	    class Category,
	    class T,
	    class Distance = std::ptrdiff_t,
	    class Pointer = T*,
	    class Reference = T&
	    >
	struct iterator
	{
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
		typedef Category	iterator_category;
	};

	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag {};
	struct bidirectional_iterator_tag {};
	struct random_access_iterator_tag {};
}