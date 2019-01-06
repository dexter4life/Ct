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

#include <ctcore/ctobject.h>
#include <Windows.h>

CtObject::CtObject(CtObject * parent) : m_objectPrivate(new CtObjectPrivate()), has_slots<>()
{
	//register a new child object
	if (parent) parent->registerChild(this);
}

CtObject::~CtObject()
{
	//delete all children assign to this object
	if (m_objectPrivate->prevHasChildren())
		m_objectPrivate->prevDeleteAllChildren();
}

bool CtObject::event(CtEvent * event)
{
	return false;
}

bool CtObject::eventFilter(CtObject * watched, CtEvent * e)
{
	//default behaviour
	if (!m_objectPrivate->m_pfilter) {
		event(e);
		return true;
	}
	else {
		//if filter is installed, forward events to this object
		m_objectPrivate->m_pfilter->eventFilter(watched, e);
		return true;
	}

	return false;
}
/*
*/
void CtObject::timerEvent(CtTimerEvent * event)
{
}
CtString CtObject::objectName() const
{
	return m_objectName;
}
void CtObject::setObjectName(const CtString & name)
{
	m_objectName = name;
}

inline void CtObject::setParent(CtObject * parent)
{
	CtObject *prevParent = m_objectPrivate->parent();

	//disown child
	if (prevParent) prevParent->m_objectPrivate->prevDeleteChild(this);

	m_objectPrivate->prevSetParent(parent);

	//register a new child object
	if (parent) parent->registerChild(this);
}

void CtObject::installEventFilter(CtObject * filter)
{
	m_objectPrivate->installEventFilter(filter);
}

int CtObject::startTimer(int interval)
{
#ifdef WIN32
	return ::SetTimer((HWND)handle(), (UINT_PTR)this, interval, NULL);
#endif
}
void CtObject::killTimer(int id)
{
#ifdef WIN32
	::KillTimer((HWND)handle(), id);
#endif
}

cthandle CtObject::handle() const
{
	return m_handle;
}

void CtObject::setHandle(cthandle handle)
{
	m_handle = handle;
}

void CtObject::registerChild(CtObject * child)
{
	m_objectPrivate->prevRegisterChild(child);
}


