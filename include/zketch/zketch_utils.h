#pragma once 

namespace zketch_type_utils {
template <typename T, typename U> struct is_same {
	static constexpr bool state = false ;
} ;

template <typename T> struct is_same<T, T> {
	static constexpr bool state = true ;
} ;

template <typename T, typename U> constexpr bool is_same_v = is_same<T, U>::state ;

// ztype traits
template <typename T> struct is_integral {
	static constexpr bool state = false ;
} ;

template <> struct is_integral<char> {
	static constexpr bool state = true ;
} ;

template <> struct is_integral<unsigned char> {
	static constexpr bool state = true ;
} ;

template <> struct is_integral<unsigned short> {
	static constexpr bool state = true ;
} ;

template <> struct is_integral<unsigned> {
	static constexpr bool state = true ;
} ;

template <> struct is_integral<unsigned long> {
	static constexpr bool state = true ;
} ;

template <> struct is_integral<unsigned long long> {
	static constexpr bool state = true ;
} ;

template <> struct is_integral<signed char> {
	static constexpr bool state = true ;
} ;

template <> struct is_integral<signed short> {
	static constexpr bool state = true ;
} ;

template <> struct is_integral<signed> {
	static constexpr bool state = true ;
} ;

template <> struct is_integral<signed long> {
	static constexpr bool state = true ;
} ;

template <> struct is_integral<signed long long> {
	static constexpr bool state = true ;
} ;

template <typename T> constexpr bool is_integral_v = is_integral<T>::state ;

template <typename T> struct is_floating_point {
	static constexpr bool state = false ;
} ;

template <> struct is_floating_point<float> {
	static constexpr bool state = true ;
} ;

template <> struct is_floating_point<double> {
	static constexpr bool state = true ;
} ;

template <> struct is_floating_point<long double> {
	static constexpr bool state = true ;
} ;

template <typename T> constexpr bool is_floating_point_v = is_floating_point<T>::state ;

template <bool Cond, typename ... Ts> struct allowed_type ;

template <typename ... Ts> struct allowed_type<true, Ts...> {
	static constexpr bool state = true ;
} ;

template <typename ... Ts> struct allowed_type<false, Ts...> {
	static constexpr bool state = false ;
} ;

template <bool Cond, typename ... Ts> constexpr bool allowed_type_v = allowed_type<Cond, Ts...>::state ;

}