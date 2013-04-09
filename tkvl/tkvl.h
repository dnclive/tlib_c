//tkvl.h 

/*
 * programing by dnclive(c)2011
 *  dnclive@gmail.com
*/
#ifndef tkvlh
#define tkvlh

#include <stdlib.h>
#include <stdio.h>

#include <tdeb.h>
#include <tcontext.h>
#include <tcre.h>
#include <tstr.h>
#include <tmem.h>
#include <tlist.h>
#include <tlist_each.h>
#include <tstr_each.h>

//tkvl
typedef struct _tkvl tkvl ;

typedef tkvl * tkvlp ;		//указатель...

//данные
struct _tkvl
{
	tcontextp context;		//ссылка на контекст
	tkvlp  self;		//ссылка на себя	
	tstrp sep;				//строка разделителей kvl
	tcharp slash_char;		//символ экранирования
	tlongp sepi;			//индекс текущего разделителя
	tlistp list;			//список элементов текущего уровня
	tstrp val;				//значение kvl элемента
};




//tkvl_sep  разделитель kvl элементов
//typedef struct _tkvl_sep tkvl_sep ;

//typedef tkvl_sep * tkvl_sepp ;		//указатель...
/*
//данные
struct _tkvl_sep
{
	tcontextp context;		//ссылка на контекст
	tkvl_sep *self;			//ссылка на себя
};
*/
//функции
/*
	tkvl *tkvl_finit()
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
tkvl *tkvl_finit();		//инициализация библиотеки

/*
	tkvl *tkvl_fcre()
	функция:
		выделение памяти под данные библиотеки
		Пример:
			
	параметры:
		
		
	эффект:
		используется для запроса требуемого объема памяти
		
	возврат:
		возвращается указатель на участок памяти запрошенного разммера
*/
tkvl *tkvl_fcre(tkvlp *selfp, tstrp kvl_str);					//создание
tkvl *tkvl_fcre_sepi(tkvlp *self, tstrp kvl_str, tlong sepi);		//выделение памяти под данные библиотеки

/*
	tkvl *tkvl_fcre()
	функция:
		выделение памяти под данные библиотеки
		Пример:
			
	параметры:
		
		
	эффект:
		используется для запроса требуемого объема памяти
		
	возврат:
		возвращается указатель на участок памяти запрошенного разммера
*/

tkvlp tkvl_fkvl(tkvlp *kvl_strp, tstrp kvl_sep, tlong sepi);		//выделение памяти под данные библиотеки

tkvl *tkvl_fkvl_2(tkvlp *selfp, tstrp kvl_str, tlong sepi);			//через строки Utf8

tlong tkvl_fsepi(tkvlp self);			//возвращает индекс разделителя kvl

tstrp tkvl_fstr(tkvlp self);			//возвращает сроку kvl

tstrp tkvl_fstr_2(tkvlp self);			//возвращает сроку kvl

tlistp tkvl_fall_val(tkvlp self);			//возвращает список всех строковых разделенных ключей/значений

tkvlp tkvl_fall_val_2(tkvlp self, tlistpp kvl_list);	//помещает все ключи/значения в список kvl_list

tlistp tkvl_fflat(tkvlp self, tchar sep);	//возвращает списко kvl уровня sep

tlistp tkvl_fflat_2(tkvlp self, tchar sep, tlistpp kvl_list);	//возвращает списко kvl уровня sep

#endif
