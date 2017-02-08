#!/bin/bash
if [ $1 ]
then
	BIN=$1
else
	echo "No binary file!"
	exit 1
fi

./$BIN 2> test.dot
dot test.dot -Tpdf > test.pdf
