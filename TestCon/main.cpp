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

#if defined(DEBUG)||defined(_DEBUG)
#include <ctCore/ctdebug.h>
#endif // DEBUG

class MyClass : public CtObject
{
public:
	void on_timeout(ctuint64 elapse_time)
	{
		PRINT("%1\n", elapse_time);
	}
};

class MyClassWithEventHandler : public CtObject
{
public:
	virtual void timerEvent(CtTimerEvent *event)
	{
		PRINT("%1\n", "timerEvent");
	}
};
int main()
{
	::
	MyClass myClassSlot;
	MyClassWithEventHandler withEventHandler;

	CtTimer timer;
	timer.timeout_connect(&myClassSlot, &MyClass::on_timeout);

	timer.start(1);

	//CtString name;
	return 0;
}
