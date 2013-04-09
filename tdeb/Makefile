#makefile for tdeb

lib_dir=/usr/lib/

include_dir=/usr/include/

all: tdeb_deb
	-@echo модуль libtdeb.so собран
	
tdeb_deb: tdeb_deb.o libtdeb.so
	gcc -o tdeb_deb tdeb_deb.o -lm -L. -ltdeb -Wl,-rpath,.

tdeb_deb.o: tdeb_deb.c
	gcc -c tdeb_deb.c

#tdeb lib
tdeb.o: tdeb.c tdeb.h
	gcc -c tdeb.c

libtdeb.so: tdeb.o
	gcc -shared -o libtdeb.so tdeb.o

#установка
install: libtdeb.so tdeb.h
	#-mkdir $(lib_dir)
	#-mkdir $(include_dir)
	cp libtdeb.so $(lib_dir)
	#cp libtdeb.so /usr/lib/
	cp tdeb.h $(include_dir)
	#cp tdeb.h /usr/include/
	
	
#удаление
unintall:
	rm $(lib_dir)/libtdeb.so
	rm $(include_dir)/tdeb.h


clean:
	rm -f *.o *.a *.so
