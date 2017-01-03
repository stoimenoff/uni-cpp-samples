#!/bin/bash
make graph clean
./graph 2> test.dot
dot test.dot -Tpdf > test.pdf
