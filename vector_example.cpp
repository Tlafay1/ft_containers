#include <iostream>
#include <stdexcept>

template<class T> class WVector {
public:

	typedef T value_type;
	typedef T* iterator;
	typedef const T* const_iterator;

	size_t size() const;

	T& operator[] (size_t index);
	const T& operator[] (size_t index) const;

	T& at(size_t index);
	const T& at(size_t index) const;

	void push_back(const T& element);

	void resize(size_t new_size);
	void resize(size_t new_size, const value_type& val);
	void reserve(size_t n);

	iterator begin();
	const_iterator begin() const;
	iterator end();
	const_iterator end() const;

	WVector();
	WVector(size_t n);
	WVector(size_t n, const value_type& val);
	WVector(const WVector& x);
	WVector(WVector&& x);

	~WVector();

    //This form of the function provides both copy- and move-assignment
    //https://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom
    //http://en.cppreference.com/w/cpp/language/operators#Assignment_operator
	WVector& operator= (WVector x);

    //see https://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom
    //and https://stackoverflow.com/questions/5695548/public-friend-swap-member-function
	friend void swap(WVector& first, WVector& second) {
		using std::swap;

		swap(first.size_, second.size_);
		swap(first.capacity_, second.capacity_);
		swap(first.data_, second.data_);
	}

private:
	size_t size_;
	size_t capacity_;
	T* data_;
	std::allocator<T> alloc_;

	void resize_smaller(size_t new_size);
	void expand_capacity(size_t new_size);
};

template<class T>
size_t WVector<T>::size() const {
	return size_;
}

template<class T>
T& WVector<T>::operator[] (size_t index) {
	return data_[index];
}

template<class T>
const T& WVector<T>::operator[] (size_t index) const {
	return data_[index];
}

template<class T>
T& WVector<T>::at(size_t index) {
	if (index >= size_) throw std::out_of_range("index too big");
	return data_[index];
}

template<class T>
const T& WVector<T>::at(size_t index) const {
	if (index >= size_) throw std::out_of_range("index too big");
	return data_[index];
}

template<class T>
void WVector<T>::push_back(const T& element) {
	resize(size_+1,element);
}

template<class T>
void WVector<T>::resize_smaller(size_t new_size) {
	for (iterator it = data_ + new_size; it != data_ + size_; ++it) {
		alloc_.destroy(it);
	}
	size_ = new_size;
}

template<class T>
void WVector<T>::expand_capacity(size_t new_size) {
	size_t new_capacity;
	if (capacity_ == 0) {
		new_capacity = 1;
	} else if (capacity_ < SIZE_MAX/2) {
		new_capacity = capacity_*2;
	} else {
		new_capacity = SIZE_MAX;
	}

	if (new_size > new_capacity) new_capacity = new_size;

	reserve(new_capacity);
}

template<class T>
void WVector<T>::resize(size_t new_size) {
	if (size_ == new_size) return;
	if (new_size < size_) {
		resize_smaller(new_size);
		return;
	}
	if (new_size > capacity_) {
		expand_capacity(new_size);
	}

	for (iterator it = data_ + size_; it != data_ + new_size; ++it) {
		alloc_.construct(it);
	}
	size_ = new_size;
}

template<class T>
void WVector<T>::resize(size_t new_size, const value_type& val) {
	if (size_ == new_size) return;
	if (new_size < size_) {
		resize_smaller(new_size);
		return;
	}
	if (new_size > capacity_) {
		expand_capacity(new_size);
	}

	for (iterator it = data_ + size_; it != data_ + new_size; ++it) {
		alloc_.construct(it,val);
	}
	size_ = new_size;
}

template<class T>
void WVector<T>::reserve(size_t n) {
	if (n <= capacity_) {
		return;
	}

	T* old_data = data_;
	size_t old_capacity = capacity_;

	data_ = alloc_.allocate(n);
	capacity_ = n;
	for (size_t i=0; i<size_; i++) {
		alloc_.construct(data_ + i, old_data[i]);
	}

	for (size_t i=0; i<size_; i++) {
		alloc_.destroy(old_data + i);
	}
	alloc_.deallocate(old_data,old_capacity);
}

template<class T>
typename WVector<T>::iterator WVector<T>::begin() {
	return &data_[0];
}

template<class T>
typename WVector<T>::const_iterator WVector<T>::begin() const {
	return &data_[0];
}

template<class T>
typename WVector<T>::iterator WVector<T>::end() {
	return &data_[size_];
}

template<class T>
typename WVector<T>::const_iterator WVector<T>::end() const {
	return &data_[size_];
}

template<class T>
WVector<T>::WVector() {
	size_ = 0;
	capacity_ = 0;
	data_ = nullptr;
}

template<class T>
WVector<T>::WVector(size_t n) {
	size_ = n;
	capacity_ = n;
	data_ = alloc_.allocate(capacity_);
	for (iterator it = data_; it != data_ + size_; ++it) {
		alloc_.construct(it);
	}
}

template<class T>
WVector<T>::WVector(size_t n, const value_type& val) {
	size_ = n;
	capacity_ = n;
	data_ = alloc_.allocate(capacity_);
	for (iterator it = data_; it != data_ + size_; ++it) {
		alloc_.construct(it, val);
	}
}

template<class T>
WVector<T>::WVector(const WVector& x) {
	size_ = x.size_;
	capacity_ = x.capacity_;
	data_ = alloc_.allocate(capacity_);
	for (size_t i=0; i<size_; i++) {
		alloc_.construct(data_ + i, x.data_[i]);
	}
}

template<class T>
WVector<T>::WVector(WVector&& x)
   : WVector() //initialize this via default constructor
   {
  swap(*this,x); //then swap the empty vector with the vector to be moved
}

template<class T>
WVector<T>::~WVector() {
	for (iterator it = data_; it != data_ + size_; ++it) {
		alloc_.destroy(it);
	}
	alloc_.deallocate(data_,capacity_);
}


template<class T>
WVector<T>& WVector<T>::operator=(WVector<T> x) { //x is constructed by either the copy or move constructor as appropriate
	swap(*this, x);
	return *this;
} //destructor of x is called, free resources originally held by *this


template<typename T>
std::ostream& operator<< (std::ostream& out, const WVector<T>& vec) {
	for (const auto &iter : vec) {
		out << iter << ",";
	}
	return out;
}