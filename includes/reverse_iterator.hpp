#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP


namespace ft
{
	template <class Iter>
	class reverse_iterator
	{
	public:
		typedef Iter 													iterator_type;
		typedef typename std::iterator_traits<Iter>::iterator_category	iterator_category;
		typedef typename std::iterator_traits<Iter>::value_type			value_type;
		typedef typename std::iterator_traits<Iter>::difference_type	difference_type;
		typedef typename std::iterator_traits<Iter>::pointer			pointer;
		typedef typename std::iterator_traits<Iter>::reference			reference;

	public:
		reverse_iterator() {}
		explicit reverse_iterator(iterator_type x): current(x) {}
		template<class U>
		reverse_iterator(const reverse_iterator<U>& other): current(other.base()) {}

		template< class U >
		reverse_iterator &operator=(const reverse_iterator<U>& other)
		{
			this->current = other.base();
			return (*this);
		}

		iterator_type base() const { return (current); }

		reference operator*() const
		{
        	Iter tmp = current;
        	return (*--tmp);
		}

		pointer operator->() const
		{
			return (&(this->operator*()));
		}

		reference operator[](difference_type n) const { return (current[-n - 1]); }

		reverse_iterator &operator++()
		{
			--current;
			return *this;
		}

		reverse_iterator &operator--()
		{
			++current;
			return *this;
		}

		reverse_iterator &operator++(int)
		{
			reverse_iterator tmp = *this;
			--(*this);
			return (tmp);
		}

		reverse_iterator &operator--(int)
		{
			reverse_iterator tmp = *this;
			++(*this);
			return (tmp);
		}

		reverse_iterator &operator+(difference_type n)
		{
			iterator_type tmp = this->base();
			tmp -= n;
			return (tmp);
		}

		reverse_iterator &operator-(difference_type n)
		{
			iterator_type tmp = this->base();
			tmp += n;
			return (tmp);
		}

		reverse_iterator &operator+=(difference_type n)
		{
			current -= n;
			return (*this);
		}

		reverse_iterator &operator-=(difference_type n)
		{
			current += n;
			return (*this);
		}

	protected:
		iterator_type	current;
	};

	template <class Iter>
	bool operator==(const reverse_iterator<Iter> &a,
		const reverse_iterator<Iter> &b)
	{
		return a.current == b.current;
	}
	
	template <class Iter>
	bool operator!=(const reverse_iterator<Iter> &a,
		const reverse_iterator<Iter> &b)
	{
		return a.current != b.current;
	}

	template <class Iter>
	bool operator<(const reverse_iterator<Iter> &a,
		const reverse_iterator<Iter> &b)
	{
		return a.current < b.current;
	}

	template <class Iter>
	bool operator<=(const reverse_iterator<Iter> &a,
		const reverse_iterator<Iter> &b)
	{
		return a.current <= b.current;
	}

	template <class Iter>
	bool operator>(const reverse_iterator<Iter> &a,
		const reverse_iterator<Iter> &b)
	{
		return a.current > b.current;
	}

	template <class Iter>
	bool operator>=(const reverse_iterator<Iter> &a,
		const reverse_iterator<Iter> &b)
	{
		return a.current >= b.current;
	}

	template< class Iter >
	reverse_iterator<Iter> operator+(typename reverse_iterator<Iter>::difference_type n,
		const reverse_iterator<Iter>& it)
	{
		return (reverse_iterator<Iter>(it.base() - n));
	}

	template< class Iterator >
	typename reverse_iterator<Iterator>::difference_type
	operator-(const reverse_iterator<Iterator>& lhs,
		const reverse_iterator<Iterator>& rhs)
	{
		return (rhs.base() - lhs.base());
	}
}

#endif