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


#ifndef GLOBAL_DEF_H
#define GLOBAL_DEF_H

//define namespace start
#ifndef BEGIN_NAMESPACE
#define BEGIN_GLOBAL_NAMESPACE namespace Ct {
#define END_GLOBAL_NAMESPACE }
#else
#undef BEGIN_NAMESPACE
#define BEGIN_NAMESPACE(name) namespace name{
#endif


/**/
#define DECLARE_OVERRIDE override

#include <ctcore/ctflags.h>
#define CT_DECLARE_FLAGS(Flags, Enum)\
typedef CtFlags<Enum> Flags;

#define API_TYPE
#include <cinttypes>

typedef wchar_t wchar;
typedef unsigned long ulong;

#include <new>

#include <iostream>
#define _wstream_operator_insertion(_class, _ty)\
static inline const _class &operator<<(const _class &debug, _ty var)\
{ std::wcout << var; return debug; }

#define _define_wchar_operator_insertion(_class, _ty) _wstream_operator_insertion(_class,_ty)

#define _stream_operator_insertion(_class, _ty)\
static inline const _class &operator<<(const _class &debug, _ty var)\
{ std::cout << var; return debug; }

#define _define_char_operator_insertion(_class, _ty) _stream_operator_insertion(_class,_ty)

#include <ctime>
#include <cstdarg>
#include <cstdio>

static void debug_log(const char * fmt, ...)
{
	std::time_t t = std::time(nullptr);
	char time_buf[100];
#ifdef _MSC_VER 
#if (_MSC_VER>=1900)
	tm _tm; gmtime_s(&_tm, &t);
	std::strftime(time_buf, sizeof time_buf, "%D %T", &_tm);
#endif // (_MSC_VER>1900)
#else
	std::strftime(time_buf, sizeof time_buf, "%D %T", gmtime(&t));
#endif
	va_list args1;
	va_start(args1, fmt);
	va_list args2;
	va_copy(args2, args1);
	std::string buf;
	buf.resize(std::vsnprintf(NULL, 0, fmt, args1) + 1);
	va_end(args1);
	std::vsnprintf(const_cast<char*>(buf.data()), buf.size(), fmt, args2);
	va_end(args2);
	std::printf("%s [debug]: %s\n", time_buf, buf.data());
}

#define LOG(fmt,...) debug_log(fmt,_VAR_ARGS_)
//#define C_DECLARE_OPERATORS_FOR_FLAGS(Flags) \
// inline CFlags<Flags::enum_type> operator|(Flags::enum_type f1, Flags::enum_type f2) __nothrow \
//{ return CFlags<Flags::enum_type>(f1) | f2; } \
// inline CFlags<Flags::enum_type> operator|(Flags::enum_type f1, CFlags<Flags::enum_type> f2) __nothrow \
//{ return f2 | f1; } Q_DECLARE_INCOMPATIBLE_FLAGS(Flags)
BEGIN_GLOBAL_NAMESPACE

enum KeyboardModifier {
	NoModifier = 0x00000000,
	ShiftModifier = 0x02000000,
	ControlModifier = 0x04000000,
	AltModifier = 0x08000000,
	GroupSwitchModifier = 0x40000000,//modify later
	// Do not extend the mask to include 0x01000000
    KeyboardModifierMask = 0xfe000000
};
/*KeyboardModifiers is valid when keys are pressed in combination to another keys
or is done via mouse click instead.*/
CT_DECLARE_FLAGS(KeyboardModifiers, KeyboardModifier)

enum Modifier {
	SHIFT = Ct::ShiftModifier,
	CTRL = Ct::ControlModifier,
	ALT = Ct::AltModifier,
	MODIFIER_MASK = KeyboardModifierMask,
	UNICODE_ACCEL = 0x00000000
};

enum MouseButton {
	NoButton = 0x00000000,
	LeftButton = 0x00000001,
	RightButton = 0x00000002,
	BackButton = 0x00000008,
	AllButtons = 0x07ffffff,
};
CT_DECLARE_FLAGS(MouseButtons, MouseButton)

enum _CaseSensitivity 
{
	CaseInsensitive,
	CaseSensitive
};
CT_DECLARE_FLAGS(CaseSensitivity, _CaseSensitivity)

enum FocusReason {
	MouseFocusReason,
	TabFocusReason,
	BacktabFocusReason,
	ActiveWindowFocusReason,
	PopupFocusReason,
	ShortcutFocusReason,
	MenuBarFocusReason,
	OtherFocusReason,
	NoFocusReason
};

END_GLOBAL_NAMESPACE

/*
Some classes do not permit copies to be made of an object. These
classes contains a private copy constructor and assignment
operator to disable copying (the compiler gives an error message).
*/
#define DISABLE_COPY(Class) \
    Class(const Class &) = delete;\
    Class &operator=(const Class &) = delete;


