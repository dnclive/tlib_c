#makefile for tnewlib

lib_dir=/usr/lib/

include_dir=/usr/include/

all: tnewlib_deb
	-@echo модуль libtnewlib.so собран
	
tnewlib_deb: tnewlib_deb.o libtnewlib.so
	gcc -o tnewlib_deb tnewlib_deb.o -lm -L. -ltnewlib -Wl,-rpath,.

tnewlib_deb.o: tnewlib_deb.c
	gcc -c tnewlib_deb.c

#tnewlib lib
tnewlib.o: tnewlib.c
	gcc -c tnewlib.c

libtnewlib.so: tnewlib.o
	gcc -shared -o libtnewlib.so tnewlib.o

#установка
install: libtnewlib.so tnewlib.h
	#-mkdir $(lib_dir)
	#-mkdir $(include_dir)
	cp libtnewlib.so $(lib_dir)
	#cp libtnewlib.so /usr/lib/
	cp tnewlib.h $(include_dir)
	#cp tnewlib.h /usr/include/
	
	
#удаление
unintall:
	rm $(lib_dir)/libtnewlib.so
	rm $(include_dir)/tnewlib.h


clean:
	rm -f *.o *.a *.so
