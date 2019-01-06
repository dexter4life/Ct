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
#ifndef CT_TIMER_H
#define CT_TIMER_H

#include <algorithm>
#include <functional>
#include <ctcore/ctglobal.h>
#include <ctcore/ctobject.h>
#include <ctcore/ctsignal.h>

#ifdef WIN32
#include <Windows.h>
#endif

class CtTimer : public CtObject
{
	friend class CtTimerPriv;
public:
	explicit CtTimer(CtObject *parent = nullptr);
	~CtTimer();

	inline bool isActive() const { return id >= 0; }
	cthandle timerId() const { return id; }

	void setInterval(int msec);
	int interval() const { return inter; }

	int remainingTime() const;

	void start(int msec);

	void start();
	void stop();

	void timerEvent(CtTimerEvent *event);

	declare_signal(timeout, ctuint64)
private:
	cthandle id;
	int inter;
	CtTimerPriv *dd;
};

#endif // !CT_TIMER_H
//auto timefunc = [](HWND, UINT, UINT_PTR, DWORD) {
//
//};
//SetTimer(NULL, cint64(this), interval, timefunc);
