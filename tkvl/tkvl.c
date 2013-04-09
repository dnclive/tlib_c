/*
 * tkvl.c
 */

#include "tkvl.h"


tkvl *tkvl_finit()								//инициализация
{

}

tkvl *tkvl_fcre(tkvlp *selfp, tstrp kvl_str)
{
	tdeb_fdeb3("tkvl_deb", __FILE__, __LINE__, "selfp=%p\r\n", selfp);
	
	
	tkvl *self=tcre_ftptr(selfp, tcre_mptr_cnt(tkvl,1));	//выделение указателей для tanjector
	
	tcre_fref(&self->self, self);							//ссылка на себя
	
	tcre_fref(&self->sep, tstr_fcre_copy(NULL, "^|&:"));	//последовательность разделителей
				
	//tcre_ftchar_val(&self->slash_char, '\\');				//символ экранирования
	tcre_fref(&self->slash_char, tstr_fcre_copy(NULL, "\\")->str);
	
	tcre_ftlong_val(&self->sepi, 0);						//индекс текущего разделителя

	tcre_fref(&self->list, tlist_fcre(NULL)); 							//список дочерних элементов
	
	//иначе запускаем парсинг kvl строки 
	tkvl_fcre_sepi(&self, kvl_str, 0);

	//возвращаем результат
	return self;
}

tkvl *tkvl_fcre_sepi(tkvlp *selfp, tstrp kvl_str, tlong sepi)	//выделение памяти под данные библиотеки
{
	tdeb_fdeb3("tkvl_deb", __FILE__, __LINE__, "selfp=%p\r\n", selfp);
	
	
	tkvl *self=tcre_ftptr(selfp, tcre_mptr_cnt(tkvl,1));	//выделение указателей для tanjector
	
	tcre_fref(&self->self, self);							//ссылка на себя
	
	tcre_fref(&self->sep, tstr_fcre_copy(NULL, "^|&:"));	//последовательность разделителей
				
	//tcre_ftchar_val(&self->slash_char, '\\');				//символ экранирования
	tcre_fref(&self->slash_char, tstr_fcre_copy(NULL, "\\")->str);
	
	tcre_ftlong_val(&self->sepi, sepi);						//индекс текущего разделителя
	
	tdeb_fdeb3("tkvl_deb", __FILE__, __LINE__, "sepi=%i\r\n *self->sepi=%i\r\n", 
											sepi, *self->sepi);
	
	tcre_fref(&self->list, tlist_fcre(NULL)); 							//список дочерних элементов
	
	tdeb_fdeb3("tkvl_deb", __FILE__, __LINE__, "self->sepi=%p\r\n *self->sepi=%i\r\n \r\n self->sep->len=%i\r\n", 
													self->sepi, *self->sepi, tstr_flen(self->sep));
		
	tdeb_fdeb3("tkvl_deb", __FILE__, __LINE__, "self->str=%s\r\n",kvl_str->str);
																								
	if (sepi>=tstr_flen(self->sep))	//если индекс текущего разделителя больше или равен
	{									//длине строки разделителей то делить больше нечего
		tcre_fref(&self->val, kvl_str);	//получаем атомарное строковое значение
		return self;					//возвращаем наверх
	}
	
	
	//иначе запускаем парсинг kvl строки 
	tkvl_fkvl(&self, kvl_str, sepi);
	
	
	tdeb_fdeb3("tkvl_deb", __FILE__, __LINE__, "self=%p\r\n", self);
	
	//возвращаем результат
	return self;
}

