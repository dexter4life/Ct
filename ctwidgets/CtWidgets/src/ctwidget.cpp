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


#include <ctcore/ctglobal.h>
#include <CtCore/ctobject.h>
#include <CtWidgets/ctwidget.h>
#include <memory>

#ifdef WIN32
#include <WinUser.h>
#define TID_TRACK 10320

#endif // WIN32

/**
* Windows specific implementation class
*/
#ifndef WIDGET_PRIVATE_H
#define WIDGET_PRIVATE_H

typedef bool(CtObject::*FuncType)(CtObject *, CtEvent*);

class WIDGET_PRIVATE_H CtWidgetWindowPrivateImp : public CtObject
{
	//declare window event handler class
	DECLARE_WNDPROC_HANDLER(EventHandler)
	
	DISABLE_COPY(CtWidgetWindowPrivateImp)
	
	friend class CtWidget;
public:
	explicit CtWidgetWindowPrivateImp(const CtWidget *widgetClass) : m_eventHandler(nullptr),
		m_hasEntered(false),
		m_isModifierFlag(false),
		m_fixedSize(0, 0),
		m_hwndParent(nullptr),
		m_hwndChild(nullptr),
		m_object(const_cast<CtWidget*>(widgetClass)),
		m_updateEnabled(true)
	{

	}
private:
	inline CtRect rect() const
	{
		CtRect rt;
#ifdef WIN32
		GetClientRect(m_hwndChild, reinterpret_cast<LPRECT>(&rt));
		if (m_rect == rt) {
			return m_rect;
		}
		return rt;
#endif // WIN32
	}

