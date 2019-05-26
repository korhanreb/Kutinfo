#include <iostream>
#include <cmath>

template<typename T> struct Matrix2;

template<typename T,bool isRow>
struct Vector2d
{
	T x, y;

	Vector2d<T, true>& operator*=( Matrix2<T> const& m);  //baj van

	template<typename T2>
	Vector2d<T, isRow>& operator+=( Vector2d<T2, isRow> const& v )
	{
		x = static_cast<T>(x + v.x);;
		y = static_cast<T>(y + v.y);
		return *this;
	}

	template<typename T2>
    Vector2d<T, isRow>& operator-=( Vector2d<T2, isRow> const& v )
	{
		x = static_cast<T>(x - v.x);
		y = static_cast<T>(y - v.y);
		return *this;
	}

	template<typename T3>
    Vector2d& operator*=(T3 const& a)
	{
		x = static_cast<T>(a*x);
		y = static_cast<T>(a*y);
		return *this;
	}

	template<typename T3>
	Vector2d& operator/=(T3 const& a)
	{
		x = static_cast<T>(x/a);
		y = static_cast<T>(y/a);
		return *this;
	}
};

template<typename T, typename T2, bool b>
auto operator+( Vector2d<T, b> const& v, Vector2d<T2, b> const& u )
{
	using T3 = decltype(v.x+u.x);
	return Vector2d<T3,b>{ v.x + u.x, v.y + u.y };
}

template<typename T, typename T2, bool b>
auto operator-( Vector2d<T, b> const& v, Vector2d<T2, b> const& u )
{
	using T3 = decltype(v.x-u.x);
	return Vector2d<T3,b>{ v.x - u.x, v.y - u.y };
}


template<typename T, typename T3, bool b>
auto operator*(T3 const& a , Vector2d<T, b> const& v)
{
	using T4 = decltype(a*v.x);
	return Vector2d<T4,b>{ a*v.x , a*v.y};
}

template<typename T, typename T3, bool b>
auto operator*(Vector2d<T, b> const& v, T3 const& a )
{
	using T4 = decltype(v.x*a);
	return Vector2d<T4,b>{ v.x*a , v.y*a};
}

template<typename T, typename T3, bool b>
auto operator/(Vector2d<T, b> const& v, T3 const& a )
{
	using T4 = decltype(v.x/a);
	return Vector2d<T4, b> { v.x/a , v.y/a };
}

template<typename T, bool b>
auto transp_vector(Vector2d<T, b> const& v)
{
	return  Vector2d<T, !b> { v.x , v.y};;
}


template<typename T, bool b>
auto sqlength(Vector2d<T, b> const& v)
{
	return v.x*v.x+v.y*v.y;
}

template<typename T, bool b>
auto length(Vector2d<T, b> const& v)
{
	return std::sqrt(v.x*v.x+v.y*v.y);
}

template<typename T, bool b>
auto normalize(Vector2d<T, b> const& v)
{
	return v/ length(v);
}


template<typename T, bool b>
std::ostream& operator<<(std::ostream& o, Vector2d<T, b> const& v)
{
    o << '[' << v.x << ',' << v.y << ']';
    return o; 
}

template<typename T, bool b>
std::istream& operator>>(std::istream& i, Vector2d<T, b>& v)
{
    i >> v.x;
    i >> v.y;
    return i; 
}