tkvl *tkvl_fkvl(tkvlp *selfp, tstrp kvl_str, tlong sepi)
{
	tdeb_fdeb3("tkvl_deb", __FILE__, __LINE__, "kvl_str=%p\r\n", kvl_str);
	
	//***проверка входных данных
	if (!selfp)		//нет указателя не с чем работать
	{
		return NULL;
	}
	if (!*selfp)
	{
		return NULL;
	}
	//***проверка входных данных

	
	
	//*** инициализируем необходимые переменные
	//tdeb_fdeb3("tkvl_deb", __FILE__, __LINE__, "self=%p\r\n", self);
	tdeb_fdeb3("tkvl_deb", __FILE__, __LINE__, "kvl_str->len=%i\r\n", *kvl_str->len);
	
	tkvlp self=*selfp;
	
	//строка хранящая текущий набираемый элемент
	tchar *kvl_stri=tcre_ftchar(NULL, tstr_flen(kvl_str)+1);
	//kvl_stri[tstr_flen(kvl_str)+1]='\0';//	упразнили так как в конце в любом случае  учтено
	
	tlong i=0;						//индекс текущего символа исходной строки
	tlong j=0;						//индекс текущего символа составляемой строки
	tlong slashed_char=0;			//признак экранирования следующего символа
	tcharp ch;						//текущий символ исходной строки
	tchar sep=tstr_fchar(self->sep, tkvl_fsepi(self));		//текущий разделитель
	//tdeb_fdeb3("tkvl_deb", __FILE__, __LINE__, "2837429374293874 sepi=%i\r\n",tkvl_fsepi(self));

	tdeb_fdeb3("tkvl_deb", __FILE__, __LINE__, "sep=%i\r\n\t\tch=%i\r\n", sep, tstr_fchar(kvl_str, i));
	//*** инициализируем необходимые переменные
	
	//*** перебераем все символы текущей строки разбивая на подстроки по разделителям
	//tstr_eachp str_each=tstr_each_fcre(NULL, kvl_str);
	while(ch=tstr_fchar(kvl_str, i))
	//while(*tstr_each_finc(str_each)->char_utf8)
	{
		tdeb_fdeb3("tkvl_deb", __FILE__, __LINE__, 
					"\t\tch=%i\r\n\t\tslashed=%i\r\n\t\tkvli=%s\r\n", ch, slashed_char, kvl_stri);
		if (*self->slash_char==ch&&!slashed_char)//если текущий символ неэкранированный экран
		//if (tstr_fcmp(self->slash_char, ch)&&!slashed_char)//если текущий символ неэкранированный экран
		{
			slashed_char=1;			//ставим признак того что следующий символ экранирован
			i++;
			continue;				//идем дальше
		}
		else if (slashed_char)
		{
			kvl_stri[j]=ch;	//помещаем текущий символ в текущий элемент
			//tstr_fjoin_2(kvl_stri, kvl_stri, ch)
			j++;			//к вставке следующего символа
			
		}
		else if (!slashed_char&&ch==sep)	//если текущий исходный символ есть неэкранированный текущий разделитель
		{
			kvl_stri[j]='\0';		//добавляем символ конца строки
			
			//*** парсим элемент текущего множества
			//добавляем текущий собранный элемент в список и отдаем его на дальнейший разбор
			//со следующим разделителем
			tdeb_fdeb3("tkvl_deb", __FILE__, __LINE__, "kvl_stri=%s\r\n", kvl_stri);
			tlist_fadd_data(&self->list, tkvl_fcre_sepi(NULL, tstr_fcre_copy(NULL, kvl_stri), *self->sepi+1));
			//*** парсим элемент текущего множества
			
			j=0;			//собираем новый элемент заполняем текущую строку заново
			
		}
		else
		{
			kvl_stri[j]=ch;				//добавляем текущий символ в текущий элемент
			j++;						//к вставке следующего символа
		}
		
		i++;						//к проверке следующий исходный символ
		slashed_char=0; 			//сбрасываем экран
	}
	
	//*** обрабатываем последний элемент
	
	//попали сюда - дошли до последнего символа парсим последний элемент
	kvl_stri[j]='\0';		//добавляем символ конца строки
	//добавляем текущий собранный элемент в список и отдаем его на дальнейший разбор
	//со следующим разделителем
	tdeb_fdeb3("tkvl_deb", __FILE__, __LINE__, "kvl_stri=%s\r\n", kvl_stri);
	
	tlist_fadd_data(&self->list, tkvl_fcre_sepi(NULL, tstr_fcre_copy(NULL, kvl_stri), *self->sepi+1));
	
	//*** обрабатываем последний элемент
	
	return self;					//возвращаем полученный kvl
	
}

