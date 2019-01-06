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

#ifndef CRECT_H
#define CRECT_H

#include <ctcore/ctmargins.h>
#include <ctcore/ctsize.h>
#include <ctcore/ctpoint.h>
#include <ctcore/ctglobal.h>
//
//#ifdef topLeft
//#error CtRect.h must be included before any header file that defines topLeft
//#endif


class CtRect
{
public:
	CtRect()  : x1(0), y1(0), x2(-1), y2(-1) {}
	CtRect(const CtPoint &topleft, const CtPoint &bottomright);
	CtRect(const CtPoint &topleft, const CtSize &size);
	CtRect(int left, int top, int width, int height);

	inline bool isNull() const;
	inline bool isEmpty() const;
	inline bool isValid() const;

	inline int left() const;
	inline int top() const;
	inline int right() const;
	inline int bottom() const;
	CtRect normalized();

	inline int x() const;
	inline int y() const;
	inline void setLeft(int pos);
	inline void setTop(int pos);
	inline void setRight(int pos);
	inline void setBottom(int pos);
	inline void setX(int x);
	inline void setY(int y);

	inline void setTopLeft(const CtPoint &p);
	inline void setBottomRight(const CtPoint &p);
	inline void setTopRight(const CtPoint &p);
	inline void setBottomLeft(const CtPoint &p);

	inline CtPoint topLeft() const;
	inline CtPoint bottomRight() const;
	inline CtPoint topRight() const;
	inline CtPoint bottomLeft() const;
	inline CtPoint center() const;

	inline void moveLeft(int pos);
	inline void moveTop(int pos);
	inline void moveRight(int pos);
	inline void moveBottom(int pos);
	inline void moveTopLeft(const CtPoint &p);
	inline void moveBottomRight(const CtPoint &p);
	inline void moveTopRight(const CtPoint &p);
	inline void moveBottomLeft(const CtPoint &p);
	inline void moveCenter(const CtPoint &p);

	inline void translate(int dx, int dy);
	inline void translate(const CtPoint &p);
	inline CtRect translated(int dx, int dy) const;
	inline CtRect translated(const CtPoint &p) const;
	inline CtRect transposed() const;

	inline void moveTo(int x, int t);
	inline void moveTo(const CtPoint &p);

	inline void setRect(int x, int y, int w, int h);
	inline void getRect(int *x, int *y, int *w, int *h) const;

	inline void setCoords(int x1, int y1, int x2, int y2);
	inline void getCoords(int *x1, int *y1, int *x2, int *y2) const;

	inline void adjust(int x1, int y1, int x2, int y2);
	inline CtRect adjusted(int x1, int y1, int x2, int y2) const;

	inline CtSize size() const;
	inline int width() const;
	inline int height() const;
	inline void setWidth(int w);
	inline void setHeight(int h);
	inline void setSize(const CtSize &s);

	CtRect operator|(const CtRect &r) const;
	CtRect operator&(const CtRect &r) const;
	inline CtRect& operator|=(const CtRect &r);
	inline CtRect& operator&=(const CtRect &r);

	bool contains(const CtRect &r, bool proper = false) const;
	bool contains(const CtPoint &p, bool proper = false) const;
	inline bool contains(int x, int y) const;
	inline bool contains(int x, int y, bool proper) const;
	inline CtRect united(const CtRect &other) const;
	inline CtRect intersected(const CtRect &other) const;
	bool intersects(const CtRect &r) const;

	inline CtRect marginsAdded(const CtMargins &margins) const;
	inline CtRect marginsRemoved(const CtMargins &margins) const;
	inline CtRect &operator+=(const CtMargins &margins);
	inline CtRect &operator-=(const CtMargins &margins);

	friend inline bool operator==(const CtRect &, const CtRect &);
	friend inline bool operator!=(const CtRect &, const CtRect &);

	inline void swapLeftRight() throw();

	inline void swapLeftRight(CtRect *lpRect) throw();

	inline operator LPRECT() throw()
	{
		return (LPRECT)this;
	}

	inline CtRect mulDiv(
		 int nMultiplier,
		int nDivisor) const throw();
private:
	int x1;
	int y1;
	int x2;
	int y2;
};
//Q_DECLARE_TYPEINFO(CtRect, Q_MOVABLE_TYPE);

inline bool operator==(const CtRect &, const CtRect &);
inline bool operator!=(const CtRect &, const CtRect &);


