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


#include <Windows.h>
#include <typeinfo>
#include <string>
#include <functional>
#include <varargs.h>
#include <stddef.h>
#include <commctrl.h>
#include <iostream>

#include <ctcore/ctutilitydef.h>
#include <ctcore/ctregexp.h>
#include <ctcore/ctstring.h>
#include <ctcore/ctobject.h>
#include <ctcore/ctsignal.h>
#include <ctcore/cttimer.h>

#include <chrono>
#include <thread>

#if defined(DEBUG)||defined(_DEBUG)
#include <ctCore/ctdebug.h>
#endif // DEBUG

#ifdef WIN32
class CtTimerPriv : CtObject
{
	friend class CtTimer;
public:
	CtTimerPriv(CtObject *parent = 0)
		: m_parent(parent)
	{
	}

	void stop()
	{
		m_stop = true;
		CancelWaitableTimer(m_timerHandle);
		CloseHandle(m_timerHandle);
	}

	static CtTimerPriv *getInstance(CtTimer *timer)
	{
		static CtTimerPriv timerPriv(timer);
		return &timerPriv;
	}

	inline void setTimerHandle(cthandle handle)
	{
		m_timerHandle = handle;
	}
	inline cthandle timerHandle() const
	{
		return m_timerHandle;
	}
	inline void setStop(bool flag)
	{
		m_stop = flag;
	}
	inline bool isStop() const
	{
		return m_stop;
	}
	inline void setParent(CtObject *parent)
	{
		m_parent = parent;
	}
	inline CtObject *parent() const
	{
		return m_parent;
	}
	inline void setStartTime(ctuint64 time)
	{
		m_startTime = time;
	}
	inline ctuint64 startTime() const
	{
		return m_startTime;
	}
private:
	cthandle m_timerHandle;
	bool	m_stop;
	CtObject *m_parent;
	ctuint64 m_startTime;

public:
	DECLARE_EVENT_HANDLER(EventHandler,void, LPVOID,DWORD,DWORD)
};
	
#endif //WIN32


CtTimer::CtTimer(CtObject *parent)
	: CtObject(parent),
	dd(new CtTimerPriv(this)),
	id(0)
{
	id = dd->handle();
}

CtTimer::~CtTimer()
{
	delete dd;
}

void CtTimer::setInterval(int msec)
{
	inter = msec;
}

int CtTimer::remainingTime() const
{
	return 0;
}

void CtTimer::start(int msec)
{
	dd->setParent(this->parent());

	inter = msec;

	dd->setStop(false);

	// create the timer
	id = CreateWaitableTimer(NULL, FALSE, NULL);
	
	dd->setTimerHandle(id);

	// set the timer
	using namespace std::chrono;
	milliseconds ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
	
	dd->setStartTime(ms.count());

	std::thread timerThread([&]
	{
		lock_block<DEFAULT_MULT_THREAD_POLICY> lock(this);

		dd->__class.assignFunc([&](LPVOID lpArgToCompletionRoutine,
			DWORD dwTimerLowValue,
			DWORD dwTimerHighValue)
		{
			CtTimerPriv *_this = (CtTimerPriv*)lpArgToCompletionRoutine;

			CtTimerEvent ev(_this->m_timerHandle);

			static_cast<CtObject*>(_this)->timerEvent(&ev);
		});

		LARGE_INTEGER lElapse;
		lElapse.QuadPart = 0;// -((int)msec * 10000);
		BOOL succ = SetWaitableTimer(dd->timerHandle(), &lElapse, inter, (PTIMERAPCROUTINE)dd->__class.windowProc,
			(dd->parent()) ? dd->parent() : this, FALSE);

		while (!dd->isStop())
			SleepEx(INFINITE, TRUE);
	});

	timerThread.join();
}

void CtTimer::timerEvent(CtTimerEvent *event)
{
	using namespace std::chrono;

	milliseconds ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch());

	timeout(ms.count() - dd->startTime());
}

void CtTimer::start()
{
	start(inter);
}

void CtTimer::stop()
{
	dd->stop();

	id = 0;
}

