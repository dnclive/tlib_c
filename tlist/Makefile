#makefile for tlist

lib_dir=/usr/lib/

include_dir=/usr/include/

all: tlist_deb
	-@echo модуль libtlist.so собран
	
tlist_deb: tlist_deb.o libtlist.so
	gcc -o tlist_deb tlist_deb.o -lm -L. -ltlist -ltdeb -ltcre -ltlisti -ltmem -ltstr -ltlist_each -Wl,-rpath,.

tlist_deb.o: tlist_deb.c
	gcc -c tlist_deb.c

#tlist lib
tlist.o: tlist.c tlist.h
	gcc -c tlist.c

libtlist.so: tlist.o
	gcc -shared -o libtlist.so tlist.o

#установка
install: libtlist.so tlist.h
	#-mkdir $(lib_dir)
	#-mkdir $(include_dir)
	cp libtlist.so $(lib_dir)
	#cp libtlist.so /usr/lib/
	cp tlist.h $(include_dir)
	#cp tlist.h /usr/include/
	
	
#удаление
unintall:
	rm $(lib_dir)/libtlist.so
	rm $(include_dir)/tlist.h


clean:
	rm -f *.o *.a *.so
