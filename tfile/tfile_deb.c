//      tfile_deb.c
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

#include <tdeb.h>

#include "tfile.h"

int main(int argc, char **argv)
{
	printf ("tfile_deb_start\r\n");
	
	tdeb_finit("tfile_deb");
	
	tfile * tfile_data= tfile_finit();
	
	printf ("tfile_deb_end\r\n");
	
	FILE *f;

	f=fopen("1.txt","r");

	FILE *f2=NULL;
	f2=fopen("2.txt","w+");

	tcharp word=tcre_ftchar(NULL, 100);

	tlistp word_list=tlist_fcre(NULL);

	char ch="\0";
	tlong j=0;
	tlong i=0;
	while((ch=getc(f))!=EOF)
	{
		i++;
		//if (i>30) break;
		//fgetc(f);
		if (ch==' '||ch=='.'||ch==','||ch=='!'||ch=='?'||ch=='\r'||ch=='\n'
			||ch=='\''||ch=='"'||ch=='-'||ch=='%'||ch=='$'||ch=='#'
			||ch=='('||ch==')'||ch==';'||ch==':'||ch=='['||ch==']')
		{
			if (*word!='\0')
			{
				word[j]='\0';
				//tanatom_deb_fadd_word(word_list, tstr_fcre_copy(NULL, word));
				fputs(word, f2);
				fputs("\r\n", f2);
				printf ("word=%s\ti=%i\r\n", word, i);
				//tdeb_fdeb3("tanatom_deb", __FILE__, __LINE__, "word=%s\tj=%i\tch=%i\r\n", word, j, ch);
				j=0;
			}
			word[j]='\0';
			continue;
		}
		//tdeb_fdeb3("tanatom_deb", __FILE__, __LINE__, "word=%s\tj=%i\tch=%i\r\n", word, j, ch);
		//if (isupper(ch)) word[j]=_tolower(ch);
		//else 
		word[j]=ch;
		//tolower_l
		j++;
	}
	
	tdeb_fdeb3("tanatom_deb", __FILE__, __LINE__, "word=%i\r\n", *word_list->count);
	
	fclose(f);
	fclose(f2);
	
	return;
	
	f=NULL;
	f=fopen("2.txt","w+");
	
	tdeb_fdeb3("tanatom_deb", __FILE__, __LINE__, "f=%p\r\n", f);
	
	
	
	tlist_eachp each = tlist_each_fcre(NULL, word_list);
	printf ("word=%i\r\n", *word_list->count);
	while(tlist_each_finc(&each)->listi)
	{
		fputs(((tstrp)each->listi->data)->str, f);
		fputs("\r\n", f);
	}
	
	fclose(f);
	
	fgetc(stdin);
	
	return 0;
}


void tanatom_deb_fadd_word(tlistp word_list, tstrp word)
{
	tlist_eachp each = tlist_each_fcre(NULL, word_list);
	
	if (*word_list->count==0)
	{
		tdeb_fdeb3("tanatom_deb", __FILE__, __LINE__, "word=%s\r\n", word);
		tlist_fadd_data(&word_list, word);
		return;
	}
	
	tlong iseq=0;		//слово уже есть
	
	while(tlist_each_finc(&each)->listi&&1==0)
	{
		//tdeb_fdeb3("tanatom_deb", __FILE__, __LINE__, "word=%s\teach_i=%i\teach_count=%i\r\n", word, *each->i, *each->count);
		//tdeb_fdeb3("tanatom_deb", __FILE__, __LINE__, "listi=%p\r\n", each->listi);
		//tdeb_fdeb3("tanatom_deb", __FILE__, __LINE__, "listi->str=%s\r\n", ((tstrp)each->listi->data)->str);
		//tdeb_fdeb3("tanatom_deb", __FILE__, __LINE__, "cmp=%i\r\n", tstr_fcmp(tstr_fcre_copy(NULL, word), (tstrp)each->listi->data));

		
		if (tstr_fcmp(word, (tstrp)each->listi->data))
		{
			//tdeb_fdeb3("tanatom_deb", __FILE__, __LINE__, "listi->str=%s\r\n", ((tstrp)each->listi->data)->str);
			//tdeb_fdeb3("tanatom_deb", __FILE__, __LINE__, "word=%s\r\n", word);

			return;
		}
		
		//if (iseq)
		//{
		//	return;
		//}
	}
	
	tlist_fadd_data(&word_list, word);
	
	return;
	
	
}

