#!/bin/sh

## Varaibles used during build and tests ##
BINARY=weight

## Copy all stuff together into test folder ##
echo "############################################"
echo "This script tests the program weight"
echo "############################################"
echo ""
echo "creating test resource structure ..."
if [ ! -d "weight_tests" ];
then
	mkdir weight_tests
	echo "creating directory 'weight_tests'"
else
	rm -rf weight_tests
	echo "cleaning directory 'weight_tests'"
fi 
cd weight_tests
echo "in directory $(pwd)"
echo "copying header, source and make files"
cp ../weight.c .
cp ../weight.h .
cp ../common.h .
cp ../makefile .

## Compile source via make ##
echo "invoking make targets 'clean' 'depend' '$BINARY'\n\n"
make clean depend $BINARY

## Test Invalid arguments ##
echo "-------------------------------------------"
echo "Test with invalid arguments"
echo "-------------------------------------------"
echo "Case 1: ./$BINARY [no argument]"
./$BINARY 
echo "\n"

echo "Case 2: ./$BINARY 1 2.0 [too many argument]"
./$BINARY 1 2.0
echo "\n"

echo "Case 3: ./$BINARY a [argumetn not valid double]"
./$BINARY a
echo "\n"

echo "Case 4: ./$BINARY 1.a [argumetn not valid double]"
./$BINARY 1.a
echo "\n"

echo "Case 5:  ./$BINARY 1,2 [argumetn not valid double]"
./$BINARY 1,2
echo "\n"

echo "Case 7: ./$BINARY -1 [out of range]"
./$BINARY -1
echo "\n"

echo "Case 6: ./$BINARY 9 [out of range]"
./$BINARY 9
echo "\n"

echo "Case 7: ./$BINARY 500 [out of range]"
./$BINARY 500
echo "\n"

## Test valid arguments ##
echo "-------------------------------------------"
echo "Test with valid arguments"
echo "-------------------------------------------"
echo "Case 1: ./$BINARY 20 [Exact as bar weight]"
./$BINARY 20
echo "\n"

echo "Case 2: ./$BINARY 21 [found solution]"
./$BINARY 21
echo "\n"

echo "Case 3: ./$BINARY 251 [found solution]"
./$BINARY 251
echo "\n"

echo "Case 4: ./$BINARY 61 [found solution]"
./$BINARY 61
echo "\n"

echo "Case 5: ./$BINARY 158.5 [found solution]"
./$BINARY 158.5
echo "\n"

echo "Case 6: ./$BINARY 36 [found solution]"
./$BINARY 36
echo "\n"

echo "Case 7: ./$BINARY 72.5 [found solution]"
./$BINARY 72.5
echo "\n"

echo "Case 8: ./$BINARY 33.3 [no solution]"
./$BINARY 33.3
echo "\n"

echo "Case 9: ./$BINARY 30.75 [no solution]"
./$BINARY 30.75
echo "\n"

echo "Case 10: ./$BINARY 120.80 [no solution]"
./$BINARY 120.80
echo "\n"

## Cleanup created test resources ##
echo "cleanup test"
cd ..
rm -rf weight_tests
echo "cleanup complete"

