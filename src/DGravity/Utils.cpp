#include "DGravity/Utils.hpp"

namespace DGravity {
	Color::Color() : r(0), g(0), b(0) {}

	Color::Color(int r_, int g_, int b_)
		: r(r_), g(g_), b(b_) {}
	
	Color::Color(int r_, int g_, int b_, int a_)
		: r(r_), g(g_), b(b_), a(a_) {}

	Color::Color(float rgba[4]) {
		r = floatToByte(rgba[0]);
		g = floatToByte(rgba[1]);
		b = floatToByte(rgba[2]);
		a = floatToByte(rgba[3]);
	}

	int Color::floatToByte(float s) {
		return std::round(s * 255.0);
	}

	Vec2::Vec2() : x(0), y(0) {}
	Vec2::Vec2(double x, double y) : x(x), y(y) {}
	Vec2::Vec2(const Vec2& v) : x(v.x), y(v.y) {}

	Vec2& Vec2::operator+=(const Vec2& v) {
		x += v.x;
		y += v.y;
		return *this;
	}

	Vec2& Vec2::operator-=(const Vec2& v) {
		x -= v.x;
		y -= v.y;
		return *this;
	}

	Vec2 Vec2::operator+() const {
		return *this;
	}

	Vec2 Vec2::operator-() const {
		return Vec2(-x, -y);
	}

	Vec2 Vec2::operator+(const Vec2& v) const {
		return Vec2(x + v.x, y + v.y);
	}

	Vec2 Vec2::operator-(const Vec2& v) const {
		return Vec2(x - v.x, y - v.y);
	}

	Vec2 Vec2::operator*(double s) const {
		return Vec2(x * s, y * s);
	}

	Vec2 Vec2::operator/(double s) const {
		return Vec2(x / s, y / s);
	}
	
	bool Vec2::operator==(const Vec2& v) const {
		return x == v.x && y == v.y;
	};

	double Vec2::Magnitude() const {
		return std::sqrt(x*x+y*y);
	}

	Vec2 Vec2::Normalize() const {
		double magnitude = Magnitude();
		return Vec2(x / magnitude, y / magnitude);
	}
}