tkvl *tkvl_fkvl_2(tkvlp *selfp, tstrp kvl_str, tlong sepi)
{
	tdeb_fdeb3("tkvl_deb", __FILE__, __LINE__, "kvl_str=%p\r\n", kvl_str);
	
	//***проверка входных данных
	if (!selfp)		//нет указателя не с чем работать
	{
		return NULL;
	}
	if (!*selfp)
	{
		return NULL;
	}
	//***проверка входных данных

	
	
	//*** инициализируем необходимые переменные
	//tdeb_fdeb3("tkvl_deb", __FILE__, __LINE__, "self=%p\r\n", self);
	tdeb_fdeb3("tkvl_deb", __FILE__, __LINE__, "kvl_str->len=%i\r\n", *kvl_str->len);
	
	tkvlp self=*selfp;
	
	//строка хранящая текущий набираемый элемент
	tchar *kvl_stri=tcre_ftchar(NULL, tstr_flen(kvl_str)+1);
	//kvl_stri[tstr_flen(kvl_str)+1]='\0';//	упразнили так как в конце в любом случае  учтено
	
	tlong i=0;						//индекс текущего символа исходной строки
	tlong j=0;						//индекс текущего символа составляемой строки
	tlong slashed_char=0;			//признак экранирования следующего символа
	tcharp ch;						//текущий символ исходной строки
	tchar sep=tstr_fchar(self->sep, tkvl_fsepi(self));		//текущий разделитель
	//tdeb_fdeb3("tkvl_deb", __FILE__, __LINE__, "2837429374293874 sepi=%i\r\n",tkvl_fsepi(self));

	tdeb_fdeb3("tkvl_deb", __FILE__, __LINE__, "sep=%i\r\n\t\tch=%i\r\n", sep, tstr_fchar(kvl_str, i));
	//*** инициализируем необходимые переменные
	
	//*** перебераем все символы текущей строки разбивая на подстроки по разделителям
	tstr_eachp str_each=tstr_each_fcre(NULL, kvl_str);
	//while(ch=tstr_fchar(kvl_str, i))
	while(*tstr_each_finc(str_each)->char_utf8)
	{
		tdeb_fdeb3("tkvl_deb", __FILE__, __LINE__, 
					"\t\tch=%i\r\n\t\tslashed=%i\r\n\t\tkvli=%s\r\n", ch, slashed_char, kvl_stri);
		//if (*self->slash_char==ch&&!slashed_char)//если текущий символ неэкранированный экран
		if (tstr_fcmp(self->slash_char, ch)&&!slashed_char)//если текущий символ неэкранированный экран
		{
			slashed_char=1;			//ставим признак того что следующий символ экранирован
			i++;
			continue;				//идем дальше
		}
		else if (slashed_char)
		{
			kvl_stri[j]=ch;	//помещаем текущий символ в текущий элемент
			tstr_fjoin_2(kvl_stri, kvl_stri, ch);
			j++;			//к вставке следующего символа
			
		}
		else if (!slashed_char&&ch==sep)	//если текущий исходный символ есть неэкранированный текущий разделитель
		{
			kvl_stri[j]='\0';		//добавляем символ конца строки
			
			//*** парсим элемент текущего множества
			//добавляем текущий собранный элемент в список и отдаем его на дальнейший разбор
			//со следующим разделителем
			tdeb_fdeb3("tkvl_deb", __FILE__, __LINE__, "kvl_stri=%s\r\n", kvl_stri);
			tlist_fadd_data(&self->list, tkvl_fcre_sepi(NULL, tstr_fcre_copy(NULL, kvl_stri), *self->sepi+1));
			//*** парсим элемент текущего множества
			
			j=0;			//собираем новый элемент заполняем текущую строку заново
			
		}
		else
		{
			kvl_stri[j]=ch;				//добавляем текущий символ в текущий элемент
			j++;						//к вставке следующего символа
		}
		
		i++;						//к проверке следующий исходный символ
		slashed_char=0; 			//сбрасываем экран
	}
	
	//*** обрабатываем последний элемент
	
	//попали сюда - дошли до последнего символа парсим последний элемент
	kvl_stri[j]='\0';		//добавляем символ конца строки
	//добавляем текущий собранный элемент в список и отдаем его на дальнейший разбор
	//со следующим разделителем
	tdeb_fdeb3("tkvl_deb", __FILE__, __LINE__, "kvl_stri=%s\r\n", kvl_stri);
	
	tlist_fadd_data(&self->list, tkvl_fcre_sepi(NULL, tstr_fcre_copy(NULL, kvl_stri), *self->sepi+1));
	
	//*** обрабатываем последний элемент
	
	return self;					//возвращаем полученный kvl
	
}

