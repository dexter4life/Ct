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

#ifndef CT_EVENT_H
#define CT_EVENT_H
#include <ctcore/ctstring.h>
#include <ctcore/ctvec2d.h>
#include <ctcore/ctpoint.h>
#include <ctcore/ctglobal.h>


class CT_EVENT_H CtEvent
{
public:
	enum Type {
		/*
		If you get a strange compiler error on the line with None,
		it's probably because you're also including X11 headers,
		which #define the symbol None. Put the X11 includes after
		the Qt includes to solve this problem.
		*/
		None=1,
		MouseButtonPress = 2,                   // mouse button pressed
		MouseButtonRelease = 3,                 // mouse button released
		MouseButtonDblClick = 4,                // mouse button double click
		MouseMove = 5,                          // mouse move
		KeyPress = 6,                           // key pressed
		KeyRelease = 7,                         // key released
		FocusIn = 8,                            // keyboard focus received
		FocusOut = 9,                           // keyboard focus lost
		FocusAboutToChange = 23,                // keyboard focus is about to be lost
		Enter = 10,                             // mouse enters widget
		Leave = 11,                             // mouse leaves widget
		Paint = 12,                             // paint widget
		Move = 13,                              // move widget
		Resize = 14,                            // resize widget
		Create = 0x01,                            // after widget creation
		Destroy = 0x02,                           // during widget destruction
		Show = 17,                              // widget is shown
		Hide = 18,                              // widget is hidden
		Close = 19,                             // request to close widget
		Quit = 20,                              // request to quit application
		ParentChange = 21,                      // widget has been reparented
		ParentAboutToChange = 131,              // sent just before the parent change is done
		ThreadChange = 22,                      // object has changed threads
		WindowActivate = 24,                    // window was activated
		WindowDeactivate = 25,                  // window was deactivated
		ShowToParent = 26,                      // widget is shown to parent
		HideToParent = 27,                      // widget is hidden to parent
		Wheel = 31,                             // wheel event
		WindowTitleChange = 33,                 // window title changed
		WindowIconChange = 34,                  // icon changed
		ApplicationWindowIconChange = 35,       // application icon changed
		ApplicationFontChange = 36,             // application font changed
		ApplicationLayoutDirectionChange = 37,  // application layout direction changed
		ApplicationPaletteChange = 38,          // application palette changed
		PaletteChange = 39,                     // widget palette changed
		Clipboard = 40,                         // internal clipboard event
		Speech = 42,                            // reserved for speech input
		MetaCall = 43,                         // meta call event
		SockAct = 50,                           // socket activation
		WinEventAct = 132,                      // win event activation
		DeferredDelete = 52,                    // deferred delete event
		DragEnter = 60,                         // drag moves into widget
		DragMove = 61,                          // drag moves in widget
		DragLeave = 62,                         // drag leaves or is cancelled
		Drop = 63,                              // actual drop
		DragResponse = 64,                      // drag accepted/rejected
		ChildAdded = 68,                        // new child widget
		ChildPolished = 69,                     // polished child widget
		ChildRemoved = 71,                      // deleted child widget
		ShowWindowRequest = 73,                 // widget's window should be mapped
		PolishRequest = 74,                     // widget should be polished
		Polish = 75,                            // widget is polished
		LayoutRequest = 76,                     // widget should be relayouted
		UpdateRequest = 77,                     // widget should be repainted
		UpdateLater = 78,                       // request update() later

		EmbeddingControl = 79,                  // ActiveX embedding
		ActivateControl = 80,                   // ActiveX activation
		DeactivateControl = 81,                 // ActiveX deactivation
		ContextMenu = 82,                       // context popup menu
		InputMethod = 83,                       // input method
		TabletMove = 87,                        // Wacom tablet event
		LocaleChange = 88,                      // the system locale changed
		LanguageChange = 89,                    // the application language changed
		LayoutDirectionChange = 90,             // the layout direction changed
		Style = 91,                             // internal style event

		IconDrag = 96,                          // proxy icon dragged

		FontChange = 97,                        // font has changed
		EnabledChange = 98,                     // enabled state has changed
		ActivationChange = 99,                  // window activation has changed
		StyleChange = 100,                      // style has changed
		IconTextChange = 101,                   // icon text has changed.  Deprecated.
		ModifiedChange = 102,                   // modified state has changed
		MouseTrackingChange = 109,              // mouse tracking state has changed

		WindowBlocked = 103,                    // window is about to be blocked modally
		WindowUnblocked = 104,                  // windows modal blocking has ended
		WindowStateChange = 105,

		ReadOnlyChange = 106,                   // readonly state has changed

		ToolTip = 110,
		WhatsThis = 111,
		StatusTip = 112,

		ActionChanged = 113,
		ActionAdded = 114,
		ActionRemoved = 115,

		Shortcut = 117,                         // shortcut triggered
		ShortcutOverride = 51,                  // shortcut override request

		WhatsThisClicked = 118,

		ToolBarChange = 120,                    // toolbar visibility toggled

		QueryWhatsThis = 123,                   // query what's this widget help
		EnterWhatsThisMode = 124,
		LeaveWhatsThisMode = 125,

		ZOrderChange = 126,                     // child widget has had its z-order changed

		HoverEnter = 127,                       // mouse cursor enters a hover widget
		HoverLeave = 128,                       // mouse cursor leaves a hover widget
		HoverMove = 129,
	};

	explicit CtEvent(Type type = None);
	CtEvent(const CtEvent &other);
	virtual ~CtEvent();
	CtEvent operator=(const CtEvent &other);
	inline Type type() const { return static_cast<Type>(t); }

private:
	Type t;
};