/*****************************************************************************
CtRect stream functions
*****************************************************************************/
//#ifndef QT_NO_DATASTREAM
//Q_CORE_EXPORT QDataStream &operator<<(QDataStream &, const CtRect &);
//Q_CORE_EXPORT QDataStream &operator >> (QDataStream &, CtRect &);
//#endif

/*****************************************************************************
CtRect inline member functions
*****************************************************************************/

inline CtRect::CtRect(int aleft, int atop, int awidth, int aheight) 
	: x1(aleft), y1(atop), x2(aleft + awidth - 1), y2(atop + aheight - 1) {}

inline CtRect::CtRect(const CtPoint &atopLeft, const CtPoint &abottomRight) 
	: x1(atopLeft.x()), y1(atopLeft.y()), x2(abottomRight.x()), y2(abottomRight.y()) {}

inline CtRect::CtRect(const CtPoint &atopLeft, const CtSize &asize) 
	: x1(atopLeft.x()), y1(atopLeft.y()), x2(atopLeft.x() + asize.width() - 1), y2(atopLeft.y() + asize.height() - 1) {}

inline bool CtRect::isNull() const 
{
	return x2 == x1 - 1 && y2 == y1 - 1;
}

inline bool CtRect::isEmpty() const 
{
	return x1 > x2 || y1 > y2;
}

inline bool CtRect::isValid() const 
{
	return x1 <= x2 && y1 <= y2;
}

inline int CtRect::left() const 
{
	return x1;
}

inline int CtRect::top() const 
{
	return y1;
}

inline int CtRect::right() const 
{
	return x2;
}

inline int CtRect::bottom() const 
{
	return y2;
}

inline CtRect CtRect::normalized()
{
	int nTemp;
	if (x1 > x2)
	{
		nTemp = x1;
		x1 = x2;
		x2 = nTemp;
	}
	if (y1 > y2)
	{
		nTemp = y1;
		y1 = y2;
		y2 = nTemp;
	}
}

inline int CtRect::x() const 
{
	return x1;
}

inline int CtRect::y() const 
{
	return y1;
}

inline void CtRect::setLeft(int pos) 
{
	x1 = pos;
}

inline void CtRect::setTop(int pos) 
{
	y1 = pos;
}

inline void CtRect::setRight(int pos) 
{
	x2 = pos;
}

inline void CtRect::setBottom(int pos) 
{
	y2 = pos;
}

inline void CtRect::setTopLeft(const CtPoint &p) 
{
	x1 = p.x(); y1 = p.y();
}

inline void CtRect::setBottomRight(const CtPoint &p) 
{
	x2 = p.x(); y2 = p.y();
}

inline void CtRect::setTopRight(const CtPoint &p) 
{
	x2 = p.x(); y1 = p.y();
}

inline void CtRect::setBottomLeft(const CtPoint &p) 
{
	x1 = p.x(); y2 = p.y();
}

inline void CtRect::setX(int ax) 
{
	x1 = ax;
}

inline void CtRect::setY(int ay) 
{
	y1 = ay;
}

inline CtPoint CtRect::topLeft() const 
{
	return CtPoint(x1, y1);
}

inline CtPoint CtRect::bottomRight() const 
{
	return CtPoint(x2, y2);
}

inline CtPoint CtRect::topRight() const 
{
	return CtPoint(x2, y1);
}

inline CtPoint CtRect::bottomLeft() const 
{
	return CtPoint(x1, y2);
}

inline CtPoint CtRect::center() const 
{
	return CtPoint(int((ctint64(x1) + x2) / 2), int((ctint64(y1) + y2) / 2));
} // cast avoids overflow on addition

inline int CtRect::width() const 
{
	return  x2 - x1 + 1;
}

inline int CtRect::height() const 
{
	return  y2 - y1 + 1;
}

inline CtSize CtRect::size() const 
{
	return CtSize(width(), height());
}

inline void CtRect::translate(int dx, int dy) 
{
	x1 += dx;
	y1 += dy;
	x2 += dx;
	y2 += dy;
}

inline void CtRect::translate(const CtPoint &p) 
{
	x1 += p.x();
	y1 += p.y();
	x2 += p.x();
	y2 += p.y();
}

inline CtRect CtRect::translated(int dx, int dy) const 
{
	return CtRect(CtPoint(x1 + dx, y1 + dy), CtPoint(x2 + dx, y2 + dy));
}

