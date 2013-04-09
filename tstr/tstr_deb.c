//      tstr_deb.c
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

#include <tmem.h> 
#include <tdeb.h>

#include "tstr.h"

int main(int argc, char **argv)
{
	printf ("tstr_deb_start\r\n");
	
	tdeb_finit("tstr_deb");
	//*** сравнение строк
	
	tstrp str1__=tstr_fcre_copy(NULL, "строка");
	tstrp str2__=tstr_fcre_copy(NULL, "ne etot den");
	tstrp str3__=tstr_fcre_copy(NULL, "#^|&:");
	
	tdeb_fdeb3("tstr_deb", __FILE__, __LINE__, "str1_vs_str2=%i\r\n", tstr_fcmp(str1__, str2__));
	tdeb_fdeb3("tstr_deb", __FILE__, __LINE__, "str1_vs_str2=%s\r\n", str1__->str);
	
	tdeb_fdeb3("tstr_deb", __FILE__, __LINE__, "str1_vs_str2=%i\r\n", 
						tstr_fchari(str1__, tstr_fcre_copy(NULL, "о")->str));
						
	tdeb_fdeb3("tstr_deb", __FILE__, __LINE__, "str1_vs_str2=%i\r\n", 
						tstr_fchari(str3__, tstr_fcre_copy(NULL, "&")->str));
	
	return 0; 
	//tdeb_fdeb3("tstr_deb", __FILE__, __LINE__, "str1_vs_str2=%i\t%s\r\n", tstr_fchari(str1__, 'к'), str1__->str);
	/*
	char* c='rekjkjsdfi';
	int l=34;
	int k = 128;//k= 10000000b
	//printf("%d\r\n", k);
	while(k>0) { //
		//printf("%d\r\n", (k=k>>1)&c&&1 ); // печатаем нужный разряд.
		
		//printf("%d\r\n", k);
		k=k>>1;//сдвигаем k поразрядно вправо на 1.Что есть деление на 2
	};
	printf("\r\n");
	*/
	int n=33;
	int i = 1;
	while(i < 9)
	{
	  printf("%d", ((n & i) >> (i - 1)));
	  i++;
	}
	printf("\n");
	
	//tdeb_fdeb3("tstr_deb", __FILE__, __LINE__, "str1_vs_str2=%i\t%s\r\n", tstr_fchari(str1__, 'к'), str1__->str);
	
	
	//printf("%s\r\n", tbit_fi2bit(234));
	
	tlong val=234234;
	
	tcharp val_ch="iстрока";
	
	printf("%s\r\n", tbit_fbyte2bit(val_ch, 1));
	
	//tbit_fbit(*val_ch, 0);
	
	//printf("%s\r\n", tbit_fbyte2bit((tcharp)&val_ch, sizeof val));
	
	return 0; 
	//tstr *str=tstr_finit();
	
	//tstr_fcopy_pchar2str(str, "Здравствуй мир!!!");
	
	//printf("%s\r\n",str->str);
	
	//tstr_ffree(&str);		//освобождаем ресурсы

	tstr *str33=NULL;
	
	//tstr_fcre_copy(&str33, ":");
	
	tstrp str333=tstr_fjoin_2(NULL, tstr_fcre_copy(NULL, "key"), tstr_fcre_copy(NULL, "val"));
	
	tdeb_fdeb3("tstr_deb", __FILE__, __LINE__, "str333=%s\r\n", str333->str);
	tdeb_fdeb3("tstr_deb", __FILE__, __LINE__, "str333->len=%i\r\n", str333->len->ival);
	
	tstrp str3333=tstr_fjoin_3(NULL, tstr_fcre_copy(NULL, "key"), 
									tstr_fcre_copy(NULL, "&"), 
									tstr_fcre_copy(NULL, "val"));
	
	tdeb_fdeb3("tstr_deb", __FILE__, __LINE__, "str3333=%s\r\n", str3333->str);
	tdeb_fdeb3("tstr_deb", __FILE__, __LINE__, "str3333->len=%i\r\n", str3333->len->ival);
	
	tmem_ffree_all();
	
	tstrp str1_=tstr_fcre_copy(NULL, "key");
	tstrp str2_=tstr_fcre_copy(NULL, "&");
	tstrp str3_=tstr_fcre_copy(NULL, "val");
	
	tstrp str4_=NULL;
	
	tstr_fjoin_3(&str4_, str1_, str2_, str3_);
	
	//tcre_ftlong_val(NULL, 23);
	
	tdeb_fdeb3("tstr_deb", __FILE__, __LINE__, "str1=%s\r\n", str4_->str);
	tdeb_fdeb3("tstr_deb", __FILE__, __LINE__, "str1->len=%i\r\n", str4_->len->ival);
	
	tdeb_fdeb3("tstr_deb", __FILE__, __LINE__, "str from char=%s\r\n", tstr_fcre_char(NULL, '3')->str);
	
	//tmem_fdump();
	
	return;
	
	//tdeb_fdeb("tstr_deb", "%i", '3');
	
	tdeb_fdeb("tstr_deb", "tstr_fchar=%i\r\n", ((char)tstr_fchar(str33, 3)));
	
	tstr_fset_char(&str33, 2, '2');
	
	tdeb_fdeb("tstr_deb", "str->str=%s\r\n", str33->str);
	
	tcre_funref(&str33);
	
	tmem_fdump();
	
	//tdeb_fdeb("tstr_deb", "tstr_fchar=%c", tstr_fchar(tstr_fcre(NULL, "29839293840234"), 3));
	
	tdeb_fdeb("tstr_deb", "str->len=%i\r\n", tstr_flen(tstr_fcre(NULL, ":")));
	
	tmem_ffree_all();
	
	
	
	return;

	//создание строки итоговый вариант
	
	tdeb_fdeb("tstr_deb", "**********итоговый вариант создания строки\r\n");
	
	tstr *str=NULL;
	
	tstr_fcre(&str, "hello world!!!");
	
	tdeb_fdeb("tstr_deb", "полученная строка=%s\r\n", str->str);
	
	tmem_fdump();
	
	//return 0;
	
	tdeb_fdeb("tstr_deb", "отсоединение строки от str\r\n");
	
	tmem_funref(&str);
	
	tmem_fdump();
	
	tdeb_fdeb("tstr_deb", "отсоединение строки от str успешно\r\n");
	
	
	
	return 0;
	
	
	
	//быстрая инициализация!
	
	tstr *str2=tstr_fcp_pchar2str(NULL, "Тестовая строка, быстрая инициализация и присваивание");
	
	printf("%s\r\n",str2->str);
	
	tstr_ffree(&str2);		//освобождаем ресурсы
	
	//tstr_fcre(str2);		//создание объекта
	
	tstr* str3= tstr_fcp_pchar2str	//с оборачиванием в присваивание значения
	(	
		tstr_fcre			//создание объекта возвращает ссылку созданый объект
		(
			str2,			//ссылка на объект
			"hello world"
		),
		"Тестовая строка, работы с объектом по принципу фабрики..."	//присваиваемое значение
	);
	
	printf("%s\r\n",str3->str);
	
	tstr_ffree(&str3);		//освобождаем ресурсы
	
	//необходиом что бы было так
	
	//реализовано 
	tdeb_fdeb("tstr_deb", "**********итоговый вариант создания строки\r\n");
	
	tstr_fcre(NULL, "29839293840234");
	
	tdeb_fdeb("tstr_deb", "str=%s", tstr_fcre(NULL, "29839293840234")->str);
	
	
	
	tdeb_fdeb("tstr_deb", "**********итоговый вариант создания строки\r\n");
	
	tmem_ffree_all();
	
	tmem_fdump();
	
	printf ("tstr_deb_end\r\n");
	
	return 0;
}



