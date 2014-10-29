#!/bin/sh
## Varaibles used during build and tests ##
APPLICATION_TYPE=2
SOURCE_MAIN=../main.c
BINARY_MAIN=bin/main_prime_test.bin
SOURCE_TRIANGLE=../source/triangle.c
SOURCE_PRIME=../source/prime.c
INCLUDE_HEADERS_COMMONS=../../Commons/header
INCLUDE_HEADERS=../header/

echo "############################################################################"
echo "These are the tests for the prime_factorizer"
echo "############################################################################ \n"

## Compile the source file ##
## build triangle source
echo "compiling source file '$SOURCE_MAIN' and dependencies to target $BINARY_MAIN \n"
echo "$ gcc -g -I$INCLUDE_HEADERS_COMMONS -I$INCLUDE_HEADERS $SOURCE_MAIN $SOURCE_TRIANGLE $SOURCE_PRIME -o $BINARY_MAIN -lm\n" 
gcc -g -I$INCLUDE_HEADERS_COMMONS -I$INCLUDE_HEADERS $SOURCE_MAIN $SOURCE_TRIANGLE $SOURCE_PRIME -o $BINARY_MAIN -lm

## Check if file has been compiled
if [ -f "$BINARY_MAIN" ]
then
	echo "source compiled starting tests now ...\n"
else
	echo "compile of $SOURCE_MAIN failed\n"
	exit 1
fi

################################################################
## Test wrong parameter count                                 ##
################################################################
echo "----------------------------------------------------------------------------"
echo "Testing invalid parameter count"
echo "----------------------------------------------------------------------------"
## Case 1
echo "Case 1: no param"
$BINARY_MAIN $APPLICATION_TYPE
echo "\n"

## Case 2
echo "Case 2: 2 param"
$BINARY_MAIN $APPLICATION_TYPE 123 456
echo "\n"

## Case 3
echo "Case 3: 3 param"
$BINARY_MAIN $APPLICATION_TYPE 123 456 789
echo "\n"

################################################################
## Test invalid parameter range                               ##
################################################################
echo "----------------------------------------------------------------------------"
echo "Testing with invalid parameter range  "
echo "----------------------------------------------------------------------------"
## Case 1
echo "Case 1: 0"
$BINARY_MAIN $APPLICATION_TYPE 0
echo "\n"

## Case 2
echo "Case 2: 1"
$BINARY_MAIN $APPLICATION_TYPE 1
echo "\n"

## Case 3
echo "Case 3: 32566 out fo range"
$BINARY_MAIN $APPLICATION_TYPE 32566
echo "\n"

## Case 4
echo "Case 4: -1 "
$BINARY_MAIN $APPLICATION_TYPE -1
echo "\n"

################################################################
## Test invalid parameters                                      ##
################################################################
echo "----------------------------------------------------------------------------"
echo "Testing with character parameter  "
echo "----------------------------------------------------------------------------"
## Case 1
echo "Case 1: abc"
$BINARY_MAIN $APPLICATION_TYPE abc
echo "\n"

## Case 2
echo "Case 2: asdfadsfdf_454544"
$BINARY_MAIN $APPLICATION_TYPE asdfadsfdf_454544
echo "\n"

################################################################
## Test valid parameters                                      ##
################################################################
echo "----------------------------------------------------------------------------"
echo "Testing with valid params"
echo "----------------------------------------------------------------------------"
## Case 1
echo "Case 1: 10"
$BINARY_MAIN $APPLICATION_TYPE 10
echo "\n"

## Case 2
echo "Case 2: 256"
$BINARY_MAIN $APPLICATION_TYPE 256
echo "\n"

## Case 3
echo "Case 3: 6534"
$BINARY_MAIN $APPLICATION_TYPE 6534
echo "\n"

## Case 4
echo "Case 4: 13332"
$BINARY_MAIN $APPLICATION_TYPE 13332
echo "\n"

## Case 5
echo "Case 5: 167 is already prime"
$BINARY_MAIN $APPLICATION_TYPE 167
echo "\n"

## Case 6
echo "Case 6: 3673 is already prime"
$BINARY_MAIN $APPLICATION_TYPE 3673
echo "\n"

## Case 7
echo "Case 7: 6.8 reduced to int part "
$BINARY_MAIN $APPLICATION_TYPE 6.8
echo "\n"

## Case 8
echo "Case 8: 6.6.6!"!§"sdfga "
$BINARY_MAIN $APPLICATION_TYPE 6.6.6!"!§"sdfga
echo "\n"

## Case 9
echo "Case 9: 6458_aadfdfdfsadfsadfsdf "
$BINARY_MAIN $APPLICATION_TYPE 6458_aadfdfdfsadfsadfsdf
echo "\n"
echo "tests done !!!!!"

## Cleanup binary
echo "Remove binaries ..."
rm -rf $BINARY_MAIN
echo "Binaries removed"
exit 0