#makefile for tbit

lib_dir=/usr/lib/

include_dir=/usr/include/

all: tbit_deb
	-@echo модуль libtbit.so собран
	
tbit_deb: tbit_deb.o libtbit.so
	gcc -o tbit_deb tbit_deb.o -lm -L. -ltbit -ltdeb -ltbit -ltcre -ltmem -Wl,-rpath,.

tbit_deb.o: tbit_deb.c
	gcc -c tbit_deb.c

#tbit lib
tbit.o: tbit.c tbit.h
	gcc -c tbit.c

libtbit.so: tbit.o
	gcc -shared -o libtbit.so tbit.o

#установка
install: libtbit.so tbit.h
	#-mkdir $(lib_dir)
	#-mkdir $(include_dir)
	cp libtbit.so $(lib_dir)
	#cp libtbit.so /usr/lib/
	cp tbit.h $(include_dir)
	#cp tbit.h /usr/include/
	
	
#удаление
unintall:
	rm $(lib_dir)/libtbit.so
	rm $(include_dir)/tbit.h


clean:
	rm -f *.o *.a *.so
