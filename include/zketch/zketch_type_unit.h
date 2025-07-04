#pragma once
#include <type_traits>

struct Vec {
	int x, y ;
} ;

struct Vecf {
	float x, y ;
} ;

struct Rect {
	int x, y, w, h ;
} ;

struct Rectf {
	int x, y, w, h ;
} ;

/**
 * @brief tipe objek untuk pengecualian ketika kondisinya dibagi 0
 * 
 */
struct zero_division {
	const char* what() {
		return "Invalid operation, can't divide by zero!" ;
	}
} ;

/**
 * @brief default spesialisasi templat dari `is_vec_variant`
 * 
 * @tparam T 
 */
template <typename T> struct is_vec_variant {
	static constexpr bool state = false ;
} ;

/**
 * @brief spesialisasi templat dari `is_vec_variant` yang di gunakan untuk menangani tipe `Vec`
 * 
 * @tparam Vec
 */
template <> struct is_vec_variant<Vec> {
	static constexpr bool state = true ;
} ;

/**
 * @brief spesialisasi templat dari `is_vec_variant` yang di gunakan untuk menangani tipe `Vecf`
 * 
 * @tparam Vecf
 */
template <> struct is_vec_variant<Vecf> {
	static constexpr bool state = true ;
} ;

/**
 * @brief mempersingkat penulisan `is_vec_variant::state` menjadi `is_vec_variant_v`
 * 
 * @tparam T 
 */
template <typename T> constexpr bool is_vec_variant_v = is_vec_variant<T>::state ;

/**
 * @brief default spesialisasi templat dari `is_rect_variant`
 * 
 * @tparam T 
 */
template <typename T> struct is_rect_variant {
	static constexpr bool state = false ;
} ;

/**
 * @brief spesialisasi templat dari `is_rect_variant` yang di gunakan untuk menangani tipe `Rect`
 * 
 * @tparam Rect
 */
template <> struct is_rect_variant<Rect> {
	static constexpr bool state = true ;
} ;

/**
 * @brief spesialisasi templat dari `is_rect_variant` yang di gunakan untuk menangani tipe Rectf
 * 
 * @tparam Rectf 
 */
template <> struct is_rect_variant<Rectf> {
	static constexpr bool state = true ;
} ;

/**
 * @brief mempersingkat penulisan `is_rect_variant::state` menjadi `is_rect_variant_v`
 * 
 * @tparam T 
 */
template <typename T> constexpr bool is_rect_variant_v = is_rect_variant<T>::state ;

/**
 * @brief default spesialisasi templat dari `is_integral_variant`
 * 
 * @tparam T 
 */
template <typename T> struct is_integral_variant {
	static constexpr bool state = false ;
} ;

/**
 * @brief spesialisasi templat dari `is_integral_variant` yang di gunakan untuk menangani tipe `Vec`
 * 
 * @tparam Vec
 */
template <> struct is_integral_variant<Vec> {
	static constexpr bool state = true ;
} ;

/**
 * @brief spesialisasi templat dari `is_integral_variant` yang di gunakan untuk menangani tipe `Rect`
 * 
 * @tparam Rect
 */
template <> struct is_integral_variant<Rect> {
	static constexpr bool state = true ;
} ;

/**
 * @brief mempersingkat penulisan `is_integral_variant::state` menjadi `is_integral_variant_v`
 * 
 * @tparam T 
 */
template <typename T> constexpr bool is_integral_variant_v = is_integral_variant<T>::state ;

/**
 * @brief default spesialisasi templat dari `is_floating_variant`
 * 
 * @tparam T 
 */
template <typename T> struct is_floating_variant {
	static constexpr bool state = false ;
} ;

/**
 * @brief spesialisasi templat dari `is_floating_variant` yang di gunakan untuk menangani tipe `Vecf`
 * 
 * @tparam Vecf
 */
template <> struct is_floating_variant<Vecf> {
	static constexpr bool state = true ;
} ;

/**
 * @brief spesialisasi templat dari `is_floating_variant` yang di gunakan untuk menangani tipe Rectf
 * 
 * @tparam Rectf 
 */
template <> struct is_floating_variant<Rectf> {
	static constexpr bool state = true ;
} ;

/**
 * @brief mempersingkat penulisan `is_floating_variant::state` menjadi `is_floating_variant_v`
 * 
 * @tparam T 
 */
template <typename T> constexpr bool is_floating_variant_v = is_floating_variant<T>::state ;

/**
 * @brief shortcut templat yang digunakan untuk mengecek apakah ini unit type
 * 
 * @tparam T 
 */
template <typename T> constexpr bool is_unit_variant_v = is_vec_variant_v<T> || is_rect_variant_v<T> ;

/**
 * @brief deklarasi dari tipe opsional yang menyesuaikan dengan pernyataan `true` or `false`
 * 
 * @tparam Cond 
 * @tparam if_true 
 * @tparam if_false 
 */
template <bool Cond, typename if_true = void, typename if_false = void> struct optional_unit_type ;

/**
 * @brief tipe opsional yang digunakan untuk menangani jika pernyataan `true`
 * 
 * @tparam if_true 
 * @tparam if_false 
 */
template <typename if_true, typename if_false> struct optional_unit_type<true, if_true, if_false> {
	using type = if_true ;
} ;

