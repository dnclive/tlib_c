/*
 * mem.c
 */
#include <stdlib.h>
#include <stdio.h>

#include <tbit.h>

#include "tmem.h"



//менеджер памяти

long init_size_in_byte=tmem_init_size_in_byte_default;	//размер блока при инициализации
tmemblock * memblock=NULL;								//указатель на первый блок памяти
tmemblock * mb2del=NULL;								//указатель на блок для возврата ОС

//статистика
tulong memblock_count=0;			//количество используемых блоков памяти
tulong memblock_all_size=0;			//выделенная память в байтах
tulong memblock_all_size_mb=0;			//выделенная память в байтах
tulong alloc_main_block_count=0;	//количесво запрошенных у ОС блоков
tulong alloc_main_block_size=0;		//суммарная запрошенная у ОС память

tmemblock *tmem_finit(long size_in_byte)				//инициализация выделение пямяти
{
	init_size_in_byte=size_in_byte;						//запоминаем базовый размер блока
	long size=size_in_byte;								//размер блока
	
	memblock=NULL;

	return memblock;
}

tmemblock *_tmem_falloc_mb(tmemblock *mb, long size)	//уровень 1 выделение блока mb размером size
{

	//если передан недействительный указатель то
	//	либо нет еще ни одного блока работа с менеджером только началась
	//	либо дошли до последнего блока (указатель nextblock предылущего null)
	//в обоих случаях создаем новый блок
	if (!mb)
	{
		return _tmem_fmb2use(_tmem_finit_first_mb(_tmem_fspase2newbm(NULL, size)), size);
		//return _tmem_fmemblock(NULL, size);		//запрашиваем новый блок
	}
	//иначе если свободное пространство текущего блока позволяет выделить
	//требуемый объем пробуем задействовать объем текущего блока либо
	//создать в свободном пространстве следующий блок и выделить из него
	if (tmem_ffreemem(mb)>=size)			//если в текущем блоке есть достаточная свободная память
	{
		return _tmem_fgetmb(mb, size);
	}
	//если существует следующий блок переходим к нему (рекурсия)
	if (mb->nextblock)
	{
		return _tmem_falloc_mb(mb->nextblock, size);	//пробуем получить указатель из следующего блока
	}
	
	//если мы дошли сюда значит пересмотрены все блоки
	//память так и не удалось выделить
	//запрашиваем память у системы создаем новый заголовочный блок требуемого или размера по умолчанию
	//(если помещаемся в него) и выделяем память из него
	return _tmem_fgetmb(mb, size);

}

tmemblock *_tmem_fgetmb(tmemblock* mb, long size)		//попытка получения mb или создания в его свободном		
{														//пространстве возвращает свободный блок
	if (!mb) return NULL;
	
	if (mb->usemem)//если текущий блок используется то создаем в его свободном пространстве
	{
		return  _tmem_fmb2use(_tmem_fnewmb(mb, _tmem_fspase2newbm(mb,size)), size);
	}
	if (!mb->usemem)//если текущий блок не используется то возвращаем его
	{
		return _tmem_fmb2use(mb, size);
	}
}

tmemblock *_tmem_finit_first_mb(tmemblock *mb)			//инициализация первого блока если это первый
{														//запрошенный или была освобождена вся память
	mb->selfblock=mb;
	mb->nextblock=NULL;
	mb->usemem=0;
	memblock=mb;
	
	return mb;
}

tmemblock *_tmem_fnewmb(tmemblock *mb, tmemblock *newmb)//инициализация нового блока
{	
	//вставляем созданный блок в цепочку блоков
	newmb->nextblock=mb->nextblock;	//следующий блок для нового равен следующему блоку для родителя
	mb->nextblock=newmb;			//родитель теперь указывает на новый блок
	mb->freemem=0;					//свободная память предыдущего блока равно 0
	newmb->usemem=0;				//размер используемой памяти нового блока равен 0
	newmb->refcount=0;				//счетчик ссылок для нового блока устанавливаем в 0
	newmb->flag=0;					//по умолчанию все флаги сброшены
	newmb->selfblock=newmb;			//указатель на себя включая tmemblock
	
	return newmb;
}

