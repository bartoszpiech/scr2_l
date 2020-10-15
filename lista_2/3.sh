#!/bin/sh
if [ "$#" -ne 3 ]; then
	echo "podaj 3 argumenty"
	exit 1
fi
find . -iname "*"$1"*" -mtime -"$2"d -exec tar -rvf "$3".tar {} \;
