//      tstr.c
//      
//      Copyright 2011 dnclive <dnclive@ubunlive3>
//      
//      This program is free software; you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation; either version 2 of the License, or
//      (at your option) any later version.
//      
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//      
//      You should have received a copy of the GNU General Public License
//      along with this program; if not, write to the Free Software
//      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
//      MA 02110-1301, USA.


#include "tstr.h"

//создание строки путем прикрепление ссылки на существующий массив tchar
//то есть копирование символов не происходит а лишь создание данных tstr
//и запоминание ссылки на tcharp
tstr *tstr_fcre(tstrpp selfp, tcharp charp)
{
	tdeb_fdeb3("tstr_deb", __FILE__, __LINE__, "self=%p\r\n", selfp);
	
	tstr *self=tcre_ftptr(selfp, tcre_mptr_cnt(tstr,1));	//выделение множества указателей
	
	tcre_ftnum_val(&self->len, (tnum)tstr_fcharp_len(charp));		//длина строки
	
	tcre_fref(&self->str, charp);							//строка символов
	
	return self; 
}

//создание новой строки путем копирования массива символов по указателю
tstr *tstr_fcre_copy(tstrpp selfp, tcharp str)
{
	tdeb_fdeb3("tstr_deb", __FILE__, __LINE__, "self=%p\r\n", selfp);
	
	tstrp self=tcre_ftptr(selfp, tcre_mptr_cnt(tstr,1)); //выделение множества указателей
	
	//tcre_ftnum(&self->len, 1);				//выделение памяти под len
	
	tcre_ftnum(&self->len, 1);		//под len 
	self->len->ival=0;
	
	tcre_ftlong_val(&self->count, (tlong)0);	//count
	
	//self->len->ival=0;
	//tdeb_fdeb("tstr_deb", "sizeof(tpchar)=%i\r\n", sizeof(tptr));
	//self->len=0;
	//self->str=NULL;
	
	tstr_fcp_pchar2str(self, str);
	
	//если передан указатель на указатель на создаваемый объект
	if (selfp) *selfp=self;   //передаем указатель на созданную структуру этопу указателю
	
	return self; 
}

//создание новой строки из числового значения 1 символа
tstr *tstr_fcre_char(tstrpp selfp, tchar char_val)
{
	tdeb_fdeb3("tstr_deb", __FILE__, __LINE__, "self=%p\r\n", selfp);
	
	tstrp self=tcre_ftptr(selfp, tcre_mptr_cnt(tstr,1)); //выделение множества указателей
	
	tcre_ftnum_val(&self->len, (tnum)(tlong)1);	//выделение памяти под len
		
	tcre_ftchar(&self->str, 2);		//выделяем место под два символа
	self->str[0]=char_val;			//первый переданный нам char_val
	self->str[1]='\0';				//второй нулевой закрывающий)

	return self;
}
	
tstrp tstr_fcre_len(tstrp *selfp, tlong len)
{
	tstrp self=tcre_ftptr(selfp, tcre_mptr_cnt(tstr,1)); //выделение множества указателей
	
	//tcre_ftnum(&self->tp_pcnt, 1);			//выделение памяти под tp_pcnt
	tcre_ftnum(&self->len, 1);				//выделение памяти под len
	self->len->ival=len;					//устанавливаем равным требуемой длине
	//tcre_ftnum(&self->fspace, 1);				//выделение памяти под fspace
	
	return self;
}

tstr *tstr_finit()
{
	//tstr *str=(tstr*)malloc(sizeof(tstr));
	tstr *str=(tstr*)tmem_falloc(sizeof(tstr));
	str->len=0;
	str->str=NULL;
	
	return str; 
}


//*** работа с символами строки ***

tlong tstr_fcharp_len(tcharp charp)
{
	tlong len=0;
	tcharp sp=charp;
	while (*sp!='\0')
	{
		len++;
		sp++;
	}
	return len;		//возвращаем длину строки +1 закрывающий нулевой символ
}

