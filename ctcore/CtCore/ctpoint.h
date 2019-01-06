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
#ifndef CPOINT_H
#define CPOINT_H

#include <ctcore/ctutilitydef.h>

#include <cmath>
#include <Windows.h>

class CtPoint {
public:
	CtPoint();
	CtPoint(const CtPoint &p);
	CtPoint(int xpos, int ypos);

	inline int manhattanLength() const;

	inline bool isNull() const;

	inline int x() const;
	inline int y() const;
	inline void setX(int x);
	inline void setY(int y);

	inline CtPoint &operator+=(const CtPoint &p);
	inline CtPoint &operator-=(const CtPoint &p);
	inline CtPoint &operator*=(int c);
	inline CtPoint &operator/=(int c);

	static inline int dotProduct(const CtPoint &p1, const CtPoint &p2)
	{
		return p1.xp * p2.xp + p1.yp * p2.yp;
	}

	friend inline bool operator==(const CtPoint &, const CtPoint &);
	friend inline bool operator!=(const CtPoint &, const CtPoint &);
	friend inline const CtPoint operator+(const CtPoint &, const CtPoint &);
	friend inline const CtPoint operator-(const CtPoint &, const CtPoint &);
	friend inline const CtPoint operator*(int, const CtPoint &);
	friend inline const CtPoint operator*(const CtPoint &, int);
	friend inline const CtPoint operator+(const CtPoint &);
	friend inline const CtPoint operator-(const CtPoint &);
	friend inline const CtPoint operator/(const CtPoint &, int);

private:
	int xp;
	int yp;
};

/*****************************************************************************
CPoint inline functions
*****************************************************************************/

 inline CtPoint::CtPoint() : xp(0), yp(0) {}

 inline CtPoint::CtPoint(const CtPoint & p)
 {
	 xp = p.xp;
	 yp = p.yp;
 }

 inline CtPoint::CtPoint(int xpos, int ypos) : xp(xpos), yp(ypos) {}

 inline bool CtPoint::isNull() const
{
	return xp == 0 && yp == 0;
}

 inline int CtPoint::x() const
{
	return xp;
}

 inline int CtPoint::y() const
{
	return yp;
}

inline void CtPoint::setX(int xpos)
{
	xp = xpos;
}

inline void CtPoint::setY(int ypos)
{
	yp = ypos;
}

inline CtPoint &CtPoint::operator+=(const CtPoint &p)
{
	xp += p.xp; yp += p.yp; return *this;
}

inline CtPoint &CtPoint::operator-=(const CtPoint &p)
{
	xp -= p.xp; yp -= p.yp; return *this;
}

inline CtPoint &CtPoint::operator*=(int factor)
{
	xp = (int)(int)round(xp*factor); yp = (int)(int)round(yp*factor); return *this;
}

inline bool operator==(const CtPoint &p1, const CtPoint &p2)
{
	return p1.xp == p2.xp && p1.yp == p2.yp;
}

inline bool operator!=(const CtPoint &p1, const CtPoint &p2)
{
	return p1.xp != p2.xp || p1.yp != p2.yp;
}

inline const CtPoint operator+(const CtPoint &p1, const CtPoint &p2)
{
	return CtPoint(p1.xp + p2.xp, p1.yp + p2.yp);
}

inline const CtPoint operator-(const CtPoint &p1, const CtPoint &p2)
{
	return CtPoint(p1.xp - p2.xp, p1.yp - p2.yp);
}

inline const CtPoint operator*(const CtPoint &p, float factor)
{
	return CtPoint((int)(int)round(p.x()*factor), (int)(int)round(p.y()*factor));
}

inline const CtPoint operator*(const CtPoint &p, double factor)
{
	return CtPoint((int)(int)round(p.x()*factor), (int)(int)round(p.y()*factor));
}

inline const CtPoint operator*(const CtPoint &p, int factor)
{
	return CtPoint(p.xp*factor, p.yp*factor);
}

inline const CtPoint operator*(float factor, const CtPoint &p)
{
	return CtPoint((int)(int)round(p.x()*factor), (int)(int)round(p.y()*factor));
}

inline const CtPoint operator*(double factor, const CtPoint &p)
{
	return CtPoint((int)(int)round(p.x()*factor), (int)(int)round(p.y()*factor));
}

class CtPointF {
public:
	 CtPointF();
	 CtPointF(const CtPoint &p);
	 CtPointF(float xpos, float ypos);
	 CtPointF(const POINT &p);
	 inline float manhattanLength() const;

	inline bool isNull() const;

	 inline float x() const;
	 inline float y() const;
	inline void setX(float x);
	inline void setY(float y);

