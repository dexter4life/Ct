
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

#ifndef CT_MARGINS_H
#define CT_MARGINS_H

#include <ctcore/ctglobal.h>

/*****************************************************************************
CtMargins class
*****************************************************************************/

class CtMargins
{
public:
	CtMargins();
	CtMargins(int left, int top, int right, int bottom);

	bool isNull() const;

	int left() const;
	int top() const;
	int right() const;
	int bottom() const;

	void setLeft(int left);
	void setTop(int top);
	void setRight(int right);
	void setBottom(int bottom);

	CtMargins &operator+=(const CtMargins &margins);
	CtMargins &operator-=(const CtMargins &margins);
	CtMargins &operator+=(int);
	CtMargins &operator-=(int);
	CtMargins &operator*=(int);
	CtMargins &operator/=(int);
	CtMargins &operator*=(ctreal);
	CtMargins &operator/=(ctreal);

private:
	int m_left;
	int m_top;
	int m_right;
	int m_bottom;

	friend inline bool operator==(const CtMargins &, const CtMargins &);
	friend inline bool operator!=(const CtMargins &, const CtMargins &);
};

//Q_DECLARE_TYPEINFO(CtMargins, Q_MOVABLE_TYPE);
//
///*****************************************************************************
//CtMargins stream functions
//*****************************************************************************/
//#ifndef QT_NO_DATASTREAM
//Q_CORE_EXPORT QDataStream &operator<<(QDataStream &, const CtMargins &);
//Q_CORE_EXPORT QDataStream &operator >> (QDataStream &, CtMargins &);
//#endif

/*****************************************************************************
CtMargins inline functions
*****************************************************************************/

inline CtMargins::CtMargins() : m_left(0), m_top(0), m_right(0), m_bottom(0) {}

inline CtMargins::CtMargins(int aleft, int atop, int aright, int abottom)
	: m_left(aleft), m_top(atop), m_right(aright), m_bottom(abottom) {}

inline bool CtMargins::isNull() const
{
	return m_left == 0 && m_top == 0 && m_right == 0 && m_bottom == 0;
}

inline int CtMargins::left() const
{
	return m_left;
}

inline int CtMargins::top() const
{
	return m_top;
}

inline int CtMargins::right() const
{
	return m_right;
}

inline int CtMargins::bottom() const
{
	return m_bottom;
}


inline void CtMargins::setLeft(int aleft)
{
	m_left = aleft;
}

inline void CtMargins::setTop(int atop)
{
	m_top = atop;
}

inline void CtMargins::setRight(int aright)
{
	m_right = aright;
}

inline void CtMargins::setBottom(int abottom)
{
	m_bottom = abottom;
}

inline bool operator==(const CtMargins &m1, const CtMargins &m2)
{
	return
		m1.m_left == m2.m_left &&
		m1.m_top == m2.m_top &&
		m1.m_right == m2.m_right &&
		m1.m_bottom == m2.m_bottom;
}

inline bool operator!=(const CtMargins &m1, const CtMargins &m2)
{
	return
		m1.m_left != m2.m_left ||
		m1.m_top != m2.m_top ||
		m1.m_right != m2.m_right ||
		m1.m_bottom != m2.m_bottom;
}

inline CtMargins operator+(const CtMargins &m1, const CtMargins &m2)
{
	return CtMargins(m1.left() + m2.left(), m1.top() + m2.top(),
		m1.right() + m2.right(), m1.bottom() + m2.bottom());
}

inline CtMargins operator-(const CtMargins &m1, const CtMargins &m2)
{
	return CtMargins(m1.left() - m2.left(), m1.top() - m2.top(),
		m1.right() - m2.right(), m1.bottom() - m2.bottom());
}

inline CtMargins operator+(const CtMargins &lhs, int rhs)
{
	return CtMargins(lhs.left() + rhs, lhs.top() + rhs,
		lhs.right() + rhs, lhs.bottom() + rhs);
}

inline CtMargins operator+(int lhs, const CtMargins &rhs)
{
	return CtMargins(rhs.left() + lhs, rhs.top() + lhs,
		rhs.right() + lhs, rhs.bottom() + lhs);
}

inline CtMargins operator-(const CtMargins &lhs, int rhs)
{
	return CtMargins(lhs.left() - rhs, lhs.top() - rhs,
		lhs.right() - rhs, lhs.bottom() - rhs);
}

inline CtMargins operator*(const CtMargins &margins, int factor)
{
	return CtMargins(margins.left() * factor, margins.top() * factor,
		margins.right() * factor, margins.bottom() * factor);
}

inline CtMargins operator*(int factor, const CtMargins &margins)
{
	return CtMargins(margins.left() * factor, margins.top() * factor,
		margins.right() * factor, margins.bottom() * factor);
}

