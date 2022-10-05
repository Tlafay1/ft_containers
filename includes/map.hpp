#ifndef MAP_HPP
# define MAP_HPP

#include <limits>

#include "pair.hpp"
#include "iterator_traits.hpp"
#include "reverse_iterator.hpp"
#include "avl_tree.hpp"
#include "equal.hpp"

namespace ft
{
	template< class Key, class T, class Compare = std::less<Key>,
	class Alloc = std::allocator< ft::pair<const Key, T> > >
	class map
	{
		private:
			typedef avl_tree<Key, T, Compare, Alloc>					tree;
		public:
			typedef Key													key_type;
			typedef	T													mapped_type;
			typedef pair<const Key, T>									value_type;
			typedef	std::size_t											size_type;
			typedef	Compare												key_compare;
			typedef	Alloc												allocator_type;
			typedef	value_type											&reference;
			typedef	const value_type									&const_reference;
			typedef typename Alloc::pointer								pointer;
			typedef typename Alloc::const_pointer						const_pointer;
			typedef typename tree::iterator								iterator;
			typedef typename tree::const_iterator						const_iterator;
			typedef ft::reverse_iterator<iterator>						reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>				const_reverse_iterator;
			typedef	typename iterator_traits<iterator>::difference_type	difference_type;

			class value_compare
			{
				friend class map;
				protected:
					key_compare comp;
					value_compare(const key_compare &c): comp(c) {}
				public:
					typedef bool		result_type;
					typedef value_type	first_argument_type;
					typedef value_type	second_argument_type;
					bool 				operator()(const value_type& x, const value_type& y) const
					{
						return comp(x.first, y.first);
					}
			};

			map();
			explicit map(const Compare &comp, const Alloc& alloc = Alloc());
			template< class InputIt >
			map(InputIt first, InputIt last, const Compare& comp = Compare(),
				const allocator_type& alloc = Alloc());
			map(const map &other);
			~map();

			map										&operator=(const map &other);
			allocator_type							get_allocator() const;
			T										&at(const Key &key);
			const T									&at(const Key &key) const;
			T										&operator[](const Key &key);
			iterator								begin();
			const_iterator							begin() const;
			iterator								end();
			const_iterator							end() const;
			reverse_iterator						rbegin();
			const_reverse_iterator					rbegin() const;
			reverse_iterator						rend();
			const_reverse_iterator					rend() const;
			bool									empty() const;
			size_type								size() const;
			size_type								max_size() const;
			void									clear();
			pair<iterator, bool>					insert(const value_type &value);
			iterator								insert(iterator hint, const value_type &value);
			template <class InputIt>
			void									insert(InputIt first, InputIt last);
			void									erase(iterator pos);
			void									erase(iterator first, iterator last);
			size_type								erase(const Key &key);
			void									swap(map &other);
			size_type								count(const Key &key) const;
			iterator								find(const Key &key);
			const_iterator							find(const Key &key) const;
			pair<iterator, iterator>				equal_range(const Key &key);
			pair<const_iterator, const_iterator>	equal_range(const Key &key) const;
			iterator								lower_bound(const Key &key);
			const_iterator							lower_bound(const Key &key) const;
			iterator								upper_bound(const Key &key);
			const_iterator							upper_bound(const Key &key) const;
			key_compare								key_comp() const;
			value_compare							value_comp() const;

		private:
			tree	_tree;
	};

template <class Key, class T, class Compare, class Alloc>
bool	operator==(const map<Key, T, Compare, Alloc>& lhs,
	const map<Key, T, Compare, Alloc>& rhs);	

template <class Key, class T, class Compare, class Alloc>
bool	operator!=(const map<Key, T, Compare, Alloc>& lhs,
	const map<Key, T, Compare, Alloc>& rhs);

template <class Key, class T, class Compare, class Alloc>
bool	operator<(const map<Key, T, Compare, Alloc>& lhs,
	const map<Key, T, Compare, Alloc>& rhs);

template <class Key, class T, class Compare, class Alloc>
bool	operator<=(const map<Key, T, Compare, Alloc>& lhs,
	const map<Key, T, Compare, Alloc>& rhs);

template <class Key, class T, class Compare, class Alloc>
bool	operator>(const map<Key, T, Compare, Alloc>& lhs,
	const map<Key, T, Compare, Alloc>& rhs);

template <class Key, class T, class Compare, class Alloc>
bool	operator>=(const map<Key, T, Compare, Alloc>& lhs,
	const map<Key, T, Compare, Alloc>& rhs);

template <class Key, class T, class Compare, class Alloc>
void	swap(map<Key, T, Compare, Alloc>& lhs, map<Key, T, Compare, Alloc>& rhs);

}

#include "map.tpp"

#endif