//tnewlib.h 

/*
 * programing by dnclive(c)2011
 *  dnclive@gmail.com
*/
#ifndef tnewlibh
#define tnewlibh


typedef struct _tnewlib tnewlib ;

//данные
struct _tnewlib
{
	tnewlib *self;			//ссылка на себя
};


//функции
/*
	tnewlib *tmem_finit()
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
tnewlib *tmem_finit();		//инициализация библиотеки

/*
	tnewlib *tnewlib_fcre()
	функция:
		выделение памяти под данные библиотеки
		Пример:
			
	параметры:
		
		
	эффект:
		используется для запроса требуемого объема памяти
		
	возврат:
		возвращается указатель на участок памяти запрошенного разммера
*/
tnewlib *tnewlib_fcre();		//выделение памяти под данные библиотеки


#endif
