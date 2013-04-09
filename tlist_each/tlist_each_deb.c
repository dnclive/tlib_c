//      tlist_each_deb.c
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

#include "tlist_each.h"

int main(int argc, char **argv)
{
	printf ("tlist_each_deb_start\r\n");
	
	tdeb_finit("tlist_each_deb");
	
	//создаем тестовый список
	tlistp list =tlist_fcre(NULL);
	
	//заполняем данными
	tlist_fadd_item(&list, tlisti_fcre(NULL, tstr_fcre_copy(NULL, "наша торжественная строка\r\n")));
	tlist_fadd_item(&list, tlisti_fcre(NULL, tstr_fcre_copy(NULL, "наша торжественная строка2\r\n")));
	
	//создаем перебор для тестового списка
	//при этом не берется первый элемент списка
	tlist_eachp list_each= tlist_each_fcre(NULL, list);
	
	tlist_each_finc(&list_each);		//берем следующий элемент
	
	//выводим текущи элемент (первый)
	printf("\r\nitem=%s", ((tstr *)((tlisti *)list_each->listi)->data)->str);
	
	
	
	tlist_each_finc(&list_each);		//берем следующий элемент
	
	//выводим текущий элемет - следующий (второй)
	printf("\r\nitem=%s", ((tstr *)((tlisti *)list_each->listi)->data)->str);
	
	tlist_fadd_item(&list, tlisti_fcre(NULL, tstr_fcre_copy(NULL, "наша торжественная строка3\r\n")));
	
	tlist_each_finc(&list_each);		//берем следующий элемент
	
	//выводим текущий элемет - следующий (второй)
	if (list_each->listi)
	printf("\r\nitem=%s", ((tstr *)((tlisti *)list_each->listi)->data)->str);
	
	//выводим текущий элемет - следующий (третий)
	if (list_each->listi)
	printf("\r\nitem=%s", ((tstr *)((tlisti *)list_each->listi)->data)->str);
	
	tcre_funref(&list_each);
	
	//tmem_fdump();
	
	tlistp list___=tlist_fcre(NULL);
	tlist_eachp list___each=tlist_each_fcre(NULL, list___);
	
	tlist_each_finc(&list___each);
	
	tmem_ffree_all();
	printf ("tlist_each_deb_end\r\n");
	
	
	
	return 0;
}

