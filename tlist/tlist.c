/*
 * tlist.c
 */

#include "tlist.h"


tlist *tlist_finit()								//инициализация
{
	
	
}

tlist *tlist_fcre(tlist **selfp)						//выделение памяти под данные библиотеки
{
	//tstr *self=NULL;							//указатель на обрабатываемый объект	
	
	tdeb_fdeb("tlist_deb", "selfp=%p\r\n", selfp);
	
	tlist *self=tcre_ftptr(selfp, tcre_mptr_cnt(tlist,1));		//выделение указателей для tlisti
	
	tdeb_fdeb3("tlist_deb", __FILE__, __LINE__, "list=%p\r\n", self);
	
	//printf("%s:%i:", __FILE__,__LINE__);	//вывод номера строки
	tdeb_fdeb3("tlist_deb", __FILE__, __LINE__, "selfp=%p\r\n", selfp);
	
	//=*selfp;								//для локальной работы
	//printf("%s:%i:", __FILE__,__LINE__);	//вывод номера строки
	tcre_fref(&(self->self), self);					//ссылка на себя
	
	tdeb_fdeb3("tlist_deb", __FILE__, __LINE__, "list=%p\r\n", self);
	
	//tcre_fref(&self->count, tcre_ftlong(NULL, 1));	//создаем счетчик элементов
	tcre_ftlong_val(&self->count, 0);
	//self->count=0;
	
	tdeb_fdeb3("tlist_deb", __FILE__, __LINE__, "list=%p\r\n", self);
	
	//printf("%s:%i:", __FILE__,__LINE__);	//вывод номера строки
	//tcre_ftptr(&self, tcre_mptr_cnt(tstr,1)); 	//выделение множества указателей
	//self->self=self;							//ссылка на себя
	
	return self;
}

tlist *tlist_fadd_item(tlist **selfp, tlisti *item)
{
	
	//return NULL;
	tdeb_fdeb3("tlist_deb", __FILE__, __LINE__, "tlist_fadd\r\nselfp=%p\r\n", selfp);
	
	//return NULL;

	tlist *self=NULL;
	if (selfp) 
	{
		self=*selfp;		//если указатель на себя дейвствительный то работаем
	}
	if (!selfp)
	{
		self=tlist_fcre(selfp);	//если нет то создаем новый список... и работаем
	}
	
	tdeb_fdeb3("tlist_deb", __FILE__, __LINE__, "self=%p\r\n", self);
	
	tdeb_fdeb3("tlist_deb", __FILE__, __LINE__, "self->count=%i\r\n", *self->count);
	
	(*self->count)++;			//увеличиваем счетчик количества
	
	if (self->lastblock)		//если есть последний элемент
	{
		tcre_fref(&self->lastblock->nextblock,item);	//то цепляем как следующий элемент к этому элементу
		tcre_fref(&item->prevblock,self->lastblock);	//а в новом блоке указатель на предыдущий 
														//на текущий последний блок
		tcre_funref(&self->lastblock);					//отсоединяем текущий последний блок
		tcre_fref(&self->lastblock, item);				//присоединяем новый последний
		
		return self;		//на этом все мы вставили новый элемент в список возвращаем его
	}
	tdeb_fdeb("tlist_deb", __FILE__, __LINE__, "selfp=%p\r\n", selfp);
	if (!self->firstblock)
	{
		tcre_fref(&self->firstblock, item);				//присоединяем новый последний
	}
	
	if (!self->lastblock)
	{
		tcre_fref(&self->lastblock, item);				//присоединяем новый последний
	}
	
	return self;
}

tlist *tlist_fadd_data(tlist **selfp, tptr data)
{
	tlist_fadd_item(selfp, tlisti_fcre(NULL, data));
}

tlisti *tlist_fitem_by_i(tlist **selfp, long index)		//возвращает элемент по индексу
{
	tdeb_fdeb3("tlist_deb", __FILE__, __LINE__, "tlist_fitem_by_i\r\nselfp=%p\r\n", selfp);
	
	if (!selfp) return NULL;		//если нет указателя негде искать
	
	tlist *self=*selfp;				//для локальной работы
	
	if (!self->firstblock) return NULL;	//если нет первого блока список пуст нечего искать
	
	if (index>(*self->count))	return NULL;	//если запрошенный индекс превышает размер списка возвращать нечего
	
	if (index==0)	return self->firstblock;	//если запрошен первый элемент возвращаем
	
	if (index==(*self->count)-1)	return self->lastblock;	//если запрошен последний элемент возвращаем
	
	
	//иначе идем в цикл... перебираем элементы
	long i=0;
	
	tlisti *listi=self->firstblock;	//берем первый блок
	
	while(i++<index)	//так как 0 мы уже возвращали то сразу переходим к первому
	{
		listi=listi->nextblock;
	}
	
	return listi;		//возвращаем запрошенный элемент
	
}

tlist *tlist_fremove(tlist **selfp, tlisti *listi)
{
	if (!selfp) return NULL;		//если нет указателя
	
	if (!listi) return *selfp;		//если не указан удаляемый элемет нечего делать
	
	tlist *self=*selfp;				//для локальной работы
	
	
}

tlist *tlist_fdrop(tlistp *selfp)							//удаляет список selfp освобождая элементы
{
	//принцип удаления списка
	//необходимо отсоединить каждый элемент списка от списка и от ссылок между элементами
	//если при этом на список не сохранится внешних ссылок... элементы будут автоматически удалены...
	if (!selfp) return NULL;		//если нет указателя
	
	tlist *self=*selfp;				//для локальной работы
	
	
	//так как библиотека системная мы берем ссылку на первый блок в обход счетчика
	//затем отсоединяем сслыку на первый блок списка
	//даже если элемент 1 в списке на него сохранится ссылка на последний блок списка
	//и он не будет удален после отссоединения ссылки на первый блок
	tlistip listi=self->firstblock;	//берем первый блок
	//отсоединяем ссылку на первый блок из списка
	tcre_funref(&self->firstblock);
	
	while (listi->nextblock)		//пока существует следующий блок наш не последний
	{
		//отсоединяем ссылку на текущий блок из следующего
		tcre_funref(&listi->nextblock->prevblock);
	}
	
	//отсоединяем ссылку на последний блок списка  по идее он последний
	tcre_funref(&self->lastblock);
	
	//и в итоге отсоединяем внешнюю ссылку на сам список
	tcre_funref(selfp);
	
}

