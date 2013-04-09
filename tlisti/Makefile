#makefile for tlisti

lib_dir=/usr/lib/

include_dir=/usr/include/

all: tlisti_deb
	-@echo модуль libtlisti.so собран
	
tlisti_deb: tlisti_deb.o libtlisti.so
	gcc -o tlisti_deb tlisti_deb.o -lm -L. -ltlisti -ltdeb -ltmem -ltstr -ltcre -Wl,-rpath,.

tlisti_deb.o: tlisti_deb.c
	gcc -c tlisti_deb.c

#tlisti lib
tlisti.o: tlisti.c tlisti.h
	gcc -c tlisti.c

libtlisti.so: tlisti.o
	gcc -shared -o libtlisti.so tlisti.o

#установка
install: libtlisti.so tlisti.h
	#-mkdir $(lib_dir)
	#-mkdir $(include_dir)
	cp libtlisti.so $(lib_dir)
	#cp libtlisti.so /usr/lib/
	cp tlisti.h $(include_dir)
	#cp tlisti.h /usr/include/
	
	
#удаление
unintall:
	rm $(lib_dir)/libtlisti.so
	rm $(include_dir)/tlisti.h


clean:
	rm -f *.o *.a *.so
