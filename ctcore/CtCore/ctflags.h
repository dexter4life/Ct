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
#include <cstdint>
#include <cstdint>

template<typename Enum>
class CtFlags
{
public:
	enum Direction
	{
		DR_LEFT,
		DR_RIGHT,
		DR_NONE
	};

	typedef Enum enum_type;
	typedef uint32_t  Int;

	 inline CtFlags(Enum f) : i(uint32_t(f)) {}
	 inline CtFlags() : i(0) {}
	 inline CtFlags(uint32_t f) : i(f) {}

	 inline CtFlags &operator=(int mask) { i = mask; return *this; }
	 inline CtFlags &operator&=(int mask) { i &= mask; return *this; }
	 inline CtFlags &operator&=(uint32_t mask) { i &= mask; return *this; }
	 inline CtFlags &operator&=(Enum mask) { i &= Int(mask); return *this; }
	 inline CtFlags &operator|=(CtFlags f) { i |= f.i; return *this; }
	 inline CtFlags &operator|=(Enum f) { i |= Int(f); return *this; }
	 inline CtFlags &operator^=(CtFlags f) { i ^= f.i; return *this; }
	 inline CtFlags &operator^=(Enum f) { i ^= Int(f); return *this; }
	 inline		   operator Enum() { return Enum(i); }

	 inline operator Int() const { return i; }

	 inline CtFlags operator|(CtFlags f) const { return CtFlags(QFlag(i | f.i)); }
	 inline CtFlags operator|(Enum f) const { return CtFlags(QFlag(i | Int(f))); }
	 inline CtFlags operator^(CtFlags f) const { return CtFlags(QFlag(i ^ f.i)); }
	 inline CtFlags operator^(Enum f) const { return CtFlags(QFlag(i ^ Int(f))); }
	 inline CtFlags operator&(int mask) const { return CtFlags(QFlag(i & mask)); }
	 inline CtFlags operator&(uint32_t mask) const { return CtFlags(QFlag(i & mask)); }
	 inline CtFlags operator&(Enum f) const { return CtFlags(QFlag(i & Int(f))); }
	 inline CtFlags operator~() const { return CtFlags(QFlag(~i)); }
	
	 inline bool operator!() const { return !i; }

	 inline bool testFlag(Enum f) const { return (i & Int(f)) == Int(f) && (Int(f) != 0 || i == Int(f)); }
	 inline CtFlags &setFlag(Enum f, bool on = true)
	{
		return on ? (*this |= f) : (*this &= ~f);
	}

	 inline void setDirection(Direction d) { m_direction = d; }
	 inline int	direction() const { return m_direction; }
private:
	uint32_t i;
	Direction m_direction;
};