namespace ft
{
	template <class T, T v>
	struct integral_constant
	{
		static const T value = v;
		typedef T value_type;
		typedef integral_constant<T,v> type;
	};

	template <class T> struct is_integral :							public integral_constant<bool, false>{};

	template<> struct is_integral <unsigned char>:					public integral_constant<bool, true>{};
	template<> struct is_integral <unsigned short>:					public integral_constant<bool, true>{};
	template<> struct is_integral <unsigned int>:					public integral_constant<bool, true>{};
	template<> struct is_integral <unsigned long>:					public integral_constant<bool, true>{};
	template<> struct is_integral <signed char>:					public integral_constant<bool, true>{};
	template<> struct is_integral <short>: 							public integral_constant<bool, true>{};
	template<> struct is_integral <int>:							public integral_constant<bool, true>{};
	template<> struct is_integral <long long int>:					public integral_constant<bool, true>{};
	template<> struct is_integral <unsigned long long int>:			public integral_constant<bool, true>{};
	template<> struct is_integral <long>:							public integral_constant<bool, true>{};
	template<> struct is_integral <char>:							public integral_constant<bool, true>{};
	template<> struct is_integral <bool>:							public integral_constant<bool, true>{};
	template<> struct is_integral <wchar_t>:						public integral_constant<bool, true>{};
	template<> struct is_integral <char16_t>:						public integral_constant<bool, true>{};
	template<> struct is_integral <char32_t>:						public integral_constant<bool, true>{};
	template<> struct is_integral <const unsigned char>:			public integral_constant<bool, true>{};
	template<> struct is_integral <const unsigned short>:			public integral_constant<bool, true>{};
	template<> struct is_integral <const unsigned int>:				public integral_constant<bool, true>{};
	template<> struct is_integral <const unsigned long>:			public integral_constant<bool, true>{};
	template<> struct is_integral <const signed char>:				public integral_constant<bool, true>{};
	template<> struct is_integral <const short>: 					public integral_constant<bool, true>{};
	template<> struct is_integral <const int>:						public integral_constant<bool, true>{};
	template<> struct is_integral <const long long int>:			public integral_constant<bool, true>{};
	template<> struct is_integral <const unsigned long long int>:	public integral_constant<bool, true>{};
	template<> struct is_integral <const long>:						public integral_constant<bool, true>{};
	template<> struct is_integral <const char>:						public integral_constant<bool, true>{};
	template<> struct is_integral <const bool>:						public integral_constant<bool, true>{};
	template<> struct is_integral <const wchar_t>:					public integral_constant<bool, true>{};
	template<> struct is_integral <const char16_t>:					public integral_constant<bool, true>{};
	template<> struct is_integral <const char32_t>:					public integral_constant<bool, true>{};
}

// bool
// signed char
// short int
// int
// long int
// long long int
// unsigned char
// unsigned short int
// unsigned int
// unsigned long int
// unsigned long long int