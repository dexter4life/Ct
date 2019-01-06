/*
Author: Peter Nwanosike
Email: dexter4life@gmail.com

Ct is free software : you can redistribute it and / or modify it under the
terms of the GNU General Public License as published by the Free Software
Foundation, either version 3 of the License.


Ct is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE.See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
Ct.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#ifndef __VEC2_H__
#define __VEC2_H__

#include <cmath>

template <class T>
class CtVec2 {
public:
	T x, y;

	CtVec2() :x(0), y(0) {}
	CtVec2(T x, T y) : x(x), y(y) {}
	CtVec2(const CtVec2& v) : x(v.x), y(v.y) {}

	CtVec2& operator=(const CtVec2& v) {
		x = v.x;
		y = v.y;
		return *this;
	}

	CtVec2 operator+(CtVec2& v) {
		return CtVec2(x + v.x, y + v.y);
	}
	CtVec2 operator-(CtVec2& v) {
		return CtVec2(x - v.x, y - v.y);
	}

	CtVec2& operator+=(CtVec2& v) {
		x += v.x;
		y += v.y;
		return *this;
	}
	CtVec2& operator-=(CtVec2& v) {
		x -= v.x;
		y -= v.y;
		return *this;
	}

	CtVec2 operator+(double s) {
		return CtVec2(x + s, y + s);
	}
	CtVec2 operator-(double s) {
		return CtVec2(x - s, y - s);
	}
	CtVec2 operator*(double s) {
		return CtVec2(x * s, y * s);
	}
	CtVec2 operator/(double s) {
		return CtVec2(x / s, y / s);
	}


	CtVec2& operator+=(double s) {
		x += s;
		y += s;
		return *this;
	}
	CtVec2& operator-=(double s) {
		x -= s;
		y -= s;
		return *this;
	}
	CtVec2& operator*=(double s) {
		x *= s;
		y *= s;
		return *this;
	}
	CtVec2& operator/=(double s) {
		x /= s;
		y /= s;
		return *this;
	}

	void set(T x, T y) {
		this->x = x;
		this->y = y;
	}

	void rotate(double deg) {
		double theta = deg / 180.0 * M_PI;
		double c = cos(theta);
		double s = sin(theta);
		double tx = x * c - y * s;
		double ty = x * s + y * c;
		x = tx;
		y = ty;
	}

	CtVec2& normalize() {
		if (length() == 0) return *this;
		*this *= (1.0 / length());
		return *this;
	}

	float dist(CtVec2 v) const {
		CtVec2 d(v.x - x, v.y - y);
		return d.length();
	}
	float length() const {
		return std::sqrt(x * x + y * y);
	}
	void truncate(double length) {
		double angle = atan2f(y, x);
		x = length * cos(angle);
		y = length * sin(angle);
	}

	CtVec2 ortho() const {
		return CtVec2(y, -x);
	}

	static float dot(CtVec2 v1, CtVec2 v2) {
		return v1.x * v2.x + v1.y * v2.y;
	}
	static float cross(CtVec2 v1, CtVec2 v2) {
		return (v1.x * v2.y) - (v1.y * v2.x);
	}

};

typedef CtVec2<float> vec2f;
typedef CtVec2<double> vec2d;

#endif