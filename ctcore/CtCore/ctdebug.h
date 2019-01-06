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
#ifdef DEBUG
#ifndef CT_DEBUG_H
#define CT_DEBUG_H

#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <string>

#ifdef _DEBUG
#include <ctcore/ctstring.h>
#include <ctcore/ctregexp.h>

#endif

#include <ctcore/ctglobal.h>

class CtDebug
{
public:
	typedef const wchar_t * const_wchart;


	friend _define_wchar_operator_insertion(CtDebug, int)
		friend _define_wchar_operator_insertion(CtDebug, size_t)
		friend _define_wchar_operator_insertion(CtDebug, double)
		friend _define_wchar_operator_insertion(CtDebug, float)
		friend _define_wchar_operator_insertion(CtDebug, const_wchart)
		friend _define_wchar_operator_insertion(CtDebug, std::wstring)
		friend _define_char_operator_insertion(CtDebug, const char)
		friend _define_wchar_operator_insertion(CtDebug, const wchar_t)

public:
	CtDebug();
	~CtDebug();
};

#endif
static CtDebug debug;
#if defined(UNICODE) || defined(_UNICODE)
#define NEW_LINE L"\n";
#if NODEBUG
#else
#define _debugl(_param_) debug<<_param_<<NEW_LINE
#define debugl(n) _debugl((n))
#endif
#else
#define NEW_LINE "\n";
#endif // 


#if defined(DEBUG)||defined(_DEBUG)
typedef std::vector<std::wstring> WideStringList;
//display to output stream
static inline const CtDebug &operator<<(const CtDebug &debug, WideStringList &stringList)
{
	std::wcout << "{";
	auto _begin = stringList.begin();
	while (_begin != stringList.end()) {
		std::wcout << (*_begin);
		if (std::next(_begin, 1) != stringList.end())
			std::wcout << L",";
		++_begin;
	}
	std::wcout << "}";
	return debug;
}
_define_wchar_operator_insertion(CtDebug, const StringList &)
_define_wchar_operator_insertion(CtDebug, CtString)
#endif
#include <utility>
#include <ctcore/ctstring.h>


class ParameterHelper
{
private:
	int param_count, m_iParamCount, m_arg;

	ParameterHelper() : param_count(0)
	{
	}

	template<class Head>
	void replaceArgument(CtString &fmt, Head&& head)
	{
		param_count++;

		if (param_count > m_iParamCount)return;

		std::wostringstream wsout;
		wsout << std::forward<Head>(head);

		std::wstring toSearch = (L"%" + std::to_wstring(param_count));

		if (fmt.find(toSearch) != fmt.npos)
			fmt.replaceAll(toSearch, wsout.str());
	}
	template<class Head>
	void print_args_(CtString &fmt, Head&& head) {
		replaceArgument(fmt, head);
	}

	template<class Head, class... Tail>
	void print_args_(CtString &fmt, Head&& head, Tail&&... tail) {
		replaceArgument(fmt, head);
		print_args_(fmt, std::forward<Tail>(tail)...);
	}
	template<class... Args>
	void print_args(CtString &fmt, Args&&... args) {

		m_iParamCount = sizeof... (args);
		print_args_(fmt, std::forward<Args>(args)...);
	}

public:
	template<class... Args>
	inline static void print(CtString fmt, Args&&... args) {
		auto sp = fmt.findAll("%");

		ParameterHelper paramHelper;
		paramHelper.m_arg = sp.size();
		CtString _fmt = fmt;
		paramHelper.print_args(_fmt, args...);
		std::wcout << _fmt.c_str();
	}
	template<class... Args>
	inline static void println(CtString fmt, Args&&... args) {
		ParameterHelper paramHelper;
		CtString _fmt = fmt;
		paramHelper.print_args(_fmt, args...);
		std::wcout << _fmt.c_str() << "\n";
	}
	template<class... Args>
	inline static void printToBuffer(CtString &str, CtString fmt, Args&&... args) {
		ParameterHelper paramHelper;
		CtString _fmt = fmt;
		paramHelper.print_args(_fmt, args...);
		std::wostringstream out;
		out << _fmt.c_str();
		str = out.str();
	}
	template<class... Args>
	inline static void printlnToBuffer(CtString &str, CtString fmt, Args&&... args) {
		ParameterHelper paramHelper;
		CtString _fmt = fmt;
		paramHelper.print_args(_fmt, args...);
		std::wostringstream out;
		out << _fmt.c_str() << std::endl;
		str = out.str();
	}
};
#ifdef _WIN32
#define _MULT_ARG_PRINT(fmt /*string type i.e String class */, ...) ParameterHelper::print(CtString(fmt), __VA_ARGS__) 
#define _PRINT_TO_STRING(str,fmt, ...) ParameterHelper::printToBuffer(str,CtString(fmt), __VA_ARGS__) 
#define _PRINTLN_TO_STRING(str,fmt, ...) ParameterHelper::printlnToBuffer(str,CtString(fmt), __VA_ARGS__) 
#define	PRINT(fmt /*string*/,...) _MULT_ARG_PRINT(fmt,__VA_ARGS__)
#define PRINT_TO_STRING(str,fmt,...) _PRINT_TO_STRING(str,fmt,__VA_ARGS__)
#define PRINTLN_TO_STRING(str,fmt,...) _PRINTLN_TO_STRING(str,fmt,__VA_ARGS__)



#endif
#include <windows.h>
#ifdef _DEBUG
template<typename ...Args>
static void _trace(CtString &format, Args... args)
{
	CtString str;
	PRINTLN_TO_STRING(str, format, args...);
	OutputDebugString(str.c_str());
}
#define TRACE(fmt,...) _trace(CtString(fmt),__VA_ARGS__)
#ifdef WIN32
#include <xutility>
#endif
#endif // DEBUG

#endif // !CT_DEBUG_H