/**
 * @brief tipe opsional yang digunakan untuk menangani jika pernyataan `false`
 * 
 * @tparam if_true 
 * @tparam if_false 
 */
template <typename if_true, typename if_false> struct optional_unit_type<false, if_true, if_false> {
	using type = if_false ;
} ;

/**
 * @brief shortcut templat yang digunakan untuk memakai tipe berdasarkan kondisi
 * 
 * @tparam Cond 
 * @tparam if_true 
 * @tparam if_false 
 */
template <bool Cond, typename if_true, typename if_false> using optional_unit_type_t = typename optional_unit_type<Cond, if_true, if_false>::type ;

/**
 * @brief spesialisasi templat yang digunakan untuk membungkus unit yang akan di operasikan
 * 
 * @tparam T 
 * @tparam U 
 */
template <typename T, typename U> struct op_unit_wrapper {
	static_assert(
		(is_vec_variant_v<T> && is_vec_variant_v<U>) ||
		(is_rect_variant_v<T> && is_rect_variant_v<U>)
		, "kedua tipe tidak valid!"
	) ;

/**
 * @brief functor yang digunakan sebagai template data kedua unit, dan fungsi operasi
 * 
 * @tparam Op 
 * @param a 
 * @param b 
 * @param op 
 * @return auto 
 */
	template <typename Op> constexpr auto operator()(const T& a, const U& b, Op op) {
		using FieldType = decltype(op(a.x, b.x)) ;
		if constexpr (is_vec_variant_v<T> && is_vec_variant_v<U>) {
			using RetType = optional_unit_type_t<is_floating_variant_v<T> || is_floating_variant_v<U>, Vecf, Vec> ;
			if constexpr (std::is_same_v<FieldType, bool>)
				return op(a.x, b.x) && op(a.y, b.y) ;
			return RetType{op(a.x, b.x), op(a.y, b.y)} ;
		}
		using RetType = optional_unit_type_t<is_floating_variant_v<T> || is_floating_variant_v<U>, Rectf, Rect> ;
		if constexpr (std::is_same_v<FieldType, bool>)
			return op(a.x, b.x) && op(a.y, b.y) && op(a.w, b.w) && op(a.h, b.h) ;
		return RetType{op(a.x, b.x), op(a.y, b.y), op(a.w, b.w), op(a.h, b.h) } ;
	}
} ;

/**
 * @brief fungsi operator yang digunakan untuk mengoperasikan kedua tipe unit
 * 
 * @tparam T 
 * @tparam U 
 * @param a 
 * @param b 
 * @return auto 
 */
template <typename T, typename U> auto operator+(const T& a, const U& b) {
	return op_unit_wrapper<T, U>{}(a, b, [](auto a, auto b){ return a + b ; }) ;
}

/**
 * @brief fungsi operator yang digunakan untuk mengoperasikan kedua tipe unit
 * 
 * @tparam T 
 * @tparam U 
 * @param a 
 * @param b 
 * @return auto 
 */
template <typename T, typename U> auto operator-(const T& a, const U& b) {
	return op_unit_wrapper<T, U>{}(a, b, [](auto a, auto b){ return a - b ; }) ;
}

/**
 * @brief fungsi operator yang digunakan untuk mengoperasikan kedua tipe unit
 * 
 * @tparam T 
 * @tparam U 
 * @param a 
 * @param b 
 * @return auto 
 */
template <typename T, typename U> auto operator*(const T& a, const U& b) {
	return op_unit_wrapper<T, U>{}(a, b, [](auto a, auto b){ return a * b ; }) ;
}

/**
 * @brief fungsi operator yang digunakan untuk mengoperasikan kedua tipe unit
 * 
 * @tparam T 
 * @tparam U 
 * @param a 
 * @param b 
 * @return auto 
 */
template <typename T, typename U> auto operator/(const T& a, const U& b) {
	if(b == 0) throw zero_division() ;
	return op_unit_wrapper<T, U>{}(a, b, [](auto a, auto b){ return a / b ; }) ;
}

/**
 * @brief fungsi operator yang digunakan untuk mengoperasikan kedua tipe unit
 * 
 * @tparam T 
 * @tparam U 
 * @param a 
 * @param b 
 * @return bool 
 */
template <typename T, typename U> bool operator==(const T& a, const U& b) {
	return op_unit_wrapper<T, U>{}(a, b, [](auto a, auto b){ return a == b ; }) ;
}

/**
 * @brief fungsi operator yang digunakan untuk mengoperasikan kedua tipe unit
 * 
 * @tparam T 
 * @tparam U 
 * @param a 
 * @param b 
 * @return bool 
 */
template <typename T, typename U> bool operator!=(const T& a, const U& b) {
	return !(a == b) ;
}

/**
 * @brief fungsi yang digunakan untuk mendapatkan data unit dengan value yang sama semua di setiap unit field
 * 
 * @tparam T 
 * @tparam V 
 * @param v 
 * @return T 
 */
template <typename T, typename V> T fill_unit(const V& v) {
	static_assert(is_vec_variant_v<T> || is_rect_variant_v<T>, "T must be a Vec/Vecf or Rect/Rectf");
	using FieldType = optional_unit_type_t<is_floating_variant_v<T>, float, int> ;
	FieldType val = static_cast<FieldType>(v);
	if constexpr (is_vec_variant_v<T>) 
		return T{val, val} ;
	return T{val, val, val, val} ;
} ;