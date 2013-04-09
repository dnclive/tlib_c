#makefile for tfile

lib_dir=/usr/lib/

include_dir=/usr/include/

all: tfile_deb
	-@echo модуль libtfile.so собран
	
tfile_deb: tfile_deb.o libtfile.so
	gcc -o tfile_deb tfile_deb.o -lm -L. -ltfile -ltanatom -ltkvl -ltdeb -ltcontext -ltcre -ltmem -ltstr -ltlist -ltlisti -ltlist_each -ltinctor -Wl,-rpath,.

tfile_deb.o: tfile_deb.c
	gcc -c tfile_deb.c

#tfile lib
tfile.o: tfile.c
	gcc -c tfile.c

libtfile.so: tfile.o
	gcc -shared -o libtfile.so tfile.o

#установка
install: libtfile.so tfile.h
	#-mkdir $(lib_dir)
	#-mkdir $(include_dir)
	cp libtfile.so $(lib_dir)
	#cp libtfile.so /usr/lib/
	cp tfile.h $(include_dir)
	#cp tfile.h /usr/include/
	
	
#удаление
unintall:
	rm $(lib_dir)/libtfile.so
	rm $(include_dir)/tfile.h


clean:
	rm -f *.o *.a *.so