	LRESULT nativeEvent(Message &message)
	{
		m_object->nativeEvent(message);

#ifdef WIN32
		switch (message.msg())
		{
		case WM_CREATE:
		{
			m_hwndChild = message.handle();
			GetClientRect(m_hwndChild, reinterpret_cast<LPRECT>(&m_rect));
			CtEvent e(CtEvent::Create);

			if (m_object) (*m_object.*m_eventHandler)(this, &e);
		}
		case WM_SIZE:
		{
			CtSize oldSize = m_size;
			m_size = message.toSize();

			///* code to prevent the window from exceeding a "full text page" */
			//BOOL resize = FALSE;

			//if (m_size.width() > m_fixedSize.width())
			//{
			//	resize = TRUE;
			//	m_size.setWidth(m_fixedSize.width());
			//}
			//if (m_size.height() > m_fixedSize.height())
			//{
			//	resize = TRUE;
			//	m_size.setHeight(m_fixedSize.height());
			//}
			//if (resize)
			//	SetWindowPos(message.handle(),
			//		GetNextWindow(message.handle(), GW_HWNDPREV),
			//		0, 0,
			//		m_fixedSize.width(), m_fixedSize.height(),
			//		SWP_NOMOVE);

			//	CtRect rect = clientToScreen(m_rect);
			//	MoveWindow(message.handle(), rect.x(), rect.y(), rect.width(), rect.height(), true);
			//resize(0, 100);
			//	if (m_fixedSize.width() > 1 && m_fixedSize.height()<=0/*if only the width is specified*/)
			//	{
			//		resize(m_fixedSize.width(), 0);
			//	}
			//	else if (m_fixedSize.height() > 1 && m_fixedSize.width()<=0/*if only the height is specified*/)
			//	{
			//		resize(0, m_fixedSize.height());
			//	}
			CtResizeEvent e(m_size, oldSize);

			if (m_object) (*m_object.*m_eventHandler)(this, static_cast<CtEvent*>(&e));
		}
		break;
		case WM_SIZING:
		{
			CtRect *rect = (CtRect*)message.lParam();
			CtResizeEvent e(rect->size(), m_rect.size());

			switch (message.wParam())
			{
			case WMSZ_BOTTOM:	//Bottom edge
			{
				//	resize(300, 0);
			}
			break;
			case WMSZ_BOTTOMLEFT: //Bottom - left corner
				break;
			case WMSZ_BOTTOMRIGHT: //Bottom - right corner
				break;
			case WMSZ_LEFT: // Left edge
				break;
			case WMSZ_RIGHT: //Right edge
				break;
			case WMSZ_TOP: //Top edge
				break;
			case WMSZ_TOPLEFT: //Top - left corner
				break;
			case WMSZ_TOPRIGHT://Top - right corner
				break;
			}


			if (m_object) (*m_object.*m_eventHandler)(this, static_cast<CtEvent*>(&e));
		}
		break;
		case WM_MOVING:
		{

		}
		break;
		// We accept this so we can scale our controls to the client size.
		case WM_WINDOWPOSCHANGING:
		case WM_WINDOWPOSCHANGED:
		{
			//		LPWINDOWPOS wp = (LPWINDOWPOS)lParam;
		}
		break;
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(message.handle(), &ps);

			// TODO: Add any drawing code here...

			EndPaint(message.handle(), &ps);
		}
		break;
		case WM_DESTROY:
		{
			PostQuitMessage(0);

			CtEvent e(CtEvent::Destroy);

			if (m_object) (*m_object.*m_eventHandler)(this, static_cast<CtEvent*>(&e));
		}
		break;
		case WM_SHOWWINDOW:
		{
			if ((BOOL)message.wParam()) {
				//show window
				CtShowEvent e;
				if (m_object) (*m_object.*m_eventHandler)(this, static_cast<CtEvent*>(&e));
			}
			else {
				//hide window
				CtHideEvent e;
				if (m_object) (*m_object.*m_eventHandler)(this, static_cast<CtEvent*>(&e));
			}
		}
		break;
		case WM_ACTIVATE:
		{
			int fActive = LOWORD(message.wParam()); // activation flag 
			switch (fActive)
			{
			case WA_ACTIVE:
			case WA_CLICKACTIVE:
				m_windowActive = true;
				break;
			case WA_INACTIVE:
				m_windowActive = false;
				break;
			}
			m_winMinMax = ((BOOL)HIWORD(message.wParam())) ? true : false; // minimized flag 
			HWND hwndPrevious = (HWND)message.lParam();   // window handle 
		}
		break;
		case WM_CLOSE:
		{
			CtCloseEvent e;
			if (m_object) (*m_object.*m_eventHandler)(this, static_cast<CtEvent*>(&e));

			DefWindowProc(message.handle(), message.msg(), message.wParam(), message.lParam());
		}
		break;
		case WM_LBUTTONDBLCLK:
		case WM_MBUTTONDBLCLK:
		case WM_RBUTTONDBLCLK:
		{
			CtPointF localPos(message.toPointF()), windowPos, screenPos;

			Ct::MouseButton button = Ct::MouseButton::LeftButton;

			windowPos = mapToParent(localPos.toPoint());
			screenPos = screenToClient(localPos.toPoint());

			if (message.wParam() & MK_LBUTTON)
			{
				CtMouseEvent mouseEvent(CtMouseEvent::MouseButtonDblClick, localPos, windowPos, screenPos, button,
					Ct::MouseButton::LeftButton, setModifier(message.wParam()));
				if (m_object) (*m_object.*m_eventHandler)(this, static_cast<CtEvent*>(&mouseEvent));
			}
			if (message.wParam() & MK_RBUTTON)
			{
				CtMouseEvent mouseEvent(CtMouseEvent::MouseButtonDblClick, localPos, windowPos, screenPos, button,
					Ct::MouseButton::RightButton, setModifier(message.wParam()));

				if (m_object) (*m_object.*m_eventHandler)(this, static_cast<CtEvent*>(&mouseEvent));
			}
			if (message.wParam() & MK_MBUTTON)
			{
				CtMouseEvent mouseEvent(CtMouseEvent::MouseButtonDblClick, localPos, windowPos, screenPos, button,
					Ct::MouseButton::BackButton, setModifier(message.wParam()));

				if (m_object) (*m_object.*m_eventHandler)(this, static_cast<CtEvent*>(&mouseEvent));
			}
		}
		break;
		case WM_LBUTTONDOWN:
		case WM_RBUTTONDOWN:
		case WM_MBUTTONDOWN:
		{
			CtPointF localPos(message.toPointF()), windowPos, screenPos;

			windowPos = mapToParent(localPos.toPoint());
			screenPos = screenToClient(localPos.toPoint());

			if (message.wParam() & MK_LBUTTON)
			{
				Ct::MouseButton button = Ct::MouseButton::LeftButton;
				CtMouseEvent mouseEvent(CtMouseEvent::MouseButtonPress, localPos, windowPos, screenPos, button,
					Ct::MouseButton::LeftButton, setModifier(message.wParam()));

				if (m_object) (*m_object.*m_eventHandler)(this, static_cast<CtEvent*>(&mouseEvent));
			}
			if (message.wParam() & MK_RBUTTON)
			{
				Ct::MouseButton button = Ct::MouseButton::RightButton;
				CtMouseEvent mouseEvent(CtMouseEvent::MouseButtonPress, localPos, windowPos, screenPos, button,
					Ct::MouseButton::RightButton, setModifier(message.wParam()));

				if (m_object) (*m_object.*m_eventHandler)(this, static_cast<CtEvent*>(&mouseEvent));
			}
			if (message.wParam() & MK_MBUTTON)
			{
				Ct::MouseButton button = Ct::MouseButton::BackButton;
				CtMouseEvent mouseEvent(CtMouseEvent::MouseButtonPress, localPos, windowPos, screenPos, button,
					Ct::MouseButton::BackButton, setModifier(message.wParam()));

				if (m_object) (*m_object.*m_eventHandler)(this, static_cast<CtEvent*>(&mouseEvent));
			}
		}
		break;
		case WM_LBUTTONUP:
		case WM_RBUTTONUP:
		case WM_MBUTTONUP:
		{
			CtPointF localPos(message.toPointF()), windowPos, screenPos;

			windowPos = mapToParent(localPos.toPoint());
			screenPos = screenToClient(localPos.toPoint());

			if (message.wParam() & MK_LBUTTON)
			{
				Ct::MouseButton button = Ct::MouseButton::LeftButton;
				CtMouseEvent mouseEvent(CtMouseEvent::MouseButtonRelease, localPos, windowPos, screenPos, button,
					Ct::MouseButton::LeftButton, setModifier(message.wParam()));

				if (m_object) (*m_object.*m_eventHandler)(this, static_cast<CtEvent*>(&mouseEvent));
			}
			if (message.wParam() & MK_RBUTTON)
			{
				Ct::MouseButton button = Ct::MouseButton::RightButton;
				CtMouseEvent mouseEvent(CtMouseEvent::MouseButtonRelease, localPos, windowPos, screenPos, button,
					Ct::MouseButton::RightButton, setModifier(message.wParam()));

				if (m_object) (*m_object.*m_eventHandler)(this, static_cast<CtEvent*>(&mouseEvent));
			}
			if (message.wParam() & MK_MBUTTON)
			{
				Ct::MouseButton button = Ct::MouseButton::BackButton;
				CtMouseEvent mouseEvent(CtMouseEvent::MouseButtonRelease, localPos, windowPos, screenPos, button,
					Ct::MouseButton::BackButton, setModifier(message.wParam()));

				if (m_object) (*m_object.*m_eventHandler)(this, static_cast<CtEvent*>(&mouseEvent));
			}
		}
		break;
		case WM_MOUSEMOVE:
		{
			CtRect rt = rect();

			CtPoint pt = clientToScreen(message.toPoint());

			rt = clientToScreen(rt);

			/*mouse track structure*/
			TRACKMOUSEEVENT m_trackMouse;
			m_trackMouse.cbSize = sizeof(TRACKMOUSEEVENT);
			m_trackMouse.dwFlags = TME_LEAVE | TME_HOVER;
			m_trackMouse.dwHoverTime = HOVER_DEFAULT;
			m_trackMouse.hwndTrack = m_hwndChild;

			TrackMouseEvent(&m_trackMouse);

			//is in client rectangle
			if (rt.contains(pt))
			{
				if (!m_hasEntered)
				{
					m_hasEntered = true;
					CtEvent enter(CtEvent::Enter);
					if (m_object) (*m_object.*m_eventHandler)(this, static_cast<CtEvent*>(&enter));
				}

				CtPointF localPos(message.toPointF()), windowPos, screenPos;

				windowPos = mapToParent(localPos.toPoint());
				screenPos = screenToClient(localPos.toPoint());

				if (message.wParam() & MK_LBUTTON)
				{
					Ct::MouseButton button = Ct::MouseButton::LeftButton;
					CtMouseEvent mouseEvent(CtMouseEvent::MouseMove, localPos, windowPos, screenPos, button,
						button, setModifier(message.wParam()));

					if (m_object) (*m_object.*m_eventHandler)(this, static_cast<CtEvent*>(&mouseEvent));
				}
				else if (message.wParam() & MK_RBUTTON)
				{
					Ct::MouseButton button = Ct::MouseButton::RightButton;
					CtMouseEvent mouseEvent(CtMouseEvent::MouseMove, localPos, windowPos, screenPos, button,
						button, setModifier(message.wParam()));

					if (m_object) (*m_object.*m_eventHandler)(this, static_cast<CtEvent*>(&mouseEvent));
				}
				else if (message.wParam() & MK_MBUTTON)
				{
					Ct::MouseButton button = Ct::MouseButton::BackButton;
					CtMouseEvent mouseEvent(CtMouseEvent::MouseMove, localPos, windowPos, screenPos, button,
						button, setModifier(message.wParam()));

					if (m_object) (*m_object.*m_eventHandler)(this, static_cast<CtEvent*>(&mouseEvent));
				}
				else if (!(message.wParam() & MK_RBUTTON) && !(message.wParam() & MK_LBUTTON) && !(message.wParam() & MK_MBUTTON))
				{
					Ct::MouseButton button = Ct::MouseButton::NoButton;
					CtMouseEvent mouseEvent(CtMouseEvent::MouseMove, localPos, windowPos, screenPos, button,
						button, setModifier(message.wParam()));

					if (m_object) (*m_object.*m_eventHandler)(this, static_cast<CtEvent*>(&mouseEvent));
				}
			}
		}
		break;
		break;
		case WM_TIMER:
		{
			TRACE("TRACE[ %1 ]\n", "WM_TIMER");

		}
		break;
		case WM_SETFOCUS:
		{
			////get cursor current position
			//CtPoint cursorPos;
			//GetCursorPos((LPPOINT)&cursorPos);
			////focus enum
			//Ct::FocusReason focusReason;

			//point is inside the client or current window rect recieving the focus
			/*	if (rect().contains(cursorPos)) {
			focusReason = Ct::FocusReason::MouseFocusReason;
			}
			*/

			CtFocusEvent event(CtEvent::FocusIn);
			if (m_object) (*m_object.*m_eventHandler)(this, static_cast<CtEvent*>(&event));
		}
		break;
		case WM_KILLFOCUS:
		{
			////get cursor current position
			//CtPoint cursorPos;
			//GetCursorPos((LPPOINT)&cursorPos);
			////focus enum
			//Ct::FocusReason focusReason;

			////point is inside the client or current window rect recieving the focus
			//if (rect().contains(cursorPos)) {
			//	focusReason = Ct::FocusReason::MouseFocusReason;
			//}

			CtFocusEvent event(CtEvent::FocusOut);
			if (m_object) (*m_object.*m_eventHandler)(this, static_cast<CtEvent*>(&event));
		}
		break;
		case WM_DROPFILES:
		{

		}
		break;
		case WM_MOUSEHOVER:
		{
			CtPointF localPos(message.toPointF()), windowPos, screenPos;

			windowPos = mapToParent(localPos.toPoint());
			screenPos = screenToClient(localPos.toPoint());

			Ct::MouseButton button = Ct::MouseButton::LeftButton;
			CtMouseEvent mouseEvent(CtMouseEvent::MouseMove, localPos, windowPos, screenPos, button,
				button, setModifier(message.wParam()));

			if (m_object) (*m_object.*m_eventHandler)(this, static_cast<CtEvent*>(&mouseEvent));
		}
		break;
		case WM_MOUSELEAVE:
		{
			CtEvent leave(CtEvent::Leave);
			(*m_object.*m_eventHandler)(this, static_cast<CtEvent*>(&leave));

			m_hasEntered = false;
		}
		break;
		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
		{
			int nVirtKey = (size_t)message.wParam();    // virtual-key code 

			Ct::KeyboardModifier modifiers;
			if (GetAsyncKeyState(VK_CONTROL) < 0)
			{
				modifiers = Ct::ControlModifier;
			}
			else if (GetAsyncKeyState(VK_SHIFT) < 0)
			{
				modifiers = Ct::ShiftModifier;
			}
			else if (GetAsyncKeyState(VK_MENU) < 0)
			{
				modifiers = Ct::AltModifier;
			}
			else modifiers = Ct::NoModifier;

			CtKeyEvent keyEvent(CtEvent::KeyPress, nVirtKey, modifiers);

			if (m_object) (*m_object.*m_eventHandler)(this, reinterpret_cast<CtEvent*>(&keyEvent));
		}
		break;
		case WM_KEYUP:
		case WM_SYSKEYUP:
		{
			int nVirtKey = (size_t)message.wParam();

			Ct::KeyboardModifier modifiers;
			modifiers = Ct::NoModifier;

			CtKeyEvent keyEvent(CtEvent::KeyRelease, nVirtKey, modifiers);

			if (m_object) (*m_object.*m_eventHandler)(this, reinterpret_cast<CtEvent*>(&keyEvent));
		}
		break;
		case WM_GETMINMAXINFO:
		{
			////size was specified
			//if (!m_fixedSize.isNull() && !m_fixedSize.isEmpty())
			//{
			//	if (m_fixedSize.width() > 0) {
			//		//width was set only
			//		((MINMAXINFO*)message.lParam())->ptMinTrackSize.x = m_fixedSize.width();
			//	}
			//	else if (m_fixedSize.height() > 0) {
			//		//height was set only
			//		((MINMAXINFO*)message.lParam())->ptMinTrackSize.y = m_fixedSize.height();
			//	}
			//	else {
			//		//both was set
			//		((MINMAXINFO*)message.lParam())->ptMinTrackSize.x = m_fixedSize.width();
			//		((MINMAXINFO*)message.lParam())->ptMinTrackSize.y = m_fixedSize.height();
			//	}
			//}
			//((MINMAXINFO*)message.lParam())->ptMaxSize.x = 100;
			//((MINMAXINFO*)message.lParam())->ptMaxSize.y = 100;
		}
		break;
		default:
			return DefWindowProc(message.handle(), message.msg(), message.wParam(), message.lParam());
		}
#endif // WIN32
		return 0;//DefWindowProc(message.handle(), message.msg(), message.wParam(), message.lParam());
	}

	CtPoint mapToParent(const CtPoint &point)
	{
		auto pt = point;
		MapWindowPoints(m_hwndChild, m_hwndParent, (LPPOINT)&pt, 1);
		return point;
	}

	void resize(const CtSize &s)
	{
		if (s.width() > 1 && s.height() <= 0)
		{
			m_rect.setWidth(s.width());
			SetWindowPos(m_hwndChild, 0, 0, 0, m_rect.width(),
				m_rect.height(), SWP_SHOWWINDOW | SWP_NOMOVE);
			return;
		}
		else if (s.width() <= 0 && s.height() > 1)
		{
			m_rect.setHeight(s.height());
			SetWindowPos(m_hwndChild, 0, 0, 0, m_rect.width(),
				m_rect.height(), SWP_SHOWWINDOW | SWP_NOMOVE);

			return;
		}

		m_rect.setSize(s);
		CtRect rect = clientToScreen(m_rect);
		SetWindowPos(m_hwndChild, 0, 0, 0, m_rect.width(),
			m_rect.height(), SWP_SHOWWINDOW | SWP_NOMOVE);
	}

	inline CtSize size() const
	{
		return m_rect.size();
	}
	void caputeMouse() const
	{
		SetCapture(m_hwndChild);
	}
	CtPoint screenToClient(const CtPoint &point)
	{
		auto pt = point;
		::ScreenToClient(m_hwndChild, (LPPOINT)&pt);
		return pt;
	}

	inline CtPoint clientToScreen(const CtPoint &point)
	{
		CtPoint pt(point.x(), point.y());
		::ClientToScreen(m_hwndChild, (LPPOINT)&pt);
		return pt;
	}

	CtRect screenToClient(const CtRect &rect)
	{
		auto t_rect = rect;
		MapWindowPoints(HWND_DESKTOP, m_hwndChild, LPPOINT(&t_rect), 2);
		return t_rect;
	}

	CtRect clientToScreen(const CtRect &rect)
	{
		CtRect t_rect(rect.left(), rect.top(), rect.width(), rect.height());
		MapWindowPoints(m_hwndChild, HWND_DESKTOP, LPPOINT(&t_rect), 2);
		return t_rect;
	}

	void resize(int w, int h)
	{
		resize(CtSize{ w,h });
	}

	void registerWindowsClass()
	{
		if (!RegisterClassEx(&m_windowClass))
		{
			MessageBox(NULL, CtString("Can't register window class"), CtString("Register Error"),
				MB_OK | MB_ICONERROR);
			exit(EXIT_FAILURE);
		}
	}

	void initializeWindow()
	{
		memset(&m_windowClass, 0, sizeof(WNDCLASSEX));

		m_hInstance = GetModuleHandle(NULL);

		m_className = typeid(*this).raw_name();
		//set structure pre-information
		m_windowClass.cbSize = sizeof(WNDCLASSEX);
		m_windowClass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
		m_windowClass.cbClsExtra = 0;
		m_windowClass.cbWndExtra = 0;
		m_windowClass.hInstance = GetModuleHandle(NULL);
		m_windowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		m_windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
		m_windowClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		m_windowClass.lpszMenuName = NULL;
		m_windowClass.lpszClassName = m_className;
		m_windowClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

		ASSIGN_EVENT_HANDLER([this](HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)->LRESULT
		{
			//#ifdef WIN32
			if (message == WM_CREATE) {
				//child handle
				m_hwndChild = hwnd;
				//	setChildHandle(hwnd);
				m_hwndParent = GetParent(hwnd);
			}

			Message msg(hwnd, message, wParam, lParam);

			return nativeEvent(msg);

		});

		m_windowClass.lpfnWndProc = (WNDPROC)WINPROCHANDLE;

		//register class
		registerWindowsClass();
	}

	void setParent(cthandle hwndParent)
	{
		::SetParent(m_hwndChild, (HWND)hwndParent);
	}

	void assignEventHandler(FuncType func)
	{
		m_eventHandler = func;
	}

	static CtWidgetWindowPrivateImp *getInstance(const CtWidget *classPtr)
	{
		static std::unique_ptr<CtWidgetWindowPrivateImp> instancePtr =
			std::make_unique<CtWidgetWindowPrivateImp>(classPtr);

		return instancePtr.get();
	}

	inline cthandle childHandle() const
	{
		return (cthandle)m_hwndChild;
	}

	inline cthandle parentHandle() const
	{
		return  (cthandle)m_hwndParent;
	}

	inline void setHandle(cthandle handle)
	{
		m_hwndChild = (HWND)handle;
	}

	inline void setFocus() const
		// The SetFocus function sets the keyboard focus to the window.
	{
		assert(::IsWindow(m_hwndChild));
		::SetFocus(m_hwndChild);
	}

	inline void setParentHandle(cthandle handle)
	{
		m_hwndParent = (HWND)handle;
	}

	inline HINSTANCE instanceHandle() const
	{
		return m_hInstance;
	}

	Ct::KeyboardModifiers setModifier(ctuint32 modifier)
	{
		Ct::KeyboardModifiers modifiers;

		if (modifier & MK_SHIFT)
		{
			if (modifier & MK_CONTROL)
			{
				//[Shift and Ctrl keys are down]
				modifiers = Ct::KeyboardModifier::ControlModifier | Ct::KeyboardModifier::ShiftModifier;
			}
			else
			{
				//	[Shift key is down]
				modifiers = Ct::KeyboardModifier::ShiftModifier;
			}
		}

		else
		{
			if (modifier & MK_CONTROL)
			{
				//CONTROL KEY INSTEAD
				modifiers = Ct::KeyboardModifier::ControlModifier;
			}
			else
			{
				modifiers = Ct::KeyboardModifier::NoModifier;
			}
		}
		return modifiers;
	}

	inline void hide()
	{
		ShowWindow(m_hwndChild, SW_HIDE);
	}

	inline void show()
	{
		ShowWindow(m_hwndChild, SW_SHOW);
	}

	inline void update()
	{
		UpdateWindow(m_hwndChild);
	}

	inline void setEnabled(bool value)
	{
		assert(isWindow());

		EnableWindow(m_hwndChild, value);
	}
	inline bool isEnabled() const
	{
		return (::IsWindowEnabled(m_hwndChild)) ? true : false;
	}

	inline bool isWindow() const
	{
		return (IsWindow(m_hwndChild)) ? true : false;
	}

	inline bool setWindowTitle(CtString text) const
	{
		if (!SetWindowText(m_hwndChild, text))
			return false;
		return true;
	}

	inline void move(int x, int y)
	{
		if (!MoveWindow(m_hwndChild, x, y, m_rect.width(), m_rect.height(), true))
			TRACE("%1", "Can't move window");
	}

	inline bool isWindowActive() const
	{
		return m_windowActive;
	}

	inline bool isMinimized() const
	{
		return !m_winMinMax;
	}

	inline bool isMiximized() const
	{
		return m_winMinMax;
	}

	void	setGeometry(const CtRect &rt)
	{
		setGeometry(rt.x(), rt.y(), rt.width(), rt.height());
	}

	void	setGeometry(int x, int y, int w, int h)
	{
		assert(isWindow());

		m_rect.setRect(x, y, w, h);

		MoveWindow(m_hwndChild, x, y, w, h, true);
	}

	void setFixedHeight(int h)
	{
		if (h > 1)
		{
			m_fixedSize.setHeight(h);

			long dwStyle;
			dwStyle = GetWindowLong(m_hwndChild, GWL_STYLE);
			dwStyle ^= WS_MAXIMIZEBOX;
			SetWindowLong(m_hwndChild, GWL_STYLE, dwStyle);

			resize(0, h);
		}
	}
	void setFixedWidth(int w)
	{
		if (w > 1)
		{
			m_fixedSize.setWidth(w);

			long dwStyle;
			dwStyle = GetWindowLong(m_hwndChild, GWL_STYLE);
			dwStyle ^= WS_MAXIMIZEBOX;
			SetWindowLong(m_hwndChild, GWL_STYLE, dwStyle);

			resize(w, 0);
		}
	}

	bool isVisible() const
	{
		return (::IsWindowVisible(m_hwndChild)) ? true : false;
	}

	void setWindowState(bool bNewState)
	{
		bool    bEnabled;

		bEnabled = (isEnabled() != FALSE);

		if (bEnabled != bNewState)
			EnableWindow(m_hwndChild, bNewState);
	}

	void setFixedSize(const CtSize & s)
	{
		if (!s.isEmpty())
		{
			setFixedHeight(s.height());
			setFixedWidth(s.width());

			long dwStyle;
			dwStyle = GetWindowLong(m_hwndChild, GWL_STYLE);
			dwStyle ^= WS_SIZEBOX | WS_MAXIMIZEBOX;
			SetWindowLong(m_hwndChild, GWL_STYLE, dwStyle);

			resize(s);
		}
	}

	CtString	className() const
	{
		return m_className;
	}

	void	update(CtRect rt)
	{
		assert(::IsWindow(m_hwndChild));
		RedrawWindow(m_hwndChild, (tagRECT*)&rt, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
	}

	inline void setUpdatesEnabled(bool enable)
	{
		assert(::IsWindow(m_hwndChild));
		SendMessage(m_hwndChild, WM_SETREDRAW, enable, 0);
		m_updateEnabled = enable;
	}

	inline bool updateEnabled() const
	{
		return m_updateEnabled;
	}

	// The MapWindowPoints function converts (maps) a set of points from a coordinate space relative to one
	// window to a coordinate space relative to another window.
	inline void mapWindowPoints(CtWidget* pWidgetTo, CtPoint *ptArray) const
	{
		assert(m_hwndChild);
		if (pWidgetTo)
		{
			assert(pWidgetTo->handle());
			::MapWindowPoints(m_hwndChild, (HWND)pWidgetTo->handle(), (LPPOINT)ptArray, 1);
		}
		else
			::MapWindowPoints(m_hwndChild, NULL, (LPPOINT)ptArray, 1);
	}
	// The MapWindowPoints function converts (maps) a set of points from a coordinate space relative to one
	// window to a coordinate space relative to another window.
	inline void mapWindowPoints(CtWidget* pWidgetTo, CtRect &rc) const
	{
		assert(m_hwndChild);
		if (pWidgetTo)
		{
			assert(pWidgetTo->handle());
			::MapWindowPoints(m_hwndChild, (HWND)pWidgetTo->handle(), (LPPOINT)&rc, 2);
		}
		else
			::MapWindowPoints(m_hwndChild, NULL, (LPPOINT)&rc, 2);
	}
	// The GetWindowTextLength function retrieves the length, in characters, of the specified window's
	// title bar text (if the window has a title bar).
	inline int GetWindowTextLength() const
	{
		assert(isWindow());
		return ::GetWindowTextLength(m_hwndChild);
	}

	// The Invalidate function adds the entire client area the window's update region.
	// The update region represents the portion of the window's client area that must be redrawn.
	inline void invalidate(bool erase /*= TRUE*/) const
	{
		assert(isWindow());
		::InvalidateRect(m_hwndChild, NULL, erase);
	}

	// The InvalidateRect function adds a rectangle to the window's update region.
	// The update region represents the portion of the window's client area that must be redrawn.
	inline BOOL invalidateRect(CtRect *lpRect, bool erase /*= TRUE*/) const
	{
		assert(isWindow());
		return ::InvalidateRect(m_hwndChild, (LPRECT)lpRect, erase);
	}

	// The IsChild function tests whether a window is a child window or descendant window
	// of a parent window's CWnd.
	inline BOOL isChild(CtWidget* pChildWidget) const
	{
		assert(::IsWindow(m_hwndChild));
		return ::IsChild(m_hwndChild, (HWND)pChildWidget->handle());
	}
private:
	//window attribute
	CtString m_className;

	WNDCLASSEX m_windowClass;

	HWND m_hwndParent, m_hwndChild;

	HINSTANCE m_hInstance;

	FuncType m_eventHandler;

	CtWidget *m_object;

	//virtual Key modifier 
	int m_virtKey;
	bool m_hasEntered;


	CtRect m_rect;
	CtSize m_size;

	//save the key pressed in combinations
	std::map<size_t, std::vector<ctuint32>> m_vCombineKeys;
	//flat to watch for other keys pressed in combination
	bool		m_isModifierFlag;
	size_t		m_modifier;
	bool		m_windowActive, m_winMinMax;
	CtSize		m_fixedSize;
	bool		m_updateEnabled;
};
#endif // !WIDGET_PRIVATE_H

