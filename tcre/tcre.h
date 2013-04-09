//tcre.h 

/*
 * programing by dnclive(c)2011
 *  dnclive@gmail.com
*/
#ifndef tcreh
#define tcreh

#include <stdlib.h>
#include <stdio.h>

#include <tdeb.h>
#include <tmem.h>

typedef struct _tcre tcre ;

//данные
struct _tcre
{
	tcre *self;			//ссылка на себя
};




//макросы

#define tcre_mptr_cnt(type,cnt) sizeof(type)*(cnt)/sizeof(tptr)

#define tcre_mtype(type) sizeof(type)

//функции
/*
	tcre *tcre_finit()
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
tcre *tcre_finit();		//инициализация библиотеки

/*
	tcre *tcre_fref(void **self, long count)
	функция:
		выделение памяти под данные библиотеки
		Пример:
			
	параметры:
		
		
	эффект:
		используется для запроса требуемого объема памяти
		
	возврат:
		возвращается указатель на участок памяти запрошенного разммера
*/
tptr *tcre_ftptr(void **self, long count);		//выделение памяти под данные библиотеки

/*
	tcre *tcre_fnum(void **self, long count)
	функция:
		выделение памяти под данные библиотеки
		Пример:
			
	параметры:
		
		
	эффект:
		используется для запроса требуемого объема памяти
		
	возврат:
		возвращается указатель на участок памяти запрошенного разммера
*/
tcre *tcre_ftnum(tpp selfp, long count);		//создание массива данных типа tnum
tcre *tcre_ftnum_val(tpp selfp, tnum num_val);	//создание одного элемента со значением num_val
/*
	tcre *tcre_ftlong(void **self, long count)
	функция:
		выделение памяти под данные библиотеки
		Пример:
			
	параметры:
		
		
	эффект:
		используется для запроса требуемого объема памяти
		
	возврат:
		возвращается указатель на участок памяти запрошенного разммера
*/
tlong *tcre_ftlong(tpp selfp, long count);
tlong *tcre_ftlong_val(tpp selfp, tlong long_val);


/*
	tcre *tcre_fchar(void **self, long count)
	функция:
		выделение памяти под данные библиотеки
		Пример:
			
	параметры:
		
		
	эффект:
		используется для запроса требуемого объема памяти
		
	возврат:
		возвращается указатель на участок памяти запрошенного разммера
*/
tchar *tcre_ftchar(void **self, long count);		//создание массива данных типа tchar

tchar *tcre_ftchar_val(tp *selfp, tchar char_val);	//создание одного символа и присвоение ему значения

/*
	void *tcre_fdub(void *self)
	функция:
		дублирование переданного массива
		* фактически дублируется tmemblock
		* возвращается указатель на первый элемент новых данных
		* refcnt у содзаданного блока = 0 поэтому если его не соотнести ни с одной переменной 
		будет уничтожен при следующем tmem_ffree() 
		Пример:
			tchar *chp1=NULL;
			tchar *chp2=NULL;
			tcre_ftchar_val(&chp1, 9);
			tcre_ftchar_cp(&chp1, "привет мир");
			tcre_ftchar_mv(&chp1, &chp2);
			tcre_fref(&chp2, tcre_fdub(&chp1));
			
	параметры:
		
		
	эффект:
		используется для запроса требуемого объема памяти
		
	возврат:
		возвращается указатель на участок памяти запрошенного разммера
*/
tcre *tcre_fdub(void **self, long count);		//создание массива данных типа tchar

tp tcre_fref(void **selfp, void *ref);		//копирование ссылки на данные

tcre *tcre_funref(tptr **selfp);					//отключение ссылки

tcre *tcre_fdrop(tpp selfp);		//попытка удаления блока

tcre *tcre_fdrop_all();				//очистка от мусора

tcre *tcre_fmem_stat();				//статистика памяти

#endif
