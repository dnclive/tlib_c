/*
 * tlist_each.c
 */

#include "tlist_each.h"


tlist_each *tlist_each_finit()								//инициализация
{

}

tlist_each *tlist_each_fcre(tlist_each **selfp, tlist *list)								//выделение памяти под данные библиотеки
{
	tdeb_fdeb3("tlist_each_deb", __FILE__, __LINE__, "selfp=%p\r\n", selfp);
	//создание
	tlist_each *self=tcre_ftptr(selfp, tcre_mptr_cnt(tlist_each,1));		//выделение указателей для tlisti
	
	if (!list)			//нет списка нечего перебирать
	{
		return NULL;
	}
	
	//printf("%s:%i:", __FILE__,__LINE__);	//вывод номера строки
	//tdeb_fdeb("tlist_each_deb", __FILE__, __LINE__, "selfp=%p\r\n", selfp);
	
	//=*selfp;								//для локальной работы
	//printf("%s:%i:", __FILE__,__LINE__);	//вывод номера строки
	tcre_fref(&self->self, self);					//ссылка на себя
	tcre_fref(&self->i, tcre_ftnum(NULL, 1));		//создаем индекс текущего элемента
	tcre_fref(&self->count, tcre_ftnum(NULL, 1));	//создаем счетчик количества элементов
	
	//return self;
	
	//инициализация
	self->i->ival=-1;					//устанавливаем начальный индекс 1 элемента
	self->count->ival=*list->count;		//количество элементов списка
	tcre_fref(&self->list, list);		//устанавливаем указатель на перебираемый список  
	//return self;
	//printf("list=%p  %i", self->list, self->i->ival);
	tdeb_fdeb3("tlist_each_deb", __FILE__, __LINE__, "list=%p\r\n", self->list);
	
	//было решено не брать первый элемент при инициализации для логичности работы
	//с конструкциями вида
	//while(tlist_each_finc(list_each))
	//{
	//	
	//}
	//tcre_fref(&self->listi, tlist_fitem_by_i(&self->list, self->i->ival));	//текущий элемент
	//return self;
	//printf("%s:%i:", __FILE__,__LINE__);	//вывод номера строки
	//tcre_ftptr(&self, tcre_mptr_cnt(tstr,1)); 	//выделение множества указателей
	//self->self=self;							//ссылка на себя
	
	return self;
}


tlist_each *tlist_each_finc(tlist_each **selfp)
{
	tdeb_fdeb3("tlist_each_deb", __FILE__, __LINE__, "selfp=%p\r\n", *selfp);
	if (!selfp) return NULL;				//если нет указателя выходим
	
	tlist_eachp self=*selfp;				//для локальной работы
	
	if (++(self->i->ival)<self->count->ival)	//инкрементируем текущий индекс
	{
		//printf("tlist_each_deb i=%i\tcount=%i\r\n", self->i->ival, self->count->ival);
		tdeb_fdeb3("tlist_each_deb", __FILE__, __LINE__, "self->listi=%p\r\n", self->listi);
		tdeb_fdeb3("tlist_each_deb", __FILE__, __LINE__, "self->i->ival=%i\r\n", self->i->ival);
		tdeb_fdeb3("tlist_each_deb", __FILE__, __LINE__, "count->ival=%i\r\n", self->count->ival);
		//***введено авто! отсоединение***tcre_funref(&self->item);	//отсоединяемся от текущего элемента
		tcre_fref(&self->listi, tlist_fitem_by_i(&self->list, self->i->ival));	//текущий элемент
		return self;
	}
	tcre_fref(&self->listi, NULL);
	//printf("tlist_each_deb self->listi=%p\r\n", self->listi);
	tdeb_fdeb3("tlist_each_deb", __FILE__, __LINE__, "self->listi=%p\r\n", self->listi);
	tdeb_fdeb3("tlist_each_deb", __FILE__, __LINE__, "i=%i\r\n", self->i->ival);
	tdeb_fdeb3("tlist_each_deb", __FILE__, __LINE__, "each_count=%i\r\n", self->count->ival);
	tdeb_fdeb3("tlist_each_deb", __FILE__, __LINE__, "list->count=%i\r\n", *self->list->count);
	
	return self;
}

