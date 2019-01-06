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

#ifndef UTILITY_DEF_H
#define UTILITY_DEF_H

#include <utility>

#ifndef _T
#define _T(s) L##s
#endif

#include <string>
#include <String>
#include <cstdint>
#include <algorithm>

static std::wstring to_wstring(std::string s) {
	std::wstring t(s.length(), _T(' '));
	std::copy(s.begin(), s.end(), t.begin());
	return t;
}

static inline bool isNull(float f)
{
	union U {
		float f;
		uint32_t u;
	};
	U val;
	val.f = f;
	return (val.u & 0x7fffffff) == 0;
}

static inline bool fuzzyIsNull(float f)
{
	return abs(f) <= 0.00001f;
}


#endif //UTILITY_DEF_H