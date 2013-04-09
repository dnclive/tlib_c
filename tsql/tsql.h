//tsql.h 

/*
 * programing by dnclive(c)2011
 *  dnclive@gmail.com
*/
#ifndef tsqlh
#define tsqlh

#define ERREXIT(status, rc)	{isc_print_status(status); return rc;}



#include <stdlib.h>
#include <stdio.h>

#include <tdeb.h>


#include <ibase.h>

typedef struct _tsql tsql ;

//данные
struct _tsql
{
	tsql *self;			//ссылка на себя
};


//функции
/*
	tsql *tsql_finit()
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
tsql *tsql_finit();		//инициализация библиотеки

/*
	tsql *tsql_fcre()
	функция:
		выделение памяти под данные библиотеки
		Пример:
			
	параметры:
		
		
	эффект:
		используется для запроса требуемого объема памяти
		
	возврат:
		возвращается указатель на участок памяти запрошенного разммера
*/
tsql *tsql_fcre();		//выделение памяти под данные библиотеки


#endif
