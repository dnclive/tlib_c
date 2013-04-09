//tlist.h 

/*
 * programing by dnclive(c)2011
 *  dnclive@gmail.com
*/
#ifndef tlisth
#define tlisth

#include <stdlib.h>
#include <stdio.h>

#include <tdeb.h>
#include <tlisti.h>

typedef struct _tlist tlist ;

//данные
struct _tlist
{
	tlist *self;			//ссылка на себя
	tlisti *firstblock;		//ссылка на первый элемент списка
	tlisti *lastblock;		//ссылка на последний элемент списка
	long len;				//количество элементов списка
};


//функции
/*
	tlist *tlist_finit()
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
tlist *tlist_finit();		//инициализация библиотеки

/*
	tlist *tlist_fcre()
	функция:
		выделение памяти под данные библиотеки
		Пример:
			
	параметры:
		
		
	эффект:
		используется для запроса требуемого объема памяти
		
	возврат:
		возвращается указатель на участок памяти запрошенного разммера
*/
tlist *tlist_fcre();		//выделение памяти под данные библиотеки

tlist *tlist_fadd(tlist *list, tlisti *listi)

#endif
