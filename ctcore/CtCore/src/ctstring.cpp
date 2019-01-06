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

#include <cstdarg>
#include <cwctype>

#include <ctcore/ctstring.h>
#include <ctcore/ctglobal.h>
#include <CtCore/CtRegExp.h>


CtString CtString::tolower() const
{
	CtString _lowerstring = *this;
	std::transform(_lowerstring.begin(), _lowerstring.end(), _lowerstring.begin(), ::tolower);
	return _lowerstring;
}
CtString::CtString(const CtString & s) : std::wstring(s.c_str()) {}

std::wstring CtString::to_wstring(const std::string &s)
{
	std::wstringbuf buffer;
	std::wostream stream(&buffer);
	stream << s.c_str();

	return buffer.str();
}
CtString CtString::toupper() const
{
	CtString _upperstring = *this;
	std::transform(_upperstring.begin(), _upperstring.end(), _upperstring.begin(), ::toupper);
	return _upperstring;
}

int CtString::indexOf(wchar c, int from, Ct::CaseSensitivity cs) const
{
	//assume if not found
	size_t pos = std::wstring::npos;

	if (cs == Ct::CaseInsensitive) {
		if (std::iswupper(c) && std::iswalpha(c)) {
			wint_t lc = std::towlower(c);
			CtString tp = *this;
			std::transform(tp.begin(), tp.end(), tp.begin(), ::tolower);
			pos = tp.find(lc, (size_t)from);
			return pos;
		}
	}
	//everthing else goes here
	pos = this->find(c, (size_t)from);
	return (int)pos;
}

int CtString::indexOf(const CtString & s, int from, Ct::CaseSensitivity cs) const
{
	//assume if not found
	size_t pos = std::wstring::npos;
	if (cs == Ct::CaseInsensitive) {
		CtString tp = tolower(), ta = s.tolower();
		pos = tp.find(ta, (size_t)from);
		return pos;
	}
	pos = find(s, from);
	return pos;
}

int CtString::lastIndexOf(wchar c, int from, Ct::CaseSensitivity cs) const
{
	//assume if not found
	size_t pos = std::wstring::npos;

	if (cs == Ct::CaseInsensitive) {
		if (std::iswupper(c) && std::iswalpha(c)) {
			wint_t lc = std::towlower(c);
			CtString tp = *this;
			std::transform(tp.begin(), tp.end(), tp.begin(), ::tolower);
			pos = tp.find_last_of(lc, (size_t)from);
			return pos;
		}
	}
	//everthing else goes here
	pos = this->find_last_of(c, (size_t)from);
	return (int)pos;
}

int CtString::lastIndexOf(const CtString & s, int from, Ct::CaseSensitivity cs) const
{
	//assume if not found
	size_t pos = std::wstring::npos;
	if (cs == Ct::CaseInsensitive) {
		CtString tp = *this, ta = s;
		std::transform(tp.begin(), tp.end(), tp.begin(), ::tolower);
		std::transform(ta.begin(), ta.end(), ta.begin(), ::tolower);
		pos = tp.find_last_of(ta, (size_t)from);
		return pos;
	}
	pos = find_last_of(s, from);
	return pos;
}

bool CtString::contains(wchar c, Ct::CaseSensitivity cs) const
{
	int pos = indexOf(c, 0, cs);
	return (pos != std::string::npos);
}

bool CtString::contains(const CtString & s, Ct::CaseSensitivity cs) const
{
	int pos = indexOf(s, 0, cs);
	return (pos != std::string::npos);
}

int CtString::count(wchar c, Ct::CaseSensitivity cs) const
{
	int _count = 0;
	if (cs == Ct::CaseInsensitive) {
		if (std::iswupper(c) && std::iswalpha(c)) {
			wint_t lc = std::towlower(c);
			CtString ta = *this;
			std::transform(ta.begin(), ta.end(), ta.begin(), ::tolower);
			std::for_each(ta.begin(), ta.end(), [&](wchar ac) {
				if (ac == c) _count++;
			});
		}
		return _count;
	}
	std::for_each(begin(), end(), [&](wchar ac) {
		if (ac == c) _count++;
	});
	return _count;
}

