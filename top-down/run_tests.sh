#!/bin/bash

make nuke

(
	cd test
	make
	if [[ $? != 0 ]];
	then
		echo "make failed"
		exit 1
	fi
	./tests
	if [[ $? != 0 ]];
	then
		echo "tests did not pass"
		exit 1
	fi
)

(
	cd testingFiles
	./test_compiler.sh
)
