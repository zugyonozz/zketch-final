#pragma once
#include <type_traits>

struct Color {
	unsigned char r, g, b, a ;
} ;

struct Colorf {
	float r, g, b, a ;
} ;

template <typename T> struct is_color {
	static constexpr bool state = false ;
} ;

template <> struct is_color<Color> {
	static constexpr bool state = true ;
} ;

template <> struct is_color<Colorf> {
	static constexpr bool state = true ;
} ;

template <typename T> constexpr bool is_color_v = is_color<T>::state ;

constexpr bool is_valid_range_hex_color(char c) noexcept {
	return (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f') || (c >= '0' && c <= '9') ;
}

constexpr unsigned char char_to_Uint8(char c) noexcept {
	if(!is_valid_range_hex_color(c))
		return 0 ;
	if(c >= 'A' && c <= 'F') return 
		static_cast<unsigned char>((c - 'A') + 10) ;
	if(c >= 'a' && c <= 'f') return 
		static_cast<unsigned char>((c - 'a') + 10) ;
	return static_cast<unsigned char>(c - '0') ;
}

constexpr float char_to_float(char c) noexcept {
	if(!is_valid_range_hex_color(c))
		return 0.0f ;
	if(c >= 'A' && c <= 'F') 
		return static_cast<float>((c - 'A') + 10) / 255.0f ;
	if(c >= 'a' && c <= 'f') 
		return static_cast<float>((c - 'a') + 10) / 255.0f ;
	return static_cast<float>(c - '0') / 255.0f ;
}

template <typename T> T make_color(const char hexcode[8]) {
	static_assert(is_color_v<T>, "Hanya support tipa Color, & Colorf!") ;
	if constexpr (std::is_same_v<T, Color>)
		for(auto it = hexcode; it != (hexcode + 8); it++)
			
}