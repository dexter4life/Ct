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
#ifndef OBJECT_PRIVATE_H
#define OBJECT_PRIVATE_H

#include <ctcore/ctglobal.h>
#include <vector>
#include <algorithm>
#include <memory>

class CtObjectPrivate
{
	friend class CtObject;

	CtObjectPrivate();

	//manage child parent relation for each object
	void prevRegisterChild(CtObject *child);
	void prevDeleteChild(CtObject *child);
	void prevDeleteAllChildren();
	bool prevHasChildren() const;
	void installEventFilter(CtObject *filter);

	void prevSetParent(CtObject *parent);

	inline CtObject *parent() const { return m_parent; }
	
	inline CtObject *filter() const { return m_pfilter; }
private:
	DISABLE_COPY(CtObjectPrivate)
		//child pointers
		std::vector<CtObject*> m_children;
	//this object parent
	CtObject *m_parent, *m_pfilter;
};
#endif // !OBJECT_PRIVATE_H