tmemblock *_tmem_fspase2newbm(tmemblock *mb, long size)	//создание нового блока в freemem mb
{														//или запрос у ОС необходимого места
	tmemblock *newmb=NULL;				//новый блок данных
	//long mbfreemem=tmem_ffreemem(mb);
	//printf("_tmem_fspase2newbm\r\nfreemem=%i\r\nsize=%i\r\n", tmem_ffreemem(mb), size);
	if (mb&&tmem_ffreemem(mb)>=size)//если в блоке mb достаточно памяти для выделения требуемого количества
	{
		tdeb_fdeb3("tmem_deb", __FILE__, __LINE__, "mb next block poin=%i\r\n", sizeof(tmemblock)+mb->usemem);
		tdeb_fdeb3("tmem_deb", __FILE__, __LINE__, "mb->selfblock=%p\r\n", mb->selfblock);
		tdeb_fdeb3("tmem_deb", __FILE__, __LINE__, "mb->selfblock+=%p\r\n", (char*)mb->selfblock+sizeof(tmemblock)+mb->usemem);
		newmb=(char*)mb->selfblock+sizeof(tmemblock)+mb->usemem;
		newmb->freemem=mb->freemem-sizeof(tmemblock);
		newmb->memsize=0;
		
		//статистика
		memblock_count++;
		memblock_all_size+=size;
		memblock_all_size_mb+=size+sizeof(tmemblock);
		
		return newmb;
	}
	if (init_size_in_byte>=size+sizeof(tmemblock))	//если размера блока по умолчанию достаточно 
	{
		newmb=(tmemblock*)malloc(init_size_in_byte);
		newmb->freemem=init_size_in_byte-sizeof(tmemblock);
		newmb->memsize=init_size_in_byte;
		
		//статистика
		alloc_main_block_count++;
		alloc_main_block_size+=init_size_in_byte;
		memblock_count++;
		memblock_all_size+=size;
		memblock_all_size_mb+=size+sizeof(tmemblock);
		
		return newmb; //возвращаем блок размером по умолчанию
	}
	newmb=(tmemblock*)malloc(size+sizeof(tmemblock));
	newmb->freemem=size;
	newmb->memsize=size+sizeof(tmemblock);
	
	//статистика
	alloc_main_block_count++;
	alloc_main_block_size+=size+sizeof(tmemblock);
	memblock_count++;
	memblock_all_size+=size;
	memblock_all_size_mb+=size+sizeof(tmemblock);
	
	return newmb;					//иначе возвращаем блок размером size
}

long tmem_ffreemem(tmemblock *mb)						//возвращает размер свободного пространства mb
{
	//если mb действительный указаетль 
	if (mb) return mb->freemem-sizeof(tmemblock);
	return 0;		//иначе возввращаю 0
}

void *tmem_fmem(tmemblock *mb)							//возвращает указатель на начало блока данных mb
{
	//если
	if (mb) return (void *)mb+sizeof(tmemblock);
	return NULL;
}

tmemblock *tmem_fmb(void *self)							//возвращает указатель на блок mb
{
	//если
	if (self) return (tmemblock *)(self-sizeof(tmemblock));
	return NULL;
}

tmemblock *_tmem_fmb2use(tmemblock *mb,long size)		//задействует свободный блок
{
	mb->freemem=mb->freemem-size;
	mb->usemem=size;					//размер используемой памяти нового блока равен 0
	mb->refcount=0;						//счетчик ссылок равен 0
	mb->flag=0;							//Обнуляем флаги
	
	return mb;
}

void *tmem_falloc(int size)								//получение указатель на свободный блок памяти
{
	printf("tmem_falloc\r\nmb=%p\r\nsize=%i\r\n", memblock, size);
	
	//возвращаем указатель на выделенный блок памяти
	return tmem_fmem(_tmem_falloc_mb(memblock, size));
}