	inline float &rx();
	inline float &ry();

	inline CtPointF &operator+=(const CtPointF &p);
	inline CtPointF &operator-=(const CtPointF &p);
	inline CtPointF &operator*=(float c);
	inline CtPointF &operator/=(float c);

	 static inline double dotProduct(const CtPointF &p1, const CtPointF &p2)
	{
		return p1.xp * p2.xp + p1.yp * p2.yp;
	}

	friend inline bool operator==(const CtPointF &, const CtPointF &);
	friend inline bool operator!=(const CtPointF &, const CtPointF &);
	friend inline const CtPointF operator+(const CtPointF &, const CtPointF &);
	friend inline const CtPointF operator-(const CtPointF &, const CtPointF &);
	friend inline const CtPointF operator*(double, const CtPointF &);
	friend inline const CtPointF operator*(const CtPointF &, double);
	friend inline const CtPointF operator+(const CtPointF &);
	friend inline const CtPointF operator-(const CtPointF &);
	friend inline const CtPointF operator/(const CtPointF &, double);

	 CtPoint toPoint() const;

private:
	//friend class QMatrix;
	//friend class QTransform;

	float xp;
	float yp;
};

/*****************************************************************************
CPointF inline functions
*****************************************************************************/

inline CtPointF::CtPointF() : xp(0), yp(0) { }

inline CtPointF::CtPointF(float xpos, float ypos) : xp(xpos), yp(ypos) { }

inline CtPointF::CtPointF(const POINT & p)
{
	xp = float(p.x); yp = float(p.y);
}

 inline CtPointF::CtPointF(const CtPoint &p) : xp(float(p.x())), yp(float(p.y())) { }

 inline float CtPointF::manhattanLength() const
{
	return abs(x()) + abs(y());
}

inline bool CtPointF::isNull() const
{
	return ::isNull(xp) && ::isNull(yp);
}

 inline float CtPointF::x() const
{
	return xp;
}

 inline float CtPointF::y() const
{
	return yp;
}

inline void CtPointF::setX(float xpos)
{
	xp = xpos;
}

inline void CtPointF::setY(float ypos)
{
	yp = ypos;
}

inline float &CtPointF::rx()
{
	return xp;
}

inline float &CtPointF::ry()
{
	return yp;
}

inline CtPointF &CtPointF::operator+=(const CtPointF &p)
{
	xp += p.xp;
	yp += p.yp;
	return *this;
}

inline CtPointF &CtPointF::operator-=(const CtPointF &p)
{
	xp -= p.xp; yp -= p.yp; return *this;
}

inline CtPointF &CtPointF::operator*=(float c)
{
	xp *= c; yp *= c; return *this;
}

inline bool operator==(const CtPointF &p1, const CtPointF &p2)
{
	return fuzzyIsNull(p1.xp - p2.xp) && fuzzyIsNull(p1.yp - p2.yp);
}

inline bool operator!=(const CtPointF &p1, const CtPointF &p2)
{
	return !fuzzyIsNull(p1.xp - p2.xp) || !fuzzyIsNull(p1.yp - p2.yp);
}

inline const CtPointF operator+(const CtPointF &p1, const CtPointF &p2)
{
	return CtPointF(p1.xp + p2.xp, p1.yp + p2.yp);
}

inline const CtPointF operator-(const CtPointF &p1, const CtPointF &p2)
{
	return CtPointF(p1.xp - p2.xp, p1.yp - p2.yp);
}

inline const CtPointF operator*(const CtPointF &p, float c)
{
	return CtPointF(p.x()*c, p.y()*c);
}

inline const CtPointF operator*(float c, const CtPointF &p)
{
	return CtPointF(p.x()*c, p.y()*c);
}

inline const CtPointF operator+(const CtPointF &p)
{
	return p;
}

inline const CtPointF operator-(const CtPointF &p)
{
	return CtPointF(-p.xp, -p.yp);
}

inline CtPointF &CtPointF::operator/=(float divisor)
{
	xp /= divisor;
	yp /= divisor;
	return *this;
}

inline const CtPointF operator/(const CtPointF &p, float divisor)
{
	return CtPointF(p.x() / divisor, p.y() / divisor);
}

inline CtPoint CtPointF::toPoint() const
{
	return CtPoint(int(std::roundf(xp)), int(std::roundf(yp)));
}

//#ifdef DEBUG
//#include <iostream>
//using std::ostream;
//ostream &operator<<(ostream &d, const CPointF &p) {
//	d << typeid(p).name() + std::string("{ x: ") + std::to_string(p.x()) + ", y: ";
//	return d;
//}
//#endif

#endif // !CPOINT_H