/*******************************************************************/

CtWidget::CtWidget(CtWidget * parent)
	: CtObject(reinterpret_cast<CtObject*>(parent)),
	dd(new CtWidgetWindowPrivateImp(this))
{
	assert(dd);

	dd->initializeWindow();

	dd->assignEventHandler(&CtWidget::eventFilter);

	if (!parent)//if null then is parent
	{
		dd->setHandle((cthandle)CreateWindowEx(WS_EX_CLIENTEDGE,
			dd->className(),
			CtString("Ct Application"),
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			NULL,
			NULL,
			dd->instanceHandle(),
			NULL
		));

		setHandle(dd->childHandle());
	}
	else //is a child widget
	{

	}
}
CtWidget::~CtWidget()
{
	delete dd;
}
void CtWidget::setParent(CtWidget * parent)
{
	dd->setParent(parent->handle());
}

void CtWidget::update(int x, int y, int w, int h)
{
	dd->update({ x,y,w,h });
}

void CtWidget::update(const CtRect & rect)
{
	update(rect.x(), rect.y(), rect.width(), rect.height());
}

bool CtWidget::updatesEnabled() const
{
	return dd->updateEnabled();
}

void CtWidget::setUpdateEnabled(bool enable)
{
	dd->setUpdatesEnabled(enable);
}

