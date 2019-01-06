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

#ifndef CT_Size_H
#define CT_Size_H

#include <ctcore/ctglobal.h>
#include <cassert>

class CtSize
{
public:
	CtSize();
	CtSize(int w, int h);

	inline bool isNull() const;
	inline bool isEmpty() const;
	inline bool isValid() const;

	inline int width() const;
	inline int height() const;
	inline void setWidth(int w);
	inline void setHeight(int h);
	void transpose();
	inline CtSize transposed() const;

	//inline void scale(int w, int h, Qt::AspectRatioMode mode);
	//inline void scale(const CtSize &s, Qt::AspectRatioMode mode);
	//CtSize scaled(int w, int h, Qt::AspectRatioMode mode) const;
	//CtSize scaled(const CtSize &s, Qt::AspectRatioMode mode) const;

	inline CtSize expandedTo(const CtSize &) const;
	inline CtSize boundedTo(const CtSize &) const;

	inline int &rwidth();
	inline int &rheight();

	inline CtSize &operator+=(const CtSize &);
	inline CtSize &operator-=(const CtSize &);
	inline CtSize &operator*=(ctreal c);
	inline CtSize &operator/=(ctreal c);

	friend inline bool operator==(const CtSize &, const CtSize &);
	friend inline bool operator!=(const CtSize &, const CtSize &);
	friend inline const CtSize operator+(const CtSize &, const CtSize &);
	friend inline const CtSize operator-(const CtSize &, const CtSize &);
	friend inline const CtSize operator*(const CtSize &, ctreal);
	friend inline const CtSize operator*(ctreal, const CtSize &);
	friend inline const CtSize operator/(const CtSize &, ctreal);

private:
	int wd;
	int ht;
};

/*****************************************************************************
CtSize inline functions
*****************************************************************************/

inline CtSize::CtSize() : wd(-1), ht(-1) {}

inline CtSize::CtSize(int w, int h) : wd(w), ht(h) {}

inline bool CtSize::isNull() const
{
	return wd == 0 && ht == 0;
}

inline bool CtSize::isEmpty() const
{
	return wd<1 || ht<1;
}

inline bool CtSize::isValid() const
{
	return wd >= 0 && ht >= 0;
}

inline int CtSize::width() const
{
	return wd;
}

inline int CtSize::height() const
{
	return ht;
}

inline void CtSize::setWidth(int w)
{
	wd = w;
}

inline void CtSize::setHeight(int h)
{
	ht = h;
}

inline CtSize CtSize::transposed() const
{
	return CtSize(ht, wd);
}

//inline void CtSize::scale(int w, int h, Qt::AspectRatioMode mode)
//{
//	scale(CtSize(w, h), mode);
//}
//
//inline void CtSize::scale(const CtSize &s, Qt::AspectRatioMode mode)
//{
//	*this = scaled(s, mode);
//}
//
//inline CtSize CtSize::scaled(int w, int h, Qt::AspectRatioMode mode) const
//{
//	return scaled(CtSize(w, h), mode);
//}

inline int &CtSize::rwidth()
{
	return wd;
}

inline int &CtSize::rheight()
{
	return ht;
}

inline CtSize &CtSize::operator+=(const CtSize &s)
{
	wd += s.wd; ht += s.ht; return *this;
}

inline CtSize &CtSize::operator-=(const CtSize &s)
{
	wd -= s.wd; ht -= s.ht; return *this;
}

inline CtSize &CtSize::operator*=(ctreal c)
{
	wd = (int)round(wd*c); ht = (int)round(ht*c); return *this;
}

inline bool operator==(const CtSize &s1, const CtSize &s2)
{
	return s1.wd == s2.wd && s1.ht == s2.ht;
}

inline bool operator!=(const CtSize &s1, const CtSize &s2)
{
	return s1.wd != s2.wd || s1.ht != s2.ht;
}

inline const CtSize operator+(const CtSize & s1, const CtSize & s2)
{
	return CtSize(s1.wd + s2.wd, s1.ht + s2.ht);
}

