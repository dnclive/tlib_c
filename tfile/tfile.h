//tfile.h 

/*
 * programing by dnclive(c)2011
 *  dnclive@gmail.com
*/
#ifndef tfileh
#define tfileh

#include <stdlib.h>
#include <stdio.h>

#include <tdeb.h>
#include <tcontext.h>
#include <tcre.h>
#include <tstr.h>
#include <tmem.h>
#include <tlist.h>
#include <tlist_each.h>
#include <tinctor.h>

typedef struct _tfile tfile ;

//данные
struct _tfile
{
	tfile *self;			//ссылка на себя
};


//функции
/*
	tfile *tfile_finit()
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
tfile *tfile_finit();		//инициализация библиотеки

/*
	tfile *tfile_fcre()
	функция:
		выделение памяти под данные библиотеки
		Пример:
			
	параметры:
		
		
	эффект:
		используется для запроса требуемого объема памяти
		
	возврат:
		возвращается указатель на участок памяти запрошенного разммера
*/
tfile *tfile_fcre();		//выделение памяти под данные библиотеки


#endif
