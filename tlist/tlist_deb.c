//      tlist_deb.c
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

#include "tlist.h"

int main(int argc, char **argv)
{
	printf ("tlist_deb_start\r\n");
	
	tdeb_finit("tlist_deb");
	
	//tlist * tlist_data= tlist_finit();
	
	tlist * list=tlist_fcre(NULL);
	//tstr* str=tstr_fcre(NULL, "234234"); 
	
	tdeb_fdeb3("tlist_deb", __FILE__, __LINE__, "list=%p\r\n", list);
	
	//tcre_funref(&list);
	//tmem_funref(&list);
	
	tdeb_fdeb3("tlist_deb", __FILE__, __LINE__, "list=%p\r\n", list);
	
	tmem_fdump();
	
	//return;
	
	
	
	tlist_fadd_item(&list, tlisti_fcre(NULL, tstr_fcre(NULL, "наша торжественная строка\r\n")));
	tlist_fadd_item(&list, tlisti_fcre(NULL, tstr_fcre(NULL, "еще одна строка\r\n")));
	
	tnump num=tcre_ftnum(NULL, 1);
	
	//tlist_fadd_item(&list, tlisti_fcre(NULL, num));
	
	tlisti *list3=tlist_fitem_by_i(&list, 0);
	printf(((tstr*)list3->data)->str);
	
	
	list3=tlist_fitem_by_i(&list, 1);
	printf(((tstr*)list3->data)->str);
	
	printf(((tstr*)tlist_fitem_by_i(&list, 0)->data)->str);
	
	tmem_fdump();
	
	tlist_fdrop(&list);
	
	
	tcre_funref(&num);
	
	tmem_fdump();
	
	//tmem_ffree_all();
	
	//tmem_fdump();
	
	printf ("tlist_deb_end\r\n");
	
	return 0;
}