void *tmem_falloc_ref(void **selfp, int size, int is_pointer)//получение указатель на свободный блок памяти
{
	//printf("tmem_falloc\r\nmb=%p\r\nsize=%i\r\n", memblock, size);
	//tmemblock *mb=_tmem_falloc_mb(memblock, size);
	//tmem_fdump();
	tmemblock *mb=_tmem_f_mb_type(_tmem_falloc_mb(memblock, size), is_pointer);
	//tmem_fdump();
	//_tmem_f_mb_type(_tmem_fref(mb), is_pointer);
	
	tmem_fnull(mb);		//обнуляем указатели
	
	//printf("tmem_falloc\r\nmb=%p\r\nsize=%i\r\n", memblock, size);
	//если передан указатель на указатель на создаваемый объект
	if (selfp) 
	{
		_tmem_fref(mb);			//инкрементируем счетчик ссылок
		*selfp=tmem_fmem(mb);   //передаем указатель на созданную структуру этому указателю
		
	}
	
	//возвращаем указатель на выделенный блок памяти
	return tmem_fmem(mb);
}

void *tmem_falloc_int(void **selfp, int size)//получение указатель на свободный блок памяти
{
	printf("tmem_falloc_int\r\nmb=%p\r\nsize=%i\r\n", memblock, size);
	//tmemblock *mb=_tmem_falloc_mb(memblock, size);
	//tmem_fdump();
	tmemblock *mb=_tmem_f_mb_type(_tmem_falloc_mb(memblock, size*sizeof(long)), 0);
	//tmem_fdump();
	
	printf("tmem_falloc_int\r\nmb=%p\r\nsize=%i\r\n", memblock, size);
	
	//если передан указатель на указатель на создаваемый объект
	if (selfp)
	{
		_tmem_fref(mb);			//инкрементируем счетчик ссылок
		*selfp=tmem_fmem(mb);   //передаем указатель на созданную структуру этому указателю
	}
	
	//возвращаем указатель на выделенный блок памяти
	return tmem_fmem(mb);
}

tmemblock *tmem_fnull(tmemblock *mb)
{
	int i=0;
	int pcnt=mb->usemem/tmem_pointer_size;
	void **p=tmem_fmem(mb);
	//void *pp=(void *)*p;
	while(i<pcnt)
	{
		*p=NULL;
		p++;
		i++;
	}
	return mb;
}

tmemblock *_tmem_f_mb_type(tmemblock *mb, int is_pointer)//устанавливает флаг типа блока указатель/данные
{
	tdeb_fdeb("tmem_deb", "_tmem_f_mb_type\r\n");
	tdeb_fdeb3("tmem_deb", __FILE__, __LINE__, "tmem_fref flag_0=%i\tis_pointer=%i\r\n", 
						tbit_fbit_ulong_set(mb->flag, 0, is_pointer),is_pointer);
	mb->flag=tbit_fbit_ulong_set(mb->flag, 0, is_pointer);
	//mb->flag=is_pointer;
	return mb;
}

//***управление указателями***