tlong tkvl_fsepi(tkvlp self)
{
	tdeb_fdeb3("tkvl_deb", __FILE__, __LINE__, "kvl_str=%p\r\n", self);
	
	if (!self)
	{
		return 0;
	}
	
	//tdeb_fdeb3("tkvl_deb", __FILE__, __LINE__, "kvl_str->sepi=%i\r\n", *self->sepi);
	
	return *self->sepi;
}

tstrp tkvl_fstr_2(tkvlp self) 				//возвращает сроку kvl
{
	tdeb_fdeb3("tkvl_deb", __FILE__, __LINE__, "self=%p\r\n", self);
	
	if (!self)		//если не передано указателя возвращаем так же пустой указатель
	{
		return NULL;
	}
	
	tlong sepi = tkvl_fsepi(self);
	tdeb_fdeb3("tkvl_deb", __FILE__, __LINE__, "sepi=%i\r\n\t\t str_len=%i\r\n", sepi, tstr_flen(self->sep));
	if (sepi>=tstr_flen(self->sep))		//если индекс текущего разделителя больше или равен
	{									//длине строки разделителей то это последний уровень
										//возвращаем значение val текущего Kvl
		tdeb_fdeb3("tkvl_deb", __FILE__, __LINE__, "self->val->str.val=%s\r\n", self->val->str);
		return self->val;				//возвращаем наверх строку текущего kvl
	}
	
	//иначе перебираем свои элементы и запрашиваем fstr у них
	tlist_eachp list_each= tlist_each_fcre(NULL, self->list);
	
	//строка текущего kvl
	tstrp kvl_str=NULL;
	
	//текущий соединитель
	tstrp sep = tstr_fcre_char(NULL, tstr_fchar(self->sep, sepi));	
	
	//*** получаем строку первого элемента
	if (tlist_each_finc(&list_each)->listi)
	{
		tdeb_fdeb3("tkvl_deb", __FILE__, __LINE__, "list_each->listi=%p\r\n", list_each->listi->data);
		kvl_str=tkvl_fstr(list_each->listi->data);
		
		//tdeb_fdeb3("tkvl_deb", __FILE__, __LINE__, "kvl_str=%s\r\n", kvl_str->str);
		//tdeb_fdeb3("tkvl_deb", __FILE__, __LINE__, "контрольная точка\r\n");
		//tmem_fdump();
	}
	//*** получаем строку первого элемента
	
	//*** перебираем все остальные элементы
	while(tlist_each_finc(&list_each)->listi)
	{
		tdeb_fdeb3("tkvl_deb", __FILE__, __LINE__, "контрольная точка\r\n");
		//tdeb_fdeb3("tkvl_deb", __FILE__, __LINE__, "list_each=%i\r\n", *list_each->count);
		tdeb_fdeb3("tkvl_deb", __FILE__, __LINE__, "list_each->i=%i\r\n", *list_each->i);

		tstrp currnet_kvl_str=tkvl_fstr(list_each->listi->data);
		tdeb_fdeb3("tkvl_deb", __FILE__, __LINE__, "kvl_str=%s\r\n", kvl_str->str);
		tdeb_fdeb3("tkvl_deb", __FILE__, __LINE__, "kvl_str=%s\r\n", currnet_kvl_str->str);
		
		//соединаем kvl_str каждого элемента через текущий разделитель
		tstr_fjoin_3(	&kvl_str,					//помещаем резальтат сюда
						kvl_str,					//первая строка соединения все предыдущие элементы
						sep,						//текущий соединитель
						currnet_kvl_str				//kvl строка следующиего элемента
					);
					
		tdeb_fdeb3("tkvl_deb", __FILE__, __LINE__, "kvl_str=%s\r\n", kvl_str->str);
	}
	
	//tdeb_fdeb3("tkvl_deb", __FILE__, __LINE__, "контрольная точка\r\n");
	
	tdeb_fdeb3("tkvl_deb", __FILE__, __LINE__, "kvl_str=%s\r\n", kvl_str->str);
	
	return kvl_str;
}

