#makefile for tsql

lib_dir=/usr/lib/

include_dir=/usr/include/

all: tsql_deb
	-@echo модуль libtsql.so собран
	
tsql_deb: tsql_deb.o libtsql.so
	gcc -o tsql_deb tsql_deb.o -lm -L. -ltsql -ltdeb -lib_util -lfbclient -Wl,-rpath,.

tsql_deb.o: tsql_deb.c
	gcc -c tsql_deb.c

#tsql lib
tsql.o: tsql.c
	gcc -c tsql.c

libtsql.so: tsql.o
	gcc -shared -o libtsql.so tsql.o

#установка
install: libtsql.so tsql.h
	#-mkdir $(lib_dir)
	#-mkdir $(include_dir)
	cp libtsql.so $(lib_dir)
	#cp libtsql.so /usr/lib/
	cp tsql.h $(include_dir)
	#cp tsql.h /usr/include/
	
	
#удаление
unintall:
	rm $(lib_dir)/libtsql.so
	rm $(include_dir)/tsql.h


clean:
	rm -f *.o *.a *.so
