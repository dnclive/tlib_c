#makefile for tstr

lib_dir=/usr/lib/

include_dir=/usr/include/

all: tstr_deb
	-@echo модуль libtstr.so собран
	
tstr_deb: tstr_deb.o libtstr.so
	gcc -o tstr_deb tstr_deb.o -lm -L. -ltstr -ltmem -ltdeb -ltcre -ltbit -Wl,-rpath,.

tstr_deb.o: tstr_deb.c
	gcc -c tstr_deb.c

#tstr lib
tstr.o:  tstr.c tstr.h
	gcc -c tstr.c  -std=c99
	
libtstr.so:  tstr.o
	gcc -shared -o libtstr.so tstr.o

#установка
install: libtstr.so tstr.h
	#-mkdir $(lib_dir)
	#-mkdir $(include_dir)
	cp libtstr.so $(lib_dir)
	cp tstr.h $(include_dir)
	
#удаление
unintall:
	rm $(lib_dir)/libtstr.so
	rm $(include_dir)/tstr.h


clean:
	rm -f *.o *.a *.so