#if defined(WIN32)||defined(_WIN32)
#include <functional>
#include <Windows.h>

//HWND, UINT, WPARAM, LPARAM
#define _DECLARE_EVENT_HANDLER(EventClass)\
template <typename Ret,typename ...Args>\
class EventClass{\
friend class CWidgetPrivate;\
typedef std::function < Ret(Args...) > FUNCTYPE;\
public:\
	static Ret windowProc(Args ... args){\
	    FUNCTYPE m_func = functionObject();\
		return m_func(args...);}\
	void assignFunc(const FUNCTYPE &func) {\
		FUNCTYPE &m_func = functionObject();\
		m_func = func;}\
private:\
static FUNCTYPE &functionObject() {\
	static FUNCTYPE m_func;\
	return m_func;}\
};


#define DECLARE_EVENT_HANDLER(_class,...) _DECLARE_EVENT_HANDLER(_class)\
_class<__VA_ARGS__> __class;
#endif


#ifdef WIN32
#define ASSIGN_EVENT_HANDLER(handler) __class.assignFunc(handler)
/*Declare event handles for widgets*/
#define DECLARE_WNDPROC_HANDLER(EventHandler)  DECLARE_EVENT_HANDLER(EventHandler, LRESULT, HWND, UINT, WPARAM, LPARAM)
#define _WINPROCHANDLE EventHandler<LRESULT, HWND, UINT, WPARAM, LPARAM>::windowProc
#define WINPROCHANDLE _WINPROCHANDLE

#define DECLARE_TIMER_HANDLER() DECLARE_EVENT_HANDLER(EventHandler,void,LPVOID,DWORD,DWORD)
#define _TIMERPROCHANDLE EventHandler<void,LPVOID,DWORD,DWORD>::windowProc
#define TIMERPROCHANDLE _TIMERPROCHANDLE
#endif



#ifndef CT_CORE_TYPE
#define CT_CORE_TYPE
typedef		std::float_t		ctreal;
typedef		std::uint64_t 		ctuint64;
typedef		std::uint32_t		ctuint32;
typedef		ctuint32			ctuint;
typedef		std::int64_t		ctint64;
typedef		std::int32_t		ctint32;
typedef		ctint32				ctint;
typedef		unsigned short		ctushort;
typedef		void *				cthandle;

#endif
#undef min
#undef max
#include <utility>
#include <algorithm>

static inline bool cFuzzyCompare(double p1, double p2)
{
	return (std::abs(p1 - p2) * 1000000000000. <= std::min(std::abs(p1), std::abs(p2)));
}

static inline bool cFuzzyCompare(float p1, float p2)
{
	return (std::abs(p1 - p2) * 100000.f <= std::min(std::abs(p1), std::abs(p2)));
}

/*!
\internal
*/
static inline bool cFuzzyIsNull(double d)
{
	return std::abs(d) <= 0.000000000001;
}

/*!
\internal
*/
static inline bool qFuzzyIsNull(float f)
{
	return std::abs(f) <= 0.00001f;
}

/*
This function tests a double for a null value. It doesn't
check whether the actual value is 0 or close to 0, but whether
it is binary 0, disregarding sign.
*/
static inline bool qIsNull(double d)
{
	union U {
		double d;
		ctuint64 u;
	};
	U val;
	val.d = d;
	return (val.u & ctuint64(0x7fffffffffffffff)) == 0;
}

/*
This function tests a float for a null value. It doesn't
check whether the actual value is 0 or close to 0, but whether
it is binary 0, disregarding sign.
*/
static inline bool cIsNull(float f)
{
	union U {
		float f;
		ctuint32 u;
	};
	U val;
	val.f = f;
	return (val.u & 0x7fffffff) == 0;
}

#ifdef WIN32
#include <Windows.h>
#include <ctcore/ctpoint.h>
#include <ctcore/ctrect.h>
#include <ctcore/ctsize.h>

class Message 
{
public:
	Message(HWND handle,ctint32 message, WPARAM wParam, LPARAM lParam)
		: m_wParam(wParam),m_lParam(lParam), m_msg(message),m_hwnd(handle)
	{
	}
	inline CtPoint toPoint() const
	{
		return CtPoint(MAKEPOINTS(m_lParam).x, MAKEPOINTS(m_lParam).y);
	}
	inline CtPointF toPointF() const
	{
		return CtPointF(toPoint());
	}
	inline CtSize toSize() const 
	{
		return CtSize(HIWORD(m_lParam), LOWORD(m_lParam));
	}
	inline CtSizeF	toSizeF() const
	{
		return CtSizeF(toSize());
	}
	inline WPARAM wParam() const
	{
		return m_wParam;
	}
	inline LPARAM lParam() const
	{
		return m_lParam;
	}
	inline HWND handle() const
	{
		return m_hwnd;
	}
	inline ctuint32 msg() const { return m_msg; }
private:
	WPARAM  m_wParam;
	LPARAM	m_lParam;
	ctuint32	m_msg;
	HWND	m_hwnd;
};
#endif

