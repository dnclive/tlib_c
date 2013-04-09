//tmem.h 

/*
 * programing by dnclive /2009/
 *  
*/
#ifndef tmemh
#define tmemh

#include <stdlib.h>
#include <stdio.h>

#include <tdeb.h>

//#include "tmem.h"

//****реализация универсального менеджера памяти через указатели****
#define tint "int"

#define tmem_init_size_in_byte_default 	8096;
#define tmem_pointer_size				sizeof(void *)
#define tmem_pointer 					void *;

//индекс битов флага блока
#define tmem_flag_isref					0;	//признак того что блок содержит ссылки
#define tmem_flag_mark					1;	//признак того что блок обрабатывается

typedef struct _tmemblock tmemblock ;

//данные
struct _tmemblock
{
	//void *mem;				//указатель на начало блока данных
	//void *freemem;			//указатель на начало свободного блока
	long memsize;			//размер блока данных
	long usemem;			//размер используемой памяти для данных
	long freemem;			//размер свободной памяти блока
	long refcount;			//количество ссылок на данный блок
	unsigned  long flag;	//различные да/нет переключатели
							//0 - 1:блок массив ссылок, 0 - блок массив данных
							//1 - метка работы с блоком 1: блок обрабатывается 
							//							0: в текущей операции встречен первый раз
	tmemblock *selfblock;	//указатель на себя на блок целеком а на на блок данных
	tmemblock *nextblock;	//указатель на следующий выделенный блок памяти
};



typedef struct
{
	void *mem;
} tmemp;


//базовые типы данных

//тип число может содержать любое число
typedef union //_tnum
{
	signed long int ival;
	unsigned long int uval;
	float fval;
	long double dval
} tnum;


//указатель на tnum
typedef tnum * tnump;

//typedef _tnum tnum;
//тип целове
typedef long tlong;

//тип указатель на целове
typedef tlong * tlongp;

//тип целове
typedef unsigned long tulong;

//тип указатель на целове
typedef tulong * tulongp;

//тип с плавоющей точкой одинарной точности
typedef float tfloat;

//тип с плавоющей точкой двойной точности
typedef double tdouble;

//тип для хранения симовола строки
typedef unsigned char tchar;
typedef unsigned char * tcharp;

//тип для хранения адреса
typedef void * tp;
typedef tp * tpp;
typedef void * tptr;

//макросы

#define tmem_mref_cnt(type,count) sizeof(type)*(count)/tmem_pointer_size

//функции
tmemblock *tmem_finit(long size_in_byte);//инициализация выделение пямяти

/*
	void *tmem_falloc(int size)
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
void *tmem_falloc(int size);//выделение пямяти размером size

/*
	void *tmem_falloc_ref(void **selfp, int size, int is_pointer)
	функция:
		уровня 0 (для внешних вызовов) выделяющая последовательный блок памяти размера size байт
		и устанавливающая указатель selfp на данный блок,
		- помимо этого инкрементируется счетчик ссылок для вновь выделенного блока памяти
		- и устанавливается флаг is_pointer, указываеющий на то что выделенная память есть массив
		указателей void *!, то есть в момент освобождения данного блока будет произведена попытка освободить
		каждый блоки на которые указывают указатели данного блока
		Пример:
			
	параметры:
		void **selfp	указатель на указатель получающий ссылку на новый блок
		int size		размер в байтах необходимый к выделению
		int is_pointer	флаг указывающий что блок содержит указатели
		
	эффект:
		используется для запроса требуемого объема памяти
		
	возврат:
		возвращается указатель на участок памяти запрошенного разммера
*/
void *tmem_falloc_ref(void **selfp, int size, int is_pointer);//выделение пямяти размером size

