//      tbit_deb.c
//      
//      Copyright 2011 dnclive <dnclive@ubunlive3>
//      
//      This program is free software; you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation; either version 2 of the License, or
//      (at your option) any later version.
//      
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//      
//      You should have received a copy of the GNU General Public License
//      along with this program; if not, write to the Free Software
//      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
//      MA 02110-1301, USA.


#include <stdio.h>

#include <tdeb.h>

#include "tbit.h"

int main(int argc, char **argv)
{
	printf ("tbit_deb_start\r\n");
	
	tdeb_finit("tbit_deb");
	
	tdeb_fdeb3("tbit_deb", __FILE__, __LINE__, "str_each=%s\r\n", tbit_fbyte2bit("3", 1));
	
	tdeb_fdeb3("tbit_deb", __FILE__, __LINE__, "fbit_ulong=%i\r\n", tbit_fbit_ulong(8, 3));
	
	tdeb_fdeb3("tbit_deb", __FILE__, __LINE__, "fbit_ulong=%i\r\n", tbit_fbit_ulong_set(8, 0, 1));
	
	tdeb_fdeb3("tbit_deb", __FILE__, __LINE__, "fbit_ulong=%d\r\n", tbit_fbit_ulong_set(2, 1, 0));
	
	//tbit * tbit_data= tbit_finit();
	
	printf ("tbit_deb_end\r\n");
	
	return 0;
}

