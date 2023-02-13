#pragma once

#include <iostream>

namespace DGravity {
	class Color {
		private:
			int floatToByte(float s);
		public:
			int r, g, b, a = 255; 
			
			Color();
			Color(int r_, int g_, int b_);
			Color(int r_, int g_, int b_, int a_);
			Color(float rgba[4]);
	};
	
	class Vec2 {
	public:
		double x, y;

		Vec2();
		Vec2(double x, double y);
		Vec2(const Vec2& v);

		Vec2& operator+=(const Vec2& v);
		Vec2& operator-=(const Vec2& v);
		Vec2 operator+(const Vec2& v) const;
		Vec2 operator-(const Vec2& v) const;

		Vec2 operator+() const;
		Vec2 operator-() const;

		Vec2 operator*(double s) const;
		Vec2 operator/(double s) const;
		
		bool operator==(const Vec2& v) const;

		double Magnitude() const;
		Vec2 Normalize() const;
	};
}