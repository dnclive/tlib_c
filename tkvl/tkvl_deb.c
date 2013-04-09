//      tkvl_deb.c
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

#include "tkvl.h"

int main(int argc, char **argv)
{
	printf ("tkvl_deb_start\r\n");
	
	tdeb_finit("tkvl_deb");
	
	tstrp kvl_str=tstr_fcre_copy(NULL, "ключ:val1&key2:val2|key3:val3&key4:val4^key5:val5&key6:val6|key7:val7&key8:val8");
	
	tdeb_fdeb3("tkvl_deb", __FILE__, __LINE__, "kvl_str_=%p\r\n", kvl_str);
	
	tkvl * kvl= tkvl_fcre(NULL, kvl_str);
	
	tdeb_fdeb3("tkvl_deb", __FILE__, __LINE__, "kvl=%p\r\n", kvl);
	
	tdeb_fdeb3("tkvl_deb", __FILE__, __LINE__, "kvl_fstr=%s\r\n", tkvl_fstr(kvl)->str);
	
	//tdeb_fdeb3("tkvl_deb", __FILE__, __LINE__, "kvl_fstr=%s\r\n", tkvl_fstr_2(kvl)->str);
	
	tlist_eachp list_each = tlist_each_fcre(NULL, tkvl_fall_val(kvl));
	
	while (tlist_each_finc(&list_each)->listi)
	{
	
		tdeb_fdeb3("tkvl_deb", __FILE__, __LINE__, "kvl_fstr=%s\r\n", ((tstrp)list_each->listi->data)->str);
		
	}
	
	printf ("tkvl_deb_end\r\n");
	
	return 0;
}