int CtWidget::x() const
{
	return dd->rect().x();
}

int CtWidget::y() const
{
	return dd->rect().x();
}

void CtWidget::caputeMouse() const
{
	dd->caputeMouse();
}

CtPoint CtWidget::mapToParent(const CtPoint &pt)
{
	return dd->mapToParent(pt);
}

void CtWidget::mapWindowPoints(CtWidget * pWidgetTo, CtPoint *ptArray) const
{
	dd->mapWindowPoints(pWidgetTo, ptArray);
}

void CtWidget::mapWindowPoints(CtWidget * pWidgetTo, CtRect & rc) const
{
	dd->mapWindowPoints(pWidgetTo, rc);
}

CtPoint CtWidget::screenToClient(const CtPoint &pt)
{
	return dd->screenToClient(pt);
}
inline CtPoint CtWidget::clientToScreen(const CtPoint &pt)
{
	return dd->clientToScreen(pt);
}
CtRect CtWidget::screenToClient(const CtRect &rect)
{
	return dd->screenToClient(rect);
}
CtRect CtWidget::clientToScreen(const CtRect &rect)
{
	return dd->clientToScreen(rect);
}

inline CtRect CtWidget::rect() const
{
	return dd->rect();
}

void CtWidget::setGeometry(const CtRect & rt)
{
	dd->setGeometry(rt);
}