inline const CtSize operator-(const CtSize &s1, const CtSize &s2)
{
	return CtSize(s1.wd - s2.wd, s1.ht - s2.ht);
}

inline const CtSize operator*(const CtSize &s, ctreal c)
{
	return CtSize((int)round(s.wd*c), (int)round(s.ht*c));
}

inline const CtSize operator*(ctreal c, const CtSize &s)
{
	return CtSize((int)round(s.wd*c), (int)round(s.ht*c));
}

inline CtSize &CtSize::operator/=(ctreal c)
{
	assert(!cFuzzyIsNull(c));
	wd = (int)round(wd / c); ht = (int)round(ht / c);
	return *this;
}

inline const CtSize operator/(const CtSize &s, ctreal c)
{
	assert(!cFuzzyIsNull(c));
	return CtSize((int)round(s.wd / c), (int)round(s.ht / c));
}

inline CtSize CtSize::expandedTo(const CtSize & otherSize) const
{
	return CtSize(std::max(wd, otherSize.wd), std::max(ht, otherSize.ht));
}

inline CtSize CtSize::boundedTo(const CtSize & otherSize) const
{
	return CtSize(std::min(wd, otherSize.wd), std::min(ht, otherSize.ht));
}
//
//#ifndef QT_NO_DEBUG_STREAM
//Q_CORE_EXPORT QDebug operator<<(QDebug, const CtSize &);
//#endif


class CtSizeF
{
public:
	CtSizeF();
	CtSizeF(const CtSize &sz);
	CtSizeF(ctreal w, ctreal h);

	inline bool isNull() const;
	inline bool isEmpty() const;
	inline bool isValid() const;

	inline ctreal width() const;
	inline ctreal height() const;
	inline void setWidth(ctreal w);
	inline void setHeight(ctreal h);
	void transpose();
	inline CtSizeF transposed() const;

	/*inline void scale(creal w, creal h, Qt::AspectRatioMode mode);
	inline void scale(const CtSizeF &s, Qt::AspectRatioMode mode);
	CtSizeF scaled(creal w, creal h, Qt::AspectRatioMode mode) const;
	CtSizeF scaled(const CtSizeF &s, Qt::AspectRatioMode mode) const;*/

	inline CtSizeF expandedTo(const CtSizeF &) const;
	inline CtSizeF boundedTo(const CtSizeF &) const;

	inline ctreal &rwidth();
	inline ctreal &rheight();

	inline CtSizeF &operator+=(const CtSizeF &);
	inline CtSizeF &operator-=(const CtSizeF &);
	inline CtSizeF &operator*=(ctreal c);
	inline CtSizeF &operator/=(ctreal c);

	friend inline bool operator==(const CtSizeF &, const CtSizeF &);
	friend inline bool operator!=(const CtSizeF &, const CtSizeF &);
	friend inline const CtSizeF operator+(const CtSizeF &, const CtSizeF &);
	friend inline const CtSizeF operator-(const CtSizeF &, const CtSizeF &);
	friend inline const CtSizeF operator*(const CtSizeF &, ctreal);
	friend inline const CtSizeF operator*(ctreal, const CtSizeF &);
	friend inline const CtSizeF operator/(const CtSizeF &, ctreal);

	inline CtSize toSize() const;

private:
	ctreal wd;
	ctreal ht;
};
//Q_DECLARE_TYPEINFO(CtSizeF, Q_MOVABLE_TYPE);


///*****************************************************************************
//CtSizeF stream functions
//*****************************************************************************/
//
//#ifndef QT_NO_DATASTREAM
//Q_CORE_EXPORT QDataStream &operator<<(QDataStream &, const CtSizeF &);
//Q_CORE_EXPORT QDataStream &operator >> (QDataStream &, CtSizeF &);
//#endif


/*****************************************************************************
CtSizeF inline functions
*****************************************************************************/

inline CtSizeF::CtSizeF() : wd(-1.), ht(-1.) {}

inline CtSizeF::CtSizeF(const CtSize &sz) : wd((ctreal)sz.width()), ht((ctreal)sz.height()) {}

inline CtSizeF::CtSizeF(ctreal w, ctreal h) : wd(w), ht(h) {}

