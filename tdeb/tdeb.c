/*
 * tdeb.c
 */

#include "tdeb.h"

char *tdeb_debgroup=NULL;						//текущая отладочная группа

tdeb *tdeb_finit(char *group)					//инициализация
{
	tdeb_debgroup=group;						//текущая группа отладки
}

tdeb *tdeb_fcre()								//выделение памяти под данные библиотеки
{
	
}

int tdeb_fdeb(char *group, char *fmt, ...)
{
	if (tdeb_debgroup) if (strcmp(tdeb_debgroup,group)) return 0;
	
	va_list ap;        /* указывает на очередной безымянный аргумент */ 
    char *p, *sval;
    char chval;
    int ival;
    void *pval;
    double dval;
	
    va_start(ap, fmt); /* устанавливает ap на 1-й безымянный аргумент */ 
    for (p=fmt; *p; p++) {
        if (*p !='%') {
            putchar(*p);
            continue;
        }
        //printf("tdeb_fdeb   %c\r\n", *p);
        switch (*++p) 
        {
			case 'i':
				ival = va_arg(ap, int);
				printf ("%i", ival);
				break;
			case 'd':
				ival = va_arg(ap, int);
				printf ("%d", ival);
				break;
			case 'f':
				dval = va_arg(ap, double);
				printf("%f", dval);
				break;
			case 's':
				for (sval = va_arg(ap, char *); *sval; sval++)
					putchar(*sval);
				break;
			case 'c':
				//for (sval = va_arg(ap, char *); *sval; sval++)
				//	putchar(*sval);
				chval=va_arg(ap, char);
				printf("%c", chval);
				break;
			case 'p':
				pval = va_arg(ap, void *);
				printf ("%p", pval);
				break;
			default:
				putchar(*p);
				break;
        }
    }
    va_end(ap); /* очистка, когда все сделано */
}

int tdeb_fdeb3(char *group, char *file, int line, char *fmt, ...)
{								
	if (tdeb_debgroup) if (strcmp(tdeb_debgroup,group)) return 0;
	
	va_list ap;        /* указывает на очередной безымянный аргумент */ 
    char *p, *sval;
    char chval;
    int ival;
    void *pval;
    double dval;
	
	printf("%s:%i:", file, line);	//вывод файла и номера строки в которых 
									//вызвано отладочное сообщение
	
    va_start(ap, fmt); /* устанавливает ap на 1-й безымянный аргумент */ 
    for (p=fmt; *p; p++) {
        if (*p !='%') {
            putchar(*p);
            continue;
        }
        //printf("tdeb_fdeb   %c\r\n", *p);
        switch (*++p) 
        {
			case 'i':
				ival = va_arg(ap, int);
				printf ("%i", ival);
				break;
			case 'd':
				ival = va_arg(ap, int);
				printf ("%d", ival);
				break;
			case 'f':
				dval = va_arg(ap, double);
				printf("%f", dval);
				break;
			case 's':
				for (sval = va_arg(ap, char *); *sval; sval++)
					putchar(*sval);
				break;
			case 'c':
				//for (sval = va_arg(ap, char *); *sval; sval++)
				//	putchar(*sval);
				chval=va_arg(ap, char);
				printf("%c", chval);
				break;
			case 'p':
				pval = va_arg(ap, void *);
				printf ("%p", pval);
				break;
			default:
				putchar(*p);
				break;
        }
    }
    va_end(ap); /* очистка, когда все сделано */
}

char *tdeb_fdebgroup()
{
	return tdeb_debgroup;
}



