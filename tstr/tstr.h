/*
	tstr.h
*/
#ifndef tstrh
#define tstrh

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <wchar.h>

#include <tmem.h> 
#include <tdeb.h>
#include <tcre.h>
#include <tbit.h>


#define tstr_enc_unicode 0;
#define tstr_enc_ascii 1;

#define mfcopy(self, val) typeof(self)##_fcopy_##typeof(val)(self, val);
#define mffree(type, self) typeof(type)##_ffree(self);

#define max(a,b) ((a) > (b) ? (a) : (b))

typedef struct _tstr tstr ;

typedef tstr * tstrp ;  //указатель на tstr
typedef tstrp * tstrpp ;  //указатель на tstrp

struct _tstr
{
	//tnum *tp_pcnt;			//количество ссылок на структуру
	tnum *len;				//текущая длина строки
	tlong *count;			//количество байт занимаемых строкой
	//tnum *fspace;			//процент первоначального свободного пространства в строке
	tchar *str;				//указатель на строку
};


//функции

/*
	tstr *tstr_fcre();
	функция:
		функция-конструктор
		выделяет память из кучи и инициализирует структуру tstr
		Пример: 
			tstr *str=tstr_init();
			
	параметры:
		
	эффект:
		выделяет память и инициализирует структуру tstr
		
	возврат:
		функция возвращает пороговое значение maxact-sens 
*/
tstr *tstr_fcre(tstrpp selfp, tcharp charp);		//создание строки как ссылки на tchar

tstr *tstr_fcre_copy(tstrpp selfp, tcharp str);		//создание новой строки копирование символов

tstr *tstr_fcre_char(tstrpp selfp, tchar char_val);		//создание новой строки из числового значения 1 символа

tlong tstr_fcharp_len(tcharp charp);				//количество символов в строке
/*
	tstr *tstr_fcre();
	функция:
		функция-конструктор
		выделяет память из кучи и инициализирует структуру tstr длины len 
		* при этом значение никак не инициализируется
		Пример: 
			tstr *str=tstr_init();
			
	параметры:
		
	эффект:
		выделяет память и инициализирует структуру tstr
		
	возврат:
		функция возвращает пороговое значение maxact-sens 
*/
tstr *tstr_fcre_len(tstr **selfp, tlong len);

/*
	tstr *tstr_finit();
	функция:
		функция-конструктор
		выделяет память из кучи и инициализирует структуру tstr
		Пример: 
			tstr *str=tstr_init();
			
	параметры:
		
	эффект:
		выделяет память и инициализирует структуру tstr
		
	возврат:
		функция возвращает пороговое значение maxact-sens 
*/
tstr *tstr_finit();

/*
	tstr *tstr_fcopy_pchar(tstr *self, char *sourse_str)
	функция:
		Копирует символы по переданному указателю sourse_str до \0 по указателю str->str
		считает количество скопированных символов и записывает новую длину строки в len
		Пример: 
			
	параметры:
		*sourse_str	строка содержащая присваиваемое значение
		*self указатель на обрабатываемуюу структуру
	эффект:
		
		
	возврат:
		возвращает self
*/
tstr *tstr_fcp_pchar2str(tstr *self, tcharp sourse_str);

/*
	tstr *tstr_fncopy_pchar2str(tstr *self, char *sourse_str, int n)
	функция:
		Копирует n символов по переданному указателю sourse_str до \0 по указателю str->str
		считает количество скопированных символов и записывает новую длину строки в len
		Пример: 
			
	параметры:
		*sourse_str	строка содержащая присваиваемое значение
		*self указатель на обрабатываемуюу структуру
	эффект:
		
		
	возврат:
		возвращает self
*/
tstr *tstr_fncp_pchar2str(tstr *self,  char *source_str, int n);

tstr *tstr_fp(tstr **selfp, tstr *str); //устанавливаем указатель self=str

tstr *tstr_funp(tstr **selfp);			//отсоединить self от структуры

tstr *tstr_ffree(tstr **selfp);			//освобождаем ресурсы занятые self

tchar tstr_fchar(tstrp self, tlong i);	//возвращает символ с индексом i

tulong tstr_fchari(tstrp self, tcharp chp);	//возвращает индекс символа char

tulong tstr_fchari_2(tstrp self, tcharp chp);

tchar tstr_fset_char(tstrp *selfp, tlong i, tchar ch);	//устанавливает символ с индексом i в ch

tlong tstr_flen(tstrp self);			//возвращает длину строки...

tstrp tstr_fjoin_2(tstrpp selfp, tstrp str1, tstrp str2);	//возвращает строку объединение двух переданных в том же порядке

//возвращает строку объединение трех переданных для объединения с разделителем
tstrp tstr_fjoin_3(tstrpp selfp, tstrp str1, tstrp str2, tstrp str3);//возвращает строку объединение двух переданных c разделителем между

tlong tstr_fcmp(tstrp str1, tstrp str2);	//сравнивает две строки

#endif



