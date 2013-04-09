#makefile for tlist_each

lib_dir=/usr/lib/

include_dir=/usr/include/

all: tlist_each_deb
	-@echo модуль libtlist_each.so собран
	
tlist_each_deb: tlist_each_deb.o libtlist_each.so
	gcc -o tlist_each_deb tlist_each_deb.o -lm -L. -ltlist_each -ltdeb -ltcre -ltlist -ltlisti -ltmem -ltstr -ltbit -ltstr_each -Wl,-rpath,.

tlist_each_deb.o: tlist_each_deb.c
	gcc -c tlist_each_deb.c

#tlist_each lib
tlist_each.o: tlist_each.c tlist_each.h
	gcc -c tlist_each.c

libtlist_each.so: tlist_each.o
	gcc -shared -o libtlist_each.so tlist_each.o

#установка
install: libtlist_each.so tlist_each.h
	#-mkdir $(lib_dir)
	#-mkdir $(include_dir)
	cp libtlist_each.so $(lib_dir)
	#cp libtlist_each.so /usr/lib/
	cp tlist_each.h $(include_dir)
	#cp tlist_each.h /usr/include/
	
	
#удаление
unintall:
	rm $(lib_dir)/libtlist_each.so
	rm $(include_dir)/tlist_each.h


clean:
	rm -f *.o *.a *.so
