#!/bin/sh

## Varaibles used during build and tests ##
BINARY=polynom

## Copy all stuff together into test folder ##
echo "############################################"
echo "This script tests the program polynom"
echo "############################################"
echo ""
echo "creating test resource structure ..."
if [ ! -d "polynom_tests" ];
then
	mkdir polynom_tests
	echo "creating directory 'polynom_tests'"
else
	rm -rf polynom_tests
	echo "cleaning directory 'polynom_tests'"
fi 
cd polynom_tests
echo "in directory $(pwd)"
echo "copying header, source and make files"
cp ../polynom.c .
cp ../polynom.h .
cp ../common.h .
cp ../makefile .

## Compile source via make ##
echo "invoking make targets 'clean' 'depend' '$BINARY'\n\n"
make clean depend $BINARY

## Test ##
echo "-------------------------------------------"
echo "Tests are included in polynom.c"
echo "-------------------------------------------"
echo "./$BINARY"
./$BINARY 
echo "\n"
echo "cleanup test"

cd ..
rm -rf polynom_tests
echo "cleanup complete"