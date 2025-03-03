//tp.h 

/*
 * programing by dnclive(c)2011
 *  dnclive@gmail.com
 * 
 * Билбиотека реализует подстчет ссылок на структуры данных
 * Возможно использование с любой структурой данных при условии добавления в ее состав
 * переменной long tp_pcnt - хранящей текущее количество ссылок на объект
*/
#ifndef tph
#define tph

#include <stdlib.h>
#include <stdio.h>

#include <tdeb.h>

typedef struct _tp tp ;

//данные
struct _tp
{
	long tp_pcnt;			//количество ссылок на структуру
};


//функции
/*
	tp *tp_finit()
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
tp *tp_finit();		//инициализация библиотеки

/*
	tp *tp_fcre()
	функция:
		выделение памяти под данные библиотеки
		Пример:
			
	параметры:
		
		
	эффект:
		используется для запроса требуемого объема памяти
		
	возврат:
		возвращается указатель на участок памяти запрошенного разммера
*/
tp *tp_fcre();		//выделение памяти под данные библиотеки

/*
	tp *tp_fp(void *p1, void *p2)
	функция:
		1. Выполняет tp_funp для p1 - отсоединяет указатель p1 от адреса на который он указывает
		2. Устанавливает указатель p1 на адрес который указывает p2 - p1=p2;
		3. Инкрементирует tp_pcnt у p2;
		Пример:
			
	параметры:
		
		
	эффект:
		используется для привязки указателя к другому адресу... по сути присваивание переменной 
		другого значения, не копированием а указателем...
		
	возврат:
		возвращается указатель на участок памяти запрошенного разммера
*/
tp *tp_fp(void *p1, void *p2);

tp *tp_funp(void *p);

tp *tp_fp(void *p);

#endif