tstrp tkvl_fstr(tkvlp self) 				//возвращает сроку kvl
{
	tdeb_fdeb3("tkvl_deb", __FILE__, __LINE__, "self=%p\r\n", self);
	
	if (!self)		//если не передано указателя возвращаем так же пустой указатель
	{
		return NULL;
	}
	
	tlong sepi = tkvl_fsepi(self);
	
	//*** возврат текущего значения
	tdeb_fdeb3("tkvl_deb", __FILE__, __LINE__, "sepi=%i\r\n\t\t str_len=%i\r\n", sepi, tstr_flen(self->sep));
	if (sepi>=tstr_flen(self->sep))		//если индекс текущего разделителя больше или равен
	{									//длине строки разделителей то это последний уровень
										//возвращаем значение val текущего Kvl
		tdeb_fdeb3("tkvl_deb", __FILE__, __LINE__, "self->val->str.val=%s\r\n", self->val->str);
		return self->val;				//возвращаем наверх строку текущего kvl
	}
	//*** если текущего разделителя нет то возвращаем текущее строковое значение
	
	//*** перебираем дочерние элементы собирая их строковое значение
	//иначе перебираем свои элементы и запрашиваем fstr у них
	tlist_eachp list_each= tlist_each_fcre(NULL, self->list);
	
	//строка текущего kvl
	tstrp kvl_str=NULL;
	
	//текущий соединитель
	tstrp sep = NULL;// tstr_fcre_char(NULL, tstr_fchar(self->sep, sepi));	
	
	//*** перебираем дочерние элементы
	while(tlist_each_finc(&list_each)->listi)
	{		
		//соединаем kvl_str каждого элемента через текущий разделитель
		tstr_fjoin_3(	&kvl_str,							//помещаем резальтат сюда
						kvl_str,							//первая строка соединения все предыдущие элементы
						sep,								//текущий соединитель
						tkvl_fstr(list_each->listi->data)	//kvl строка следующиего элемента
					);
		if (!sep)
		{
			sep = tstr_fcre_char(NULL, tstr_fchar(self->sep, sepi));
		}
		tdeb_fdeb3("tkvl_deb", __FILE__, __LINE__, "kvl_str=%s\r\n", kvl_str->str);
	}
	//*** перебираем дочерние элементы собирая их строковое значение
	
	tdeb_fdeb3("tkvl_deb", __FILE__, __LINE__, "kvl_str=%s\r\n", kvl_str->str);
	
	return kvl_str;
}

tlistp tkvl_fall_val(tkvlp self)			//возвращает список всех строковых разделенных ключей/значений
{
	tlistp list= tlist_fcre(NULL);
	
	tdeb_fdeb3("tkvl_deb", __FILE__, __LINE__, "self=%p\t kvl_list->count=%i\r\n", self, *list->count);
	
	tkvl_fall_val_2(self, &list);
	
	return list;
}

