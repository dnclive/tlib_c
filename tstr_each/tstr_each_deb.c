//      tstr_each_deb.c
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

#include "tstr_each.h"

int main(int argc, char **argv)
{
	printf ("tstr_each_deb_start\r\n");
	
	tdeb_finit("tstr_each_deb");
	
	tstr_each * str_each= tstr_each_fcre(NULL, tstr_fcre_copy(NULL, "строка"));
	
	tdeb_fdeb3("tstr_each_deb", __FILE__, __LINE__, "str_each=%p\r\n", str_each);
	tdeb_fdeb3("tstr_each_deb", __FILE__, __LINE__, "str_each->chari=%p\r\n", *str_each->chari);
	tdeb_fdeb3("tstr_each_deb", __FILE__, __LINE__, "str_each->bytei=%p\r\n", *str_each->bytei);
	tdeb_fdeb3("tstr_each_deb", __FILE__, __LINE__, "str_each->charp=%i\r\n", str_each->charp);
	
	tstr_each_finc(&str_each);
	
	tdeb_fdeb3("tstr_each_deb", __FILE__, __LINE__, "str_each=%p\r\n", str_each);
	tdeb_fdeb3("tstr_each_deb", __FILE__, __LINE__, "str_each->chari=%p\r\n", *str_each->chari);
	tdeb_fdeb3("tstr_each_deb", __FILE__, __LINE__, "str_each->bytei=%p\r\n", *str_each->bytei);
	tdeb_fdeb3("tstr_each_deb", __FILE__, __LINE__, "str_each->charp=%i\r\n", (char)*str_each->charp);
	tdeb_fdeb3("tstr_each_deb", __FILE__, __LINE__, "str_each->charp=%s\r\n", 
								tbit_fbyte2bit(str_each->charp,1));
	tulong i=0;
	while (*tstr_each_finc(&str_each)->charp&&i<10)
	{
		tdeb_fdeb3("tstr_each_deb", __FILE__, __LINE__, "str_each=%p\r\n", str_each);
		tdeb_fdeb3("tstr_each_deb", __FILE__, __LINE__, "str_each->chari=%i\r\n", *str_each->chari);
		tdeb_fdeb3("tstr_each_deb", __FILE__, __LINE__, "str_each->bytei=%i\r\n", *str_each->bytei);
		tdeb_fdeb3("tstr_each_deb", __FILE__, __LINE__, "str_each->charp=%i\r\n", (char)*str_each->charp);
		tdeb_fdeb3("tstr_each_deb", __FILE__, __LINE__, "str_each->charp=%s\r\n", 
									tbit_fbyte2bit(str_each->charp,1));
		tdeb_fdeb3("tstr_each_deb", __FILE__, __LINE__, "str_each->charp=%s\r\n", 
									tbit_fbyte2bit(str_each->charp,1));
		tdeb_fdeb3("tstr_each_deb", __FILE__, __LINE__, "str_each->char_utf8=%s\r\n", 
									str_each->char_utf8);
		i++;
	}
	
	tdeb_fdeb3("tstr_each_deb", __FILE__, __LINE__, "str_each->chari=%i\r\n", *str_each->chari);
	tdeb_fdeb3("tstr_each_deb", __FILE__, __LINE__, "str_each->bytei=%i\r\n", *str_each->bytei);
	tdeb_fdeb3("tstr_each_deb", __FILE__, __LINE__, "str_each->charp=%s\r\n", 
									tbit_fbyte2bit(str_each->charp,1));
	
	printf ("tstr_each_deb_end\r\n");
	
	return 0;
}

