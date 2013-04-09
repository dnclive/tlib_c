#makefile for tkvl

lib_dir=/usr/lib/

include_dir=/usr/include/

all: tkvl_deb
	-@echo модуль libtkvl.so собран
	
tkvl_deb: tkvl_deb.o libtkvl.so
	gcc -o tkvl_deb tkvl_deb.o -lm -L. -ltkvl -ltdeb -ltcontext -ltcre -ltmem -ltstr -ltlist -ltlisti -ltlist_each -ltbit -ltstr_each -Wl,-rpath,.

tkvl_deb.o: tkvl_deb.c
	gcc -c tkvl_deb.c

#tkvl lib
tkvl.o: tkvl.c tkvl.h
	gcc -c tkvl.c

libtkvl.so: tkvl.o
	gcc -shared -o libtkvl.so tkvl.o

#установка
install: libtkvl.so tkvl.h
	#-mkdir $(lib_dir)
	#-mkdir $(include_dir)
	cp libtkvl.so $(lib_dir)
	#cp libtkvl.so /usr/lib/
	cp tkvl.h $(include_dir)
	#cp tkvl.h /usr/include/
	
	
#удаление
unintall:
	rm $(lib_dir)/libtkvl.so
	rm $(include_dir)/tkvl.h


clean:
	rm -f *.o *.a *.so
