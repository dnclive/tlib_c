//      tmem_deb.c
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


#include <stdio.h>
#include <string.h>

#include <tdeb.h>

#include <tlist.h>

#include "tmem.h"

int main(int argc, char **argv)
{
	tdeb_finit("tmem_deb");
	
	//*** умный unref
	
	tlistp list___=tlist_fcre(NULL);
	
	tmem_fdump();
	
	tlistp list___2=NULL;
	
	tmem_fref(list___, &list___2);
	
	tmem_fstatistic();
	
	tmem_funref(&list___2);
	tmem_fdrop(&list___);
	//tmem_fref(NULL, &list___);
	
	
	
	tmem_fdump();
	
	tmem_fstatistic();
	
	//tmem_funref(&list___);
	
	return 0;
	
	
	//***ссылки на себя!
	
	tchar * chp=malloc(167*sizeof(char));
	
	tdeb_fdeb3("tmem_deb", __FILE__, __LINE__, "chp=%p\r\nchp+=%p\r\nchp+10=%p\r\n", chp, chp++, chp+93);
	
	//return ;
	
	struct {tptr *self; tnum *num} *obj3=NULL;
	
	obj3=tmem_falloc_ref(NULL, sizeof(struct {tptr * self; tnum *num}), 1);
	
	tmem_fdump();
	
	tmem_funref(&obj3);
	
	tmem_falloc_ref(NULL, sizeof(struct {tptr * self; tnum *num}), 1);
	
	
	
	tmem_fdump();
	
	tmem_fstatistic();
	
	//tmem_ffree_all();
	tmem_fdrop_all();
	//tmem_fdrop_all();
	
	tmem_fstatistic();
	
	return;
	
	
	//не работает unref!!!
	tlist * list=tlist_fcre(NULL);
	//tstr* str=tstr_fcre(NULL, "234234"); 
	
	tmem_fdump();
	
	tdeb_fdeb3("tmem_deb", __FILE__, __LINE__, "list=%p\r\n", list);
	
	tcre_funref(&list);
	tmem_funref(&list);
	
	tdeb_fdeb3("tmem_deb", __FILE__, __LINE__, "list=%p\r\n", list);
	
	tmem_fdump();
	
	return;
	
	
	//***ссылки на себя!
	
	struct {tptr *self; tnum *num} *obj=NULL;
	
	obj=tmem_falloc_ref(NULL, sizeof(struct {tptr * self; tnum *num}), 1);
	
	//tmem_fdump();
	
	tdeb_fdeb3("tmem_deb", __FILE__, __LINE__, "obj=%p\r\n", obj);
	
	tmem_fref(obj, &obj->self);
	
	tdeb_fdeb3("tmem_deb", __FILE__, __LINE__, "obj=%p\r\n obj->self=%p\r\n", obj, obj->self);
	
	//tmem_fdump();
	
	tmem_funref(&(obj->self));
	
	tdeb_fdeb3("tmem_deb", __FILE__, __LINE__, "obj=%p\r\n obj->self=%p\r\n", obj, obj->self);
	
	tdeb_fdeb3("tmem_deb", __FILE__, __LINE__, "obj=%p\r\n", obj);
	
	tmem_fdump();
	
	tmem_funref(&obj);
	
	tmem_ffree_all();
	
	tmem_fdump();
	
	return;
	
	
	//инициализация менеджера с размером выделяемых по умолчанию блоков 1 байт
	tmemblock *memblock=tmem_finit(1);		//возвращается ссылка на первый блок
	
	//инициализация менеджера с размером выделяемых по умолчанию блоков 4096 байт
	tmemblock *memblock1=tmem_finit(4096);	//возвращается ссылка на первый блок
	
	//выделение блока размером 10 байт
	void * mem1=tmem_falloc(10); //mem1 указывает на выделенный блок размером 10 байт
	strcpy(mem1,"1234567890");	 //копируем 10 символов по указанному
	
	printf ("mem1_%s\r\n%p\r\n", mem1, mem1); //выводим скопированную строку
	
	//освобождение выделенного блока
	tmem_fdump();			//дамп до высвобождения
	
	//tmem_ffree(mem1);		//освобождаем первый блок
	
	tmem_ffree_all();		//удаление всего
	
	tmem_fdump();			//дамп после освобождения 1 блока
	
	
	
	//**** выделение работа и освобождение блоков *****
	
	//выделение блока размером 10 байт
	mem1=tmem_falloc(10); //mem1 указывает на выделенный блок размером 10 байт
	
	//выделение блока размером 405 байт
	void *mem2=tmem_falloc(405); //mem1 указывает на выделенный блок размером 10 байт
	
	strcpy(mem1,"1234567890");	 //копируем 10 символов по указанному
	strcpy(mem2,"1234567890sdfjwoeifjoiasjdgofiajdsgojwoiejfgoasjdgoaisjd");
	
	printf ("mem1_%s\r\n%p\r\n", mem1, mem1); //выводим скопированную строку
	printf ("mem2_%s\r\n%p\r\n", mem2, mem2); //выводим скопированную строку
	
	//освобождение выделенного блока
	tmem_fdump();			//дамп до высвобождения
	
	tmem_ffree(mem2);		//освобождаем первый блок
	
	tmem_fdump();			//дамп после освобождения 1 блока
	
	tmem_ffree(mem1);		//освобождаем второй блок
	
	tmem_fdump();			//дамп после освобождения 2 блока
	
	
	//****новая система выделения памяти +автоматическое освобождение +подсчет ссылок
	
	tdeb_fdeb("tmem_deb", "***тестируем новую систему выделения памяти***\r\n");
	
	void *pblock=NULL;
	tmem_falloc_ref(&pblock, sizeof(void *)*3, 1);
	
	//создание данных и передача ссылки в pblock
	void *iblock=NULL;
	tmem_falloc_ref(&iblock, sizeof(int)*1, 0);
	tmem_fref(iblock, &pblock);
	
	tdeb_fdeb("tmem_deb", "iblock=%p\r\n", &pblock);
	
	int *pblock1=((int *)pblock)+1;
	//pblock1++;
	tdeb_fdeb("tmem_deb", "pblock1=%p\r\n", pblock1);
	tdeb_fdeb("tmem_deb", "pblock1=%p\r\n", &pblock1);
	tdeb_fdeb("tmem_deb", "pblock1=%p\r\n", pblock);
	//еще один более короткий вариант
	tmem_fref(tmem_falloc_int(NULL, 1), &pblock1);
	
	tdeb_fdeb("tmem_deb", "iblock=%p\r\n", &pblock);
	
	tmem_fdump();
	
	tmem_funref(&pblock);
	//tdeb_fdeb("tmem_deb", "зblock=%p\r\n", pblock);
	//tmem_ffree(pblock);		//освобождаем блок
	
	//tmem_ffree(iblock);
	
	tmem_ffree_all();
	
	tmem_fdump();
	
	//тестирование ссылки на ссылку
	tdeb_fdeb("tmem_deb", "***тестирование ссылки на ссылку***\r\n");
	
	
	
	struct {  struct { char *pc } *p2c } *pchar=NULL;
	
	tmem_falloc_ref(&pchar, sizeof(void *), 1);
	tmem_falloc_ref(&pchar->p2c, sizeof(void *), 1);
	tmem_falloc_ref(&pchar->p2c->pc, sizeof(char)*10, 0);
	//tmem_fref(tmem_falloc_ref(NULL, sizeof(char)*10, 0), &pchar->p);
	
	//char *charp=*(pchar->p);
	tmem_fdump();
	tdeb_fdeb("tmem_deb", "*pchar->p2c=%p pchar->p2c->pc=%p\r\n", pchar->p2c, pchar->p2c->pc);
	
	strncpy(pchar->p2c->pc, "hello world", 10);
	
	tdeb_fdeb("tmem_deb", "pchar->p=%s\r\n", pchar->p2c->pc);
	
	tmem_funref(&pchar);
	
	return 0;
	
	//memblock= (tmemblock*)(mem1-sizeof(tmemblock));
	
	//printf("memblock=%p\r\n selfblock=%p\r\n usemem=%i\r\n memsize=%i\r\n freememsize=%i\r\n", 
	//	memblock, memblock->selfblock, memblock->usemem, memblock->memsize, memblock->freemem);
	
	void *mem=tmem_falloc(sizeof(char)*20);
	
	strcpy(mem,"12345678901234567890");
	
	printf ("mem_%s\r\n%p\r\n", mem, mem);
	printf ("%s\r\n", mem1);
	
	//printf("\r\n\r\n\r\n\r\n");
	//printf("memblock=%p\r\n selfblock=%p\r\n usemem=%i\r\n memsize=%i\r\n freememsize=%i\r\n", 
	//	memblock, memblock->selfblock, memblock->usemem, memblock->memsize, memblock->freemem);
	//printf("memblock=%p\r\n selfblock=%p\r\n usemem=%i\r\n memsize=%i\r\n freememsize=%i\r\n", 
	//	memblock->nextblock, memblock->nextblock->selfblock, memblock->nextblock->usemem, memblock->nextblock->memsize, memblock->nextblock->freemem);
	
	//tmem_ffree(mem);
	//printf("\r\n\r\n\r\n\r\n");
	//printf("memblock=%p\r\n selfblock=%p\r\n usemem=%i\r\n memsize=%i\r\n freememsize=%i\r\n", 
	//	memblock, memblock->selfblock, memblock->usemem, memblock->memsize, memblock->freemem);
	
	//tmem_ffree(mem1);
	
	//tmem_ffree(mem);
	
	tmem_fdump();			//дамп до высвобождения
	
	tmem_ffree(mem1);		//освобождаем первый блок
	
	tmem_fdump();			//дамп после освобождения 1 блока
	
	tmem_ffree(mem);		//освобождаем второй
	
	tmem_fdump();			//дамп после освобождения 2 блока
	
	//free(memblock);
	
	//printf("memblock=%p\r\n selfblock=%p\r\n usemem=%i\r\n memsize=%i\r\n freememsize=%i\r\n", 
	//	memblock, memblock->selfblock, memblock->usemem, memblock->memsize, memblock->freemem);
	
	
	//printf("memblock=%p\r\n selfblock=%p\r\n usemem=%i\r\n memsize=%i\r\n freememsize=%i\r\n", 
	//	memblock->nextblock, memblock->nextblock->selfblock, memblock->nextblock->usemem, memblock->nextblock->memsize, memblock->nextblock->freemem);
	//printf("тестируем новую систему выделения памяти\r\n");
	
	
	
	
	return 0;
}