inline CtRect CtRect::translated(const CtPoint &p) const 
{
	return CtRect(CtPoint(x1 + p.x(), y1 + p.y()), CtPoint(x2 + p.x(), y2 + p.y()));
}

inline CtRect CtRect::transposed() const 
{
	return CtRect(topLeft(), size().transposed());
}

inline void CtRect::moveTo(int ax, int ay) 
{
	x2 += ax - x1;
	y2 += ay - y1;
	x1 = ax;
	y1 = ay;
}

inline void CtRect::moveTo(const CtPoint &p) 
{
	x2 += p.x() - x1;
	y2 += p.y() - y1;
	x1 = p.x();
	y1 = p.y();
}

inline void CtRect::moveLeft(int pos) 
{
	x2 += (pos - x1); x1 = pos;
}

inline void CtRect::moveTop(int pos) 
{
	y2 += (pos - y1); y1 = pos;
}

inline void CtRect::moveRight(int pos) 
{
	x1 += (pos - x2);
	x2 = pos;
}

inline void CtRect::moveBottom(int pos) 
{
	y1 += (pos - y2);
	y2 = pos;
}

inline void CtRect::moveTopLeft(const CtPoint &p) 
{
	moveLeft(p.x());
	moveTop(p.y());
}

inline void CtRect::moveBottomRight(const CtPoint &p) 
{
	moveRight(p.x());
	moveBottom(p.y());
}

inline void CtRect::moveTopRight(const CtPoint &p) 
{
	moveRight(p.x());
	moveTop(p.y());
}

inline void CtRect::moveBottomLeft(const CtPoint &p) 
{
	moveLeft(p.x());
	moveBottom(p.y());
}

inline void CtRect::moveCenter(const CtPoint &p) 
{
	int w = x2 - x1;
	int h = y2 - y1;
	x1 = p.x() - w / 2;
	y1 = p.y() - h / 2;
	x2 = x1 + w;
	y2 = y1 + h;
}

inline void CtRect::getRect(int *ax, int *ay, int *aw, int *ah) const
{
	*ax = x1;
	*ay = y1;
	*aw = x2 - x1 + 1;
	*ah = y2 - y1 + 1;
}

inline void CtRect::setRect(int ax, int ay, int aw, int ah) 
{
	x1 = ax;
	y1 = ay;
	x2 = (ax + aw - 1);
	y2 = (ay + ah - 1);
}

inline void CtRect::getCoords(int *xp1, int *yp1, int *xp2, int *yp2) const
{
	*xp1 = x1;
	*yp1 = y1;
	*xp2 = x2;
	*yp2 = y2;
}

inline void CtRect::setCoords(int xp1, int yp1, int xp2, int yp2) 
{
	x1 = xp1;
	y1 = yp1;
	x2 = xp2;
	y2 = yp2;
}

inline CtRect CtRect::adjusted(int xp1, int yp1, int xp2, int yp2) const 
{
	return CtRect(CtPoint(x1 + xp1, y1 + yp1), CtPoint(x2 + xp2, y2 + yp2));
}

inline void CtRect::adjust(int dx1, int dy1, int dx2, int dy2) 
{
	x1 += dx1;
	y1 += dy1;
	x2 += dx2;
	y2 += dy2;
}

inline void CtRect::setWidth(int w) 
{
	x2 = (x1 + w - 1);
}

inline void CtRect::setHeight(int h) 
{
	y2 = (y1 + h - 1);
}

inline void CtRect::setSize(const CtSize &s) 
{
	x2 = (s.width() + x1 - 1);
	y2 = (s.height() + y1 - 1);
}

inline bool CtRect::contains(int ax, int ay, bool aproper) const 
{
	return contains(CtPoint(ax, ay), aproper);
}

inline bool CtRect::contains(int ax, int ay) const 
{
	return contains(CtPoint(ax, ay), false);
}

inline CtRect& CtRect::operator|=(const CtRect &r) 
{
	*this = *this | r;
	return *this;
}

inline CtRect& CtRect::operator&=(const CtRect &r) 
{
	*this = *this & r;
	return *this;
}

inline CtRect CtRect::intersected(const CtRect &other) const 
{
	return *this & other;
}

inline CtRect CtRect::united(const CtRect &r) const 
{
	return *this | r;
}

inline bool operator==(const CtRect &r1, const CtRect &r2) 
{
	return r1.x1 == r2.x1 && r1.x2 == r2.x2 && r1.y1 == r2.y1 && r1.y2 == r2.y2;
}

