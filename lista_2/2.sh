#!/bin/sh
# do zadania uzywam programu neomutt

addresses_file='adresy.txt'
content_file='tresc.txt'
attachment_files='spec*.pdf'

while read -r address; do
	cat $content_file | neomutt -s "oferta" $line -a $attachment_files
done < $addresses_file

