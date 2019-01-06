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
#ifndef CT_REG_EXP_H
#define CT_REG_EXP_H


#include <ctcore/ctregexpprivate.h>
#include <ctcore/ctutilitydef.h>

class CtRegExp 
{
public:
	typedef CtRegExpPrivate::RegExpType RegExpType;
	
	CT_DECLARE_FLAGS(PatternSyntax, std::wregex::flag_type)
	CT_DECLARE_FLAGS(MatchType, std::regex_constants::match_flag_type)
	
	~CtRegExp() {};

	explicit CtRegExp(const CtString &s, PatternSyntax _Flag = PatternSyntax::enum_type::ECMAScript);

	explicit CtRegExp(const wchar *s, PatternSyntax _Flag = PatternSyntax::enum_type::ECMAScript);

	explicit CtRegExp(const wchar *s, size_t _count, PatternSyntax _Flag = PatternSyntax::enum_type::ECMAScript);

	template<class _InIt> CtRegExp(_InIt beg, _InIt end, PatternSyntax _Flag = PatternSyntax::enum_type::ECMAScript);

	explicit CtRegExp(std::initializer_list<wchar>&, PatternSyntax _Flag = PatternSyntax::enum_type::ECMAScript);

	void assign(const CtString & s, PatternSyntax _Flag);

	void assign(const wchar * s, size_t _count, PatternSyntax _Flag);

	operator RegExpType() { return m_regPriv.m_wregex; }

	CtRegExp & CtRegExp::operator=(CtRegExp && other)
	{
		//assignment to self is not a valid operation so return
		if (this == &other) return *this;

		//use the parent assignment operator instead
		m_regPriv.assign(other.pattern(), m_regPriv.patternSyntax());

		return *this;
	}

	bool CtRegExp::operator==(const CtRegExp & rx) const
	{
		if (this == &rx && pattern() == rx.pattern()) return true;
		return false;
	}

	bool isEmpty() const { return m_regPriv.isEmpty(); }
	bool isValid() const { return m_regPriv.isValid(); }


	CtString pattern() const;
	void setPattern(const CtString &pattern);

	Ct::CaseSensitivity caseSensitivity() const;
	void setCaseSensitivity(Ct::CaseSensitivity cs);

	PatternSyntax patternSyntax() const { return m_regPriv.patternSyntax(); };
	void setPatternSyntax(PatternSyntax syntax) { m_regPriv.setPatternSyntax(syntax); };

	bool exactMatch(const CtString &str) const;
	int indexIn(const CtString &str, int offset = 0) const;

	StringList captureTexts(const CtString &str, MatchType match_type = MatchType::enum_type::match_default);

	int captureCount(const CtString & str) const;

	/*last match substring in a string*/
	int lastMatchIn(const CtString & s, int offset = 0) const;

	bool replace(CtString & s, const CtString& _rep, MatchType match_type = MatchType::enum_type::match_default) const;

	MatchCapturedVector tokenize(const CtString & s, int offset = 0,
		MatchType match_type = std::regex_constants::match_default) const;

	int matchedLength() const;

	void setCaptureList(const CtString &s, MatchType match_type = MatchType::enum_type::match_default) const;

#ifndef NO_REGEXP_CAPTURE
	int captureCount() const;;

	StringList capturedTexts() const;
	StringList capturedTexts();

	CtString cap(int nth = 0) const;
	CtString cap(int nth = 0);

	int pos(int nth = 0) const;
	int pos(int nth = 0);
#endif
private:
	//in case of no constnest 
	int indexIn(const CtString &str, int offset = 0);

	CtRegExpPrivate m_regPriv;
};


#endif // !CT_REG_EXP_H


