#makefile for tdata

lib_dir=/usr/lib/

include_dir=/usr/include/

all: tdata_deb
	-@echo модуль libtdata.so собран
	
tdata_deb: tdata_deb.o libtdata.so
	gcc -o tdata_deb tdata_deb.o -lm -L. -ltdata -ltdeb -Wl,-rpath,.

tdata_deb.o: tdata_deb.c
	gcc -c tdata_deb.c

#tdata lib
tdata.o: tdata.c
	gcc -c tdata.c

libtdata.so: tdata.o
	gcc -shared -o libtdata.so tdata.o

#установка
install: libtdata.so tdata.h
	#-mkdir $(lib_dir)
	#-mkdir $(include_dir)
	cp libtdata.so $(lib_dir)
	#cp libtdata.so /usr/lib/
	cp tdata.h $(include_dir)
	#cp tdata.h /usr/include/
	
	
#удаление
unintall:
	rm $(lib_dir)/libtdata.so
	rm $(include_dir)/tdata.h


clean:
	rm -f *.o *.a *.so