void *tmem_fref(void *self, void **selfp)				//устанавливает selfp на то что указывает self
{														//при этом инкрементируется refcount++
	tdeb_fdeb3("tmem_deb", __FILE__, __LINE__, "tmem_fref\r\n");
	//tmem_fdump();
	
	tdeb_fdeb3("tmem_deb", __FILE__, __LINE__, "tmem_fref self=%p selfp=%\r\n",self);
	
	if (!selfp)		//если указатель не действителен то нечего соединять.....
	{
		return NULL;
	}
	
	
	
	tdeb_fdeb3("tmem_deb", __FILE__, __LINE__, "tmem_fref self->refcount=%i usemem=%i\r\n",tmem_fmb(self)->refcount
															,tmem_fmb(self)->usemem );
	//tdeb_fdeb("tmem_deb", "tmem_fref self=%p *selfp=%p **selfp=%p\r\n",self, *selfp, **selfp);
	
	tdeb_fdeb3("tmem_deb", __FILE__, __LINE__, "tmem_fref selfp=%p self=%p self+usemem=%p\r\n", 
				selfp, self, self+tmem_fmb(self)->usemem);
	
	//ссылки на себя не инкрементируются!!!
	if (selfp&&selfp>=self&&selfp<=self+tmem_fmb(self)->usemem)
	{
		tdeb_fdeb3("tmem_deb", __FILE__, __LINE__, "tmem_fref selfp=%p self=%p\r\n", selfp, self);
		*selfp=self;					//устанавливаем selfp туда же куда и self
		return self;
	}
	if (self) (tmem_fmb(self)->refcount)++;	//инкрементирую счетчик ссылок
	//void ***p1=*selfp;
	//**p1=self;
	//void *
	if (selfp)
	{
		*selfp=self;					//устанавливаем selfp туда же куда и self
		//**selfp=(void*)self;
	}
	tdeb_fdeb3("tmem_deb", __FILE__, __LINE__, "tmem_fref self=%p *selfp=%p **selfp=%p\r\n",self, *selfp, *selfp);
	//*selfp=self;
	tdeb_fdeb3("tmem_deb", __FILE__, __LINE__, "tmem_fref self=%p *selfp=%p **selfp=%p\r\n",self, *selfp, *selfp);
	tdeb_fdeb3("tmem_deb", __FILE__, __LINE__, "tmem_fref self->refcount=%i\r\n",tmem_fmb(self)->refcount);
	//tmem_fdump();
	return self;
}

void *tmem_funref(void **selfp)							//отсоединяет selfp от данных
{														//устанавливает selp в NULL refcount--, возвр NULL
	tdeb_fdeb3("tmem_deb", __FILE__, __LINE__, "_tmem_funref *selfp=%p\r\n selfp=%p\r\n", *selfp, selfp);
	
	if (!*selfp)		//если указатель не действителен то нечего отсоединять.....
	{
		return NULL;
	}
	
	void * self=*selfp;
	
	//ссылки на себя не декрементируются!!!
	if (selfp&&selfp>=*selfp&&selfp<=*selfp+tmem_fmb(*selfp)->usemem)
	{
		tdeb_fdeb3("tmem_deb", __FILE__, __LINE__, "_tmem_funref ссылка на себя %p\r\n",*selfp+tmem_fmb(*selfp)->usemem);
		*selfp=NULL;	 //обNULLяем указатель сюда
		return NULL;
	}
	
	tdeb_fdeb3("tmem_deb", __FILE__, __LINE__, "_tmem_funref *selfp=%p\r\n", *selfp);
	//tdeb_fdeb("tmem_deb", "_tmem_funref *selfp=%p\r\n", *selfp);
	//если передан действительный указатель работаем
	if (selfp&&(*selfp))
	{
		tdeb_fdeb3("tmem_deb", __FILE__, __LINE__, "_tmem_funref *selfp=%p\r\n", *selfp);
		tmemblock *mb=tmem_fmb(*selfp);
		//если этот блок уже обрабатывался то снимаем флаг обработки
		//обнуляем указатель сюда и возвращаемся
		
		if(tbit_fbit_ulong(mb->flag, 1))
		{
			//сбрасываем флаг обработки атома
			mb->flag=tbit_fbit_ulong_set(mb->flag, 1, 0);
			*selfp=NULL;		//обналяем указатель сюда
			return NULL;		//и возвращаемся
		}
		
		//если блок еще не обрабатывался включаем флаг обработки текущего атома
		mb->flag=tbit_fbit_ulong_set(mb->flag, 1, 1);
		
		
		tdeb_fdeb3("tmem_deb", __FILE__, __LINE__, "_tmem_funref 123 mb->refcount=%i\r\n", mb->refcount);
		//tmem_fdump();
		mb->refcount--;
		if (mb->refcount<1)		//если это последняя ссылка на блок
		{
			tdeb_fdeb3("tmem_deb", __FILE__, __LINE__, "_tmem_funref mb->refcount=%i\r\n", mb->refcount);
			tdeb_fdeb3("tmem_deb", __FILE__, __LINE__, "_tmem_funref flag_0=%i\r\n", 
														tbit_fbit_ulong(mb->flag, 0));
			if (tbit_fbit_ulong(mb->flag, 0))
			{
				_tmem_f_free_each_p(mb);		//освобождаем указатели данного блока
				tmem_ffree(*selfp);				//высвобождаем текущий блок
			}
			if (!tbit_fbit_ulong(mb->flag, 0))
			{
				tmem_ffree(*selfp);				//высвобождаем текущий блок
			}
			
		}
		else
		{
			//сбрасываем флаг обработки атома
			mb->flag=tbit_fbit_ulong_set(mb->flag, 1, 0);
		}
		
		*selfp=NULL;						//обналяем указатель сюда
		//tmem_fdump();
		

		
		tdeb_fdeb3("tmem_deb", __FILE__, __LINE__, "_tmem_funref mb->refcount=%i\r\n", mb->refcount);
	}
	
	return NULL;
	
}

