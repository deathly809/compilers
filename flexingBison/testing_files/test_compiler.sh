#!/bin/bash

EMU=../../../emulator/emu

for F in *.go;
do
	echo $F
	echo "-------------------------------------"
	OUT=${F}.out
	../../bin/main $F > ${OUT}
	echo 10 5 | timeout -s 9 -k 2 2 ${EMU} ${OUT} 
	if [[ $? != 0 ]]; then
		exit 1
	fi
	rm -f ${OUT}
	echo
done