class CT_EVENT_H CtInputEvent : public CtEvent
{
public:
	explicit CtInputEvent(Type type, Ct::KeyboardModifiers modifiers = Ct::NoModifier);
	~CtInputEvent();
	inline Ct::KeyboardModifiers modifiers() const { return modState; }
	inline void setModifiers(Ct::KeyboardModifiers amodifiers) { modState = amodifiers; }
	inline ulong timestamp() const { return ts; }
	inline void setTimestamp(ulong atimestamp) { ts = atimestamp; }
protected:
	Ct::KeyboardModifiers modState;
	ulong ts;
};


class CT_EVENT_H CtTimerEvent : public CtEvent
{
public:
	explicit CtTimerEvent(cthandle timerId);
	~CtTimerEvent();
	cthandle timerId() const { return id; }
protected:
	cthandle id;
};


class CT_EVENT_H CtResizeEvent : public CtEvent
{
public:
	CtResizeEvent(const CtSize &size, const CtSize &oldSize);
	~CtResizeEvent();

	inline const CtSize &size() const { return s; }
	inline const CtSize &oldSize()const { return olds; }
protected:
	CtSize s, olds;
	friend class QApplication;
};

class CT_EVENT_H CtHoverEvent : public CtInputEvent
{
public:
	CtHoverEvent(Type type, const CtPointF &pos, const CtPointF &oldPos, Ct::KeyboardModifiers modifiers = Ct::NoModifier);
	~CtHoverEvent();

	inline CtPoint pos() const { return p.toPoint(); }
	inline CtPoint oldPos() const { return op.toPoint(); }

	inline const CtPointF &posF() const { return p; }
	inline const CtPointF &oldPosF() const { return op; }

protected:
	CtPointF p, op;
};

class CT_EVENT_H CtCloseEvent : public CtEvent
{
public:
	CtCloseEvent();
	~CtCloseEvent();
};


class CT_EVENT_H CtFocusEvent : public CtEvent
{
public:
	explicit CtFocusEvent(Type type, Ct::FocusReason reason = Ct::OtherFocusReason);
	~CtFocusEvent();

	inline bool gotFocus() const { return type() == FocusIn; }
	inline bool lostFocus() const { return type() == FocusOut; }
};



class CT_EVENT_H CtMouseEvent : public CtInputEvent
{
public:
	CtMouseEvent(Type type = CtEvent::MouseButtonPress) : CtInputEvent(type) {}
	CtMouseEvent(Type type, const CtPointF &localPos, Ct::MouseButton button,
		Ct::MouseButtons buttons, Ct::KeyboardModifiers modifiers);
	CtMouseEvent(Type type, const CtPointF &localPos, const CtPointF &screenPos,
		Ct::MouseButton button, Ct::MouseButtons buttons,
		Ct::KeyboardModifiers modifiers);
	CtMouseEvent(Type type, const CtPointF &localPos, const CtPointF &windowPos, const CtPointF &screenPos,
		Ct::MouseButton button, Ct::MouseButtons buttons,
		Ct::KeyboardModifiers modifiers);
	~CtMouseEvent();

	inline CtPoint pos() const { return l.toPoint(); }
	inline CtPoint globalPos() const { return s.toPoint(); }
	inline int x() const { return (int)(int)round(l.x()); }
	inline int y() const { return (int)(int)round(l.y()); }
	inline int globalX() const { return (int)(int)round(s.x()); }
	inline int globalY() const { return (int)(int)round(s.y()); }

	const CtPointF &localPos() const { return l; }
	const CtPointF &windowPos() const { return w; }
	const CtPointF &screenPos() const { return s; }

	inline Ct::MouseButton button() const { return b; }
	inline Ct::MouseButtons buttons() const { return mouseState; }

protected:
	CtPointF l, w, s;
	Ct::MouseButton b;
	Ct::MouseButtons mouseState;
	int caps;
};

class CT_EVENT_H CtKeyEvent : public CtInputEvent
{
public:
	CtKeyEvent(Type type, int key, Ct::KeyboardModifiers modifiers, const CtString& text = CtString(),
		bool autorep = false, ctushort count = 1);
	CtKeyEvent(Type type, int key, Ct::KeyboardModifiers modifiers,
		ctuint32 nativeScanCode, ctuint32 nativeVirtualKey, ctuint32 nativeModifiers,
		const CtString &text = CtString(), bool autorep = false, ctushort count = 1);
	~CtKeyEvent();

	int key() const { return k; }

	Ct::KeyboardModifiers modifiers() const;
	inline CtString text() const { return txt; }
	inline bool isAutoRepeat() const { return autor; }
	inline int count() const { return int(c); }

	inline ctuint32 nativeScanCode() const { return nScanCode; }
	inline ctuint32 nativeVirtualKey() const { return nVirtualKey; }
	inline ctuint32 nativeModifiers() const { return nModifiers; }


protected:
	CtString txt;
	int k;
	ctuint32 nScanCode;
	ctuint32 nVirtualKey;
	ctuint32 nModifiers;
	ctushort c;
	ctushort autor : 1;
	// ushort reserved:15;
};

class CT_EVENT_H CtShowEvent : public CtEvent
{
public:
	CtShowEvent();
	~CtShowEvent() {}
};


class CT_EVENT_H CtHideEvent : public CtEvent
{
public:
	CtHideEvent();
	~CtHideEvent() {}
};

#endif // !CT_EVENT_H
