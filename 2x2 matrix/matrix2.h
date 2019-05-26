#include "vector2.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <initializer_list>
#include <cmath>
#include <ostream>

template<typename T>
struct Matrix2
{
	T x1, x2, x3, x4;

	template<typename T2>
	Matrix2<T>& operator+=( Matrix2<T2> const& m )
	{
		x1 = static_cast<T>(x1 + m.x1);
		x2 = static_cast<T>(x2 + m.x2);
		x3 = static_cast<T>(x3 + m.x3);
		x4 = static_cast<T>(x4 + m.x4);
		return *this;
	}

	template<typename T2>
    Matrix2<T>& operator-=( Matrix2<T2> const& m )
	{
		x1 = static_cast<T>(x1 - m.x1);
		x2 = static_cast<T>(x2 - m.x2);
		x3 = static_cast<T>(x3 - m.x3);
		x4 = static_cast<T>(x4 - m.x4);
		return *this;
	}

	template<typename T3>
    Matrix2& operator*=(T3 const& a)
	{
		x1 = static_cast<T>(a*x1);
		x2 = static_cast<T>(a*x2);
		x3 = static_cast<T>(a*x3);
		x4 = static_cast<T>(a*x4);
		return *this;
	}

	template<typename T3>
	Matrix2& operator/=(T3 const& a)
	{
		x1 = static_cast<T>(x1/a);
		x2 = static_cast<T>(x2/a);
		x3 = static_cast<T>(x3/a);
		x4 = static_cast<T>(x4/a);
		return *this;
	}

	template<typename T2>
    Matrix2& operator*=(Matrix2<T2> const& m )
	{
		T X1 = x1 ;
		T X2 = x2 ;
		T X3 = x3 ;
		T X4 = x4 ;
		x1 = static_cast<T>(X1*m.x1+X2*m.x3);
		x2 = static_cast<T>(X1*m.x2+X2*m.x4);
		x3 = static_cast<T>(X3*m.x1+X4*m.x3);
		x4 = static_cast<T>(X3*m.x2+X4*m.x4);
		return *this;
	}

	template<typename T2>
    Matrix2& operator/=(Matrix2<T2> const& m )
	{
		T X1 = x1 ;
		T X2 = x2 ;
		T X3 = x3 ;
		T X4 = x4 ;
		auto det = determinant(m);
		x1 = static_cast<T>((X1*m.x4-X2*m.x3)/det);
		x2 = static_cast<T>((-X1*m.x2+X2*m.x1)/det);
		x3 = static_cast<T>((X3*m.x4-X4*m.x3)/det);
		x4 = static_cast<T>((-X3*m.x2+X4*m.x1)/det);
		return *this;
	}

	template<typename T2>
	auto determinant( Matrix2<T2> const& m)
	{	
		return (m.x1*m.x4-m.x2*m.x3);		
	}

		
};

template<typename T, bool isRow>   //baj van
Vector2d<T, true>& Vector2d<T, isRow>::operator*=( Matrix2<T> const& m)
{
    T X=x;
	T Y=y;
	x=m.x1*X + m.x3*Y;
	y=m.x2*X + m.x4*Y;
	return *this;
}


template <typename T>
auto multiplication_matrix(  Matrix2<T> const& m1, Matrix2<T> const& m2)
{
    Matrix2<T> m3;
	m3.x1 = static_cast<T>(m1.x1*m2.x1+m1.x2*m2.x3);
	m3.x2 = static_cast<T>(m1.x1*m2.x2+m1.x2*m2.x4);
	m3.x3 = static_cast<T>(m1.x3*m2.x1+m1.x4*m2.x3);
	m3.x4 = static_cast<T>(m1.x3*m2.x2+m1.x4*m2.x4);
    return m3;
}


template <typename T>
auto determinant( Matrix2<T> const& m)
{	
	return (m.x1*m.x4-m.x2*m.x3);		
}

template <typename T>
Matrix2<T>  adjoint( Matrix2<T> const& m)
{	
	return {m.x4, -m.x2, -m.x3, m.x1};		
}

template <typename T>
auto inv( Matrix2<T> const& m)
{
	return adjoint(m)/determinant(m);
}

