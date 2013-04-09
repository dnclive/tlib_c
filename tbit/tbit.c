/*
 * tbit.c
 */

#include "tbit.h"


tbit *tbit_finit()								//инициализация
{

}

tbit *tbit_fcre()								//выделение памяти под данные библиотеки
{
	
}


tcharp tbit_fi2bit(long val)
{
	tlong val_size=sizeof(val);
	unsigned long bit=2147483648;
	tcharp bit_str=tcre_ftchar(NULL,  32);
	printf("123123123\r\n");
	int i=0;
	while(bit>0) 
	{ //
		printf("%d", bit&val&&1 ); // печатаем нужный разряд.
		if (bit&val) bit_str[i]='1'; else bit_str[i]='0';
		//=bit&val&&1+48;
		bit=bit>>1;
		i++;
		//printf("%d\r\n", k);
		//k=k>>1;//сдвигаем k поразрядно вправо на 1.Что есть деление на 2
	};
	printf("\r\n");
	return bit_str;
}

tcharp tbit_fbyte2bit(tcharp bytep, tulong count)
{
	//tlong val_size=sizeof(val);
	
	tcharp bit_str=tcre_ftchar(NULL,  8*count+count+1);
	//printf("123123123\r\n");
	tcharp bytei=bytep;
	
	int j=0;
	while(j<count)
	{
		int i=0;
		tchar bit=128;
		bit_str[j*8]=' ';
		while(bit>0) 
		{
			tdeb_fdeb3("tbit_deb", __FILE__, __LINE__, "bit=%d\r\n", bit&(*bytei)&&1);
			//printf("bit=%d\r\n", bit&(*bytei)&&1 ); // печатаем нужный разряд.
			if (bit&(*bytei)) bit_str[j*8+i]='1'; else bit_str[j*8+i]='0';
			//=bit&val&&1+48;
			bit=bit>>1;
			i++;
			//printf("%d\r\n", k);
			//k=k>>1;//сдвигаем k поразрядно вправо на 1.Что есть деление на 2
		}
		bytei++;
		j++;
		tdeb_fdeb3("tbit_deb", __FILE__, __LINE__, "%d\r\n", bit&*bytei&&1);
		//printf("%d", bit&*bytei&&1 ); // печатаем нужный разряд.
		
	}
	tdeb_fdeb3("tbit_deb", __FILE__, __LINE__, "%s\r\n", bit_str);
	//printf("%s\r\n", bit_str);
	return bit_str;
}

tcharp tbit_fbit(tchar byte, tulong biti)
{
	
	int i=0;
	tchar bit=128;
	
	tdeb_fdeb3("tbit_deb", __FILE__, __LINE__, "bit=%d\r\n", byte&(bit>>biti)&&1);
	//printf("bit=%d\r\n", byte&(bit>>biti)&&1);
	
	return byte&bit>>biti&&1;
	
}

tulong tbit_fbit_ulong_set(tulong ulong_val, tulong bit_i, tulong bit_val)
{
	tdeb_fdeb3("tbit_deb", __FILE__, __LINE__, "bit_n=%i\tval=%i\r\n", bit_i, ulong_val);
	

	//накладываемая битовая маска
	tulong bit_mask=1;		//00000000 00000000 00000000 00000001
	
	if (bit_val)
	{
		//сдвигаем маску на bit_i, складываем с искомым значением
		//0001<<1=0010
		//0100|0010=0110
		return ulong_val|bit_mask<<bit_i;
	}
	else
	{
		//сдвигаем маску на bit_i, инвертируем и умножаем на искомое значение
		//0001<<1=0010
		//~0010=1101
		//0110&1101=0100
		return ulong_val&~bit_mask<<bit_i;
	}
	
}

tulong tbit_fbit_ulong(tulong ulong_val, tulong bit_i)
{
	tdeb_fdeb3("tbit_deb", __FILE__, __LINE__, "bit_n=%i\tval=%i\r\n", bit_i, ulong_val);
	//накладываемая битовая маска
	tulong bit_mask=1;		//00000000 00000000 00000000 00000001
	
	//сдвигаем маску на bit_i, умножаем на искомое значение 
	//и возвращаем результат сравнения с 1
	//00000001<<3=00001000  -  побитовое смешение на три разряда
	//00101000&00000100=00000000&&1=0
	//00101000&00001000=00001000&&1=1
	return ulong_val&bit_mask<<bit_i&&1;
}