/*
	void *tmem_falloc(void **selfp, int size, int is_pointer)
	функция:
		уровня 0 (для внешних вызовов) выделяющая последовательный блок памяти для целых размера size
		и устанавливающая указатель selfp на данный блок,
		- помимо этого инкрементируется счетчик ссылок для вновь выделенного блока памяти,
		  если был передан указатель
		- и устанавливается флаг is_pointer, указываеющий на то что выделенная память не являетмя 
		массивом указателей void *! массив есть массив данных и просто освобождается, 
		то есть в момент освобождения данного блока НЕ будет произведена попытка освободить
		каждый блоки на которые указывают указатели данного блока
		Пример:
			
	параметры:
		void **selfp	указатель на указатель получающий ссылку на новый блок
		int size		размер в количестве необходымых элементов
		
	эффект:
		используется для запроса блока памяти под массив целых размера size
		
	возврат:
		возвращается указатель на участок памяти запрошенного разммера
*/
void *tmem_falloc_int(void **selfp, int size); //получение указатель на свободный блок памяти под int

/*
	tmemblock *_tmem_fref(tmemblock *mb)
	функция:
		- уровня 1 (для внутренних нуж) 
		- инкрементирует счетчик ссылок для переданного блока
		Пример:
			
	параметры:
		tmemblock *mb	указатель на блок данных для инкрементации
		
	эффект:
		используется для запроса требуемого объема памяти
		
	возврат:
		возвращается указатель на блок
*/
tmemblock *_tmem_fref(tmemblock *mb);//увеличивает счетчик ссылок для блока

/*
	tmemblock *_tmem_f_mb_type(tmemblock *mb, int is_pointer)
	функция:
		- уровня 1 (для внутренних нуж)
		- инкрементирует счетчик ссылок для переданного блока
		
		Пример:
			
	параметры:
		tmemblock *mb	указатель на блок данных для инкрементации
		
	эффект:
		используется для запроса требуемого объема памяти
		
	возврат:
		возвращается указатель на блок
*/
tmemblock *_tmem_f_mb_type(tmemblock *mb, int is_pointer);

/*
	void *_tmem_falloc_mb(tmemblock *mb, long size)
	функция:
		уровня 1 (для внутренних нужд) функция пытается выделить блок памяти требуемого объема
		из последовательности имеющихся свободных блоков, для етого она вызывает сама себя рекурсивно 
		перебирая последовательность блоков
		Пример:
			
	параметры:
		int size	размер в байтах необходимый к выделению
		
	эффект:
		используется для запроса требуемого объема памяти
		
	возврат:
		возвращается указатель на участок памяти запрошенного разммера
*/
tmemblock *_tmem_falloc_mb(tmemblock *mb, long size);//выделение пямяти из блока mb
//tmemblock * _tmem_fmemblock(tmemblock *mb, long size); //создание блока в свободном пространстве переданного
//void *_tmem_ffreememp(tmemblock *mb, long size);
long tmem_ffreemem(tmemblock *mb);
void *tmem_fmem(tmemblock *mb);
tmemblock *tmem_fmb(void *self);							//возвращает указатель на блок mb
tmemblock *_tmem_fmb2use(tmemblock *mb,long size);
tmemblock *_tmem_fgetmb(tmemblock* mb, long size);
tmemblock *_tmem_fnewmb(tmemblock *mb, tmemblock *newmb);
tmemblock *_tmem_fspase2newbm(tmemblock *mb, long size);
tmemblock *_tmem_finit_first_mb(tmemblock *mb);

void *tmem_fref(void *self, void **selfp);				//устанавливает selfp на то что указывает self
														//при этом инкрементируется refcount++
void *tmem_funref(void **selfp);						//отсоединяет selfp от данных
														//устанавливает selp в NULL refcount--, возвр NULL
														
void *tmem_fdrop(void **selfp);					//устанавливает selfp в NULL, при этом refcount не 
												//декрементируется, но если ссылок на блок нет то он удаляется

void *tmem_fdrop_all();							//пробегает по всем блокам и удаляем все на что нет ссылок
												//своеобразный сборщик мусора

tmemblock *_tmem_f_free_each_p(tmemblock *mb);

tmemblock *tmem_fnull(tmemblock *mb);					//обнуление указателей

void *tmem_frealloc(tmemblock *mb, int size);//
int tmem_ffree(void *mem);//освобождение памяти)
int _tmem_ffree_mb(tmemblock *mb, void *mem);

int tmem_ffree_all();	//возврат ОС всех запрошенных блоков
int _tmem_ffree_all(tmemblock *mb);
//int tmem_

//информация по используемой памяти
int tmem_fdump();		//дамп 

int tmem_fstatistic();	//статистика использования памяти


#endif