void *tmem_fdrop(void **selfp)			//устанавливает selfp в NULL, при этом refcount не 
{										//декрементируется, но если ссылок на блок нет то он удаляется
	tdeb_fdeb3("tmem_deb", __FILE__, __LINE__, "_tmem_fdrop *selfp=%p\r\n selfp=%p\r\n", *selfp, selfp);
	
	if (!*selfp)		//если указатель не действителен то нечего отсоединять.....
	{
		return NULL;
	}
	
	/*
	//ссылки на себя не декрементируются!!!
	if (selfp&&selfp>=*selfp&&selfp<=*selfp+tmem_fmb(*selfp)->usemem)
	{
		tdeb_fdeb("tmem_deb", "_tmem_funref ссылка на себя %p\r\n",*selfp+tmem_fmb(*selfp)->usemem);
		*selfp=NULL;	 //обNULLяем указатель сюда
		return NULL;
	}
	*/
	tdeb_fdeb3("tmem_deb", __FILE__, __LINE__, __FILE__, __LINE__, "_tmem_fdrop *selfp=%p\r\n", *selfp);
	//tdeb_fdeb("tmem_deb", "_tmem_funref *selfp=%p\r\n", *selfp);
	//если передан действительный указатель работаем
	if (selfp&&(*selfp))
	{
		
		tmemblock *mb=tmem_fmb(*selfp);
		
		//если этот блок уже обрабатывался то снимаем флаг обработки
		//обнуляем указатель сюда и возвращаемся
		if(tbit_fbit_ulong(mb->flag, 1))
		{
			//сбрасываем флаг обработки атома
			mb->flag=tbit_fbit_ulong_set(mb->flag, 1, 0);
			//*selfp=NULL;		//обналяем указатель сюда
			return NULL;		//и возвращаемся
		}
		
		//если блок еще не обрабатывался включаем флаг обработки текущего атома
		mb->flag=tbit_fbit_ulong_set(mb->flag, 1, 1);
		
		
		tdeb_fdeb3("tmem_deb", __FILE__, __LINE__, "_tmem_fdrop 123 mb->refcount=%i\r\n", mb->refcount);
		//tmem_fdump();
		//mb->refcount--;
		if (mb->refcount<1)		//если это последняя ссылка на блок
		{
			tdeb_fdeb3("tmem_deb", __FILE__, __LINE__, "_tmem_fdrop mb->refcount=%i\r\n", mb->refcount);
			if (tbit_fbit_ulong(mb->flag, 0))
			{
				_tmem_f_free_each_p(mb);		//освобождаем указатели данного блока
				tmem_ffree(*selfp);				//высвобождаем текущий блок
			}
			if (!tbit_fbit_ulong(mb->flag, 0))
			{
				tmem_ffree(*selfp);				//высвобождаем текущий блок
			}
			
		}
		*selfp=NULL;						//обналяем указатель сюда
		//tmem_fdump();
		
		//сбрасываем флаг обработки атома
		//mb->flag=tbit_fbit_ulong_set(mb->flag, 1, 0);
		
		tdeb_fdeb3("tmem_deb", __FILE__, __LINE__, "_tmem_fdrop mb->refcount=%i\r\n", mb->refcount);
	}
	
	return NULL;
	
}

