//      tcre_deb.c
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

#include "tcre.h"

int main(int argc, char **argv)
{
	printf ("tcre_deb_start\r\n");
	
	tdeb_finit("tmem_deb");
	
	//tdeb_finit("tcre_deb");
	
	tcre * tcre_data= tcre_finit();
	
	char **pchar=NULL;
	
	tcre_ftptr(&pchar, tcre_mptr_cnt(char **,3));
	tcre_ftchar(&*pchar, 12);
	
	char **pchar2=NULL;
	
	//tdeb_finit("tmem_deb");
	
	//tmem_fref(pchar, &pchar2);
	
	//tdeb_finit("tcre_deb");
	
	tcre_fref(&pchar2, pchar);
	
	strncpy(*pchar, "hello world", 12);
	
	tdeb_fdeb("tcre_deb", "\t\t**pchar=%s\r\n", *pchar);
	
	tdeb_fdeb("tcre_deb", "\t\t**pchar=%s\r\n", *pchar2);
	
	tmem_funref(&pchar);
	
	tmem_funref(&pchar2);
	
	tchar *ch=tcre_ftchar_val(NULL, '3');
	
	tdeb_fdeb("tcre_deb", "\t\t**ch=%i\r\n", *ch);
	
	tlong *long_val=tcre_ftlong_val(NULL, 23234);
	
	tdeb_fdeb("tcre_deb", "long_val=%i\r\n", *long_val);
	
	tmem_fdump();
	
	tcre_fref(&long_val, NULL);
	
	printf ("tcre_deb_end\r\n");
	
	tmem_ffree_all();
	
	tcharp str=tcre_ftchar(NULL, 34);
	
	tcharp str2=NULL;
	
	tcre_fref(&str2, str);
	
	tmem_fdump();
	
	tcre_fdrop(&str);
	
	tmem_fdump();
	
	tcre_fref(&str2, NULL);
	
	tmem_fdump();
	
	tcre_fmem_stat();
	
	tcre_fdrop_all();
	
	tcre_fmem_stat();
	
	return 0;
}