inline bool operator!=(const CtRect &r1, const CtRect &r2) 
{
	return r1.x1 != r2.x1 || r1.x2 != r2.x2 || r1.y1 != r2.y1 || r1.y2 != r2.y2;
}

inline CtRect operator+(const CtRect &rectangle, const CtMargins &margins) 
{
	return CtRect(CtPoint(rectangle.left() - margins.left(), rectangle.top() - margins.top()),
		CtPoint(rectangle.right() + margins.right(), rectangle.bottom() + margins.bottom()));
}

inline CtRect operator+(const CtMargins &margins, const CtRect &rectangle) 
{
	return CtRect(CtPoint(rectangle.left() - margins.left(), rectangle.top() - margins.top()),
		CtPoint(rectangle.right() + margins.right(), rectangle.bottom() + margins.bottom()));
}

inline CtRect operator-(const CtRect &lhs, const CtMargins &rhs) 
{
	return CtRect(CtPoint(lhs.left() + rhs.left(), lhs.top() + rhs.top()),
		CtPoint(lhs.right() - rhs.right(), lhs.bottom() - rhs.bottom()));
}

inline CtRect CtRect::marginsAdded(const CtMargins &margins) const 
{
	return CtRect(CtPoint(x1 - margins.left(), y1 - margins.top()),
		CtPoint(x2 + margins.right(), y2 + margins.bottom()));
}

inline CtRect CtRect::marginsRemoved(const CtMargins &margins) const 
{
	return CtRect(CtPoint(x1 + margins.left(), y1 + margins.top()),
		CtPoint(x2 - margins.right(), y2 - margins.bottom()));
}

inline CtRect &CtRect::operator+=(const CtMargins &margins) 
{
	*this = marginsAdded(margins);
	return *this;
}

inline CtRect &CtRect::operator-=(const CtMargins &margins) 
{
	*this = marginsRemoved(margins);
	return *this;
}

inline void CtRect::swapLeftRight() throw()
{
	swapLeftRight(this);
}

inline void CtRect::swapLeftRight(CtRect * lpRect) throw()
{
	if (!lpRect) return;

	long temp = lpRect->left();
	lpRect->setLeft(lpRect->right());
	lpRect->setRight(temp);
}

inline CtRect CtRect::mulDiv(int nMultiplier, int nDivisor) const throw()
{
	return CtRect(
		::MulDiv(left(), nMultiplier, nDivisor),
		::MulDiv(top(), nMultiplier, nDivisor),
		::MulDiv(right(), nMultiplier, nDivisor),
		::MulDiv(bottom(), nMultiplier, nDivisor));
}

//#ifndef QT_NO_DEBUG_STREAM
//Q_CORE_EXPORT QDebug operator<<(QDebug, const CtRect &);
//#endif
//

class CtRectF
{
public:
	CtRectF()  : xp(0.), yp(0.), w(0.), h(0.) {}
	CtRectF(const CtPointF &topleft, const CtSizeF &size);
	CtRectF(const CtPointF &topleft, const CtPointF &bottomRight);
	CtRectF(ctreal left, ctreal top, ctreal width, ctreal height);
	CtRectF(const CtRect &rect);

	inline bool isNull() const;
	inline bool isEmpty() const;
	inline bool isValid() const;
	CtRectF normalized() const;

	inline ctreal left() const  { return xp; }
	inline ctreal top() const  { return yp; }
	inline ctreal right() const  { return xp + w; }
	inline ctreal bottom() const  { return yp + h; }

	inline ctreal x() const;
	inline ctreal y() const;
	inline void setLeft(ctreal pos);
	inline void setTop(ctreal pos);
	inline void setRight(ctreal pos);
	inline void setBottom(ctreal pos);
	inline void setX(ctreal pos)  { setLeft(pos); }
	inline void setY(ctreal pos)  { setTop(pos); }

	inline CtPointF topLeft() const  { return CtPointF(xp, yp); }
	inline CtPointF bottomRight() const  { return CtPointF(xp + w, yp + h); }
	inline CtPointF topRight() const  { return CtPointF(xp + w, yp); }
	inline CtPointF bottomLeft() const  { return CtPointF(xp, yp + h); }
	inline CtPointF center() const;

	inline void setTopLeft(const CtPointF &p);
	inline void setBottomRight(const CtPointF &p);
	inline void setTopRight(const CtPointF &p);
	inline void setBottomLeft(const CtPointF &p);

