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

#include <ctcore/ctevent.h>
#include <ctcore/ctglobal.h>
#include <ctcore/ctstring.h>


CtEvent::CtEvent(Type type)
	: t(type)
{

}

CtEvent::CtEvent(const CtEvent & other)
{
	t = other.t;
}

CtEvent::~CtEvent()
{
}

CtEvent CtEvent::operator=(const CtEvent & other)
{
	// TODO: insert return statement here
	return CtEvent(other);
}

CtInputEvent::CtInputEvent(Type type, Ct::KeyboardModifiers modifiers)
	: CtEvent(type), modState(modifiers)
{
}

CtInputEvent::~CtInputEvent()
{
}
/*Timer event class definition*/
CtTimerEvent::CtTimerEvent(cthandle timerId)
	: id(timerId)
{
}

CtTimerEvent::~CtTimerEvent()
{
}

CtCloseEvent::CtCloseEvent()
	: CtEvent(CtEvent::Close)
{
}

CtCloseEvent::~CtCloseEvent()
{
}

CtMouseEvent::CtMouseEvent(Type type, const CtPointF & localPos, Ct::MouseButton button, Ct::MouseButtons buttons, Ct::KeyboardModifiers modifiers)
	: CtInputEvent(type, modifiers), l(localPos), b(button), mouseState(buttons)
{
}

CtMouseEvent::CtMouseEvent(Type type, const CtPointF & localPos, const CtPointF & screenPos, Ct::MouseButton button, Ct::MouseButtons buttons, Ct::KeyboardModifiers modifiers)
	: CtInputEvent(type, modifiers), l(localPos), s(screenPos), b(button), mouseState(buttons)
{
}

CtMouseEvent::CtMouseEvent(Type type, const CtPointF & localPos, const CtPointF & windowPos, const CtPointF & screenPos, Ct::MouseButton button, Ct::MouseButtons buttons, Ct::KeyboardModifiers modifiers)
	: CtInputEvent(type, modifiers), l(localPos), s(screenPos), b(button), mouseState(buttons), w(windowPos)
{
}

CtMouseEvent::~CtMouseEvent()
{
}

CtKeyEvent::CtKeyEvent(Type type, int key, Ct::KeyboardModifiers modifiers, const CtString & text, bool autorep, ctushort count)
	: CtInputEvent(type, modifiers), k(key), txt(text), c(count), autor(autorep)
{

}

CtKeyEvent::CtKeyEvent(Type type, int key, Ct::KeyboardModifiers modifiers, ctuint32 nativeScanCode, ctuint32 nativeVirtualKey, ctuint32 nativeModifiers, const CtString & text, bool autorep, ctushort count)
	: CtInputEvent(type, modifiers), k(key), nScanCode(nativeScanCode), nVirtualKey(nativeVirtualKey),
	nModifiers(nativeModifiers), txt(text), c(count), autor(autorep)
{

}

CtKeyEvent::~CtKeyEvent()
{
}

Ct::KeyboardModifiers CtKeyEvent::modifiers() const
{
	return Ct::KeyboardModifiers();
}

CtResizeEvent::CtResizeEvent(const CtSize & size, const CtSize & oldSize)
	: s(size), olds(oldSize)
{

}

CtResizeEvent::~CtResizeEvent()
{
}

CtFocusEvent::CtFocusEvent(Type type, Ct::FocusReason reason)
{

}

CtFocusEvent::~CtFocusEvent()
{
}


CtHoverEvent::CtHoverEvent(Type type, const CtPointF & pos, const CtPointF & oldPos, Ct::KeyboardModifiers modifiers)
	: CtInputEvent(type, modifiers)
{
}

CtHoverEvent::~CtHoverEvent()
{
}

CtShowEvent::CtShowEvent()
	: CtEvent(CtEvent::Show)
{

}

CtHideEvent::CtHideEvent()
	: CtEvent(CtEvent::Hide)
{
}
/*end timer definition*/