void *tmem_fdrop_all()					//пробегает по всем блокам и удаляем все на что нет ссылок
{										//своеобразный сборщик мусора
	tdeb_fdeb3( "tmem_deb", __FILE__, __LINE__, "_tmem_fdrop_all *selfp=%p\r\n selfp=%p\r\n");
	
	if (!memblock)		//если указатель не действителен то нет не одного блока
	{
		return NULL;
	}
	
	tmemblock * mb=memblock;
	
	void * mem=tmem_fmem(mb);
	/*
	if (mb) 
	{
		mb=mb->nextblock;
		
		//проверяем первый блок
		if (mb->refcount<1)
		{
			tmem_fdrop(&mem);
		}
	}
	*/
	tdeb_fdeb3( "tmem_deb", __FILE__, __LINE__, "_tmem_fdrop_all mb=%p\r\n", mb);
	
	//проходим по всей цепочке и проверяем каждый блок
	while(mb)
	{
		//указатель на данные блока
		void * mem=tmem_fmem(mb);
		
		tlong refcount=mb->refcount;
		
		//берем следующий блок
		mb=mb->nextblock;
		
		tdeb_fdeb3( "tmem_deb", __FILE__, __LINE__, "_tmem_fdrop_all mb->nextblock=%p\r\n", mb);
		
		//если нет ссылок на блок удаляем его
		if (refcount<1)
		{
			tmem_fdrop(&mem);
		}
		
		tdeb_fdeb3( "tmem_deb", __FILE__, __LINE__, "_tmem_fdrop_all mb=%p\r\n", mb);
		
	}
}

tmemblock *_tmem_f_free_each_p(tmemblock *mb)
{
	tdeb_fdeb3("tmem_deb", __FILE__, __LINE__, "_tmem_f_free_each_p usemem=%i\tpinter_size=%i\r\n", 
													mb->usemem, tmem_pointer_size);
	int i=0;
	int pcnt=mb->usemem/tmem_pointer_size;
	void **p=tmem_fmem(mb);
	//void *pp=(void *)*p;
	while(i<pcnt)
	{
		tdeb_fdeb("tmem_deb", "_tmem_f_free_each_p *p=%p\r\n", *p);
		if (*p) tmem_funref(p);			//если указатели
		p++;
		i++;
	}
	return mb;
}

tmemblock *_tmem_fref(tmemblock *mb)					//инкрементирует счетчик ссылок блока
{
	tdeb_fdeb("tmem_deb", "_tmem_fref mb->refcount=%i\r\n", mb->refcount);
	mb->refcount++;
	return mb;
}

//***освобождение блоков***

