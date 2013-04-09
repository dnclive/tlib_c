/*
 * tinctor.c
 */

#include "tinctor.h"

tinctorp tinctor_fcre_flex(tinctorpp selfp, tlong lim, tlong val, tfloat sens)	//функция инициализации структуры
{
	/*
	self->lim=lim;
	self->val=val;
	
	//инициализируем вычисление среднего занчения
	med_finit(&self->med, val, sens);
	*/
}

tinctorp tinctor_fcre_strong(tinctorpp selfp, tlong lim, tlong val)	//функция инициализации структуры
{
	tdeb_fdeb3("tinctor_deb", __FILE__, __LINE__, "selfp=%p\r\n", selfp);
	
	tinctorp self=tcre_ftptr(selfp, tcre_mptr_cnt(tinctor,1));	//выделение указателей для tanjector
	
	tcre_ftlong_val(&self->lim, lim);						// предел 
	tcre_ftlong_val(&self->val, val);						// текущее значение
	
	//self->lim=lim;
	//self->val=val;
	
	//инициализируем вычисление среднего занчения
	//med_finit(&self->med, val, sens);
	
	tdeb_fdeb3("tinctor_deb", __FILE__, __LINE__, "self=%p\r\n", self);
	
	//возвращаем результат
	return self;
}

tinctorp tinctor_finc(tinctorpp selfp)				//функция инкрементирующая текущее значение
{
	
	//***проверка входных данных
	if (!selfp)		//нет указателя не с чем работать
	{
		return NULL;
	}
	if (!*selfp)
	{
		return NULL;
	}
	tinctorp self=*selfp;
	//***проверка входных данных
	
	(*self->val)++;
	/*
	if (*self->val>=*self->lim)
	{
		//(*self->femit)(self);
	}
	*/
	return self;
}

tinctorp tinctor_fincn(tinctorpp selfp, tlong n)		//функция инкрементирующая текущее значение на n
{
	//***проверка входных данных
	if (!selfp)		//нет указателя не с чем работать
	{
		return NULL;
	}
	if (!*selfp)
	{
		return NULL;
	}
	tinctorp self=*selfp;
	//***проверка входных данных
	
	*self->val+=n;
	/*
	if (self->val>=self->lim)
	{
		//(*self->femit)(self);
	}*/
	return self;
}

tlong tinctor_femit(tinctorpp selfp)				//функция возаврщает 1 если текущее значение первысило предел
{
	//***проверка входных данных
	if (!selfp)		//нет указателя не с чем работать
	{
		return 0;
	}
	if (!*selfp)
	{
		return 0;
	}
	tinctorp self=*selfp;
	//***проверка входных данных
	
	if (*self->val>=*self->lim)
	{
		return 1;
	}
	return 0;
}

tinctorp tinctor_freset(tinctorpp selfp)					//функция сбрасывающая текущее значение в 0
{
	//***проверка входных данных
	if (!selfp)		//нет указателя не с чем работать
	{
		return NULL;
	}
	if (!*selfp)
	{
		return NULL;
	}
	tinctorp self=*selfp;
	//***проверка входных данных
	
	*self->val=0;
	return self;
}

/*
 * формула вычисления очередного среднего
 * мы храним два значения среднее med и количество фиксаций значения и вычисления среднего cmed
 * таким образом новое среднее равно 
 * med=(med*cmed+val)/cmed+1
 */

tinctorp tinctor_ftobestable(tinctorpp selfp)	//функция фиксирующая текущее значение и вычислчющяя среднее
{
	// пока не реализованно
	/*
	med_ffixmed(&self->med, self->val);
	long med_val=med_fval(&self->med);	
	if (med_val>0) self->lim=med_val;
	*/
	//printf("med %f\r\n", self->med.med);
	//printf("med_val %i %i\r\n", self->med.val, self->val, self->lim);			
}

