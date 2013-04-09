//      tlisti_deb.c
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
#include <tstr.h>

#include "tlisti.h"

int main(int argc, char **argv)
{
	printf ("tlisti_deb_start\r\n");
	
	tdeb_finit("tlisti_deb");
	
	//tstr *str=NULL;
	//tstr_fcre(NULL, "hello world");
	
	tmem_fdump();
	
	//return 0;
	
	tlisti *listi=NULL;
	tlisti_fcre(&listi, tstr_fcre(NULL, "новая строка"));
	//return 0;
	tdeb_fdeb("tlisti_deb", "listi2->data=%s\r\n", ((tstr *)listi->data)->str);
	tdeb_fdeb("tlisti_deb", "listi=%p\r\n", listi);
	
	//tmem_funref(&str);
	//tmem_funref(&str);
	
	tdeb_fdeb("tlisti_deb", "listi2->data=%s\r\n", ((tstr *)listi->data)->str);
	tmem_fdump();
	//tmem_funref(&listi);
	//tmem_funref(&listi);
	tcre_funref(&listi);
	//tcre_fself_unref(&listi);
	
	//tmem_funref(&str);
	tmem_fdump();
	return 0;
	
	//tstr *str=tstr_fcopy_pchar2str(NULL, "test string");
	
	//tlisti *listi=tlisti_fcre(&listi, str);
	
	tlisti *listi2=tlisti_fcre(&listi2, tstr_fcre(NULL, "test string 2"));
	
	tdeb_fdeb("tlisti_deb", "listi->data=%s\r\n", listi->data);
	
	tdeb_fdeb("tlisti_deb", "listi2->data=%s\r\n", ((tstr *)listi2->data)->str);
	
	tlisti_ffree(&listi);
	tlisti_ffree(&listi2);
	
	//tlisti * tlisti_data= tlisti_finit();
	
	printf ("tlisti_deb_end\r\n");
	
	return 0;
}

