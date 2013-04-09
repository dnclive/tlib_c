//      tdeb_deb.c
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

#include "tdeb.h"

int main(int argc, char **argv)
{
	printf ("tdeb_deb_start\r\n");
	
	tdeb * tdeb_data= tdeb_finit("tdeb_deb");
	
	tdeb_fdeb("tdeb_deb", "целое число формат i=%i\r\n", 123);
	
	tdeb_fdeb("tdeb_deb", "указатель формат p=%p\r\n", tdeb_data);
	
	tdeb_fdeb("tdeb_deb", "строка формат s=%s\r\n", "тестовая строка");
	
	//не работает
	//tdeb_fdeb("tdeb_deb", "символ формат c=%c\r\n", 123);
	
	tdeb_fdeb("tdeb_deb", "число с плавающей точкой f=%f\r\n", 123.23);
	
	tdeb_fdeb("tdeb_deb", "перечислимое d=%d\r\n", 12);
	
	printf ("tdeb_deb_end\r\n");
	
	return 0;
}

