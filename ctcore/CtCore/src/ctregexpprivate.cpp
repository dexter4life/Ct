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

#include <ctcore/ctregexpprivate.h>

Ct::CaseSensitivity CtRegExpPrivate::caseSensitivity() const
{
	return m_caseSensitive;
}

template<class _InIt>
CtRegExpPrivate::CtRegExpPrivate(_InIt beg, _InIt end, PatternSyntax _Flag)
	: m_pattern(new CtString()), m_last_mat(0), m_flag(_Flag)
{
	try
	{
		m_wregex = std::wregex(beg, end, _Flag);
	}
	catch (std::regex_error &e)
	{
		m_invalidRegExpSyntax = true;
		m_errorType = e.what();
		m_errorCode = e.code();
		return;//leave here if we got exception
	}
	//if everything went well, here is false
	m_invalidRegExpSyntax = false;

	std::copy(beg, end, m_pattern.begin());
}

bool CtRegExpPrivate::exactMatch(const CtString & str) const
{
	return std::regex_match(str, m_wregex);
}

void CtRegExpPrivate::setCaseSensitivity(Ct::CaseSensitivity cs)
{
	switch (cs) {
	case Ct::CaseInsensitive:
		m_patternSyntax = icase | ECMAScript;
		m_wregex = std::wregex(pattern(), m_patternSyntax);
		break;
	case Ct::CaseSensitive:
		m_wregex = std::wregex(pattern(), ECMAScript);
		m_patternSyntax = ECMAScript;
		break;
	}
}

CtRegExpPrivate::CtRegExpPrivate(const CtString & s, PatternSyntax _Flag)
	: m_pattern(new CtString(s)), m_last_mat(0), m_patternSyntax(_Flag)
{
	try
	{
		m_wregex = std::wregex(s, _Flag);
	}
	catch (std::regex_error &e)
	{
		m_invalidRegExpSyntax = true;
		m_errorType = e.what();
		m_errorCode = e.code();
		return;//leave here if we got exception
	}

	//if everything went well, here is false
	m_invalidRegExpSyntax = false;
}

CtRegExpPrivate::CtRegExpPrivate(const wchar * s, PatternSyntax _Flag)
	: m_pattern(new CtString(s)), m_last_mat(0), m_patternSyntax(_Flag)
{
	try
	{
		m_wregex = std::wregex(s, _Flag);
	}
	catch (std::regex_error &e)
	{
		m_invalidRegExpSyntax = true;
		m_errorType = e.what();
		m_errorCode = e.code();
		return;//leave here if we got exception
	}
	//if everything went well, here is false
	m_invalidRegExpSyntax = false;
}

CtRegExpPrivate::CtRegExpPrivate(const wchar * s, size_t _count, PatternSyntax _Flag)
	: m_pattern(new CtString(s)), m_last_mat(0), m_patternSyntax(_Flag)
{
	try
	{
		m_wregex = std::wregex(s, _count, _Flag);
	}
	catch (std::regex_error &e)
	{
		m_invalidRegExpSyntax = true;
		m_errorType = e.what();
		m_errorCode = e.code();
		return;//leave here if we got exception
	}
	//if everything went well, here is false
	m_invalidRegExpSyntax = false;
}

CtRegExpPrivate::CtRegExpPrivate(std::initializer_list<wchar>& list, PatternSyntax _Flag)
	: m_pattern(new CtString()), m_last_mat(0), m_patternSyntax(_Flag)
{
	try
	{
		m_wregex = std::wregex(list, _Flag);
	}
	catch (std::regex_error &e)
	{
		m_invalidRegExpSyntax = true;
		m_errorType = e.what();
		m_errorCode = e.code();
		return;//leave here if we got exception
	}
	//if everything went well, here is false
	m_invalidRegExpSyntax = false;

	std::copy(list.begin(), list.end(), m_pattern->begin());
}

void CtRegExpPrivate::assign(const CtString & s, PatternSyntax _Flag)
{
	try
	{
		m_pattern = new CtString(s); m_last_mat = 0;  m_patternSyntax = _Flag;
		m_wregex = std::wregex(s, _Flag);
	}
	catch (std::regex_error &e)
	{
		m_invalidRegExpSyntax = true;
		m_errorType = e.what();
		m_errorCode = e.code();
		return;//leave here if we got exception
	}
	//if everything went well, here is false
	m_invalidRegExpSyntax = false;
}

void CtRegExpPrivate::assign(const wchar * s, size_t _count, PatternSyntax _Flag)
{
	try
	{
		m_wregex = std::wregex(s, _count, _Flag);
		m_pattern = new CtString(s);
		m_last_mat = 0;
		m_patternSyntax = _Flag;
	}
	catch (std::regex_error &e)
	{
		m_invalidRegExpSyntax = true;
		m_errorType = e.what();
		m_errorCode = e.code();
		return;//leave here if we got exception
	}

	//if everything went well, here is false
	m_invalidRegExpSyntax = false;

}

