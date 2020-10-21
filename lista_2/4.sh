#!/bin/sh

usage() { echo "Uzycie: $0 [-h - pokazanie helpa] [-n <modyfikowane w ciagu ostatnich N dni>] [-m <maska>] [-a <nazwa tara>]" 1>&2; exit 1; }


while getopts ":n:m:a:h" o; do
	case "${o}" in
		n)
			n=${OPTARG}
			;;
		m)
			m=${OPTARG}
			;;
		a)
			a=${OPTARG}
			;;
		h)
			usage
			;;
	esac
done

if [ -z "$n" ]; then
	if [ -z "$ENV_DAYS" ]; then
		echo Modyfikowane w ciagu ostatnich ?? dni:
		read n;
	else
		n=$ENV_DAYS
	fi
fi

if [ -z "$m" ]; then
	if [ -z "$ENV_MASK" ]; then
		echo Maska:
		read m;
	else
		m=$ENV_MASK
	fi
fi

if [ -z "$a" ]; then
	if [ -z "$ENV_TARNAME" ]; then
		echo Nazwa tara:
		read a;
	else
		a=$ENV_TARNAME
	fi
fi

find . -iname "*$m*" -mtime -"$n"d -exec tar -rvf "$a".tar {} \;
