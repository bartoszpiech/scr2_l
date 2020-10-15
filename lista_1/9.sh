#!/bin/sh

#set -x
touch plik.txt plik2.txt
mkdir folder
mv folder folder2
chmod 777 folder2
ln -s plik.txt folder2
rm plik2.txt

