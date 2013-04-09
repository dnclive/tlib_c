#makefile for tcre

lib_dir=/usr/lib/

include_dir=/usr/include/

all: tcre_deb
	-@echo модуль libtcre.so собран
	
tcre_deb: tcre_deb.o libtcre.so
	gcc -o tcre_deb tcre_deb.o -lm -L. -ltmem -ltcre -ltdeb -ltbit -Wl,-rpath,.

tcre_deb.o: tcre_deb.c
	gcc -c tcre_deb.c

#tcre lib
tcre.o: tcre.c
	gcc -c tcre.c

libtcre.so: tcre.o
	gcc -shared -o libtcre.so tcre.o

#установка
install: libtcre.so tcre.h
	#-mkdir $(lib_dir)
	#-mkdir $(include_dir)
	cp libtcre.so $(lib_dir)
	#cp libtcre.so /usr/lib/
	cp tcre.h $(include_dir)
	#cp tcre.h /usr/include/
	
	
#удаление
unintall:
	rm $(lib_dir)/libtcre.so
	rm $(include_dir)/tcre.h


clean:
	rm -f *.o *.a *.so