tlong _tstr_flen(tcharp charp)
{
	tlong len=0;
	tcharp sp=charp;
	while (*sp!='\0')
	{
		//если первые два бита 1 или 1 бит 0 то считаем за очередной символ (или его начало)
		if (tbit_fbit(*sp, 0)&&tbit_fbit(*sp, 0)||!tbit_fbit(*sp, 0))
		{
			len++;
		}
		sp++;
	}
	return len;		//возвращаем длину строки +1 закрывающий нулевой символ
}

tlong _tstr_fcount(tcharp charp)
{
	tulong count=0;
	tcharp sp=charp;
	while (*sp!='\0')
	{
		count++;
		sp++;
	}
	return count+1;		//возвращаем длину строки +1 закрывающий нулевой символ
}

tlong tstr_fcount(tstrp self)
{
	tdeb_fdeb3("tstr_deb", __FILE__, __LINE__, "self=%p\t self->len=%i\r\n", self, *self->count);
	
	//tstrp self=NULL;
	if (!self)
	{
		return 0;
	}
	
	return *(tlong *)self->count;
}

tstr *tstr_fcp_pchar2str(tstr *self,  tcharp source_str)
{	
	if(!self) tstr_fcre(&self, source_str);//self=tstr_fcre(NULL);	//создание если не создано!
	
	
	
	//вычисляем длину новой строки
	
	*self->count=_tstr_fcount(source_str);
	
	self->len->ival=_tstr_flen(source_str);
	
	/*
	int len=0;
	char *sp=source_str;
	while (*sp!='\0')
	{
		tdeb_fdeb("tstr_deb", "____1_______%i\r\n%p\r\n%s\r\n%s\r\n",len, sp, source_str, sp); 
		tdeb_fdeb("tstr_deb", "____2_______%i\r\n",*sp); 
		tdeb_fdeb("tstr_deb", "____size_____%s\r\n",strchr("влова", 'о')); 
		len++;
		sp+=1;
	}
	
	*/
	
	//выделяем пямять под строку если значение задается первый раз
	//if (*self->count==0)
	//{
		//tstr *str=(tstr*)tmem_falloc(sizeof(tstr));
		//self->str->val=(char*)tmem_falloc(sizeof(char)*len+1);
		//tmem_falloc_ref(&self->str, sizeof(char)*len, 0);
		tcre_ftchar(&self->str, *self->count+1);
		
	//}
	
	tdeb_fdeb("tstr_deb", "копируем строку\r\n%i\r\n%p\r\n",*self->count, self->str); 
	strncpy(self->str, source_str, *self->count);
	tdeb_fdeb("tstr_deb", "строка скопирована\r\n%s\r\n",source_str);
	
	//self->len->ival=len;
	
	//tmem_fdump();
	
	return self;
}

tstr *tstr_fncp_pchar2str(tstr *self,  char *source_str, int n)
{	
	if(!self) tstr_fcre(&self, source_str);//self=tstr_fcre(NULL);	//создание если не создано!
	
	//вычисляем длину новой строки
	int len=0;
	char *sp=source_str;
	while (*sp!='\0')
	{
		len++;
		sp++;
	}
	//выделяем пямять под строку если значение задается первый раз
	if (self->len==0)
	{
		//tstr *str=(tstr*)tmem_falloc(sizeof(tstr));
		self->str=(char*)tmem_falloc(sizeof(char)*len+1);
		
	}
	
	tdeb_fdeb("tstr_deb", "копируем строку%i\r\n%i\r\n%p\r\n",len,self->len, self->str); 
	strncpy(self->str, source_str, len);
	tdeb_fdeb("tstr_deb", "строка скопирована\r\n%s\r\n",source_str);
	
	self->len->ival=len;
	
	//tmem_fdump();
	
	return self;
}