	inline void moveLeft(ctreal pos);
	inline void moveTop(ctreal pos);
	inline void moveRight(ctreal pos);
	inline void moveBottom(ctreal pos);
	inline void moveTopLeft(const CtPointF &p);
	inline void moveBottomRight(const CtPointF &p);
	inline void moveTopRight(const CtPointF &p);
	inline void moveBottomLeft(const CtPointF &p);
	inline void moveCenter(const CtPointF &p);

	inline void translate(ctreal dx, ctreal dy);
	inline void translate(const CtPointF &p);

	inline CtRectF translated(ctreal dx, ctreal dy) const;
	inline CtRectF translated(const CtPointF &p) const;

	inline CtRectF transposed() const;

	inline void moveTo(ctreal x, ctreal y);
	inline void moveTo(const CtPointF &p);

	inline void setRect(ctreal x, ctreal y, ctreal w, ctreal h);
	inline void getRect(ctreal *x, ctreal *y, ctreal *w, ctreal *h) const;

	inline void setCoords(ctreal x1, ctreal y1, ctreal x2, ctreal y2);
	inline void getCoords(ctreal *x1, ctreal *y1, ctreal *x2, ctreal *y2) const;

	inline void adjust(ctreal x1, ctreal y1, ctreal x2, ctreal y2);
	inline CtRectF adjusted(ctreal x1, ctreal y1, ctreal x2, ctreal y2) const;

	inline CtSizeF size() const;
	inline ctreal width() const;
	inline ctreal height() const;
	inline void setWidth(ctreal w);
	inline void setHeight(ctreal h);
	inline void setSize(const CtSizeF &s);

	CtRectF operator|(const CtRectF &r) const;
	CtRectF operator&(const CtRectF &r) const;
	inline CtRectF& operator|=(const CtRectF &r);
	inline CtRectF& operator&=(const CtRectF &r);

	bool contains(const CtRectF &r) const;
	bool contains(const CtPointF &p) const;
	inline bool contains(ctreal x, ctreal y) const;
	inline CtRectF united(const CtRectF &other) const;
	inline CtRectF intersected(const CtRectF &other) const;
	bool intersects(const CtRectF &r) const;

	inline CtRectF marginsAdded(const CtMarginsF &margins) const;
	inline CtRectF marginsRemoved(const CtMarginsF &margins) const;
	inline CtRectF &operator+=(const CtMarginsF &margins);
	inline CtRectF &operator-=(const CtMarginsF &margins);

	friend inline bool operator==(const CtRectF &, const CtRectF &);
	friend inline bool operator!=(const CtRectF &, const CtRectF &);

	inline CtRect toRect() const;
	CtRect toAlignedRect() const;

private:
	ctreal xp;
	ctreal yp;
	ctreal w;
	ctreal h;
};
//Q_DECLARE_TYPEINFO(CtRectF, Q_MOVABLE_TYPE);

inline bool operator==(const CtRectF &, const CtRectF &);
inline bool operator!=(const CtRectF &, const CtRectF &);


/*****************************************************************************
CtRectF stream functions
*****************************************************************************/
//#ifndef QT_NO_DATASTREAM
//Q_CORE_EXPORT QDataStream &operator<<(QDataStream &, const CtRectF &);
//Q_CORE_EXPORT QDataStream &operator >> (QDataStream &, CtRectF &);
//#endif

/*****************************************************************************
CtRectF inline member functions
*****************************************************************************/

inline CtRectF::CtRectF(ctreal aleft, ctreal atop, ctreal awidth, ctreal aheight) 
	: xp(aleft), yp(atop), w(awidth), h(aheight)
{
}

inline CtRectF::CtRectF(const CtPointF &atopLeft, const CtSizeF &asize) 
	: xp(atopLeft.x()), yp(atopLeft.y()), w(asize.width()), h(asize.height())
{
}


inline CtRectF::CtRectF(const CtPointF &atopLeft, const CtPointF &abottomRight) 
	: xp(atopLeft.x()), yp(atopLeft.y()), w(abottomRight.x() - atopLeft.x()), h(abottomRight.y() - atopLeft.y())
{
}

inline CtRectF::CtRectF(const CtRect &r) 
	: xp((ctreal)r.x()), yp((ctreal)r.y()), w((ctreal)r.width()), h((ctreal)r.height())
{
}

inline bool CtRectF::isNull() const 
{
	return w == 0. && h == 0.;
}