int CtString::count(const CtString & s, Ct::CaseSensitivity cs) const
{
	// Get the first occurrence
	size_t pos = indexOf(s, 0, cs);

	int _count = 0;
	// Repeat till end is reached
	while (pos != std::string::npos)
	{
		// Add position to the vector
		_count++;
		// Get the next occurrence from the current position
		pos = indexOf(s, pos + s.size(), cs);
	}

	return _count;
}

int CtString::indexOf(const CtRegExp &ex, int from) const
{
	return ex.indexIn(*this, from);
}
//
//int String::lastIndexOf(const CtRegExp &exp, int from) const
//{
//	return exp.lastIndexIn(this->c_str(), from);
//}
//

int CtString::count(const CtRegExp &exp) const
{
	return exp.captureCount(*this);
}


CtString CtString::mid(int position, int offset) const
{
	return CtString(substr(position, offset));
}

bool CtString::replace(const CtRegExp & rex, const CtString & fmt, Ct::CaseSensitivity cs)
{
	//remove constness
	auto &_rex = const_cast<CtRegExp&>(rex);
	//set CaseSensitivity flag
	_rex.setCaseSensitivity(cs);

	return  _rex.replace(*this, fmt);
}

bool CtString::replace(const CtString & oldVal, const CtString & newVal, size_t _offset)
{
	return CtString::replace(*this, oldVal.c_str(), newVal.c_str(), _offset);
}

bool CtString::replace(const wchar_t *oldVal, const wchar_t *newVal, size_t _offset)
{
	return CtString::replace(*this, oldVal, newVal, _offset);
}

bool CtString::replaceAll(const wchar_t *oldVal, const wchar_t *newVal, size_t _offset)
{
	return CtString::replaceAll(*this, oldVal, newVal, _offset);
}

bool CtString::replaceAll(const CtString & oldVal, const CtString & newVal, size_t _offset)
{
	return CtString::replaceAll(*this, oldVal.c_str(), newVal.c_str(), _offset);
}

bool CtString::replace(std::wstring & buffer, const std::wstring & oldVal, const std::wstring & newVal, size_t _offset)
{
	int offset = -1;
	auto _begin = buffer.begin() + _offset;
	//find iterator 
	for (; _begin != buffer.end(); ++_begin) {
		offset = std::distance(buffer.begin() + _offset, _begin); //were we are
		if ((offset + oldVal.size()) < buffer.size()+1)
		{
			if (buffer.compare(offset, oldVal.size(), oldVal) == 0)
			{
				buffer.replace(_begin, _begin + oldVal.size(), newVal);
				break;
				return true;
			}
		}
	}
	return false;
}

bool CtString::replaceAll(std::wstring &buffer, const std::wstring &oldVal, const std::wstring &newVal, size_t _offset)
{
	bool _ret = replace(buffer, oldVal, newVal, _offset);
	//find more of oldVal
	if (buffer.find(oldVal) != npos) {
		return replaceAll(buffer,oldVal, newVal, _offset);
	}
	return false;
}

bool CtString::replace(const wchar_t oldVal, const wchar_t newVal, size_t offset)
{
	bool _found = false;
	for (auto _begin = std::next(begin(), offset); _begin != end(); ++_begin)
		if (*_begin == oldVal) {
			*_begin = newVal;
			_found = true;
		}
	return _found;
}
CtString CtString::format(CtString fmt, ...)
{
	va_list _vArgList;
	va_start(_vArgList, fmt);
	CtString _result(size_t(1 + std::vswprintf(NULL, 0, fmt.c_str(), _vArgList)));
	std::vswprintf(const_cast<wchar_t*const>(_result.data()), _result.size(), fmt.c_str(), _vArgList);
	va_end(_vArgList);
	return CtString(_result.c_str());
}
void CtString::append(CtString fmt, ...)
{
	va_list _vlArg;
	va_start(_vlArg, fmt);
	std::wstring::append(format(fmt, _vlArg));
	va_end(_vlArg);
}

