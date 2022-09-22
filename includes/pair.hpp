#ifndef PAIR_HPP
# define PAIR_HPP

namespace ft
{
	template <class T1, class T2>
	struct pair
	{
		typedef T1 first_type;
		typedef T2 second_type;

		pair(): first(T1()), second(T2()) {}
		pair(const T1 &x, const T2 &y): first(x), second(y) {}
		template<class U1, class U2>
		pair(const pair<U1, U2> &p) { *this = p; }

		pair	&operator=(const pair &other)
		{
			first = other.first;
			second = other.second;
			return (*this);
		}

		first_type	first;
		second_type	second;
	};
}

template< class T1, class T2 >
std::pair<T1, T2> make_pair(T1 t, T2 u);

#endif