void CtWidget::setGeometry(int x, int y, int w, int h)
{
	dd->setGeometry(x, y, w, h);
}

bool CtWidget::event(CtEvent * e)
{
	switch (e->type())
	{
	case CtEvent::MouseButtonDblClick:
		mouseDoubleClickEvent(reinterpret_cast<CtMouseEvent*>(e));
		return true;

	case CtEvent::MouseButtonPress:
		mousePressEvent(reinterpret_cast<CtMouseEvent*>(e));
		return true;

	case CtEvent::MouseButtonRelease:
		mouseReleaseEvent(reinterpret_cast<CtMouseEvent*>(e));
		return true;

	case CtEvent::MouseMove:
		mouseMoveEvent(reinterpret_cast<CtMouseEvent*>(e));
		return true;

	case CtEvent::Enter:
		enterEvent(e);
		return true;

	case CtEvent::Leave:
		leaveEvent(e);
		return true;

	case CtEvent::Resize:
		resizeEvent(reinterpret_cast<CtResizeEvent*>(e));
		return true;

	case CtEvent::FocusIn:
		focusInEvent(reinterpret_cast<CtFocusEvent*>(e));
		return true;

	case CtEvent::FocusOut:
		focusOutEvent(reinterpret_cast<CtFocusEvent*>(e));
		return true;
	case CtEvent::KeyPress:
		keyPressEvent(reinterpret_cast<CtKeyEvent*>(e));
		return true;
	case CtEvent::KeyRelease:
		keyPressEvent(reinterpret_cast<CtKeyEvent*>(e));
		return true;
	case CtEvent::Show:
		showEvent(reinterpret_cast<CtShowEvent*>(e));
		return true;
	case CtEvent::Hide:
		hideEvent(reinterpret_cast<CtHideEvent*>(e));
		return true;
	}
	return false;
}
void CtWidget::hide()
{
	dd->hide();
}

