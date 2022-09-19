#include "stack.hpp"

namespace ft
{
	template <class T, class Container>
	stack<T, Container>::stack(const Container &cont): c(Container(cont)) {}

	template <class T, class Container>
	stack<T, Container>::stack(const stack &other)
	{
		*this = other;
	}

	template <class T, class Container>
	stack<T, Container>	&stack<T, Container>::operator=(const stack &other)
	{
		this->c = Container(other.c);
		return (*this);
	}

	template <class T, class Container>
	typename stack<T, Container>::reference	stack<T, Container>::top()
	{
		return (c.back());
	}

	template <class T, class Container>
	typename stack<T, Container>::const_reference	stack<T, Container>::top() const
	{
		return (c.back());
	}

	template <class T, class Container>
	bool	stack<T, Container>::empty() const
	{
		return (c.empty());
	}

	template <class T, class Container>
	typename stack<T, Container>::size_type	stack<T, Container>::size() const
	{
		return (c.size());
	}

	template <class T, class Container>
	void	stack<T, Container>::push(const value_type &value)
	{
		c.push_back(value);
	}

	template <class T, class Container>
	void	stack<T, Container>::pop()
	{
		c.pop_back();
	}

}