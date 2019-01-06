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

#ifndef REG_EXP_PRIVATE_H
#define REG_EXP_PRIVATE_H

#include <algorithm>
#include <iterator>
#include <regex>
#include <vector>

#include <ctcore/ctglobal.h>
#include <ctcore/ctstring.h>

struct MatchCaptured {
	int position;
	std::wstring str;
};

typedef std::vector<MatchCaptured> MatchCapturedVector;

class CtRegExpPrivate
{	
	friend class CtRegExp;

	CT_DECLARE_FLAGS(PatternSyntax, std::wregex::flag_type)
	CT_DECLARE_FLAGS(MatchType, std::regex_constants::match_flag_type)

	typedef std::regex_constants::syntax_option_type regex_constants;
	typedef regex_constants flag_type;
	typedef typename std::iterator<std::input_iterator_tag, wchar_t> iterator;
	typedef std::regex_iterator<std::wstring::const_reverse_iterator> wsregex_rev_iterator;
	
	typedef std::basic_regex<wchar>	RegExpType;
	typedef wchar_t wchar;

	int m_last_mat, m_last_offset;
	CtString  *m_pattern, *m_pArgString;
	StringList m_capturedStringList;
	Ct::CaseSensitivity m_caseSensitive;
	mutable int m_matchPos;
	std::wsregex_iterator begin_iter;
	std::wsregex_iterator end_iter;

	PatternSyntax m_patternSyntax;

	std::wregex  m_wregex;
	bool m_invalidRegExpSyntax;
	
	static constexpr flag_type icase = regex_constants::icase;
	static constexpr flag_type nosubs = regex_constants::nosubs;
	static constexpr flag_type optimize = regex_constants::optimize;
	static constexpr flag_type collate = regex_constants::collate;
	static constexpr flag_type ECMAScript = regex_constants::ECMAScript;
	static constexpr flag_type basic = regex_constants::basic;
	static constexpr flag_type extended = regex_constants::extended;
	static constexpr flag_type awk = regex_constants::awk;
	static constexpr flag_type grep = regex_constants::grep;
	static constexpr flag_type egrep = regex_constants::egrep;


	Ct::CaseSensitivity caseSensitivity() const;
	bool exactMatch(const CtString & str) const;
	void setCaseSensitivity(Ct::CaseSensitivity cs);
	
	PatternSyntax patternSyntax() const { return m_patternSyntax; };
	void setPatternSyntax(PatternSyntax syntax) { m_patternSyntax = syntax; };

	CtString pattern() const
	{
		return *m_pattern;
	}

	void setPattern(const CtString & pattern) {
		*m_pattern = pattern;
	}

	CtRegExpPrivate(const CtString &s, PatternSyntax _Flag);
	CtRegExpPrivate(const wchar *s, PatternSyntax _Flag);

	CtRegExpPrivate(const wchar *s, size_t _count, PatternSyntax _Flag);

	template<class _InIt>
	CtRegExpPrivate(_InIt beg, _InIt end, PatternSyntax _Flag);

	CtRegExpPrivate(std::initializer_list<wchar> &list, PatternSyntax _Flag);

	void assign(const CtString &s, PatternSyntax _Flag);
	
	void assign(const wchar *s, size_t _count, PatternSyntax _Flag);
	
	inline bool isEmpty() const { return m_wregex._Empty(); }
	inline bool isValid() const { return !m_invalidRegExpSyntax; }

	StringList captureTexts(const CtString &str, MatchType match_type = MatchType::enum_type::match_default);

	int captureCount(const CtString & str) const;

	/*last match substring in a string*/
	int lastMatchIn(const CtString & s, int offset = 0) const;

	bool replace(CtString & s, const CtString& _rep, MatchType match_type = MatchType::enum_type::match_default) const;

	MatchCapturedVector tokenize(const CtString & s, int offset = 0,
		MatchType match_type = std::regex_constants::match_default) const;

	int indexIn(const CtString & str, int offset);
	inline int indexIn(const CtString & str, int offset) const;

	int matchedLength() const;

	inline CtString errorMessage() const { return m_errorType; }
	inline int	errorCode() const { return m_errorCode; }

#ifndef NO_REGEXP_CAPTURE
	int captureCount() const;;

	StringList capturedTexts() const;
	StringList capturedTexts();

	CtString cap(int nth = 0) const;
	CtString cap(int nth = 0);

	int pos(int nth = 0) const;
	int pos(int nth = 0);
	void setCaptureList(const CtString &s, MatchType match_type = MatchType::enum_type::match_default) const;
#endif

private:
	DISABLE_COPY(CtRegExpPrivate)
	CtString	m_errorType;
	int		m_errorCode;
};
#endif // !REG_EXP_PRIVATE_H

