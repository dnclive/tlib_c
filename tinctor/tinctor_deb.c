//      tinctor_deb.c
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

#include "tinctor.h"

int main(int argc, char **argv)
{
	printf ("tinctor_deb_start\r\n");
	
	tdeb_finit("tinctor_deb");
	
	tinctorp inctor= tinctor_fcre_strong(NULL, 3, 0);
	
	tdeb_fdeb3("tinctor_deb", __FILE__, __LINE__, "inctor->val=%i\t\tinctor->lim=%i\r\n", 
								*inctor->val, *inctor->lim);
	
	//увеличиваем текущее занчение val на 1
	tdeb_fdeb3("tinctor_deb", __FILE__, __LINE__, "inctor->val=%i\r\n", *tinctor_finc(&inctor)->val);
	
	//увеличиваем текущее занчение val на 1
	tdeb_fdeb3("tinctor_deb", __FILE__, __LINE__, "inctor->val=%i\r\n", *tinctor_finc(&inctor)->val);
	
	//проверяем излучение если вернуло 1 то атом должен излучать
	//иначе нет
	tdeb_fdeb3("tinctor_deb", __FILE__, __LINE__, "inctor->emit=%i\r\n", tinctor_femit(&inctor));		
	
	//увеличиваем текущее занчение val на n
	tdeb_fdeb3("tinctor_deb", __FILE__, __LINE__, "inctor->val=%i\r\n", *tinctor_fincn(&inctor, 4)->val);
	
	//проверяем излучение если вернуло 1 то атом должен излучать
	//иначе нет
	tdeb_fdeb3("tinctor_deb", __FILE__, __LINE__, "inctor->emit=%i\r\n", tinctor_femit(&inctor));
	
	//сбрасываем текущее значение val
	tdeb_fdeb3("tinctor_deb", __FILE__, __LINE__, "inctor->val=%i\r\n", *tinctor_freset(&inctor)->val);
	
	printf ("tinctor_deb_end\r\n");
	
	return 0;
}