/*
tstr *tstr_fp(tstr **selfp, tstr *str)
{
	if (!selfp) return NULL;		//если передан недействительный указатель
	
	tstr *self=*selfp;
	
	if (!self) return NULL;	//если указатель недействиетльный освобождать нечего
	
	tstr_funp(selfp);	//отключаем указатель self;
	self=str;			//подключаем self к str
	str->tp_pcnt->ival++;		//инкрементируем tp_pcnt у str
	
	return str;
}


tstr *tstr_funp(tstr **selfp)
{	
	if (!selfp) return NULL;		//если передан недействительный указатель
	
	tstr *self=*selfp;
	
	if (!self) return NULL;	//если указатель недействиетльный освобождать нечего
	
	//self->tp_pcnt->ival--;
	if (!self->tp_pcnt->ival) tstr_ffree(selfp);

	return self;
}
*/
tstr *tstr_ffree(tstr **selfp)
{
	if (!selfp) return NULL;		//если передан недействительный указатель
	
	tstr *self=*selfp;
	if (!self) return NULL;	//если указатель недействиетльный освобождать нечего
	
	tdeb_fdeb("tstr_deb", "self->str=%p\r\n", self->str);
	//tmem_fdump();
	
	tmem_ffree(self->str);	//освобождаем память выделенную под строку
	
	tdeb_fdeb("tstr_deb", "self=%p\r\n", self);
	//tmem_fdump();
	tmem_ffree(self);		//освобождаем память выделенную под структуру
	self=NULL;
	
	return NULL;
}

tchar tstr_fchar(tstrp self, tlong i)	//возвращает символ с индексом i
{
	tdeb_fdeb3("tstr_deb", __FILE__, __LINE__, "*selfp=%p\r\n", self);
	
	if (self&&self->len>i)
	{
		return self->str[i];
	}
	
	return '\0';
	
}

tcharp tstr_fchar_by_i_utf8(tstrp self, tchar ch)
{
	tdeb_fdeb3("tstr_deb", __FILE__, __LINE__, "str1=%p\r\n", self);
	if (!self) return NULL;		//если передан недействительный указатель
	
	tlong i=0;
	tlong len=tstr_flen(self);
	while(i<len)
	{
		tdeb_fdeb3("tstr_deb", __FILE__, __LINE__, "i=%i\ti=%i\r\n", i, len);
		tdeb_fdeb3("tstr_deb", __FILE__, __LINE__, "%i\t%i\r\n", ch, self->str[i]);
		if (self->str[i]==ch)	//проверяем равенство символов
		{
			return i;
		}
		i++;
	}
	
	return -1;
}

tulong tstr_fchari_2(tstrp self, tcharp chp)
{
	tdeb_fdeb3("tstr_deb", __FILE__, __LINE__, "str1=%p\r\n", self);
	if (!self) return NULL;		//если передан недействительный указатель
	
	tulong i=0;							//индекс текущего байта
	tulong j=0;							//индекс текущего символа (utf-8)
	tulong count=_tstr_fcount(self);	//количество байт в строке
	tcharp str_ch=self->str;			//текущий символ (байт) строки
	tcharp ch=chp;						//текущий байт символа который ищем
	tlong ch_start=0;					//1 если текущий байт начало символа
	tlong ch_eq=0;						//признак эквивалентности символов
	while(i<count)		//перебираем байты строки
	{
		//tdeb_fdeb3("tstr_deb", __FILE__, __LINE__, "i=%i\ti=%i\r\n", i, len);
		//tdeb_fdeb3("tstr_deb", __FILE__, __LINE__, "%i\t%i\r\n", ch, self->str[i]);
		if (tbit_fbit(*str_ch, 0)&&tbit_fbit(*str_ch, 0))	//если два первых бита 11
		{				//то мы встретили начало символа из нескольких байт
		
			if (ch_eq)	//если предыдущий символ оказался равен мы нашли целевой символ в строке
			{
				return j;
			}
			j++;		//следующий символ индексируем его
			ch=chp;		//устанавливаем в начало целевого символа и начинаем сравнение с текущего (первого байта) нового
						//символа
			if (self->str[i]==*ch)	//проверяем равенство текущих байтов
			{
				ch_eq=1;
			}
			ch++;					//берем следующий байт целевого символа
			i++;
			continue;
		}
		if (tbit_fbit(*str_ch, 0)&&!tbit_fbit(*str_ch, 0))	//если первый бит 1 а следующий 0 
		{				//то перед нами байт из символа 2-6
			if (ch_eq&&self->str[i]==*ch)//если все предыдущие байты символа совпадали то  сравниваем с тукущим байтом
			{
				ch++;
				
			}
			ch_eq=0;			//иначе сбрасываем признак равенства текущего символа и ждем следующий
			i++;
			continue;
		}
		if (!tbit_fbit(*ch, 0))							//если первый бит 0
		{
			j++;
			if (self->str[i]==ch)	//проверяем равенство символов
			{
				return i;
			}
		}
		
		i++;
	}
	
	return -1;
}

