#pragma once
#include "SDL3/SDL_Rect.h"
#include "zketch/zketch_utils.h"

using Vec2 = SDL_Point ;
using Vec2f = SDL_FPoint ;
using Box = SDL_Rect ;
using Boxf = SDL_FRect ;

// Template specialized for control

template <typename T> struct Unit {
	static_assert(expression, );
} ;

// Exception
struct zero_division {
	const char* what() {
		return "[Err] Can't divide by zero!" ;
	} ;
} ;

struct invalid_operation_type {
	const char* what() {
		return "[Err] Mismatch operation type!" ;
	} ;
} ;

// Operator
template <typename T, typename U> auto operator+(const T& a, const U& b) noexcept {
	static_assert((is_Vec2_v<T> && is_Vec2_v<U>) || (is_Box_v<T> && is_Box_v<U>), "Mismatch operation type!") ;
	if() {
		
	}
}