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

#ifndef COBJECT_H
#define COBJECT_H

#include <ctcore/ctglobal.h>
#include <ctcore/ctsignal.h>
#include <ctcore/ctstring.h>
#include <ctcore/ctdebug.h>
#include <ctcore/ctevent.h>
#include <ctcore/ctobjectprivate.h>

class CtObject : public has_slots<>
{
public:
	CtObject(CtObject *parent = nullptr);

	virtual ~CtObject();

	virtual bool event(CtEvent *event);
	virtual bool eventFilter(CtObject *watched, CtEvent *event);
	
	virtual void timerEvent(CtTimerEvent *event);

	CtString objectName() const;
	void setObjectName(const CtString &name);

	CtObject *parent() const 
	{
		return m_objectPrivate->parent();
	}
	
	void	setParent(CtObject *parent);

	virtual void installEventFilter(CtObject *filter);

	int					startTimer(int interval);
	void				killTimer(int id);

	cthandle	handle() const;
	void		setHandle(cthandle handle);

#ifdef WIN32

#endif // WIN32

private:
	void registerChild(CtObject *child);

	CtString m_objectName;
	CtObjectPrivate *m_objectPrivate;

	cthandle	m_handle;
};
#endif // !COBJECT_H