inline CtMargins operator*(const CtMargins &margins, ctreal factor)
{
	return CtMargins((int)std::round(margins.left() * factor), (int)std::round(margins.top() * factor),
		(int)std::round(margins.right() * factor), (int)std::round(margins.bottom() * factor));
}

inline CtMargins operator*(ctreal factor, const CtMargins &margins)
{
	return CtMargins((int)std::round(margins.left() * factor), (int)std::round(margins.top() * factor),
		(int)std::round(margins.right() * factor), (int)std::round(margins.bottom() * factor));
}

inline CtMargins operator/(const CtMargins &margins, int divisor)
{
	return CtMargins(margins.left() / divisor, margins.top() / divisor,
		margins.right() / divisor, margins.bottom() / divisor);
}

inline CtMargins operator/(const CtMargins &margins, ctreal divisor)
{
	return CtMargins((int)std::round(margins.left() / divisor), (int)std::round(margins.top() / divisor),
		(int)std::round(margins.right() / divisor), (int)std::round(margins.bottom() / divisor));
}

inline CtMargins &CtMargins::operator+=(const CtMargins &margins)
{
	return *this = *this + margins;
}

inline CtMargins &CtMargins::operator-=(const CtMargins &margins)
{
	return *this = *this - margins;
}

inline CtMargins &CtMargins::operator+=(int margin)
{
	m_left += margin;
	m_top += margin;
	m_right += margin;
	m_bottom += margin;
	return *this;
}

inline CtMargins &CtMargins::operator-=(int margin)
{
	m_left -= margin;
	m_top -= margin;
	m_right -= margin;
	m_bottom -= margin;
	return *this;
}

inline CtMargins &CtMargins::operator*=(int factor)
{
	return *this = *this * factor;
}

inline CtMargins &CtMargins::operator/=(int divisor)
{
	return *this = *this / divisor;
}

inline CtMargins &CtMargins::operator*=(ctreal factor)
{
	return *this = *this * factor;
}

inline CtMargins &CtMargins::operator/=(ctreal divisor)
{
	return *this = *this / divisor;
}

inline CtMargins operator+(const CtMargins &margins)
{
	return margins;
}

inline CtMargins operator-(const CtMargins &margins)
{
	return CtMargins(-margins.left(), -margins.top(), -margins.right(), -margins.bottom());
}

//#ifndef QT_NO_DEBUG_STREAM
//Debug operator<<(QDebug, const CtMargins &);
//#endif

/*****************************************************************************
CtMarginsF class
*****************************************************************************/

class CtMarginsF
{
public:
	CtMarginsF();
	CtMarginsF(ctreal left, ctreal top, ctreal right, ctreal bottom);
	CtMarginsF(const CtMargins &margins);

	bool isNull() const;

	ctreal left() const;
	ctreal top() const;
	ctreal right() const;
	ctreal bottom() const;

	void setLeft(ctreal left);
	void setTop(ctreal top);
	void setRight(ctreal right);
	void setBottom(ctreal bottom);

	CtMarginsF &operator+=(const CtMarginsF &margins);
	CtMarginsF &operator-=(const CtMarginsF &margins);
	CtMarginsF &operator+=(ctreal addend);
	CtMarginsF &operator-=(ctreal subtrahend);
	CtMarginsF &operator*=(ctreal factor);
	CtMarginsF &operator/=(ctreal divisor);

	inline CtMargins toMargins() const;

private:
	ctreal m_left;
	ctreal m_top;
	ctreal m_right;
	ctreal m_bottom;
};
//
//Q_DECLARE_TYPEINFO(CtMarginsF, Q_MOVABLE_TYPE);
//
///*****************************************************************************
//CtMarginsF stream functions
//*****************************************************************************/
//
//#ifndef QT_NO_DATASTREAM
//Q_CORE_EXPORT QDataStream &operator<<(QDataStream &, const CtMarginsF &);
//Q_CORE_EXPORT QDataStream &operator >> (QDataStream &, CtMarginsF &);
//#endif

/*****************************************************************************
CtMarginsF inline functions
*****************************************************************************/

inline CtMarginsF::CtMarginsF()
	: m_left(0), m_top(0), m_right(0), m_bottom(0) {}

inline CtMarginsF::CtMarginsF(ctreal aleft, ctreal atop, ctreal aright, ctreal abottom)
	: m_left(aleft), m_top(atop), m_right(aright), m_bottom(abottom) {}

inline CtMarginsF::CtMarginsF(const CtMargins &margins)
	: m_left((ctreal)margins.left()), m_top((ctreal)margins.top()), m_right((ctreal)margins.right()), m_bottom((ctreal)margins.bottom()) {}

inline bool CtMarginsF::isNull() const
{
	return qFuzzyIsNull(m_left) && qFuzzyIsNull(m_top) && qFuzzyIsNull(m_right) && qFuzzyIsNull(m_bottom);
}

inline ctreal CtMarginsF::left() const
{
	return m_left;
}

