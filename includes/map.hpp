#ifndef MAP_HPP
# define MAP_HPP

#include "pair.hpp"
#include "iterator_traits.hpp"
#include "reverse_iterator.hpp"

namespace ft
{
	template< class Key, class T, class Compare = std::less<Key>,
		class Allocator = std::allocator< std::pair< const Key, T> > >
	class map
	{
		typedef key_type										Key;
		typedef	T												mapped_type;
		typename typedef ft::pair<const Key, T>					value_type;
		typedef	std::size_t										size_type;
		typedef	ft::iterator_traits<iterator>::difference_type	difference_type;
		typedef	Compare											key_compare;
		typedef	Allocator										allocator_type;
		typedef	value_type										&reference;
		typedef	const value_type								&const_reference;
		typename typedef Allocator::pointer						pointer; 
		typename typedef Allocator::const_pointer				const_pointer;	 
		typename typedef ft::reverse_iterator<iterator>			reverse_iterator;
		typename typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

	};
}

#include "map.tpp"

#endif