#makefile for tmem

lib_dir=/usr/lib/uti/

include_dir=/usr/include/uti/

all: tmem_deb
	-@echo модуль libtmem.so собран
	
tmem_deb: tmem_deb.o libtmem.so
	gcc -o tmem_deb tmem_deb.o -lm -L. -ltmem -ltdeb -ltcre -ltlist -ltlisti -ltbit -Wl,-rpath,.

tmem_deb.o: tmem_deb.c
	gcc -c tmem_deb.c

#mem lib
tmem.o: tmem.c tmem.h
	gcc -c tmem.c

libtmem.so: tmem.o
	gcc -shared -o libtmem.so tmem.o

#установка
install: libtmem.so tmem.h tmem.c
	-mkdir $(lib_dir)
	-mkdir $(include_dir)
	cp libtmem.so $(lib_dir)
	cp libtmem.so /usr/lib/
	cp tmem.h $(include_dir)
	cp tmem.h /usr/include/
	
	
#удаление
unintall:
	rm $(lib_dir)/libtmem.so
	rm $(include_dir)/tmem.h


clean:
	rm -f *.o *.a *.so
