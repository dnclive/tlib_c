#makefile for tp

lib_dir=/usr/lib/

include_dir=/usr/include/

all: tp_deb
	-@echo модуль libtp.so собран
	
tp_deb: tp_deb.o libtp.so
	gcc -o tp_deb tp_deb.o -lm -L. -ltp -tdeb -Wl,-rpath,.

tp_deb.o: tp_deb.c
	gcc -c tp_deb.c

#tp lib
tp.o: tp.c
	gcc -c tp.c

libtp.so: tp.o
	gcc -shared -o libtp.so tp.o

#установка
install: libtp.so tp.h
	#-mkdir $(lib_dir)
	#-mkdir $(include_dir)
	cp libtp.so $(lib_dir)
	#cp libtp.so /usr/lib/
	cp tp.h $(include_dir)
	#cp tp.h /usr/include/
	
	
#удаление
unintall:
	rm $(lib_dir)/libtp.so
	rm $(include_dir)/tp.h


clean:
	rm -f *.o *.a *.so
