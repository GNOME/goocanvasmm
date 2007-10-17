#! /bin/bash

for file in $@ ; do
	cp $file temp_file
	cat copyright.txt temp_file > $file
done


