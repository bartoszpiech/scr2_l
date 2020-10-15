#!/bin/sh

day=$(date +%u)
if [ $day -lt 6 ]; then
	echo "dzien roboczy";
else
	echo "weekend";
fi
