#!/bin/sh
## Varaibles used during build and tests ##
APPLICATION_TYPE=1
SOURCE_MAIN=../main.c
BINARY_MAIN=bin/main_trianlge_test.bin
SOURCE_TRIANGLE=../source/triangle.c
SOURCE_PRIME=../source/prime.c
INCLUDE_HEADERS_COMMONS=../../Commons/header
INCLUDE_HEADERS=../header/

echo "############################################################################"
echo "These are the tests for the triangle_validator"
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
echo "Testing worng parameter count"
echo "----------------------------------------------------------------------------"
## Case 1
echo "Case 1: no param"
$BINARY_MAIN $APPLICATION_TYPE 
echo "\n"

## Case 2
echo "Case 2: 1 param"
$BINARY_MAIN $APPLICATION_TYPE 1.0
echo "\n"

## Case 3
echo "Case 3: 2 param"
$BINARY_MAIN $APPLICATION_TYPE 1.0 2.0
echo "\n"

## Case 4
echo "Case 4: 4 param"
$BINARY_MAIN $APPLICATION_TYPE 1.0 2.0 2 2
echo "\n"

## Case 5
echo "Case 5: 5 param"
$BINARY_MAIN $APPLICATION_TYPE 1.0 2.0 2 2 3
echo "\n"

################################################################
## Test invalid triangle site lengths                         ##
################################################################
echo "----------------------------------------------------------------------------"
echo "Testing with '0' parameter "
echo "----------------------------------------------------------------------------"
## Case 1
echo "Case 1: a = 0 | b = 1 | c = 2"
$BINARY_MAIN $APPLICATION_TYPE 0 1 2
echo "\n"

## Case 2
echo "Case 3: a = 1 | b = 0 | c = 2"
$BINARY_MAIN $APPLICATION_TYPE 1 0 2
echo "\n"

## Case 3
echo "Case 4: a = 1 | b = 2 | c = 0"
$BINARY_MAIN $APPLICATION_TYPE 1 2 0
echo "\n"

echo "----------------------------------------------------------------------------"
echo "Testing with character parameter  "
echo "----------------------------------------------------------------------------"
## Case 1
echo "Case 1: a = abc | b = 1 | c = 2"
$BINARY_MAIN $APPLICATION_TYPE abc 1 2
echo "\n"

## Case 2
echo "Case 2: a = 1 | b = abc | c = 2"
$BINARY_MAIN $APPLICATION_TYPE 1 abc 2
echo "\n"

## Case 3
echo "Case 3: a = 1 | b = 2 | c = abc"
$BINARY_MAIN $APPLICATION_TYPE 1 2 abc
echo "\n"

## Case 4
echo "Case 4: a = 1 | b = 2 | c = asdfadsfdf_454544"
$BINARY_MAIN $APPLICATION_TYPE 1 2 asdfadsfdf_454544
echo "\n"

## Case 5
echo "Case 5: a = 1 | b = asdfadsfdf_454544 | c = 2"
$BINARY_MAIN $APPLICATION_TYPE 1 asdfadsfdf_4545442 2
echo "\n"

## Case 6
echo "Case 6: a = asdfadsfdf_454544 | b = 1 | c = 2"
$BINARY_MAIN $APPLICATION_TYPE asdfadsfdf_454544 1 2
echo "\n"

echo "----------------------------------------------------------------------------"
echo "Testing with invalid site lengths "
echo "----------------------------------------------------------------------------"
## Case 1
echo "Case 1: wrong dimensions of square triangle (parese issue of 'atof'): a = 3.41 | b = 6.0 | c = 6.9"
echo "        Program does not support double precision greather than 1 and do not check this"
$BINARY_MAIN $APPLICATION_TYPE 3.41 6.0 6.9
echo "\n"

## Case 2
echo "Case 2: wrong dimensions of triangle: a = 2.5 | b = 2.5 | c = 5.0"
$BINARY_MAIN $APPLICATION_TYPE 2.5 2.5 5.0
echo "\n"

echo "----------------------------------------------------------------------------"
echo "Testing with valid site lengths "
echo "----------------------------------------------------------------------------"
## Case 1
echo "Case 1: 3 equilateral triangle: a = 2.5 | b = 2.5 | c = 2.5"
$BINARY_MAIN $APPLICATION_TYPE 2.5 2.5 2.5
echo "\n"

## Case 2
echo "Case 2: isosceles triangle: a = 2.5 | b = 2.5 | c = 3.54"
$BINARY_MAIN $APPLICATION_TYPE 2.5 2.5 3.54
echo "\n"

## Case 3
echo "Case 3: normal triangle:  a = 2.18 | b = 4.5 | c = 5"
$BINARY_MAIN $APPLICATION_TYPE 2.18 4.5 5
echo "\n"

## Case 4
echo "Case 4: square triangle: a = 6 | b = 4.5 | c = 7.5"
$BINARY_MAIN $APPLICATION_TYPE 6 4.5 7.5
echo "\n"

## Case 5
echo "Case 5: square triangle: a = 6_asasas | b = 4.5 | c = 7.5"
$BINARY_MAIN $APPLICATION_TYPE 6_asas 4.5 7.5
echo "\n"

## Case 6
echo "Case 6: square triangle: a = 6 | b = 4.5_asasas | c = 7.5"
$BINARY_MAIN $APPLICATION_TYPE 6 4.5_asasas 7.5
echo "\n"

## Case 7
echo "Case 7: square triangle: a = 6 | b = 4.5 | c = 7.5_asasas"
$BINARY_MAIN $APPLICATION_TYPE 6 4.5 7.5_asasas
echo "\n"

## Cleanup binary
echo "tests done !!!!!"
echo "Remove binaries ..."
rm -rf $BINARY_MAIN
echo "Binaries removed"
exit 0