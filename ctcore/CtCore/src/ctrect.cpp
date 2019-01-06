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

#include <ctcore/ctrect.h>

bool CtRect::contains(const CtRect & r, bool proper) const
{
	if (proper) {
		return (r.left() > left() && r.top() > top() && r.right() < right() && r.bottom() < bottom());
	}
	return (r.left() >= left() && r.top() >= top() && r.right() <= right() && r.bottom() <= bottom());
}

bool CtRect::contains(const CtPoint & p, bool proper) const
{
	if (proper)
		return (p.x() > left() && p.y() > top() && p.x() < right() && p.y() < bottom());
	
	return (p.x() >= left() && p.y() >= top() && p.x() <= right() && p.y() <= bottom());
}

inline CtRect CtRect::operator|(const CtRect & r) const
{
	return CtRect();
}

CtRect CtRect::operator&(const CtRect & r) const
{
	return CtRect();
}


bool CtRect::intersects(const CtRect & r) const
{
	return false;
}
CtRectF CtRectF::normalized() const
{
	return CtRectF();
}