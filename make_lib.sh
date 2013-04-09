#!/bin/bash

#dnclive(c)2011
#dnclive@gmail.com

#скрипт создания библиотеки на си
#параметры 
#	[название библиотеки]
#суть:
#	дублируется директория tlib переименовывая все вхождения (включая название папки в [название библиотеки])

#переменные
v_base_dir=.

v_base_lib_name=tlib
v_base_lib_dir=$PWD/${v_base_lib_name}

v_new_lib_name=$1
v_new_lib_dir=$PWD/${v_new_lib_name}

#если директория с именем библиотеки уже существует то прекращаем работу скрипта
#ничего перезаписано не будет!!!
if [ -e ${v_new_lib_dir} ]
then
	echo "Директория для библиотеки ${v_new_lib_name} уже существует ${v_new_lib_dir}!
Не выполнено ни каких действий!!!"
	exit
fi

#дублируем директорию библиотеки
cp -R ./${v_base_lib_name} ${v_new_lib_dir}

#заменяем в именах файлов библиотеки все вхождения BASE_LIB_NAME на NEW_LIB_NAME
for f in ${v_new_lib_dir}/*;
do
	if [ -f "$f" ] 
	then
		#v_full_file_name=${f}
		
		#заменяем в тексте файлов библиотеки все вхождения BASE_LIB_NAME на NEW_LIB_NAME
		v_sed_script="s/${v_base_lib_name}/${v_new_lib_name}/g"
		sed -i ${v_sed_script} ${f}
		
		#echo ${f} ${v_base_lib_name} ${v_new_lib_name}
		#echo ${f/$v_base_lib_name/$v_new_lib_name} 
		v_new_f=${f//$v_base_lib_name/$v_new_lib_name} 		#новое имя файла
		if  [ ${v_new_f} != ${f} ] 
		then
			mv -n ${f} ${v_new_f}
		fi
	fi
done



echo "Библиотека ${v_new_lib_name} успешно создана"