int tmem_ffree(void *mem)
{
	tdeb_fdeb("tmem_deb","tmem_ffree\r\nmb=%p\r\nmem=%p\r\n", memblock, mem);
	if (!mem) return 0;			//если передан null то и освобождать нечего
	
	//берем первый блок данных
	tmemblock *mb=memblock;
	tdeb_fdeb("tmem_deb","tmem_fmem=%p\r\nmem=%p\r\n",tmem_fmem(mb), mem);
	if (tmem_fmem(mb)==mem)
	{
				//статистика
		memblock_count--;
		tdeb_fdeb3("tmem_deb", __FILE__, __LINE__, "tmem_ffree_mb usemem=%i\tmemblock_all_size=%i\r\n", 
							mb->usemem, memblock_all_size);
		memblock_all_size-=mb->usemem;						//выделенная память в байтах
		memblock_all_size_mb-=mb->usemem+sizeof(tmemblock);	//выделенная память в байтах
		
		tdeb_fdeb3("tmem_deb", __FILE__, __LINE__, "tmem_ffree_mb usemem=%i\tmemblock_all_size=%i\r\n", 
							mb->usemem, memblock_all_size);
		tdeb_fdeb("tmem_deb","tmem_fmem_это первый блок\r\n");
		//первый блок в любом случае заголовочный
		mb->freemem+=mb->usemem;//освобождаем память блока
		mb->usemem=0;			//память в блоке больше не используется
		//mb->usemem=0;			//обналяем счетчик ссылок
		//удаляем полностью первый заголовочный блок если он единственный
		_tmem_ffreeblock(mb);
		

		
		//возвращаем 0 - успешно
		return 0;
	}

	//перебираем все блоки пока не найдем свой
	return _tmem_ffree_mb(memblock, mem);
	//return mb->memsize+mb->mem-mb->freemem;
}

int _tmem_ffree_mb(tmemblock *mb, void *mem)
{
	tdeb_fdeb("tmem_deb","_tmem_ffree_mb\r\nmb=%p\r\nmem=%p\r\n", mb, mem);
	tdeb_fdeb("tmem_deb","_tmem_fmem_mb=%p\r\nmem=%p\r\n",tmem_fmem(mb->nextblock), mem);
	//если следующий блок 
	if (tmem_fmem(mb->nextblock)==mem)
	{
		//статистика
		memblock_count--;
		tdeb_fdeb3("tmem_deb", __FILE__, __LINE__, "tmem_ffree_mb usemem=%i\tmemblock_all_size=%i\r\n", 
							tmem_fmb(mem)->usemem, memblock_all_size);
		memblock_all_size-=mb->nextblock->usemem;						//выделенная память в байтах
		memblock_all_size_mb-=mb->nextblock->usemem+sizeof(tmemblock);	//выделенная память в байтах
		
		tdeb_fdeb3("tmem_deb", __FILE__, __LINE__, "tmem_ffree_mb usemem=%i\tmemblock_all_size=%i\r\n", 
							tmem_fmb(mem)->usemem, memblock_all_size);
		
		if (mb->nextblock->memsize)			//если следующий блок является заголовочным
		{
			mb->nextblock->freemem+=mb->nextblock->usemem;//освобождаем память блока
			mb->nextblock->usemem=0;					//память в блоке больше не используется
			//слудеющим блоком становится следующий за следующим)
			mb->nextblock=mb->nextblock->nextblock;
			//удаляем следующий блок если он заголовочный и неиспользуется и после него ничего нет
			_tmem_ffreeblock(mb->nextblock);
			
			return 0;
		}
		else //иначе сносим блок
		{
			//свободная память предыдушего блока увеличивается на 
			//имеющуюся+используемую и свободную в удаляемом блоке + размет tmemblock
			mb->freemem+=mb->nextblock->usemem+mb->nextblock->freemem+sizeof(tmemblock);
			mb->nextblock->usemem=0;				//память в следующем блоке больше не используется
			//слудеющим блоком становится следующий за следующим)
			mb->nextblock=mb->nextblock->nextblock;
		}
		
		//удаляем полностью текущий блок если он заголовочный, не используется и после него
		//ничего уже нет
		_tmem_ffreeblock(mb);
		
		//возвращаем 0 - успешно
		return 0;
		
	}
	
	
	return _tmem_ffree_mb(mb->nextblock, mem);
}