inline bool CtSizeF::isNull() const
{
	return qIsNull(wd) && qIsNull(ht);
}

inline bool CtSizeF::isEmpty() const
{
	return wd <= 0. || ht <= 0.;
}

inline bool CtSizeF::isValid() const
{
	return wd >= 0. && ht >= 0.;
}

inline ctreal CtSizeF::width() const
{
	return wd;
}

inline ctreal CtSizeF::height() const
{
	return ht;
}

inline void CtSizeF::setWidth(ctreal w)
{
	wd = w;
}

inline void CtSizeF::setHeight(ctreal h)
{
	ht = h;
}

inline CtSizeF CtSizeF::transposed() const
{
	return CtSizeF(ht, wd);
}

//inline void CtSizeF::scale(creal w, creal h, Qt::AspectRatioMode mode)
//{
//	scale(CtSizeF(w, h), mode);
//}
//
//inline void CtSizeF::scale(const CtSizeF &s, Qt::AspectRatioMode mode)
//{
//	*this = scaled(s, mode);
//}
//
//inline CtSizeF CtSizeF::scaled(creal w, creal h, Qt::AspectRatioMode mode) const
//{
//	return scaled(CtSizeF(w, h), mode);
//}

inline ctreal &CtSizeF::rwidth()
{
	return wd;
}

inline ctreal &CtSizeF::rheight()
{
	return ht;
}

inline CtSizeF &CtSizeF::operator+=(const CtSizeF &s)
{
	wd += s.wd; ht += s.ht; return *this;
}

inline CtSizeF &CtSizeF::operator-=(const CtSizeF &s)
{
	wd -= s.wd; ht -= s.ht; return *this;
}

inline CtSizeF &CtSizeF::operator*=(ctreal c)
{
	wd *= c; ht *= c; return *this;
}

inline bool operator==(const CtSizeF &s1, const CtSizeF &s2)
{
	return cFuzzyCompare(s1.wd, s2.wd) && cFuzzyCompare(s1.ht, s2.ht);
}

inline bool operator!=(const CtSizeF &s1, const CtSizeF &s2)
{
	return !cFuzzyCompare(s1.wd, s2.wd) || !cFuzzyCompare(s1.ht, s2.ht);
}

inline const CtSizeF operator+(const CtSizeF & s1, const CtSizeF & s2)
{
	return CtSizeF(s1.wd + s2.wd, s1.ht + s2.ht);
}

inline const CtSizeF operator-(const CtSizeF &s1, const CtSizeF &s2)
{
	return CtSizeF(s1.wd - s2.wd, s1.ht - s2.ht);
}

inline const CtSizeF operator*(const CtSizeF &s, ctreal c)
{
	return CtSizeF(s.wd*c, s.ht*c);
}

inline const CtSizeF operator*(ctreal c, const CtSizeF &s)
{
	return CtSizeF(s.wd*c, s.ht*c);
}

inline CtSizeF &CtSizeF::operator/=(ctreal c)
{
	assert(!qFuzzyIsNull(c));
	wd = wd / c; ht = ht / c;
	return *this;
}

inline const CtSizeF operator/(const CtSizeF &s, ctreal c)
{
	assert(!qFuzzyIsNull(c));
	return CtSizeF(s.wd / c, s.ht / c);
}

inline CtSizeF CtSizeF::expandedTo(const CtSizeF & otherSize) const
{
	return CtSizeF(std::max(wd, otherSize.wd),std::max(ht, otherSize.ht));
}

inline CtSizeF CtSizeF::boundedTo(const CtSizeF & otherSize) const
{
	return CtSizeF(std::min(wd, otherSize.wd), std::min(ht, otherSize.ht));
}

inline CtSize CtSizeF::toSize() const
{
	return CtSize((ctint32)(int)round(wd), (ctint32)(int)round(ht));
}

//#ifndef QT_NO_DEBUG_STREAM
//Q_CORE_EXPORT QDebug operator<<(QDebug, const CtSizeF &);
//#endif

//QT_END_NAMESPACE

#endif // CtSize_H