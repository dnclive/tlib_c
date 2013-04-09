/*
 * tlisti.c
 */

#include "tlisti.h"


tlisti *tlisti_finit()								//инициализация
{

}

tlisti *tlisti_fcre(tlisti **selfp, void *data_ptr)	//выделение памяти под данные библиотеки
{
	//if (data_ptr) return NULL;	
	
	
	tlisti *self=tcre_ftptr(selfp, tcre_mptr_cnt(tlisti,1));     //выделение указателей для tlisti
	
	//=*selfp;							//для локальной работы
	
	//tmem_fdump();
	
	//tlisti *listi=tmem_falloc(sizeof(tlisti));		//выделение блока под tlisti
	//self->self=self;								//ссылка на себя
	tcre_fref(&self->self, self);
	//listi->nextblock=NULL;							//следующий блок
	//listi->prevblock=NULL;							//предыдущий блок
	//self->data=data_ptr;								//ссылка на структуру данных
	tdeb_fdeb("tlisti_deb", "self=%p\r\n", self);
	tcre_fref(&(self->data), data_ptr);
	//если передан указатель на указатель на создаваемый объект
	if (selfp) *selfp=self;   //передаем указатель на созданную структуру этому указателю
	
	return self;
}

tlisti *tlisti_ffree(tlisti **selfp)
{
	if (!selfp) return NULL;		//если передан недействительный указатель
	
	tlisti *self=*selfp;
	if (!self) return NULL;			//если указатель недействиетльный освобождать нечего
	
	tdeb_fdeb("tlisti_deb", "self->data=%s\r\n", ((tstr*)self->data)->str);
	//tdeb_fdeb("tlisti_deb", "self->data=%s\r\n", typeof(self->data));
	//tmem_fdump();
	//tmem_fdump();
	//*****данные структуры******
	//mffree((self->data), (self->data));
	//tmem_funref(self);
	//typeof(self->data)_ffree(self->data);		//освобождаем данные элемента списка
	//tmem_ffree(self->sepstr);	//освобождаем память выделенную под строку
	
	//*****себя*****
	//tdeb_fdeb("tlisti_deb", "self=%p\r\n", self);
	
	tmem_ffree(selfp);		//освобождаем память выделенную под собственную структуру
	//убиваем указатель по переданной ссылке
	//*self=NULL;
	
	return NULL;
}