inline int CtRegExpPrivate::indexIn(const CtString & str, int offset) const
{
	return const_cast<CtRegExpPrivate*>(this)->indexIn(str, offset);
}
/*
Attempts to find a match in str from position offset (0 by default). If offset is -1,
the search starts at the last character; if -2, at the next to last character; etc.
*/
int CtRegExpPrivate::indexIn(const CtString & str, int offset)
{
	if (offset < 0 || offset >(int)str.length() || str.empty()) return -1;

	if (!m_pattern) return -1;

	//save last upset
	m_last_offset = offset;

	//capture sub-strings
	setCaptureList(str);

	begin_iter = std::wsregex_iterator(std::next(str.begin(), offset), str.end(), m_wregex);
	end_iter = std::wsregex_iterator();

	if (begin_iter == end_iter) return -1;

	return begin_iter->position(0) + offset;
}

//Returns the length of the last matched string, or -1 if there was no match.
int CtRegExpPrivate::matchedLength() const
{
	if (begin_iter == end_iter) return -1;

	return begin_iter->length(0);
}

int CtRegExpPrivate::lastMatchIn(const CtString &s, int offset) const
{
	if (offset < 0 || offset >(int)s.length() || s.empty()) return -1;

	if (!m_pattern) return -1;

	//capture sub-strings
	setCaptureList(s);

	size_t index = s.length() - std::distance(wsregex_rev_iterator(s.rbegin(), s.rend(), m_wregex),
		wsregex_rev_iterator());

	if (index < 0 || index > s.length()) return -1;
	return index;
}
bool CtRegExpPrivate::replace(CtString & s, const CtString &_rep, MatchType match_type) const
{
	auto _sResult = std::regex_replace(s, m_wregex, _rep, match_type);
	if (_sResult.length() <= 0 || _sResult.empty()) return false;
	s.assign(_sResult);
	return true;
}
MatchCapturedVector CtRegExpPrivate::tokenize(const CtString &s, int offset, MatchType match_type) const
{
	MatchCapturedVector _mcvMatchCaptureVector;

	auto _mcvBeginIter = _mcvMatchCaptureVector.begin();
	auto _rtBeginIter = std::wsregex_token_iterator(s.begin(), s.end(), m_wregex, 0, match_type);
	for (; _rtBeginIter != std::wsregex_token_iterator(); ++_rtBeginIter) {
		_mcvMatchCaptureVector.push_back(MatchCaptured{ (int)s.find(_rtBeginIter->str()),_rtBeginIter->str() });
	}
	return _mcvMatchCaptureVector;
}

//Returns the number of captures contained in the regular expression.
int CtRegExpPrivate::captureCount() const { return m_capturedStringList.size(); }

//Returns a list of the captured text strings.
StringList CtRegExpPrivate::capturedTexts() const
{
	if (m_capturedStringList.empty())
		return StringList();

	return m_capturedStringList;
}

//Returns a list of the captured text strings.
StringList CtRegExpPrivate::capturedTexts()
{
	if (m_capturedStringList.empty())
		return StringList();

	return m_capturedStringList;
}

StringList CtRegExpPrivate::captureTexts(const CtString & str, MatchType match_type)
{
	StringList _slCapturedStringList;
	auto _begin_iter = std::wsregex_iterator(str.begin(), str.end(), m_wregex);
	auto _end_iter = std::wsregex_iterator();

	while (_begin_iter != _end_iter) {
		_slCapturedStringList.push_back(_begin_iter->str());
		++_begin_iter;
	}
	return _slCapturedStringList;
}
int CtRegExpPrivate::captureCount(const CtString & str) const
{
	auto _begin_iter = std::wsregex_iterator(str.begin(), str.end(), m_wregex);
	auto _end_iter = std::wsregex_iterator();
	return std::distance(_begin_iter, _end_iter);
}
//Returns the text captured by the nth subexpression.
CtString CtRegExpPrivate::cap(int nth) const
{
	if (m_capturedStringList.empty())
		return CtString();

	return m_capturedStringList[nth];
}

//Returns the text captured by the nth subexpression.
CtString CtRegExpPrivate::cap(int nth)
{
	if (m_capturedStringList.empty())
		return CtString();

	return m_capturedStringList[nth];
}

int CtRegExpPrivate::pos(int nth) const
{
	if (m_capturedStringList.empty())
		return -1;

	return std::distance(m_capturedStringList.begin() + nth, m_capturedStringList.end());
}

int CtRegExpPrivate::pos(int nth)
{
	if (m_capturedStringList.empty())
		return -1;

	return std::distance(m_capturedStringList.begin() + nth, m_capturedStringList.end());
}

void CtRegExpPrivate::setCaptureList(const CtString &s, MatchType match_type) const
{
	//avoid repeation
	const_cast<StringList&>(m_capturedStringList).clear();

	typedef std::vector<std::wstring> _StringList;
	std::vector<std::wstring> _wstring_list;
	std::copy(std::wsregex_token_iterator(s.begin(), s.end(), m_wregex, 0, match_type),
		std::wsregex_token_iterator(), std::insert_iterator<_StringList>(_wstring_list, _wstring_list.begin()));
	insert_item(const_cast<StringList&>(m_capturedStringList), _wstring_list);
}