inline bool CtRectF::isEmpty() const 
{
	return w <= 0. || h <= 0.;
}

inline bool CtRectF::isValid() const 
{
	return w > 0. && h > 0.;
}

inline ctreal CtRectF::x() const 
{
	return xp;
}

inline ctreal CtRectF::y() const 
{
	return yp;
}

inline void CtRectF::setLeft(ctreal pos) 
{
	ctreal diff = pos - xp; xp += diff; w -= diff;
}

inline void CtRectF::setRight(ctreal pos) 
{
	w = pos - xp;
}

inline void CtRectF::setTop(ctreal pos) 
{
	ctreal diff = pos - yp; yp += diff; h -= diff;
}

inline void CtRectF::setBottom(ctreal pos) 
{
	h = pos - yp;
}

inline void CtRectF::setTopLeft(const CtPointF &p) 
{
	setLeft(p.x()); setTop(p.y());
}

inline void CtRectF::setTopRight(const CtPointF &p) 
{
	setRight(p.x()); setTop(p.y());
}

inline void CtRectF::setBottomLeft(const CtPointF &p) 
{
	setLeft(p.x()); setBottom(p.y());
}

inline void CtRectF::setBottomRight(const CtPointF &p) 
{
	setRight(p.x()); setBottom(p.y());
}

inline CtPointF CtRectF::center() const 
{
	return CtPointF(xp + w / 2, yp + h / 2);
}

inline void CtRectF::moveLeft(ctreal pos) 
{
	xp = pos;
}

inline void CtRectF::moveTop(ctreal pos) 
{
	yp = pos;
}

inline void CtRectF::moveRight(ctreal pos) 
{
	xp = pos - w;
}

inline void CtRectF::moveBottom(ctreal pos) 
{
	yp = pos - h;
}

inline void CtRectF::moveTopLeft(const CtPointF &p) 
{
	moveLeft(p.x()); moveTop(p.y());
}

inline void CtRectF::moveTopRight(const CtPointF &p) 
{
	moveRight(p.x()); moveTop(p.y());
}

inline void CtRectF::moveBottomLeft(const CtPointF &p) 
{
	moveLeft(p.x()); moveBottom(p.y());
}

inline void CtRectF::moveBottomRight(const CtPointF &p) 
{
	moveRight(p.x()); moveBottom(p.y());
}

inline void CtRectF::moveCenter(const CtPointF &p) 
{
	xp = p.x() - w / 2; yp = p.y() - h / 2;
}

inline ctreal CtRectF::width() const 
{
	return w;
}

inline ctreal CtRectF::height() const 
{
	return h;
}

inline CtSizeF CtRectF::size() const 
{
	return CtSizeF(w, h);
}

inline void CtRectF::translate(ctreal dx, ctreal dy) 
{
	xp += dx;
	yp += dy;
}

inline void CtRectF::translate(const CtPointF &p) 
{
	xp += p.x();
	yp += p.y();
}

inline void CtRectF::moveTo(ctreal ax, ctreal ay) 
{
	xp = ax;
	yp = ay;
}

inline void CtRectF::moveTo(const CtPointF &p) 
{
	xp = p.x();
	yp = p.y();
}

inline CtRectF CtRectF::translated(ctreal dx, ctreal dy) const 
{
	return CtRectF(xp + dx, yp + dy, w, h);
}

inline CtRectF CtRectF::translated(const CtPointF &p) const 
{
	return CtRectF(xp + p.x(), yp + p.y(), w, h);
}

inline CtRectF CtRectF::transposed() const 
{
	return CtRectF(topLeft(), size().transposed());
}

inline void CtRectF::getRect(ctreal *ax, ctreal *ay, ctreal *aaw, ctreal *aah) const
{
	*ax = this->xp;
	*ay = this->yp;
	*aaw = this->w;
	*aah = this->h;
}

inline void CtRectF::setRect(ctreal ax, ctreal ay, ctreal aaw, ctreal aah) 
{
	this->xp = ax;
	this->yp = ay;
	this->w = aaw;
	this->h = aah;
}

inline void CtRectF::getCoords(ctreal *xp1, ctreal *yp1, ctreal *xp2, ctreal *yp2) const
{
	*xp1 = xp;
	*yp1 = yp;
	*xp2 = xp + w;
	*yp2 = yp + h;
}

