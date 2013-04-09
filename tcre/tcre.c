/*
 * tcre.c
 */

#include "tcre.h"


tcre *tcre_finit()								//инициализация
{

}

tcre *tcre_fcre()								//выделение памяти под данные библиотеки
{
	
}

tptr *tcre_ftptr(void **selfp, long count)
{
	//if (!selfp) return NULL;		//если не передан инициализируемый узказатель то возвращаем null
	
	if (selfp&&*selfp)	//если указатель действительный, то пробуем отсоединить его от текущего значения
	{
		tcre_funref(selfp);
	}
	
	return tmem_falloc_ref(selfp, sizeof(void *)*count, 1);	//выделяем требуемую память
	
	return NULL;
}

tcre *tcre_ftnum(tpp selfp, long count)
{
	//if (!self) return NULL;		//если не передан инициализируемый узказатель то возвращаем null
	
	return tmem_falloc_ref(selfp, sizeof(tnum)*count, 0);	//выделяем требуемую память
	
	return NULL;
}

tcre *tcre_ftnum_val(tpp selfp, tnum num_val)
{
	//if (!self) return NULL;		//если не передан инициализируемый узказатель то возвращаем null
	
	tnump self=tmem_falloc_ref(selfp, sizeof(tnum), 0);	//выделяем требуемую память
	
	*self=num_val;
	
	return self;
}

tlong *tcre_ftlong(tpp selfp, long count)
{
	//if (!self) return NULL;		//если не передан инициализируемый узказатель то возвращаем null
	
	return tmem_falloc_ref(selfp, sizeof(tlong)*count, 0);	//выделяем требуемую память
	
	return NULL;
}

tlong *tcre_ftlong_val(tpp selfp, tlong long_val)
{
	//if (!self) return NULL;		//если не передан инициализируемый узказатель то возвращаем null
	
	tlong *self=tmem_falloc_ref(selfp, sizeof(tlong), 0);	//выделяем требуемую память

	*self=long_val;
	
	return self;
}

tchar *tcre_ftchar(void **self, long count)
{
	//if (!self) return NULL;		//если не передан инициализируемый узказатель то возвращаем null
	
	return tmem_falloc_ref(self, sizeof(tchar)*count, 0);	//выделяем требуемую память
	
	return NULL;
}

tchar *tcre_ftchar_val(tp *selfp, tchar char_val)
{
	tdeb_fdeb3("tcre_deb", __FILE__, __LINE__, "selfp=%p\r\n", selfp);
	//if (!self) return NULL;		//если не передан инициализируемый узказатель то возвращаем null
	
	tchar *self=tmem_falloc_ref(selfp, sizeof(tchar), 0);	//выделяем требуемую память
	
	tdeb_fdeb3("tcre_deb", __FILE__, __LINE__, "self=%p\r\n", self);
	
	*self=char_val;
	
	return self;
}

tp tcre_fref(void **selfp, void *ref)
{
	if (!selfp)			//если указатель не действительный то некуда передавать ссылку
	{
		return ref;
		//tcre_funref(selfp);
	}
	
	if (*selfp)			//если указатель действительный, то пробуем отсоединить его от текущего значения
	{
		tcre_funref(selfp);
	}
	
	if (ref)			//если действителен присоединяемый указатель по присоединяем
	{
		tmem_fref(ref, selfp);	//присоединяем к новому значению
	}
	return ref;
}

tcre *tcre_funref(tptr **selfp)
{
	if (!selfp) return NULL;		//если не передан инициализируемый узказатель то возвращаем null
	//tptr self=*selfp;
	//tmem_funref(&(((tcre *)self)->self));
	tmem_funref(selfp);
}

tcre *tcre_fdrop(tpp selfp)			//попытка удаления блока
{
	if (!selfp) return NULL;		//если не передан инициализируемый узказатель то возвращаем null
	//tptr self=*selfp;
	//tmem_funref(&(((tcre *)self)->self));
	tmem_fdrop(selfp);
}

tcre *tcre_fdrop_all()				//отчистка от мусора
{
	tmem_fdrop_all();
}

tcre *tcre_fmem_stat()				//статистика памяти
{
	tmem_fstatistic();
}
