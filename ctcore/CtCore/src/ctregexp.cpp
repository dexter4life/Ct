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

#include <ctcore/ctglobal.h>
#include <ctcore/ctregexp.h>
#include <ctcore/ctstring.h>

#ifdef DEBUG
#include <ctcore/ctdebug.h>
#endif // DEBUG

CtRegExp::CtRegExp(const CtString &s, PatternSyntax _Flag)
	:m_regPriv(s,_Flag)
{
}

CtRegExp::CtRegExp(const wchar *s, PatternSyntax _Flag)
	: m_regPriv(s, _Flag)
{
}

CtRegExp::CtRegExp(const wchar *s, size_t _count, PatternSyntax _Flag)
	: m_regPriv(s,_count,_Flag)
{
}

template<class _InIt>
CtRegExp::CtRegExp(_InIt beg, _InIt end, PatternSyntax _Flag)
	: m_regPriv(beg,end,_Flag)
{
}

CtRegExp::CtRegExp(std::initializer_list<wchar> &list, PatternSyntax _Flag)
	: m_regPriv(list,_Flag)
{
}
void CtRegExp::assign(const CtString &s, PatternSyntax _Flag)
{
	m_regPriv.assign(s, _Flag);
}
void CtRegExp::assign(const wchar *s, size_t _count, PatternSyntax _Flag)
{
	m_regPriv.assign(s, _count, _Flag);
}

CtString CtRegExp::pattern() const
{
	return m_regPriv.pattern();
}

void CtRegExp::setPattern(const CtString & pattern) {
	m_regPriv.setPattern(pattern);
}

Ct::CaseSensitivity CtRegExp::caseSensitivity() const
{
	return m_regPriv.caseSensitivity();
}

void CtRegExp::setCaseSensitivity(Ct::CaseSensitivity cs)
{
	m_regPriv.setCaseSensitivity(cs);
}

bool CtRegExp::exactMatch(const CtString & str) const
{
	return m_regPriv.exactMatch(str);
}
int CtRegExp::indexIn(const CtString & str, int offset) const
{
	return const_cast<CtRegExp*>(this)->indexIn(str, offset);
}
/*
Attempts to find a match in str from position offset (0 by default). If offset is -1,
the search starts at the last character; if -2, at the next to last character; etc.
*/
int CtRegExp::indexIn(const CtString & str, int offset)
{
	return m_regPriv.indexIn(str,offset);
}

//Returns the length of the last matched string, or -1 if there was no match.
int CtRegExp::matchedLength() const
{
	return m_regPriv.matchedLength();
}

int CtRegExp::lastMatchIn(const CtString &s, int offset) const
{
	return m_regPriv.lastMatchIn(s,offset);
}
bool CtRegExp::replace(CtString & s, const CtString &_rep, MatchType match_type) const
{
	return m_regPriv.replace(s,_rep, match_type);
}
MatchCapturedVector CtRegExp::tokenize(const CtString & s, int offset, MatchType match_type) const
{
	return m_regPriv.tokenize(s, offset, match_type);
}
//Returns the number of captures contained in the regular expression.
int CtRegExp::captureCount() const { return m_regPriv.captureCount(); }

//Returns a list of the captured text strings.
StringList CtRegExp::capturedTexts() const
{
	return m_regPriv.capturedTexts();
}

StringList CtRegExp::captureTexts(const CtString & str, MatchType match_type)
{
	return m_regPriv.captureTexts(str,match_type);
}
int CtRegExp::captureCount(const CtString & str) const
{
	return m_regPriv.captureCount(str);
}
//Returns the text captured by the nth subexpression.
CtString CtRegExp::cap(int nth) const
{
	return m_regPriv.cap(nth);
}

int CtRegExp::pos(int nth) const
{
	return m_regPriv.pos(nth);
}

void CtRegExp::setCaptureList(const CtString &s, MatchType match_type) const
{
	m_regPriv.setCaptureList(s, match_type);
}

//Returns the text captured by the nth subexpression.
CtString CtRegExp::cap(int nth)
{
	return m_regPriv.cap(nth);
}