inline void CtRectF::setCoords(ctreal xp1, ctreal yp1, ctreal xp2, ctreal yp2) 
{
	xp = xp1;
	yp = yp1;
	w = xp2 - xp1;
	h = yp2 - yp1;
}

inline void CtRectF::adjust(ctreal xp1, ctreal yp1, ctreal xp2, ctreal yp2) 
{
	xp += xp1; yp += yp1; w += xp2 - xp1; h += yp2 - yp1;
}

inline CtRectF CtRectF::adjusted(ctreal xp1, ctreal yp1, ctreal xp2, ctreal yp2) const 
{
	return CtRectF(xp + xp1, yp + yp1, w + xp2 - xp1, h + yp2 - yp1);
}

inline void CtRectF::setWidth(ctreal aw) 
{
	this->w = aw;
}

inline void CtRectF::setHeight(ctreal ah) 
{
	this->h = ah;
}

inline void CtRectF::setSize(const CtSizeF &s) 
{
	w = s.width();
	h = s.height();
}

inline bool CtRectF::contains(ctreal ax, ctreal ay) const 
{
	return contains(CtPointF(ax, ay));
}

inline CtRectF& CtRectF::operator|=(const CtRectF &r) 
{
	*this = *this | r;
	return *this;
}

inline CtRectF& CtRectF::operator&=(const CtRectF &r) 
{
	*this = *this & r;
	return *this;
}

inline CtRectF CtRectF::intersected(const CtRectF &r) const 
{
	return *this & r;
}

inline CtRectF CtRectF::united(const CtRectF &r) const 
{
	return *this | r;
}

inline bool operator==(const CtRectF &r1, const CtRectF &r2) 
{
	return cFuzzyCompare(r1.xp, r2.xp) && cFuzzyCompare(r1.yp, r2.yp)
		&& cFuzzyCompare(r1.w, r2.w) && cFuzzyCompare(r1.h, r2.h);
}

inline bool operator!=(const CtRectF &r1, const CtRectF &r2) 
{
	return !cFuzzyCompare(r1.xp, r2.xp) || !cFuzzyCompare(r1.yp, r2.yp)
		|| !cFuzzyCompare(r1.w, r2.w) || !cFuzzyCompare(r1.h, r2.h);
}

inline CtRect CtRectF::toRect() const 
{
	return CtRect((int)round(xp), (int)round(yp), (int)round(w), (int)round(h));
}

inline CtRectF operator+(const CtRectF &lhs, const CtMarginsF &rhs) 
{
	return CtRectF(CtPointF(lhs.left() - rhs.left(), lhs.top() - rhs.top()),
		CtSizeF(lhs.width() + rhs.left() + rhs.right(), lhs.height() + rhs.top() + rhs.bottom()));
}

inline CtRectF operator+(const CtMarginsF &lhs, const CtRectF &rhs) 
{
	return CtRectF(CtPointF(rhs.left() - lhs.left(), rhs.top() - lhs.top()),
		CtSizeF(rhs.width() + lhs.left() + lhs.right(), rhs.height() + lhs.top() + lhs.bottom()));
}

inline CtRectF operator-(const CtRectF &lhs, const CtMarginsF &rhs) 
{
	return CtRectF(CtPointF(lhs.left() + rhs.left(), lhs.top() + rhs.top()),
		CtSizeF(lhs.width() - rhs.left() - rhs.right(), lhs.height() - rhs.top() - rhs.bottom()));
}

inline CtRectF CtRectF::marginsAdded(const CtMarginsF &margins) const 
{
	return CtRectF(CtPointF(xp - margins.left(), yp - margins.top()),
		CtSizeF(w + margins.left() + margins.right(), h + margins.top() + margins.bottom()));
}

inline CtRectF CtRectF::marginsRemoved(const CtMarginsF &margins) const 
{
	return CtRectF(CtPointF(xp + margins.left(), yp + margins.top()),
		CtSizeF(w - margins.left() - margins.right(), h - margins.top() - margins.bottom()));
}

inline CtRectF &CtRectF::operator+=(const CtMarginsF &margins) 
{
	*this = marginsAdded(margins);
	return *this;
}

inline CtRectF &CtRectF::operator-=(const CtMarginsF &margins) 
{
	*this = marginsRemoved(margins);
	return *this;
}

//#ifndef QT_NO_DEBUG_STREAM
//Q_CORE_EXPORT QDebug operator<<(QDebug, const CtRectF &);
//#endif

#endif // CtRect_H
