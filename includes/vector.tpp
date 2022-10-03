#include "vector.hpp"

namespace ft
{
		template <typename T, typename Alloc>
		vector<T, Alloc>::vector(const Alloc &alloc):
			_alloc(alloc),
			_array(pointer()),
			_size(0),
			_capacity(0)
		{}

	template <typename T, typename Alloc>
	vector<T, Alloc>::vector(size_type n, const T& value, const Alloc &alloc):
		_alloc(alloc),
		_array(pointer()),
		_size(0),
		_capacity(0)
	{
		assign(n, value);
		// _array = _alloc.allocate(n);
		// for (T *it = _array; it != _array + _size; ++it)
		// {
		// 	_alloc.construct(it, value);
		// }
	}

	template <typename T, typename Alloc>
	template <class InputIterator>
	vector<T, Alloc>::vector (InputIterator first, InputIterator last,
		const allocator_type& alloc,
		typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type*):
		_alloc(alloc),
		_array(pointer()),
		_size(0),
		_capacity(0)
	{
		assign(first, last);
	}

	template <typename T, typename Alloc>
	vector<T, Alloc>::vector(const vector<T, Alloc> &other):
		_array(pointer()),
		_size(0),
		_capacity(0)
	{
		*this = other;
	}

	template <typename T, typename Alloc>
	vector<T, Alloc>::~vector()
	{
		clear();
		_alloc.deallocate(_array, _capacity);
	}

	template <typename T, typename Alloc>
	vector<T, Alloc>
		&vector<T, Alloc>::operator=(const vector<T, Alloc> &other)
	{		
		_alloc = other._alloc;
		reserve(other._size);
		assign(other.begin(), other.end());
		return (*this);
	}

	template <typename T, typename Alloc>
	template <typename InputIterator>
	void	vector<T, Alloc>::assign(InputIterator first, InputIterator last,
		typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type*)
	{
		clear();
		for (; first != last; ++first)
			push_back(*first);
	}

