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
//#include <tlist_each.h>
#include <tcre.h>
#include <tstr.h>
#include <tmem.h>

typedef struct _tlist tlist; 	//список

typedef tlist * tlistp;			//указатель на список

typedef tlist ** tlistpp;			//указатель на список

//данные
struct _tlist
{
	tlist *self;			//ссылка на себя
	tlisti *firstblock;		//ссылка на первый элемент списка
	tlisti *lastblock;		//ссылка на последний элемент списка
	tlongp  count;				//количество элементов списка
};


//функции
/*
*	tlist *tlist_finit()
*	функция:
*		уровня 0 (для внешних вызовов) выделяющая последовательный блок памяти размера size байт
*		Пример:
*			
*	параметры:
*		int size	размер в байтах необходимый к выделению
*		
*	эффект:
*		используется для запроса требуемого объема памяти
*		
*	возврат:
*		возвращается указатель на участок памяти запрошенного разммера
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
tlist *tlist_fcre(tlist **selfp);		//выделение памяти под данные библиотеки

tlist *tlist_fadd_item(tlist **selfp, tlisti *listi);	//добавление элемента в список

tlist *tlist_fadd_data(tlist **selfp, tptr data);		//добавление элемента в список

tlist *tlist_fins(tlist **selfp, tlisti *listi, long index);	//вставка элемента в список по индексу

tlist *tlist_fremove_by_i(tlist **selfp, long index);	//убирает элемент из списка

tlist *tlist_fremove(tlist **selfp, tlisti *listi);		//убирает элемент из списка

tlisti *tlist_fitem_by_i(tlist **selfp, long index);		//возвращает элемент по индексу

tlist *tlist_fdrop(tlistp *selfp);							//удаляет список selfp освобождая элементы



#endif