void CtWidget::show()
{
	dd->show();
}

void CtWidget::setEnabled(bool value)
{
	dd->setEnabled(value);
}

bool CtWidget::isEnabled() const
{
	return dd->isEnabled();
}

bool CtWidget::isWindow() const
{
	return dd->isWindow();
}

void CtWidget::move(const CtPoint &pt)
{
	move(pt.x(), pt.y());
}

void CtWidget::move(int x, int y)
{
	return dd->move(x, y);
}

bool CtWidget::isWindowActive() const
{
	return dd->isWindowActive();
}

bool CtWidget::isMinimized() const
{
	return dd->isMinimized();
}

bool CtWidget::isMiximized() const
{
	return dd->isMiximized();
}

CtSize CtWidget::size() const
{
	return dd->size();
}

void CtWidget::resize(const CtSize &sz)
{
	dd->resize(sz);
}

void CtWidget::resize(int w, int h)
{
	dd->resize(w, h);
}

void CtWidget::setFixedHeight(int h)
{
	dd->setFixedHeight(h);
}
void CtWidget::setFixedWidth(int w)
{
	dd->setFixedWidth(w);
}

//void CtWidgetWindowImp::resize(const CtSize &s)
//{
//	if (s.width() > 1 && s.height() <= 0)
//	{
//		m_rect.setWidth(s.width());
//		SetWindowPos(m_hwndChild, 0, 0, 0, m_rect.width(),
//			m_rect.height(), SWP_SHOWWINDOW | SWP_NOMOVE);
//		return;
//	}
//	else if (s.width() <= 0 && s.height() > 1)
//	{
//		m_rect.setHeight(s.height());
//		SetWindowPos(m_hwndChild, 0, 0, 0, m_rect.width(),
//			m_rect.height(), SWP_SHOWWINDOW | SWP_NOMOVE);
//
//		return;
//	}
//
//	m_rect.setSize(s);
//	CtRect rect = clientToScreen(m_rect);
//	SetWindowPos(m_hwndChild, 0, 0, 0, m_rect.width(),
//		m_rect.height(), SWP_SHOWWINDOW | SWP_NOMOVE);
//}
//
//void CtWidgetWindowImp::resize(int w, int h)
//{
//	resize(CtSize{ w,h });
//}