/////////////////////////////////////////
// Declarations for the CCriticalSection class
// This class is used for thread synchronisation
#if defined(_WIN32) || defined(_WIN64)
#	include <windows.h>
#elif defined(__GNUG__) || defined(_POSIX_VERSION)
#	include <pthread.h>
#endif


class signal_lock_mutex {
public:
	signal_lock_mutex()
	{
#if defined(_WIN32) || defined(_WIN64)
#ifdef HAS_WIN32_THREADS_GLOBAL
		static bool isinitialised = false;

		if (!isinitialised)
		{
			InitializeCriticalSection(get_critsec());
			isinitialised = true;
		}
#else
		InitializeCriticalSection(&m_critsec); // initializes a critical section object.
#endif
#elif __linux__
		// linux
#elif __unix__ // all unices not caught above
		// Unix
#elif defined(_POSIX_VERSION)
		// POSIX
#ifdef HAS_POSIX_THREADS_GLOBAL
		pthread_mutex_init(get_mutex(), NULL);
#	else
		pthread_mutex_init(&m_mutex, NULL);
#endif
#else
#   error "Unknown compiler"
#endif
	}
	~signal_lock_mutex()
	{
#if defined(_WIN32) || defined(_WIN64)
		DeleteCriticalSection(&m_critsec);
#elif __linux__
		// linux
#elif __unix__ // all unices not caught above
		// Unix
#elif defined(_POSIX_VERSION)
		// POSIX
#ifdef HAS_POSIX_THREADS_GLOBAL

#else
		pthread_mutex_destroy(&m_mutex);
#endif
#else
#   error "Unknown compiler"
#endif
	}
	virtual void lock()
	{
#if defined(_WIN32) || defined(_WIN64)
#ifdef HAS_WIN32_THREADS_GLOBAL
		EnterCriticalSection(get_critsec());
#else
		EnterCriticalSection(&m_critsec);
#endif
#elif __linux__
		// linux
#elif __unix__ // all unices not caught above
		// Unix
#elif defined(_POSIX_VERSION)
		// POSIX
#ifdef HAS_POSIX_THREADS_GLOBAL
		pthread_mutex_lock(get_mutex());
#else
		pthread_mutex_lock(&m_mutex);
#endif
#else
#   error "Unknown compiler"
#endif
	}
	virtual void unlock()
	{
#if defined(_WIN32) || defined(_WIN64)
#ifdef HAS_WIN32_THREADS_GLOBAL
		LeaveCriticalSection(get_critsec());
#else
		LeaveCriticalSection(&m_critsec);
#endif
#elif __linux__
		// linux
#elif __unix__ // all unices not caught above
		// Unix
#elif defined(_POSIX_VERSION)
		// POSIX
#ifdef HAS_POSIX_THREADS_GLOBAL
		pthread_mutex_unlock(get_mutex());
#else
		pthread_mutex_unlock(&m_mutex);
#endif
#else
#   error "Unknown compiler"
#endif
	}
private:
#if defined(_WIN32) || defined(_WIN64)
#ifdef HAS_WIN32_THREADS_GLOBAL
	CRITICAL_SECTION* get_critsec()
	{
		static CRITICAL_SECTION g_critsec;
		return &g_critsec;
	}
#else
	CRITICAL_SECTION m_critsec;
#endif
#elif __linux__
	// linux
#elif __unix__ // all unices not caught above
	// Unix
#elif defined(_POSIX_VERSION)
	// POSIX
#ifdef HAS_POSIX_THREADS_GLOBAL
	pthread_mutex_t* get_mutex()
	{
		static pthread_mutex_t g_mutex;
		return &g_mutex;
	}
#else
	pthread_mutex_t m_mutex;
#endif
#else
#   error "Unknown compiler"
#endif
};
#if (__cplusplus>=199711L)
#define DEFAULT_MULT_THREAD_POLICY signal_lock_mutex
#else
#define DEFAULT_SINGLE_THREAD_POLICY single_threaded
#endif
class single_threaded
{
public:
	single_threaded() {}

	virtual ~single_threaded() {}

	virtual void lock() {}

	virtual void unlock() {}
};

template<class mt_policy>
class lock_block
{
public:
	mt_policy *m_mutex;

	lock_block(mt_policy *mtx)
		: m_mutex(mtx)
	{
		m_mutex->lock();
	}

	~lock_block()
	{
		m_mutex->unlock();
	}
};


#define _WINSOCKAPI_            // Prevent winsock.h #include's.


#endif // !GLOBAL_DEF_H

