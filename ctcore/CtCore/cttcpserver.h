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
#ifndef CT_TCP_SERVER_H
#define CT_TCP_SERVER_H

#include <CtCore/ctobject.h>
#include <CtCore/ctstring.h>

class CtTcpServer :
	public CtObject
{
public:
	CtTcpServer(CtString address, ctint port, CtObject *parent = nullptr);
	virtual ~CtTcpServer();


};

#endif // !CT_TCP_SERVER_H