void CtWidget::setFixedSize(const CtSize & s)
{
	dd->setFixedSize(s);
}

void CtWidget::setFixedSize(int w, int h)
{
	setFixedSize(CtSize{ w,h });
}

void CtWidget::setFocus() const
{
	dd->setFocus();
}

bool CtWidget::isVisible() const
{
	return dd->isVisible();
}

void CtWidget::setWindowState(bool bNewState)
{
	dd->setWindowState(bNewState);
}

void CtWidget::setWindowText(CtString text)
{
	dd->setWindowTitle(text);
}
/**
Event handler
*/
void CtWidget::nativeEvent(Message &message)
{
}
void CtWidget::closeEvent(CtCloseEvent * event)
{
}

void CtWidget::mousePressEvent(CtMouseEvent * event)
{
}

void CtWidget::mouseReleaseEvent(CtMouseEvent * event)
{
}

void CtWidget::mouseDoubleClickEvent(CtMouseEvent * event)
{
}

void CtWidget::mouseMoveEvent(CtMouseEvent * event)
{
}

void CtWidget::enterEvent(CtEvent * event)
{
}

void CtWidget::leaveEvent(CtEvent * event)
{
}

void CtWidget::resizeEvent(CtResizeEvent * event)
{
}

void CtWidget::keyPressEvent(CtKeyEvent * event)
{
}

void CtWidget::keyReleaseEvent(CtKeyEvent * event)
{
}

void CtWidget::focusInEvent(CtFocusEvent * event)
{
}

void CtWidget::focusOutEvent(CtFocusEvent * event)
{
}

void CtWidget::showEvent(CtShowEvent * event)
{
}

void CtWidget::hideEvent(CtHideEvent * event)
{
}
