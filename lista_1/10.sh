#!/bin/sh

#set -x
if [ "$#" -lt 1 ]; then
	echo "Podaj argumenty i sprobuj ponownie"
	exit 1
fi

echo "czy chcesz utworzyc plik/i o podanych nazwach? (t/n)"
read var
if [ $var = "t" ]; then
	for i in "$@"; do
		touch $i;
	done
fi

echo "czy chcesz utworzyc folder/y o podanych nazwach? (t/n)"
read var
if [ $var = "t" ]; then
	for i in "$@"; do
		mkdir $i;
	done
fi

echo "czy chcesz zmienic uprawnienia na (777) dla podanych plikow? (t/n)"
read var
if [ $var = "t" ]; then
	for i in "$@"; do
		chmod 777 $i;
	done
fi

echo "czy chcesz stworzyc symboliczne linki dla podanych plikow w folderze folder? (t/n)"
read var
if [ $var = "t" ]; then
	mkdir folder
	for i in "$@"; do
		ln -s $i folder;
	done
fi

echo "czy chcesz usunac podane pliki? (t/n)"
read var
if [ $var = "t" ]; then
	for i in "$@"; do
		rm $i;
	done
fi

<<COMMENT
set -x
touch plik.txt plik2.txt
mkdir folder
mv folder folder2
chmod 777 folder2
ln -s plik.txt folder2
rm plik2.txt
COMMENT

