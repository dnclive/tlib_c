/*
 * tstr_each.c
 */

#include "tstr_each.h"


tstr_each *tstr_each_finit()								//инициализация
{

}

tstr_each *tstr_each_fcre(tstr_eachpp selfp, tstrp str)		//выделение памяти под данные библиотеки
{
	tdeb_fdeb3("tstr_each_deb", __FILE__, __LINE__, "selfp=%p\r\n", selfp);
	//создание
	
	tstr_eachp self=tcre_ftptr(selfp, tcre_mptr_cnt(tstr_each,1));		//выделение указателей для tlisti
	
	tdeb_fdeb3("tstr_each_deb", __FILE__, __LINE__, "str->str=%p\r\n", str->str);
	
	tcre_fref(&self->str, str);
	tcre_fref(&self->charp, NULL);
	tcre_ftlong_val(&self->chari, -1);
	tcre_ftlong_val(&self->bytei, -1);
	
	tcre_ftchar(&self->char_utf8, 7);	//текущий символ utf-8 + 1 закрывающийм \0
	
	tcre_fref(&self->char_ascii, NULL);
	
	tdeb_fdeb3("tstr_each_deb", __FILE__, __LINE__, "chari=%i\r\n", *self->chari);
	
	return self;
}

tstr_eachp tstr_each_finc(tstr_eachpp selfp)
{
	tdeb_fdeb3("tstr_each_deb", __FILE__, __LINE__, "selfp=%p\r\n", selfp);
	//***проверка входных данных
	if (!selfp)		//нет указателя не с чем работать
	{
		return NULL;
	}
	if (!*selfp)
	{
		return NULL;
	}
	tstr_eachp self=*selfp;
	//***проверка входных данных

	if (self->charp&&!*self->charp) //если текущий символ \0 то достигли конца строки дальше не пойдем
	{
		return self;
	}
	
	tdeb_fdeb3("tstr_each_deb", __FILE__, __LINE__, "self->charp=%p\tstr=%s\r\n", 
							self->charp, self->str->str);
	//если это первый вызов то устанавливаем указатель текущего символа на первый байт строки
	if (!self->charp)
	{
		self->charp=self->str->str;
	}
	tdeb_fdeb3("tstr_each_deb", __FILE__, __LINE__, "self->charp=%p\tstr=%p\r\n", 
							self->charp, self->str->str);
	tdeb_fdeb3("tstr_each_deb", __FILE__, __LINE__, "self->charp=%p\t*self->charp=%s\r\n", 
							self->charp, self->charp);
	
	
	//tulong i=*self->bytei+1;			//индекс текущего байта+1 те индекс следующего байта
	//tulong j=*self->chari+1;			//индекс следующего символа (utf-8)
	tlong count=tstr_fcount(self->str);//количество байт в строке
	tdeb_fdeb3("tstr_each_deb", __FILE__, __LINE__, "count=%i\tbytei=%i\t%i\r\n", 
						count, *self->bytei,(*self->bytei)<count);
	tcharp str_byte=self->str;			//текущий байт строки
	//tcharp ch=chp;						//текущий байт символа который ищем
	//tlong ch_start=0;					//1 если текущий байт начало символа
	//tlong ch_eq=0;						//признак эквивалентности символов
	
	while((*self->bytei)<count)		//перебираем байты строки
	{
		(*self->bytei)++;		//индекс следующего байта
		//(*self->chari)++;		//и следующий символ
		self->charp++;		//берем следующий байт
		
		tdeb_fdeb3("tstr_each_deb", __FILE__, __LINE__, "bytei=%i\tchari=%i\r\n", 
					*self->bytei,*self->chari);
		
		//если два первых бита 11 или первый бит 0 то это первый (и возможно еднинственный) байт символа
		if (tbit_fbit(*self->charp, 0)&&tbit_fbit(*self->charp, 1)||!tbit_fbit(*self->charp, 0))	
		{
			//*self->bytei=i;
			(*self->chari)++;
			
			tcharp btp1=self->charp;		//начало текущего символа в строке
			tcharp btp2=self->char_utf8;	//текущий символ utf8
			*btp2=*btp1;					//копируем первый байт символа в текущий
			//далее пока следующий байт первый бит 1 а втророй 0
			
			tdeb_fdeb3("tstr_each_deb", __FILE__, __LINE__, "btp2=%s\tbtp1=%s\r\n", 
					tbit_fbyte2bit(btp2,1), tbit_fbyte2bit(btp1,1));
			
			tdeb_fdeb3("tstr_each_deb", __FILE__, __LINE__, "btp2=%s\tbtp1=%s\t%p\r\n", 
					tbit_fbyte2bit(btp2+1,1), tbit_fbyte2bit(btp1+1,1),btp2+1);
			btp1++;
			btp2++;
			while(tbit_fbit(*btp1, 0)&&!tbit_fbit(*btp1, 1))
			{
				tdeb_fdeb3("tstr_each_deb", __FILE__, __LINE__, "btp2=%s\tbtp1=%s\t%p\r\n", 
					tbit_fbyte2bit(btp2,1), tbit_fbyte2bit(btp1,1),btp2);
				tdeb_fdeb3("tstr_each_deb", __FILE__, __LINE__, "btp2=%p\tbtp1=%p\r\n", 
					btp2, btp1);
				*(btp2++)=*(btp1++);		//копируем каждый байт текущего символа
			}
			*(++btp2)='\0';					//закрываем символом \0
			
			
			return self;
		}
		
		//i++;
	}
	
	return self;
}

//tstr_each_fcopy
