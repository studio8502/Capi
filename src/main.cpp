/*****************************************************************************
 ╔═══════════════════════════════════════════════════════════════════════════╗
 ║ main.cpp                                                                  ║
 ╟───────────────────────────────────────────────────────────────────────────╢
 ║ Copyright © 2024 Kyle J Cardoza, Studio 8502 <Kyle.Cardoza@icloud.com>    ║
 ╟───────────────────────────────────────────────────────────────────────────╢
 ║ This program is free software: you can redistribute it and/or modify      ║
 ║ it under the terms of the GNU General Public License as published by      ║
 ║ the Free Software Foundation, either version 3 of the License, or         ║
 ║ (at your option) any later version.                                       ║
 ║                                                                           ║
 ║ This program is distributed in the hope that it will be useful,           ║
 ║ but WITHOUT ANY WARRANTY; without even the implied warranty of            ║
 ║ MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             ║
 ║ GNU General Public License for more details.                              ║
 ║                                                                           ║
 ║ You should have received a copy of the GNU General Public License         ║
 ║ along with this program.  If not, see <http://www.gnu.org/licenses/>.     ║
 ╚═══════════════════════════════════════════════════════════════════════════╝
 ****************************************************************************/

#include "kernel.h"

Kernel *kernel = new Kernel();

function VersionString() -> char * {
	static char buffer[255];

	sprintf(buffer, "v%lu.%lu.%lu (%08lx-%04lx)", (unsigned long) &__VERSION_MAJOR, 
								 	   	   		  (unsigned long) &__VERSION_MINOR, 
								 	    		  (unsigned long) &__VERSION_MICRO,
												  (unsigned long) &__BUILD_COMMIT,
									    		  (unsigned long) &__BUILD_NUMBER);

	return buffer;
}

using enum Kernel::ShutdownMode;

int main (void)
{
	kernel->initialize();
	
	auto mode = kernel->run();

	switch (mode)
	{
	case Reboot:
		reboot();
		return EXIT_REBOOT;

	case Halt:
	default:
		halt();
		return EXIT_HALT;
	}
}
