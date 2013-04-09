//tlisti.h 

/*
 * programing by dnclive(c)2011
 *  dnclive@gmail.com
*/
#ifndef tlistih
#define tlistih

#include <stdlib.h>
#include <stdio.h>

#include <tmem.h>
#include <tdeb.h>
#include <tcre.h>
#include <tstr.h>

#define mffree(type, self) typeof(type)##_ffree(self);

typedef struct _tlisti tlisti ;

typedef tlisti * tlistip;			//указатель на список

//данные
struct _tlisti
{
	tlisti *self;			//ссылка на себя
	tlisti *nextblock;		//ссылка на следующий элемент
	tlisti *prevblock;		//ссылка на предыдущий элемент
	void *data;				//указатель на данные элемента списка
};


//функции
/*
	tlisti *tlisti_finit()
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
tlisti *tlisti_finit();		//инициализация библиотеки

/*
	tlisti *tlisti_fcre()
	функция:
		выделение памяти под данные библиотеки
		Пример:
			
	параметры:
		
		
	эффект:
		используется для запроса требуемого объема памяти
		
	возврат:
		возвращается указатель на участок памяти запрошенного разммера
*/
tlisti *tlisti_fcre(tlisti **selfp, void *data_ptr);		//выделение памяти под данные библиотеки


#endif
