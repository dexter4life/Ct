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

#include <ctwidgets/ctapplication.h>
#include <ctcore/ctstring.h>
#include <ctcore/ctevent.h>


int CtGuiApplication::exec()
{
#ifdef _WIN32
	//define something for Windows (32-bit and 64-bit, this part is common)
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0) 
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
#elif __APPLE__

#elif __linux__
	// linux
#elif __unix__ // all unices not caught above
	// Unix
#else
#   error "Unknown compiler"
#endif
}

#ifdef _WIN32
/*
 Windows specific: we define the WinMain entry point,
 so that developers can use the standard main function
 even in a Win32 Application project, and thus keep a
 portable code.
*/
#include <windows.h>

extern int main(int argc, char* argv[]);

////////////////////////////////////////////////////////////
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, INT)
{
	return main(__argc, __argv);
}
#endif