//tcontext.h 

/*
 * programing by dnclive(c)2011
 *  dnclive@gmail.com
*/
#ifndef tcontexth
#define tcontexth

#include <stdlib.h>
#include <stdio.h>

#include <tdeb.h>
#include <tstr.h>

typedef struct _tcontext tcontext ;

typedef tcontext * tcontextp ;  //указатель на контекст

//данные
struct _tcontext
{
	tcontext *context;			//ссылка на себя
	tstrp context_name			//строковое описание контекста
};


//функции
/*
	tcontext *tcontext_finit()
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
tcontext *tcontext_finit();		//инициализация библиотеки

/*
	tcontext *tcontext_fcre()
	функция:
		выделение памяти под данные библиотеки
		Пример:
			
	параметры:
		
		
	эффект:
		используется для запроса требуемого объема памяти
		
	возврат:
		возвращается указатель на участок памяти запрошенного разммера
*/
tcontext *tcontext_fcre();		//выделение памяти под данные библиотеки


#endif
