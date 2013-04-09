#makefile for tlib

lib_dir=/usr/lib/

include_dir=/usr/include/

all: tlib_deb
	-@echo модуль libtlib.so собран
	
tlib_deb: tlib_deb.o libtlib.so
	gcc -o tlib_deb tlib_deb.o -lm -L. -ltlib -ltdeb -Wl,-rpath,.

tlib_deb.o: tlib_deb.c
	gcc -c tlib_deb.c

#tlib lib
tlib.o: tlib.c
	gcc -c tlib.c

libtlib.so: tlib.o
	gcc -shared -o libtlib.so tlib.o

#установка
install: libtlib.so tlib.h
	#-mkdir $(lib_dir)
	#-mkdir $(include_dir)
	cp libtlib.so $(lib_dir)
	#cp libtlib.so /usr/lib/
	cp tlib.h $(include_dir)
	#cp tlib.h /usr/include/
	
	
#удаление
unintall:
	rm $(lib_dir)/libtlib.so
	rm $(include_dir)/tlib.h


clean:
	rm -f *.o *.a *.so