inline ctreal CtMarginsF::top() const
{
	return m_top;
}

inline ctreal CtMarginsF::right() const
{
	return m_right;
}

inline ctreal CtMarginsF::bottom() const
{
	return m_bottom;
}


inline void CtMarginsF::setLeft(ctreal aleft)
{
	m_left = aleft;
}

inline void CtMarginsF::setTop(ctreal atop)
{
	m_top = atop;
}

inline void CtMarginsF::setRight(ctreal aright)
{
	m_right = aright;
}

inline void CtMarginsF::setBottom(ctreal abottom)
{
	m_bottom = abottom;
}

inline bool operator==(const CtMarginsF &lhs, const CtMarginsF &rhs)
{
	return cFuzzyCompare(lhs.left(), rhs.left())
		&& cFuzzyCompare(lhs.top(), rhs.top())
		&& cFuzzyCompare(lhs.right(), rhs.right())
		&& cFuzzyCompare(lhs.bottom(), rhs.bottom());
}

inline bool operator!=(const CtMarginsF &lhs, const CtMarginsF &rhs)
{
	return !operator==(lhs, rhs);
}

inline CtMarginsF operator+(const CtMarginsF &lhs, const CtMarginsF &rhs)
{
	return CtMarginsF(lhs.left() + rhs.left(), lhs.top() + rhs.top(),
		lhs.right() + rhs.right(), lhs.bottom() + rhs.bottom());
}

inline CtMarginsF operator-(const CtMarginsF &lhs, const CtMarginsF &rhs)
{
	return CtMarginsF(lhs.left() - rhs.left(), lhs.top() - rhs.top(),
		lhs.right() - rhs.right(), lhs.bottom() - rhs.bottom());
}

inline CtMarginsF operator+(const CtMarginsF &lhs, ctreal rhs)
{
	return CtMarginsF(lhs.left() + rhs, lhs.top() + rhs,
		lhs.right() + rhs, lhs.bottom() + rhs);
}

inline CtMarginsF operator+(ctreal lhs, const CtMarginsF &rhs)
{
	return CtMarginsF(rhs.left() + lhs, rhs.top() + lhs,
		rhs.right() + lhs, rhs.bottom() + lhs);
}

inline CtMarginsF operator-(const CtMarginsF &lhs, ctreal rhs)
{
	return CtMarginsF(lhs.left() - rhs, lhs.top() - rhs,
		lhs.right() - rhs, lhs.bottom() - rhs);
}

inline CtMarginsF operator*(const CtMarginsF &lhs, ctreal rhs)
{
	return CtMarginsF(lhs.left() * rhs, lhs.top() * rhs,
		lhs.right() * rhs, lhs.bottom() * rhs);
}

inline CtMarginsF operator*(ctreal lhs, const CtMarginsF &rhs)
{
	return CtMarginsF(rhs.left() * lhs, rhs.top() * lhs,
		rhs.right() * lhs, rhs.bottom() * lhs);
}

inline CtMarginsF operator/(const CtMarginsF &lhs, ctreal divisor)
{
	return CtMarginsF(lhs.left() / divisor, lhs.top() / divisor,
		lhs.right() / divisor, lhs.bottom() / divisor);
}

inline CtMarginsF &CtMarginsF::operator+=(const CtMarginsF &margins)
{
	return *this = *this + margins;
}

inline CtMarginsF &CtMarginsF::operator-=(const CtMarginsF &margins)
{
	return *this = *this - margins;
}

inline CtMarginsF &CtMarginsF::operator+=(ctreal addend)
{
	m_left += addend;
	m_top += addend;
	m_right += addend;
	m_bottom += addend;
	return *this;
}

inline CtMarginsF &CtMarginsF::operator-=(ctreal subtrahend)
{
	m_left -= subtrahend;
	m_top -= subtrahend;
	m_right -= subtrahend;
	m_bottom -= subtrahend;
	return *this;
}

inline CtMarginsF &CtMarginsF::operator*=(ctreal factor)
{
	return *this = *this * factor;
}

inline CtMarginsF &CtMarginsF::operator/=(ctreal divisor)
{
	return *this = *this / divisor;
}

inline CtMarginsF operator+(const CtMarginsF &margins)
{
	return margins;
}

inline CtMarginsF operator-(const CtMarginsF &margins)
{
	return CtMarginsF(-margins.left(), -margins.top(), -margins.right(), -margins.bottom());
}

inline CtMargins CtMarginsF::toMargins() const
{
	return CtMargins((int)std::round(m_left), (int)std::round(m_top), (int)std::round(m_right), (int)std::round(m_bottom));
}

//#ifndef QT_NO_DEBUG_STREAM
//Q_CORE_EXPORT QDebug operator<<(QDebug, const CtMarginsF &);
//#endif
//
//QT_END_NAMESPACE

#endif // CT_MARGINS_H
