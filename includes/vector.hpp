#ifndef VECTOR_HPP
# define VECTOR_HPP

#include "random_access_iterator.hpp"
#include "iterator_traits.hpp"
#include "reverse_iterator.hpp"
#include "equal.hpp"
#include "enable_if.hpp"
#include "is_integral.hpp"

#include <cstdlib>
#include <stdexcept>
#include <limits>
#include <algorithm>

namespace ft
{
	template < typename T, typename Alloc = std::allocator<T> >
	class vector
	{
		public:
			typedef T												value_type;
			typedef Alloc											allocator_type;
			typedef typename allocator_type::reference				reference;
			typedef typename allocator_type::const_reference		const_reference;
			typedef typename allocator_type::pointer				pointer;
			typedef typename allocator_type::const_pointer			const_pointer;
			typedef pointer											iterator;
			typedef const_pointer									const_iterator;
			typedef typename ft::reverse_iterator<iterator>			reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>	const_reverse_iterator;
			typedef typename
				ft::iterator_traits<iterator>::difference_type		difference_type;
			typedef std::size_t										size_type;

			explicit vector(const allocator_type &alloc = Alloc());
			explicit vector(size_type n,
				const value_type &value = value_type(),
				const Alloc &alloc = Alloc());
			template <class InputIterator>
			vector (InputIterator first, InputIterator last,
				const allocator_type& alloc = allocator_type(),
				typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = 0);
			vector(const vector &other);
			~vector();

			vector					&operator=(const vector &other);
			template <class InputIterator>
			void					assign(InputIterator first, InputIterator last,
				typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0);
			void					assign(size_type n, const value_type& val);
			allocator_type			get_allocator() const;

			reference				at(size_type index);
			const_reference			at(size_type index) const;
			reference				operator[](size_type n);
			const_reference			operator[](size_type n) const;
			reference				front();
			const_reference			front() const;
			reference				back();
			const_reference			back() const;
			value_type				*data();
			const value_type		*data() const;

			iterator				begin();
			const_iterator			begin() const;
			iterator				end();
			const_iterator			end() const;
			reverse_iterator		rbegin();
			const_reverse_iterator	rbegin() const;
			reverse_iterator		rend();
			const_reverse_iterator	rend() const;

			bool					empty() const;
			size_type				size() const;
			size_type				max_size();
			void					reserve(size_type new_cap);
			size_type				capacity() const;

			void					clear();
			iterator				insert(const_iterator position,
				const value_type &val);
			void					insert(const_iterator position, size_type n,
				const value_type &val);
			template< class InputIterator >
			void					insert(const_iterator position,
				InputIterator first, InputIterator last,
				typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0);
			iterator				erase(iterator position);
			iterator				erase(iterator first, iterator last);
			void					push_back(const value_type &val);
			void					pop_back();
			void					resize(size_type n,
				const value_type &val = value_type());
			void					swap(vector& other);

		private:
			allocator_type	_alloc;
			pointer			_array;
			size_type		_size;
			size_type		_capacity;

			void	expand(size_type n);
			void	range_check(std::size_t index);
	};
}

#include "vector.tpp"

#endif