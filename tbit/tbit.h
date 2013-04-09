//tbit.h 

/*
 * programing by dnclive(c)2011
 *  dnclive@gmail.com
*/
#ifndef tbith
#define tbith

#include <stdlib.h>
#include <stdio.h>

#include <tdeb.h>
#include <tmem.h>
#include <tcre.h>

typedef struct _tbit tbit ;

//данные
struct _tbit
{
	tbit *self;			//ссылка на себя
};


//функции
/*
	tbit *tbit_finit()
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
tbit *tbit_finit();		//инициализация библиотеки

/*
	tbit *tbit_fcre()
	функция:
		выделение памяти под данные библиотеки
		Пример:
			
	параметры:
		
		
	эффект:
		используется для запроса требуемого объема памяти
		
	возврат:
		возвращается указатель на участок памяти запрошенного разммера
*/
tbit *tbit_fcre();		//выделение памяти под данные библиотеки

tcharp tbit_fi2bit(long val);

tcharp tbit_fbyte2bit(tcharp bytep, tulong count);

tcharp tbit_fbit(tchar byte, tulong biti);

tulong tbit_fbit_ulong_set(tulong ulong_val, tulong bit_i, tulong bit_val);

tulong tbit_fbit_ulong(tulong ulong_val, tulong bit_i);

#endif
