#!/bin/bash

CMP=../../compiler

for F in *.go;
do
	echo $F
	echo "-------------------------------------"
	${CMP} $F
	echo
done