bool CtString::isequal(const CtString & right, Ct::CaseSensitivity cs)
{
	//self comparison true always
	if (this == &right) return true;
	switch (cs) {
	case Ct::CaseInsensitive:
		return (right.size() == size() && std::equal(begin(), end(), right.begin(), [&](auto _first, auto _second) {
			if (std::towlower(_first) != std::towlower(_second)) return false;
			return true;
		}));
		break;
	case Ct::CaseSensitive:
		return (right.size() == size() && std::equal(begin(), end(), right.begin(), std::equal_to<CtString::value_type>()));
		break;
	}
	return true;
}

int CtString::compare_l(const CtString & Input, const std::locale &loc)
{
	const std::collate<wchar>& coll = std::use_facet<std::collate<wchar> >(loc);
	auto _ptrFirst = Input.data();
	auto _ptrSecond = data();
	return coll.compare(_ptrFirst, _ptrFirst + Input.size(), _ptrSecond, _ptrSecond + size());
}

void CtString::trim(int offset)
{
	trim_right(*this);
	trim_left(*this, offset);
}

//Search string for substring. 
//Elements are compared case insensitively.
//\param Test A test sequence
//\param Loc A locale used for case insensitive comparison
//\return The result of the test
//
//\note This function provides the strong exception-safety guarantee
//*/

bool CtString::contains_l(const CtString & Test, const std::locale & Loc)
{
	auto& f = std::use_facet<std::collate<CtString::value_type>>(loc);
	auto _ItBegin = begin();
	for (; _ItBegin != end(); ++_ItBegin) {
		int offset = std::distance(begin(), _ItBegin);
		//messure to Test string
		auto _last1 = (c_str() + offset) + Test.length();
		//0 is equal
		if (f.compare(c_str() + offset, _last1, Test.c_str(),
			Test.c_str() + Test.length()) == 0) {
			return true;
		}
	}
	return false;
}
/*
//This predicate holds when the test string is a suffix of the Input.
//In other words, if the input ends with the test.
//When the optional predicate is specified, it is used for character-wise
//comparison.
//
//
//\param	Input An input sequence
//\param	Test A test sequence
//\param	loc An element of locale
//\return	The result of the test
*/

bool CtString::ends_with(const CtString & Input, const CtString & Test, const std::locale & loc)
{
	const_reverse_iterator InputEnd = Input.rend();
	const_reverse_iterator TestEnd = Test.rend();

	const_reverse_iterator it = Input.rbegin();
	const_reverse_iterator pit = Test.rbegin();

	for (;
		it != InputEnd && pit != TestEnd;
		++it, ++pit)
	{
		if (!(isequal_l(*it, *pit, loc)))
			return false;
	}

	return pit == TestEnd;
}

bool CtString::isequal_l(CtString::value_type input, CtString::value_type test, const std::locale & loc)
{
	auto &fset = std::use_facet<std::collate<CtString::value_type>>(loc);
	if (fset.compare(&input, &input + 1, &test, &test + 1) == 0)
		return true;

	return false;
}

/*
//This predicate holds when the test string is a prefix of the Input.
//In other words, if the input starts with the test.
//When the optional predicate is specified, it is used for character-wise
//comparison.
//
//\param Input An input sequence
//\param Test A test sequence
//\param Comp An element comparison predicate
//\return The result of the test
*/

bool CtString::starts_with(const CtString & Input, const CtString & Test, const std::locale & loc)
{
	const_iterator InputEnd = Input.end();
	const_iterator TestEnd = Test.end();

	const_iterator it = Input.begin();
	const_iterator pit = Test.begin();
	for (;
		it != InputEnd && pit != TestEnd;
		++it, ++pit)
	{
		if (!(isequal_l(*it, *pit, loc)))
			return false;
	}

	return pit == TestEnd;
}

inline CtString::iterator CtString::trim_begin(iterator InBegin, iterator InEnd)
{
	iterator It = InBegin;
	for (; It != InEnd; ++It)
		if (!IsSpace(*It))
			return It;
	return It;
}

inline CtString::iterator CtString::trim_end(iterator InBegin, iterator InEnd)
{
	int _len = std::distance(InBegin, InEnd) - 1;
	auto rIt = rbegin();
	auto It = begin();
	for (; rIt != rend(); ++rIt, --_len) {
		if (!IsSpace(*rIt)) {
			It = (begin() + _len);
			break;
		}
	}
	return It;
}

size_t CtString::actualSize() const
{
	return std::wstring::size() + sizeof(loc);
}
