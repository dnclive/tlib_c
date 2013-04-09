#makefile for tcontext

lib_dir=/usr/lib/

include_dir=/usr/include/

all: tcontext_deb
	-@echo модуль libtcontext.so собран
	
tcontext_deb: tcontext_deb.o libtcontext.so
	gcc -o tcontext_deb tcontext_deb.o -lm -L. -ltcontext -ltdeb -ltstr -Wl,-rpath,.

tcontext_deb.o: tcontext_deb.c
	gcc -c tcontext_deb.c

#tcontext lib
tcontext.o: tcontext.c tcontext.h
	gcc -c tcontext.c

libtcontext.so: tcontext.o
	gcc -shared -o libtcontext.so tcontext.o

#установка
install: libtcontext.so tcontext.h
	#-mkdir $(lib_dir)
	#-mkdir $(include_dir)
	cp libtcontext.so $(lib_dir)
	#cp libtcontext.so /usr/lib/
	cp tcontext.h $(include_dir)
	#cp tcontext.h /usr/include/
	
	
#удаление
unintall:
	rm $(lib_dir)/libtcontext.so
	rm $(include_dir)/tcontext.h


clean:
	rm -f *.o *.a *.so