tulong tstr_fchari(tstrp self, tcharp chp)
{
	tdeb_fdeb3("tstr_deb", __FILE__, __LINE__, "str1=%p\r\n", self);
	if (!self) return NULL;		//если передан недействительный указатель
	
	
	tcharp chp1=self->str;
	tcharp chp2=chp;
	
	tulong i=0;							//индекс текущего байта
	tulong count=_tstr_fcount(self);	//количество байт в строке
	
	tulong j=-1;						//индекс текущего символа (utf-8)
	
	tlong is_eq=0;						//
	tdeb_fdeb3("tstr_deb", __FILE__, __LINE__, "count=%i\r\n", count);
	while(i<count&&(*chp2)!='\0')		//перебираем байты строки
	{
		
		
		if (tbit_fbit(*chp1, 0)&&tbit_fbit(*chp1, 1)||!tbit_fbit(*chp1, 0))
		{
			j++;
		}
		tdeb_fdeb3("tstr_deb", __FILE__, __LINE__, "chp1=%s\tchp2=%s\t%i\t%i\r\n", chp1, chp2, *chp2, j);
		if (*chp1==*chp2)
		{
			//*chp=*chp1;
			chp2++;
			is_eq=1;
		}
		else if (*chp1!=*chp2)
		{
			chp2=chp;
			is_eq=0;
		}
		chp1++;
		i++;
	}
	if (!*chp2&&is_eq)
	{
		return j;
	}
	
	return -1;
}



tchar tstr_fchar_by_i_ascii(tstrp self, tchar ch)
{
	tdeb_fdeb3("tstr_deb", __FILE__, __LINE__, "str1=%p\r\n", self);
	if (!self) return NULL;		//если передан недействительный указатель
	
	tlong i=0;
	tlong len=tstr_flen(self);
	while(i<len)
	{
		tdeb_fdeb3("tstr_deb", __FILE__, __LINE__, "i=%i\ti=%i\r\n", i, len);
		tdeb_fdeb3("tstr_deb", __FILE__, __LINE__, "%i\t%i\r\n", ch, self->str[i]);
		if (self->str[i]==ch)	//проверяем равенство символов
		{
			return i;
		}
		i++;
	}
	
	return -1;
}

tchar tstr_fset_char(tstrp *selfp, tlong i, tchar ch)
{
	tdeb_fdeb3("tstr_deb", __FILE__, __LINE__, "*selfp=%p\r\n", selfp);
	
	tstrp self=NULL;
	if (selfp)
	{
		self=*selfp;
	}
	
	if (self&&self->len>i)
	{
		self->str[i]=ch;
		return self->str[i];
	}
	
	return '\0';

}

tlong tstr_flen(tstrp self)			//возвращает длину строки...
{
	tdeb_fdeb3("tstr_deb", __FILE__, __LINE__, "self=%p\t self->len=%i\r\n", self, *self->len);
	
	//tstrp self=NULL;
	if (!self)
	{
		return 0;
	}
	
	return *(tlong *)self->len;
}

