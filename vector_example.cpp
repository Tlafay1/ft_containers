#include <iostream>

namespace nonstd
{

	template<typename T>
	class vector
	{
		public:
			using	iterator = T * ;
			using	const_iterator = const T*;

			vector();
			explicit vector(const std::size_t count);
			vector(const std::size_t count, const T& val);
			vector(const vector& other);
			vector(vector&& other);
			~vector();

			vector&	operator=(const vector& other);
			vector&	operator=(vector&& other);

			std::size_t	size() const;
			std::size_t	capacity() const;

			void	push_back(const T& val);
			void	push_back(T&& val);
			void	pop_back();

			T& 			front();
			T& 			back();
			T& 			operator[](const std::size_t pos);
			const T&	front() const;
			const T&	back() const;
			const T&	operator[](const std::size_t pos) const;

			iterator		begin();
			const_iterator	begin() const;
			iterator		end();
			const_iterator	end() const;
		
		private:
			T			*buffer;
			iterator	m_first;
			iterator	m_last;
			iterator	m_end;

			void	realloc(const std::size_t factor, const std::size_t carry);
			void	alloc(const std::size_t cap);
	};

	template<typename T>
	vector<T>::vector() : buffer(new T[10]), m_first(buffer), m_last(buffer), m_end(buffer + 10)
	{

	}

	template<typename T>
	vector<T>::vector(const std::size_t count) : buffer(new T[count]), m_first(buffer), m_last(buffer + count), m_end(buffer + count)
	{

	}

	template<typename T>
	vector<T>::vector(const std::size_t count, const T& val) : buffer(new T[count]), m_first(buffer), m_last(buffer + count), m_end(buffer + count)
	{
		while (count--)
		{
			buffer[count] = val;
		}
	}

	template<typename T>
	vector<T>::vector(const vector& other) : buffer(new T[other.capacity()]), m_first(buffer), m_last(buffer + other.size()), m_end(buffer + other.capacity())
	{
		for (std::size_t i = 0; i < size(); ++i)
		{
			buffer[i] = other[i];
		}
	}

	template<typename T>
	vector<T>::vector(vector&& other) : buffer(other.buffer), m_first(other.m_first), m_last(other.m_last), m_end(other.m_end)
	{
		other.buffer = nullptr;
		other.m_first = other.m_last = other.m_end = nullptr;
	}

	template<typename T>
	vector<T>::~vector()
	{
		if (buffer != nullptr)
		{
			m_first = m_last = m_end = nullptr;
			delete[] buffer;
		}
	}

	template<typename T>
	vector<T>& vector<T>::operator=(const vector<T>& other)
	{
		if (this == &other)
		{
			return *this;
		}
		this->~vector();
		buffer = new T[other.capacity()];
		m_first = buffer;
		m_last = buffer + other.size();
		m_end = buffer + other.capacity();
		for (std::size_t i = 0; i < size(); ++i)
		{
			buffer[i] = other[i];
		}
		return *this;
	}

	template<typename T>
	vector<T>& vector<T>::operator=(vector<T>&& other)
	{
		if (this == &other)
		{
			return *this;
		}
		this->~vector();

		buffer = other.buffer;
		m_first = other.m_first;
		m_last = other.m_last;
		m_end = other.m_end;

		other.buffer = nullptr;
		other.m_first = other.m_last = other.m_end = nullptr;
		return *this;
	}

	template<typename T>
	std::size_t	vector<T>::size() const
	{
		return static_cast<std::size_t>(m_last - m_first);
	}

	template<typename T>
	std::size_t	vector<T>::capacity() const
	{
		return static_cast<std::size_t>(m_end - m_first);
	}

	template<typename T>
	void	vector<T>::push_back(const T& val)
	{
		if (size() < capacity())
		{
			*(m_last++) = val;
			return;
		}
		realloc(2, 2);
		*(m_last++) = val;
	}

	template<typename T>
	void	vector<T>::push_back(T&& val)
	{
		if (size() < capacity())
		{
			*(m_last++) = std::move(val);
			return;
		}
		realloc(2, 2);
		*(m_last++) = std::move(val);
	}

	template<typename T>
	void	vector<T>::pop_back()
	{
		if (size() == 0)
		{
			throw std::exception("vector is empty");
		}
		(--m_last)->~T();
	}

	template<typename T>
	T&	vector<T>::front()
	{
		if (size() == 0)
		{
			throw std::exception("front(): vector is empty");
		}
		return *begin();
	}

	template<typename T>
	const T&	vector<T>::front() const
	{
		if (size() == 0)
		{
			throw std::exception("front(): vector is empty");
		}
		return *begin();
	}

	template<typename T>
	T&	vector<T>::back()
	{
		if (size() == 0)
		{
			throw std::exception("back(): vector is empty");
		}
		return *(end() - 1);
	}

	template<typename T>
	const T&	vector<T>::back() const
	{
		if (size() == 0)
		{
			throw std::exception("back(): vector is empty");
		}
		return *(end() - 1);
	}

	template<typename T>
	T&	vector<T>::operator[](const std::size_t pos)
	{
		if (pos >= size())
		{
			throw std::exception("index out of range");
		}
		return buffer[pos];
	}

	template<typename T>
	const T&	vector<T>::operator[](const std::size_t pos) const
	{
		if (pos >= size())
		{
			throw std::exception("index out of range");
		}
		return buffer[pos];
	}

	template<typename T>
	typename vector<T>::iterator	vector<T>::begin()
	{
		return m_first;
	}

	template<typename T>
	typename vector<T>::iterator	vector<T>::end()
	{
		return m_last;
	}

	template<typename T>
	typename vector<T>::const_iterator	vector<T>::begin() const
	{
		return m_first;
	}

	template<typename T>
	typename vector<T>::const_iterator	vector<T>::end() const
	{
		return m_last;
	}

	template<typename T>
	void	vector<T>::realloc(const std::size_t factor, const std::size_t carry)
	{
		alloc(capacity() * factor + carry);
	}

	template<typename T>
	void	vector<T>::alloc(const std::size_t cap)
	{
		T* new_buffer = new T[cap];
		std::size_t sz = size();
		for (std::size_t i = 0; i < sz; ++i)
		{
			new_buffer[i] = buffer[i];
		}
		this->~vector();
		buffer = new_buffer;
		m_first = buffer;
		m_last = buffer + sz;
		m_end = buffer + cap;
	}
}