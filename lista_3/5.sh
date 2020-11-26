#!/bin/sh

trap "echo sighup" 1
trap "echo sigint" 2
trap "echo sigquit" 3
trap "echo sigill" 4
trap "echo sigtrap" 5


while true; do
    echo "siema"
    sleep 2
done