int _tmem_ffreeblock(tmemblock *mb)
{
	tdeb_fdeb("tmem_deb","_tmem_ffreeblock mb=%p\r\n", mb);
	if (mb&&mb->memsize)
	{
		
		tdeb_fdeb("tmem_deb","_tmem_ffreeblock usemem=%i  memsize=%i nextblock=%p\r\n", mb->usemem, mb->memsize, mb->nextblock);
		int tf=!mb->nextblock&&mb->usemem==0;
		tdeb_fdeb("tmem_deb","!mb->nextblock&&mb->usemem==0 = %i\r\n",tf); 
		if(!mb->nextblock&&!mb->usemem)
		{
			tdeb_fdeb("tmem_deb","_tmem_ffreeblock mb=%p удален, возвращен ОС\r\n", mb);
			free(mb);
			if (mb==memblock) memblock=NULL;
			
			//статистика
			alloc_main_block_count--;
			alloc_main_block_size-=mb->memsize;
			
			//tdeb_fdeb("tmem_deb","_tmem_ffreeblock mb=%p удален, возвращен ОС\r\n", mb);
		}
	}
}

int tmem_ffree_all()
{
	if (memblock)
	{
		_tmem_ffree_all(memblock);
		memblock=NULL;
	}
}

int _tmem_ffree_all(tmemblock *mb)
{
	//tmemblock *nextblock=NULL;
	if (mb)		//если текущий действительный	
	{	
		if (mb->memsize)	//если текущий заголовочный
		{	
			if (mb2del)		//если есть блок для удаления
			{
				free(mb2del);	//удаляем его
			}
			mb2del=mb;			//запоминаем текущий как следующий блок для удаления текущий
		}
		_tmem_ffree_all(mb->nextblock);
		return 0;				//выход
	}
	return 0;					//если следующего нет то все удалено, выходим
}

//***отладочные***

int tmem_fdump()
{
	printf("************************dump of tmem****************************\r\n");
	if (memblock) 
	{
		_tmem_fdump(memblock);
	}
	else 
	{
		printf("mem is free\r\n");
	}
	printf("**********************end dump of tmem**************************\r\n");
}

int _tmem_fdump(tmemblock *mb)
{
	if(mb->memsize)
	{
		printf ("****os_mem_block alloc=%i\r\n", mb->memsize);
	}
	printf("%p\r\n", mb->selfblock);
	printf("\tmemsize\t\t%i\r\n", mb->memsize);
	printf("\tusemem\t\t%i\r\n", mb->usemem);
	printf("\tfreemem\t\t%i\r\n", mb->freemem);
	printf("\trefcount\t\t%i\r\n", mb->refcount);
	printf("\tflag\t\t%i\r\n", mb->flag);
	printf("\tselfblock\t%p\r\n", mb->selfblock);
	printf("\tnextblock\t%p\r\n", mb->nextblock);
	printf("\r\n\tmem\t\t%p\r\n", tmem_fmem(mb));
	//printf("******\r\n");
	_tmem_fdump_d(mb);
	
	if (mb->nextblock) _tmem_fdump(mb->nextblock);
}

_tmem_fdump_d(tmemblock *mb)
{
	printf("\r\n\tDATA\tcont=%i\r\n", mb->usemem/sizeof(void *));
	printf("\r\n\tindex\t\taddress\t\t\tdata\r\n");
	int i=0;
	int pcnt=mb->usemem/tmem_pointer_size;
	void **p=tmem_fmem(mb);
	//void *pp=(void *)*p;
	while(i<pcnt)
	{
		if (p) printf("\t%i\t\t%p\t\t%p\r\n", i, p, *p);
		if (!p) printf("\t%i\t\t%p\t\t%p\r\n", i, p, *p);
		//tmem_funref(p);
		p++;
		i++;
	}
	return mb;
}

int tmem_fstatistic()	//статистика использования памяти
{
	printf ("****statistic of memory use****\r\n");
	//количество выделенных блоков
	printf("\r\n\talloc_main_block_count=%i\r\n", alloc_main_block_count);
	printf("\talloc_main_block_size=%i\r\n\r\n", alloc_main_block_size);
	printf("\tmemblock_count=%i\r\n", memblock_count);
	printf("\tmemblock_all_size=%i\r\n", memblock_all_size);
	printf("\tmemblock_all_size_mb=%i\r\n", memblock_all_size_mb);
	printf("\r\n****statistic of memory use****\r\n");
}
