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

#ifndef CORE_APPLICATION_H
#define CORE_APPLICATION_H

#include <thread>

class CtCoreApplication {
public:
	CtCoreApplication() {
	}

	virtual void processEvents();

private:
};
#endif // !CORE_APPLICATION_H
