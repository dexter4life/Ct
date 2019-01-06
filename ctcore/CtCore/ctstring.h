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

#ifndef CT_STRING_H
#define CT_STRING_H

#include <string>
#include <iosfwd>
#include <map>
#include <string>
#include <locale>
#include <codecvt>
#include <iostream>
#include <cassert>
#include <algorithm>
#include <clocale>
#include <sstream>
#include <vector>

#include <ctcore/ctutilitydef.h>
#include <ctcore/ctglobal.h>

#ifdef WIN32
#include <xutility>
#endif

#ifdef _MSC_VER 
#if !(_MSC_VER > 1800) 
#error compiler version is lesser than required.  
#endif
#endif

#define IsSpace(c) std::isspace(c,loc)

class CtRegExp;
using std::char_traits;
using std::allocator;

class CtString : public std::wstring
{
	friend static const std::wostream& operator<<(std::wostream &wo, const CtString &s) {
		wo << std::wstring(s.c_str());
		return wo;
	}
	friend static std::ostream& operator<<(std::ostream &wo, const CtString &s) {
		std::wstring_convert<std::codecvt_utf8<wchar_t>> conv1;
		std::string u8str = conv1.to_bytes(s);
		wo << u8str;
		return wo;
	}
	friend static CtString & operator+(char* wsz, CtString &s)
	{
		s.append_left(wsz);
		return s;
	}

public:

	typedef typename std::wstring std_string_type;
	typedef typename std::string std_cstring_type;
	typedef const wchar_t * _wchar_t;
	typedef const char * _char_t;
	typedef uint32_t uint;

	CtString() {};
	~CtString() { clear(); };

	CtString(const CtString &s);

	CtString(const std::wstring &s) : std::wstring(s) {}

	CtString(const std::string &s)
	{
		//assign(to_wstring(s));
	}
	CtString(const char *s)
	{
		assign(to_wstring(s));
	}

	CtString(size_t _bufferCount, wchar_t c = L' ')
	{
		resize(_bufferCount);
		std::fill(begin(), end(), c);
	}

	CtString(const_iterator _first, const_iterator _last)
	{
		assign(_first, _last);
	}

	//return wide-character 
	inline operator std_string_type ()
	{
		return std_string_type(c_str());
	}
	//return multi-byte charactor
	inline operator std_cstring_type()
	{
		std::setlocale(LC_ALL, loc.c_str());
		std_cstring_type _result;

#ifdef _MSC_VER 
		//	std::wstring ws = *this;
		std::for_each(begin(), end(), [&](const wchar_t wc) {
			int ret = 0;
			char ch;
			wctomb_s(&ret, &ch, sizeof(char), wc);
			_result.push_back(ch);
		});
#else
	std:wcstombs(const_cast<char*>(_result.data()), c_str(), length());
#endif
		return _result;
	}
	//make wchar_t *
	inline operator _wchar_t()
	{
		return c_str();
	}

	//convert wchar_t default type to char type by cast operator
	inline operator _char_t()
	{
		static std::string s = *this;
		return s.c_str();
	}

	void CtString::operator=(const CtString s)
	{
		assign(s.c_str());
	}

	static std::wstring to_wstring(const std::string &s);

	CtString tolower() const;
	CtString toupper() const;

	int indexOf(wchar c, int from = 0, Ct::CaseSensitivity cs = Ct::CaseSensitive) const;
	int indexOf(const CtString &s, int from = 0, Ct::CaseSensitivity cs = Ct::CaseSensitive) const;

	int lastIndexOf(wchar c, int from = -1, Ct::CaseSensitivity cs = Ct::CaseSensitive) const;
	int lastIndexOf(const CtString &s, int from = -1, Ct::CaseSensitivity cs = Ct::CaseSensitive) const;

	bool contains(wchar c, Ct::CaseSensitivity cs = Ct::CaseSensitive) const;
	bool contains(const CtString &s, Ct::CaseSensitivity cs = Ct::CaseSensitive) const;
	inline bool contains(const CtRegExp &rx) const { return indexOf(rx) != -1; }

	int count(wchar c, Ct::CaseSensitivity cs = Ct::CaseSensitive) const;
	int count(const CtString &, Ct::CaseSensitivity cs = Ct::CaseSensitive) const;
	int count(const CtRegExp &rex) const;


	int indexOf(const CtRegExp &rex, int from = 0) const;

	/*
	lastIndexOf(String str) : This method accepts a String as an argument,
	if the string argument occurs one or more times as a substring within this object,
	then the index of the first character of the last such substring is returned.
	If it does not occur as a substring, -1 is returned.
	*/
	//int lastIndexOf(const RegExp &rex, int from = -1, int count = 0) const;

	CtString mid(int position, int offset = -1) const;

	/*
	//!  replace
	// Replace substring that match regular expression 'rex
	// rex Regular Expression
	// fmt Formating string or replacement string
	// cs  Case sensitivity flags ( case-sensitive or insentive)
	*/
	bool replace(const CtRegExp &rex, const CtString &fmt, Ct::CaseSensitivity cs = Ct::CaseSensitive);
	bool replace(const CtString & oldVal, const CtString & newVal, size_t _offset = 0);
	bool replace(const wchar_t oldVal, const wchar_t newVal, size_t offset = 0);
	bool replace(const wchar_t *oldVal, const wchar_t *newVal, size_t _offset = 0);
	static bool replace(std::wstring &buffer, const std::wstring &oldVal, const std::wstring &newVal, size_t _offset = 0);
	//!  replace all occurence 
	static bool replaceAll(std::wstring &buffer, const std::wstring &oldVal, const std::wstring &newVal, size_t _offset = 0);
	bool replaceAll(const wchar_t * oldVal, const wchar_t * newVal, size_t _offset = 0);
	bool replaceAll(const CtString & oldVal, const CtString & newVal, size_t _offset = 0);
	/*
	//! formatString
	// Format string into string object
	// s Formatting string
	// returns new formated string
	*/
	static CtString format(CtString fmt, ...);
	void	 append(CtString fmt, ...);

