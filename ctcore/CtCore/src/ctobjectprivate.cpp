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

#include <ctcore/ctobjectprivate.h>

CtObjectPrivate::CtObjectPrivate() 
	: m_pfilter(nullptr)
{
}

void CtObjectPrivate::prevSetParent(CtObject * parent)
{
	m_parent = parent;
}

void CtObjectPrivate::prevRegisterChild(CtObject * child)
{
	m_children.push_back(child);
}

void CtObjectPrivate::prevDeleteChild(CtObject * child)
{
	auto iter = std::find(m_children.begin(), m_children.end(), child);
	delete *iter;
	m_children.erase(iter);
}

void CtObjectPrivate::prevDeleteAllChildren()
{
	std::for_each(m_children.begin(), m_children.end(), [](CtObject*& currChild) {
		delete currChild;
	});
	m_children.clear();
}

bool CtObjectPrivate::prevHasChildren() const
{
	return m_children.size()>0;
}

void CtObjectPrivate::installEventFilter(CtObject * filter)
{
	m_pfilter = filter;
}