tkvlp tkvl_fall_val_2(tkvlp self, tlistpp kvl_list)
{
	tdeb_fdeb3("tkvl_deb", __FILE__, __LINE__, "self=%p\t kvl_list->count=%i\r\n", self, *(*kvl_list)->count);
	
	//***проверка входных данных
	if (!self)		//нет указателя не с чем работать
	{
		return NULL;
	}
	if (!kvl_list)
	{
		return NULL;
	}
	if (!*kvl_list)
	{
		tdeb_fdeb3("tkvl_deb", __FILE__, __LINE__, "self=%p\t kvl_list->count=%i\r\n", self, *(*kvl_list)->count);
		tlist_fcre(kvl_list);
	}
	//***проверка входных данных
	
	tlong sepi = tkvl_fsepi(self);
	
	//*** возврат текущего значения
	tdeb_fdeb3("tkvl_deb", __FILE__, __LINE__, "sepi=%i\r\n\t\t str_len=%i\r\n", sepi, tstr_flen(self->sep));
	tdeb_fdeb3("tkvl_deb", __FILE__, __LINE__, "self=%p\t kvl_list->count=%i\r\n", self, *(*kvl_list)->count);
	if (sepi>=tstr_flen(self->sep))		//если индекс текущего разделителя больше или равен
	{									//длине строки разделителей то это последний уровень
										//возвращаем значение val текущего Kvl
		tdeb_fdeb3("tkvl_deb", __FILE__, __LINE__, "self->val->str.val=%s\r\n", self->val->str);
		tdeb_fdeb3("tkvl_deb", __FILE__, __LINE__, "*kvl_list=%i\r\n", *(*(tlistpp)kvl_list)->count);
		tlist_fadd_data(kvl_list, self->val);
		tdeb_fdeb3("tkvl_deb", __FILE__, __LINE__, "*kvl_list=%i\r\n", *(*(tlistpp)kvl_list)->count);
		return self;				//возвращаем наверх строку текущего kvl
	}
	//*** если текущего разделителя нет то возвращаем текущее строковое значение
	
	//*** перебираем дочерние элементы собирая их строковое значение
	//иначе перебираем свои элементы и запрашиваем fstr у них
	tlist_eachp list_each= tlist_each_fcre(NULL, self->list);
	
	//строка текущего kvl
	tstrp kvl_str=NULL;
	
	//текущий соединитель
	tstrp sep = NULL;// tstr_fcre_char(NULL, tstr_fchar(self->sep, sepi));	
	
	//*** перебираем дочерние элементы
	while(tlist_each_finc(&list_each)->listi)
	{	
		/*	
		//соединаем kvl_str каждого элемента через текущий разделитель
		tstr_fjoin_3(	&kvl_str,							//помещаем резальтат сюда
						kvl_str,							//первая строка соединения все предыдущие элементы
						sep,								//текущий соединитель
						tkvl_fstr_2(list_each->listi->data)	//kvl строка следующиего элемента
					);
		*/
		//tlist_fadd_data(kvl_list, list_each->listi->data);
		
		tdeb_fdeb3("tkvl_deb", __FILE__, __LINE__, "self=%p\t kvl_list->count=%i\r\n", self, *(*kvl_list)->count);
		tdeb_fdeb3("tkvl_deb", __FILE__, __LINE__, "list_each->listi=%p\r\n", list_each->listi);
		tkvl_fall_val_2(list_each->listi->data, kvl_list);
		/*
		if (!sep)
		{
			sep = tstr_fcre_char(NULL, tstr_fchar(self->sep, sepi));
		}
		* */
		tdeb_fdeb3("tkvl_deb", __FILE__, __LINE__, "*kvl_list=%i\r\n", *(*(tlistpp)kvl_list)->count);
		//tdeb_fdeb3("tkvl_deb", __FILE__, __LINE__, "kvl_str=%s\r\n", kvl_str->str);
	}
	//*** перебираем дочерние элементы собирая их строковое значение
	
	//tdeb_fdeb3("tkvl_deb", __FILE__, __LINE__, "kvl_str=%s\r\n", kvl_str->str);
	
}

tlistp tkvl_fflat(tkvlp self, tchar sep)	//возвращает спискок kvl уровня sep
{
	tdeb_fdeb3("tkvl_deb", __FILE__, __LINE__, "self=%p\t kvl_list->count=%i\r\n", self);
	
	//***проверка входных данных
	if (!self)		//нет указателя не с чем работать
	{
		return NULL;
	}
	//***проверка входных данных
	
	tlistp kvl_list=tlist_fcre(NULL); 
	
	
}



