#!/bin/bash

EMU=../../emulator/emu

for F in *.go;
do
	echo $F
	OUT=${F}.out
	../compiler $F > ${OUT}
	timeout -s 9 -k 2 2 ${EMU} ${OUT} 
	if [[ $? != 0 ]]; then
		exit 1
	fi
	rm -f ${OUT}
done