	//compare in case sensitivity
	bool isequal(const CtString & right, Ct::CaseSensitivity cs = Ct::CaseSensitive);

	//compare locale
	int compare_l(const CtString & Input, const std::locale &loc = std::locale());

	/*
	Trim
	Remove all leading and trailing spaces from the input.
	The input sequence is modified in-place.

	\param offset Starting position from left to right
	*/
	void	 trim(int offset = 0);

	/* contains_l
	//Search string for matching substring.
	//Elements are compared case sensitively.
	//\param Test A test sequence
	//\param Loc A locale used for case insensitive comparison
	//\return The result of the test
	*/
	bool contains_l(
		const CtString& Test,
		const std::locale& Loc = std::locale());
	inline void trim_right(CtString & Input, int offset = 0)
	{
		Input.erase(trim_end(Input.begin(), std::prev(Input.end(), offset)), Input.end());
	}

	/*!
	Remove all leading spaces from the input.

	\param Input An input sequence
	\param IsSpace A unary predicate identifying spaces
	*/
	inline void trim_left(CtString &Input, int offset = 0)
	{
		Input.erase(std::next(Input.begin(), offset), trim_begin(Input.begin(), Input.end()));
	}

	/*
	//! is_equal
	//  Check if two characters are equal based on locale
	//\param offset An input character from String object
	//\test character to compare
	//\loc locale to use or default is taken
	*/
	bool isequal_l(int offset, CtString::value_type test,
		const std::locale &loc = std::locale())
	{
		return isequal_l(at(offset), test, loc);
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
	inline bool starts_with(
		const CtString& Test,
		const std::locale &loc = std::locale())
	{
		return starts_with(*this, Test, loc);
	}

	/*
	//This predicate holds when the test string is a prefix of the Input.
	//In other words, if the input starts with the test.
	//When the optional predicate is specified, it is used for character-wise
	//comparison.
	//
	//\param Input An input sequence
	//\param Test A test sequence
	//\param loc An locale element
	//\return The result of the test
	*/
	bool starts_with(
		const CtString& Input,
		const CtString& Test,
		const std::locale &loc = std::locale());

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
	bool ends_with(
		const CtString& Input,
		const CtString& Test,
		const std::locale &loc = std::locale());

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

	inline bool ends_with(
		const CtString& Test,
		const std::locale &loc = std::locale())
	{
		return ends_with(*this, Test, loc);
	}
	/*
	//! is_equal
	//  Check if two characters are equal based on locale
	*/
	bool isequal_l(CtString::value_type input,
		CtString::value_type test, const std::locale &loc = std::locale());


	/*
	//! Reverse string
	*/
	void reverse()
	{
		CtString resultant(size());
		std::reverse_copy(begin(), end(), resultant.begin());
		assign(resultant);
	}

	/*
	*/
	void append_left(const CtString &s)
	{
		CtString &sRef = const_cast<CtString&>(s);
		sRef.append(*this);
		assign(sRef);
	}

	size_t actualSize() const;
	/*
	*Find all positions of the a SubString in given String
	*/
	std::vector<size_t> findAll(const CtString& toSearch)
	{
		std::vector<size_t> pos_vect;
		// Get the first occurrence
		size_t pos = indexOf(toSearch);

		// Repeat till end is reached
		while (pos != npos)
		{
			// Add position to the vector
			pos_vect.push_back(pos);

			// Get the next occurrence from the current position
			pos = indexOf(toSearch, pos + toSearch.size());
		}

		return pos_vect;
	}

	/*Convert integer data to string*/
	// convert long long to String
	static inline CtString to_string(long long _Val)
	{	
		return (std::to_wstring(_Val));
	}
	// convert long double to String
	static inline CtString to_wstring(long double _Val)
	{	
		return (std::to_wstring(_Val));
	}

private:

	// Search for first non matching character from the beginning of the sequence
	inline iterator trim_begin(
		iterator InBegin,
		iterator InEnd);

	// Search for first non matching character from the end of the sequence
	inline iterator trim_end(
		iterator InBegin,
		iterator InEnd);

	//void     Truncate(int nNewLength);
	std::locale loc;
	int m_singleCharSize;
};

// string list container
#ifndef STRING_LIST
#include <vector>
typedef std::vector<CtString> StringList;

//display to output stream
static std::wostream& operator<<(std::wostream &wo, const StringList &stringList)
{
	wo << CtString("{");
	size_t i = 0;
	for (const CtString &is : stringList) {
		wo << is;
		if (i++ < stringList.size() - 1) wo << ",";
	}
	wo << CtString("}");
	return wo;
}

typedef std::vector<std::wstring> wstring_list;
static void insert_item(StringList& list, const wstring_list &item_list)
{
	std::for_each(item_list.begin(), item_list.end(), [&](auto item) {
		list.push_back(CtString(item));
	});
}
//insertion operator 
static StringList &operator<<(StringList &stringList, const CtString &str) {
	stringList.push_back(str);
	return stringList;
}


#endif // !STRING_LIST

#endif // !STRING_H
