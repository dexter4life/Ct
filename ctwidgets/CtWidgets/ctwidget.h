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
#ifndef WIDGET_H
#define WIDGET_H

#include <ctcore/ctglobal.h>
#include <ctcore/ctobject.h>
#include <ctcore/ctstring.h>
#include <ctcore/ctevent.h>
#include <ctcore/ctrect.h>
#include <ctcore/ctsize.h>
#include <ctwidgets/ctapplication.h>
#include <ctcore/ctstring.h>

#include <set>
#include <vector>

#ifdef _WIN32
#include <Windows.h>
#endif

class WIDGET_H CtWidget : public CtObject
{
	friend class CtWidgetWindowPrivateImp;
	friend class CtWidget;
	friend class CtMDIChild;
	friend class CtDialog;
	friend class CtTaskDialog;
	friend class CtWinApp;

public:
	explicit CtWidget(CtWidget *parent = nullptr);
	virtual ~CtWidget();

	void			caputeMouse() const;

	CtPoint			mapToParent(const CtPoint &point);
	void			mapWindowPoints(CtWidget* pWidgetTo, CtPoint *ptArray) const;
	void			mapWindowPoints(CtWidget* pWidgetTo, CtRect &rc) const;

	CtPoint			screenToClient(const CtPoint & point);
	inline	CtPoint clientToScreen(const CtPoint & point);

	CtRect			screenToClient(const CtRect & rect);
	CtRect			clientToScreen(const CtRect & rect);

	CtRect			rect() const;
	void			setGeometry(const CtRect &rt);
	void			setGeometry(int x, int y, int w, int h);

	//void	setWindowIcon(const QIcon &icon);
	
	/*event handlers*/
	virtual void	nativeEvent(Message &message);
	virtual void	closeEvent(CtCloseEvent *event);
	virtual void	mousePressEvent(CtMouseEvent *event);
	virtual void	mouseReleaseEvent(CtMouseEvent *event);
	virtual void	mouseDoubleClickEvent(CtMouseEvent *event);
	virtual void	mouseMoveEvent(CtMouseEvent *event);
	virtual void	enterEvent(CtEvent *event);
	virtual void	leaveEvent(CtEvent *event);
	virtual void	resizeEvent(CtResizeEvent *event);
	virtual void	keyPressEvent(CtKeyEvent *event);
	virtual void	keyReleaseEvent(CtKeyEvent *event);
	virtual void	focusInEvent(CtFocusEvent *event);
	virtual void	focusOutEvent(CtFocusEvent *event);
	virtual void	showEvent(CtShowEvent *event);
	virtual void	hideEvent(CtHideEvent *event);

	/*virtual void dragEnterEvent(QDragEnterEvent *event);
	virtual void dragMoveEvent(QDragMoveEvent *event);
	virtual void dragLeaveEvent(QDragLeaveEvent *event);
	virtual void dropEvent(QDropEvent *event);

	virtual void paintEvent(QPaintEvent *event);
	*/

	//handle all event type
	virtual bool	event(CtEvent *event);

	//hide window
	void			hide();

	//show window
	void			show();

	void			setFocus() const;
	bool			isVisible() const;

	//enable window or disable window
	void			setEnabled(bool value);
	bool			isEnabled() const;

	bool			isWindow() const;

	void			move(const CtPoint &pt);
	void			move(int x, int y);

	bool			isWindowActive() const;
	bool			isMinimized() const;
	bool			isMiximized() const;

	CtSize			size() const;
	void			resize(const CtSize &);
	void			resize(int w, int h);

	void			setFixedHeight(int h);
	void			setFixedSize(const CtSize &s);
	void			setFixedSize(int w, int h);
	void			setFixedWidth(int w);

	/*Windows ca	n't be resize beyond this size specifications*/
	void			setMaximumHeight(int maxh);
	void			setMaximumSize(const CtSize &);
	void			setMaximumSize(int maxw, int maxh);
	void			setMaximumWidth(int maxw);
	void			setMinimumHeight(int minh);
	void			setMinimumSize(const CtSize &);
	void			setMinimumSize(int minw, int minh);

	void			setWindowState(bool bNewState);
	//void			setWindowState(WindowStates windowState)

	void			setWindowText(CtString text);

	void			setParent(CtWidget *parent);

	void			update(int x, int y, int w, int h);
	void			update(const CtRect &rect);
	//void	update(const CtRegion &rgn);

	bool			updatesEnabled() const;
	void			setUpdateEnabled(bool enable);

	int				x() const;
	int				y() const;

private:
	CtWidgetWindowPrivateImp *dd;
public:
	typedef CtWidgetWindowPrivateImp * WidgetPtr;
	inline WidgetPtr &win_ptr() { return dd; }
};
#endif // !WIDGET_H