	template <typename T, typename Alloc>
	void	vector<T, Alloc>::assign (size_type n, const value_type& val)
	{
		clear();
		reserve(n);
		for (size_type i = 0; i < n; i++)
			_alloc.construct(_array + i, val);
		_size = n;
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::allocator_type vector<T, Alloc>::get_allocator() const
	{
		return (_alloc);
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::reference	vector<T, Alloc>::at(std::size_t index)
	{
		range_check(index);
		return (_array[index]);
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::const_reference
		vector<T, Alloc>::at(std::size_t index) const
	{
		range_check(index);
		return (_array[index]);
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::reference
		vector<T, Alloc>::operator[](size_type n)
	{
		return (_array[n]);
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::const_reference
		vector<T, Alloc>::operator[](size_type n) const
	{
		return (_array[n]);
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::reference	vector<T, Alloc>::front()
	{
		return (*(begin()));
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::const_reference	vector<T, Alloc>::front() const
	{
		return (*(begin()));
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::reference	vector<T, Alloc>::back()
	{
		return (*(end() - 1));
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::const_reference	vector<T, Alloc>::back() const
	{
		return (*(end() - 1));
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::value_type	*vector<T, Alloc>::data()
	{
		return (_array);
	}

	template <typename T, typename Alloc>
	const typename vector<T, Alloc>::value_type	*vector<T, Alloc>::data() const
	{
		return (_array);
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::iterator	vector<T, Alloc>::begin()
	{
		return	(_array);
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::const_iterator	vector<T, Alloc>::begin() const
	{
		return	(_array);
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::iterator	vector<T, Alloc>::end()
	{
		return	(_array + _size);
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::const_iterator	vector<T, Alloc>::end() const
	{
		return	(_array + _size);
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::reverse_iterator	vector<T, Alloc>::rbegin()
	{
		return (reverse_iterator(end()));
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::const_reverse_iterator	vector<T, Alloc>::rbegin() const
	{
		return ((const_reverse_iterator)end());
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::reverse_iterator	vector<T, Alloc>::rend()
	{
		return (reverse_iterator(begin()));
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::const_reverse_iterator	vector<T, Alloc>::rend() const
	{
		return ((const_reverse_iterator)begin());
	}

	template <typename T, typename Alloc>
	bool	vector<T, Alloc>::empty() const
	{
		return ((_size == 0) ? true : false);
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::size_type	vector<T, Alloc>::size() const
	{
		return (_size);
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::size_type	vector<T, Alloc>::max_size() const
	{
		return (std::min(_alloc.max_size(),
			static_cast<size_type>(std::numeric_limits<difference_type>::max())));
	}

	template <typename T, typename Alloc>
	void	vector<T, Alloc>::reserve(size_type new_cap)
	{
		if (new_cap == 0 || _capacity >= new_cap)
			return ;
		if (new_cap > max_size())
			throw std::length_error("attempt to create ft::vector with a size exceeding max_size()");
		pointer	tmp;
		if (!new_cap)
			tmp = pointer();
		else
			tmp = _alloc.allocate(new_cap);
		for (size_type i = 0; i < _size; i++)
		{
			_alloc.construct(tmp + i, _array[i]);
			_alloc.destroy(_array + i);
		}
		_alloc.deallocate(_array, _capacity);
		_array = tmp;
		_capacity = new_cap;
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::size_type	vector<T, Alloc>::capacity() const
	{
		return (_capacity);
	}

	template <typename T, typename Alloc>
	void	vector<T, Alloc>::clear()
	{
		for (size_type i = 0; i < _size; i++)
			_alloc.destroy(&(_array[i]));
		_size = 0;
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::pointer	vector<T, Alloc>::insert(const_iterator position,
		const value_type &val)
	{
		size_type	size = position - begin();

		if (position == end())
			push_back(val);
		else
			insert(position, 1, val);
		return (iterator(_array + size));
	}

	template <typename T, typename Alloc>
	void	vector<T, Alloc>::insert(const_iterator position,
		size_type n, const value_type &val)
	{
		size_type	size = position - _array;

		reserve(_size + n);
		iterator src = end() - 1;
		for (iterator dest = src + n; src >= _array + size; src--, dest--)
		{
			_alloc.construct(dest, *src);
			_alloc.destroy(src);
		}
		src++;
		for (size_type i = 0; i < n; ++i, ++src)
			_alloc.construct(src, val);
		_size += n;
	}

	template <typename T, typename Alloc>
	template< class InputIterator >
	void	vector<T, Alloc>::insert(const_iterator position,
		InputIterator first, InputIterator last,
		typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type*)
	{
		size_type idx = position - _array;
		size_type cnt = std::distance(first, last);

		reserve(_size + cnt);

		for (size_type i = 0; i < cnt; ++i) {
			_alloc.construct(_array + _size + i, *first);
		}
		for (difference_type i = _size - 1; i >= 0 && i >= (difference_type)idx; --i) {
			_array[i + cnt] = _array[i];
		}
		for (size_type i = idx; i < idx + cnt; ++i) {
			_array[i] = *first++;
		}
		_size += cnt;
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::iterator	vector<T, Alloc>::erase(iterator position)
	{
		if (position + 1 != end())
			std::copy(position + 1, end(), position);
		_size--;
		_alloc.destroy(_array + _size);
		return (position);
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::iterator	vector<T, Alloc>::erase(iterator first, iterator last)
	{
		if (first != last)
		{
			if (last != end())
				std::copy(last, end(), first);
			for (iterator it = first + (end() - last); it != end(); it++)
				_alloc.destroy(it);
			_size = first + (end() - last) - _array;
		}

		return first;
	}

	template <typename T, typename Alloc>
	void	vector<T, Alloc>::push_back (const value_type& val)
	{
		resize(_size + 1, val);
	}

	template <typename T, typename Alloc>
	void	vector<T, Alloc>::pop_back()
	{
		resize(_size - 1);
	}

	template <typename T, typename Alloc>
	void	vector<T, Alloc>::resize(size_type n, const value_type& val)
	{
		if (n > _size)
			insert(end(), n - _size, val);
		else
		{
			iterator tmp = _array + n;
			for (iterator it = tmp; it != end(); it++) {
				_alloc.destroy(it);
			}
			_size = tmp - _array;
		}
	}

	template <typename T, typename Alloc>
	void	vector<T, Alloc>::swap(vector<T, Alloc> &other)
	{
		std::swap(_alloc, other._alloc);
		std::swap(_array, other._array);
		std::swap(_size, other._size);
		std::swap(_capacity, other._capacity);
	}

	template <typename T, typename Alloc>
	void	vector<T, Alloc>::expand(size_type n)
	{
		size_t	new_capacity;
		
		if (!_capacity)
			new_capacity = 1;
		else if (_capacity * 2 < max_size())
			new_capacity = 2 * _capacity;
		else if (_capacity == max_size())
			throw std::length_error("Cannot extend past max_size()");
		else if (this->_capacity + 1 <= this->max_size())
			new_capacity = max_size();
		if (n > new_capacity)
			new_capacity = n;
		reserve(new_capacity);
	}

	template <typename T, typename Alloc>
	void	vector<T, Alloc>::range_check(std::size_t index)
	{
		if (index >= _size)
			throw std::out_of_range("vector");
	}

	template <class T, class Alloc>
	bool	operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
				return (false);
		return (equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class T, class Alloc>
	bool	operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return (!(lhs == rhs));
	}

	template <class T, class Alloc>
	bool	operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return (std::lexicographical_compare(lhs.begin(),lhs.end(),
			rhs.begin(), rhs.end()));
	}

	template <class T, class Alloc>
	bool	operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return ((lhs == rhs) || (lhs < rhs));
	}

	template <class T, class Alloc>
	bool	operator>(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return (!(lhs <= rhs));
	}

	template <class T, class Alloc>
	bool	operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return (!(lhs < rhs));
	}

	template <class T, class Alloc>
	void	swap(vector<T, Alloc>& lhs, vector<T, Alloc>& rhs)
	{
		lhs.swap(rhs);
	}
}