#makefile for tinctor

lib_dir=/usr/lib/

include_dir=/usr/include/

all: tinctor_deb
	-@echo модуль libtinctor.so собран
	
tinctor_deb: tinctor_deb.o libtinctor.so
	gcc -o tinctor_deb tinctor_deb.o -lm -L. -ltinctor -ltkvl -ltdeb -ltcontext -ltcre -ltmem -ltstr -ltlist -ltlisti -ltlist_each -ltbit -ltstr_each -Wl,-rpath,.

tinctor_deb.o: tinctor_deb.c
	gcc -c tinctor_deb.c

#tinctor lib
tinctor.o: tinctor.c
	gcc -c tinctor.c

libtinctor.so: tinctor.o
	gcc -shared -o libtinctor.so tinctor.o

#установка
install: libtinctor.so tinctor.h
	#-mkdir $(lib_dir)
	#-mkdir $(include_dir)
	cp libtinctor.so $(lib_dir)
	#cp libtinctor.so /usr/lib/
	cp tinctor.h $(include_dir)
	#cp tinctor.h /usr/include/
	
	
#удаление
unintall:
	rm $(lib_dir)/libtinctor.so
	rm $(include_dir)/tinctor.h


clean:
	rm -f *.o *.a *.so
