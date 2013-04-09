#makefile for tstr_each

lib_dir=/usr/lib/

include_dir=/usr/include/

all: tstr_each_deb
	-@echo модуль libtstr_each.so собран
	
tstr_each_deb: tstr_each_deb.o libtstr_each.so
	gcc -o tstr_each_deb tstr_each_deb.o -lm -L. -ltstr_each -ltdeb -ltmem -ltcre -ltbit -ltstr -Wl,-rpath,.

tstr_each_deb.o: tstr_each_deb.c
	gcc -c tstr_each_deb.c

#tstr_each lib
tstr_each.o: tstr_each.c tstr_each.h
	gcc -c tstr_each.c

libtstr_each.so: tstr_each.o
	gcc -shared -o libtstr_each.so tstr_each.o

#установка
install: libtstr_each.so tstr_each.h
	#-mkdir $(lib_dir)
	#-mkdir $(include_dir)
	cp libtstr_each.so $(lib_dir)
	#cp libtstr_each.so /usr/lib/
	cp tstr_each.h $(include_dir)
	#cp tstr_each.h /usr/include/
	
	
#удаление
unintall:
	rm $(lib_dir)/libtstr_each.so
	rm $(include_dir)/tstr_each.h


clean:
	rm -f *.o *.a *.so