//создает строку selfp объединение двух переданных в том же порядке
tstrp tstr_fjoin_2(tstrpp selfp, tstrp str1, tstrp str2)
{
	tdeb_fdeb3("tstr_deb", __FILE__, __LINE__, "str1=%p\r\n", str1);
	tdeb_fdeb3("tstr_deb", __FILE__, __LINE__, "str2=%p\r\n", str2);
	
	tlong str1_len=0;
	if (str1) str1_len=tstr_flen(str1);
	
	tlong str2_len=0;
	if (str2) str2_len=tstr_flen(str2);
	
	tdeb_fdeb3("tstr_deb", __FILE__, __LINE__, "str1_len=%i\r\n", str1_len);
	tdeb_fdeb3("tstr_deb", __FILE__, __LINE__, "str2_len=%i\r\n", str2_len);
	
	tcharp join_str=tcre_ftchar(NULL, str1_len+str2_len+1);
	
	//копируем первую строку в новую
	if(str1) strcpy(join_str, str1->str);
	
	//копируем вторую строку если она есть в новую после первой
	if (str2) strcpy(join_str+str1_len, str2->str);
	
	//закрываем символом конца строки
	join_str[str1_len+str2_len]='\0';
	tdeb_fdeb3("tstr_deb", __FILE__, __LINE__, "str1_len+str2_len=%i\r\n", 
								str1_len+str2_len);
	
	return tstr_fcre(selfp, join_str);
}

//создает строку объединение двух переданных в том же порядке
tstrp tstr_fjoin_3(tstrpp selfp, tstrp str1, tstrp str2, tstrp str3)
{
	
	tdeb_fdeb3("tstr_deb", __FILE__, __LINE__, "str1=%p\r\n", str1);
	tdeb_fdeb3("tstr_deb", __FILE__, __LINE__, "str2=%p\r\n", str2);
	tdeb_fdeb3("tstr_deb", __FILE__, __LINE__, "str3=%p\r\n", str3);
	
	tlong str1_len=0;
	if (str1) str1_len=tstr_flen(str1);
	
	tlong str2_len=0;
	if (str2) str2_len=tstr_flen(str2);
	
	tlong str3_len=0;
	if (str3) str3_len=tstr_flen(str3);
	
	tdeb_fdeb3("tstr_deb", __FILE__, __LINE__, "str1_len=%i\r\n", str1_len);
	tdeb_fdeb3("tstr_deb", __FILE__, __LINE__, "str2_len=%i\r\n", str2_len);
	tdeb_fdeb3("tstr_deb", __FILE__, __LINE__, "str3_len=%i\r\n", str3_len);
	
	tcharp join_str=tcre_ftchar(NULL, str1_len+str2_len+str3_len+1);
	
	//копируем первую строку еси она есть в новую
	if(str1) strcpy(join_str, str1->str);
	
	//tdeb_fdeb3("tstr_deb", __FILE__, __LINE__, "join_str=%p\r\n", join_str);
	//tdeb_fdeb3("tstr_deb", __FILE__, __LINE__, "join_str2=%p\r\n", join_str+str1_len);
	
	//копируем вторую строку если она есть в новую после первой
	if (str2) strcpy(join_str+str1_len, str2->str);
	
	//копируем тертью строку если она есть в новую после второй
	if (str3) strcpy(join_str+str1_len+str2_len, str3->str);
	
	//закрываем символом конца строки
	join_str[str1_len+str2_len+str3_len]='\0';
	
	tdeb_fdeb3("tstr_deb", __FILE__, __LINE__, "str1_len+str2_len=%i\r\n", 
								str1_len+str2_len+str3_len);
	
	return tstr_fcre(selfp, join_str);
}

tlong tstr_fcmp(tstrp str1, tstrp str2)
{
	if (!str1) return NULL;		//если передан недействительный указатель
	if (!str2) return NULL;		//если передан недействительный указатель
	
	if (tstr_flen(str1)!=tstr_flen(str2))	//если не равны длины
	{
		return 0;							//не равны и строки
	}
	
	tlong i=0;
	tlong len=tstr_flen(str1);
	tlong iseq=1;
	while(i<len)
	{
		if (str1->str[i]!=str2->str[i])	//проверяем равенство символов
		{
			iseq&=0; 
		}
		
		if(!iseq)	//если не равен хоть один символ то не равны и строки
		{
			return iseq; //дальше проверять смысла нет
		}
		i++;
	}
	
	return iseq;
}

