#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <iostream>
#include <cmath>
/**
 * Vector bidimensional genérico.
 */
template<std::floating_point T = float>
class Vector2D
{
	T x, y;

public:
	Vector2D(T x, T y) : x(x), y(y) { }
	Vector2D() : Vector2D(0, 0) { }

	// Coordenadas del vector
	T getX() const { return x; }
	T getY() const { return y; }

	// Operadores
	Vector2D operator+(const Vector2D& otro) const {
		return {x + otro.x, y + otro.y};
	}
	Vector2D& operator+=(const Vector2D& otro)  {
		x += otro.x; 
		y += otro.y;
		return *this;
	}
	Vector2D operator-(const Vector2D& otro) const
	{
		return { x - otro.x, y - otro.y };
	}
	T operator*(const Vector2D& otro) const
	{
		return { x * otro.x + y * otro.y };
	}
	Vector2D operator*(const int num) const
	{
		return { x * num, y * num };
	}

	// Longitud de un vector (su magnitud)
	T Lenght() const
	{
		return sqrt(x * x + y * y);
	}
	// Operadores de entrada/salida
	friend std::ostream& operator<<(std::ostream& out, const Vector2D& v) {
		return out << '{' << v.x << ", " << v.y << '}';
	}
};

// Alias
template<std::floating_point T = float>
using Point2D = Vector2D<T>;

#endif // VECTOR2D_H