// mátrix transzponált

template <typename T>
Matrix2<T>  transp_matrix( Matrix2<T> const& m)
{	
	return {m.x1, m.x3, m.x2, m.x4};		
}






// nem beépített műveletek

template<typename T, typename T2>
auto operator+( Matrix2<T> const& m1, Matrix2<T2> const& m2 )
{
	using T3 = decltype(m1.x1+m2.x1);
	return Matrix2<T3>{ m1.x1+m2.x1, m1.x2+m2.x2, m1.x3+m2.x3, m1.x4+m2.x4};
}

template<typename T, typename T2>
auto operator-( Matrix2<T> const& m1, Matrix2<T2> const& m2 )
{
	using T3 = decltype(m1.x1-m2.x1);
	return Matrix2<T3>{ m1.x1-m2.x1, m1.x2-m2.x2, m1.x3-m2.x3, m1.x4-m2.x4};
}


template<typename T, typename T3>
auto operator*(Matrix2<T> const& m, T3 const& a)
{
	using T4 = decltype(a*m.x1);
	return Matrix2<T4>{ a*m.x1 , a*m.x2, a*m.x3, a*m.x4};
}
template<typename T, typename T2>
auto operator*( Matrix2<T> const& m1, Matrix2<T2> const& m2 )
{
	return multiplication_matrix(m1, m2);
}

template<typename T, typename T2>
auto operator/( Matrix2<T> const& m1, Matrix2<T2> const& m2 )
{
	return m1*inv(m2);
}

template<typename T, typename T3>
auto operator/( T3 const& a, Matrix2<T> const& m )
{
	return a*inv(m);
}

template<typename T, typename T3>
auto operator*(T3 const& a , Matrix2<T> const& m)
{
	using T4 = decltype(a*m.x1);
	return Matrix2<T4>{ a*m.x1 , a*m.x2, a*m.x3, a*m.x4};
}

template<typename T, typename T3>
auto operator/(Matrix2<T> const& m, T3 const& a)
{
	using T4 = decltype(m.x1/a);
	return Matrix2<T4>{ m.x1/a , m.x2/a , m.x3/a, m.x4/a};
}

// mátrix- vektor szorzás

template<typename T, typename T2>
auto operator*( Matrix2<T> const& m, Vector2d<T2, false> const& v )
{
	using T3 = decltype(m.x1*v.x);
	return Vector2d<T3, false>{ m.x1*v.x + m.x2*v.y ,  m.x3*v.x + m.x4*v.y};
}

template<typename T, typename T2>
auto operator*( Vector2d<T2, true> const& v ,  Matrix2<T> const& m)
{
	using T3 = decltype(m.x1*v.x);
	return Vector2d<T3, true>{ m.x1*v.x + m.x3*v.y ,  m.x2*v.x + m.x4*v.y};
}

//egyenletrendszer megoldás

template<typename T, typename T2>
auto eq_solver( Matrix2<T> const& m, Vector2d<T2, false> const& v )
{
	return  inv(m)*v;
}

//vektor -vektor szorzás

template<typename T, typename T2>
auto dot( Vector2d<T, true> const& v, Vector2d<T2, false> const& u )
{
	using T3 = decltype(v.x*u.x);	
	T3 res=u.x*v.x + u.y*v.y;
	return res;
		
}

template<typename T, typename T2>
auto dot( Vector2d<T, false> const& v, Vector2d<T2, true> const& u )
{
	using T3 = decltype(v.x*u.x);
	Matrix2<T3> RES= { v.x*u.x ,v.x*u.y , v.y*u.x , v.y*u.y};
	return RES ;
}


template<typename T>
std::ostream& operator<<(std::ostream& o, Matrix2<T> const& m)
{
    o << '[' << m.x1 << ',' << m.x2 << ',' <<  m.x3 << ',' << m.x4 << ']';
    return o; 
}

template<typename T>
std::istream& operator>>(std::istream& i, Matrix2<T>& m)
{
    i >> m.x1;
    i >> m.x2;
	i >> m.x3;
	i >> m.x4;
    return i; 
}







