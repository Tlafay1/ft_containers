#ifndef MAP_HPP
# define MAP_HPP

#include "pair.hpp"
#include "iterator_traits.hpp"
#include "reverse_iterator.hpp"
#include "avl_tree.hpp"

namespace ft
{
	template< class Key, class T, class Compare = std::less<Key>,
		class Allocator = std::allocator< std::pair<const Key, T> > >
	class map
	{
		typedef Key												key_type;
		typedef	T												mapped_type;
		typedef pair<const Key, T>								value_type;
		typedef	std::size_t										size_type;
		typedef	Compare											key_compare;
		typedef	Allocator										allocator_type;
		typedef	value_type										&reference;
		typedef	const value_type								&const_reference;
		typedef typename Allocator::pointer						pointer;
		typedef typename Allocator::const_pointer				const_pointer;

		// To uncomment after the iterator is done

		// typedef	ft::iterator_traits<iterator>::difference_type	difference_type;
		// typedef typename ft::reverse_iterator<iterator>			reverse_iterator;
		// typedef typename ft::reverse_iterator<const_iterator>	const_reverse_iterator;

	};
}

#include "map.tpp"

#endif