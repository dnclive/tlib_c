//tstr_each.h 

/*
 * programing by dnclive(c)2011
 *  dnclive@gmail.com
*/
#ifndef tstr_eachh
#define tstr_eachh

#include <stdlib.h>
#include <stdio.h>

#include <tdeb.h>
#include <tmem.h>
#include <tcre.h>
#include <tbit.h>
#include <tstr.h>

typedef struct _tstr_each tstr_each ;

typedef tstr_each * tstr_eachp;

typedef tstr_each ** tstr_eachpp;

//данные
struct _tstr_each
{
	//tstr_each *self;			//ссылка на себя
	tstrp str;					//обрабатываемая строка
	tcharp charp;				//указатель на текущий символ	
	tlongp chari;				//индекс текущуго символа
	tlongp bytei;				//текущий байтовый индекс
	//tulongp chari_count,		//количество байт в текущем символе
	tcharp char_utf8;			//символ в кодировке utf-8 с заверщающим символом /0
	tcharp char_ascii			//символ в кодировке asc2 локализации системы
};


//функции
/*
	tstr_each *tstr_each_finit()
	функция:
		уровня 0 (для внешних вызовов) выделяющая последовательный блок памяти размера size байт
		Пример:
			
	параметры:
		int size	размер в байтах необходимый к выделению
		
	эффект:
		используется для запроса требуемого объема памяти
		
	возврат:
		возвращается указатель на участок памяти запрошенного разммера
*/
tstr_each *tstr_each_finit();		//инициализация библиотеки

/*
	tstr_each *tstr_each_fcre()
	функция:
		выделение памяти под данные библиотеки
		Пример:
			
	параметры:
		
		
	эффект:
		используется для запроса требуемого объема памяти
		
	возврат:
		возвращается указатель на участок памяти запрошенного разммера
*/
tstr_eachp tstr_each_fcre();		//выделение памяти под данные библиотеки

tstr_eachp tstr_each_finc(tstr_eachpp selfp);

tstr_eachp tstr_each_finc_n(tstr_eachpp selfp, tulong n);

tstr_eachp tstr_each_fchar_ascii(tstr_eachpp selfp, tulong n);



#endif
