#!/bin/sh
TEST_DIR=file_visitor_test_dir
RES_DIR=resources
SEARCH_DIR=resources
APP=fv
FUN_GREP=grep
FUN_PRINT=print

###########################
## Create test resources ##
###########################
## Create test folder 
echo "\n\n"
if [ -d $TEST_DIR ]
then
	echo "clean test folder '$TEST_DIR'"
	rm -rf $TEST_DIR 
else
	echo "create test folder '$TEST_DIR'"
	mkdir $TEST_DIR
fi

## Copy test resources 
echo "copying test resources"
cp -R $RES_DIR *.c *.h Makefile $TEST_DIR

## Switch to test dir 
cd $TEST_DIR
echo "in directory '$TEST_DIR'"


###########################
## Build application     ##
###########################
echo "\ncompiling sources ..."
echo "> make clean depend fv"
make clean depend fv 

###########################
## Tests error handling  ##
###########################
echo "\n\n-------------------------------------"
echo "Test error handling "
echo "-------------------------------------"

echo "\n\nCase 1"
echo "No arguments given"
echo "> ./$APP"
./$APP

echo "\n\nCase 2"
echo "Only directory given"
echo "> ./$APP $SEARCH_DIR"
./$APP $SEARCH_DIR

echo "\n\nCase 3"
echo "grep without pattern"
echo "> ./$APP $SEARCH_DIR -grep"
./$APP $SEARCH_DIR -grep

echo "\n\nCase 4"
echo "invalid dir"
echo "> ./$APP /invalidDir -grep"
./$APP /invalidDir -grep

echo "\n\nCase 5"
echo "invalid file"
echo "> ./$APP /invalidDir/test.txt -grep"
./$APP /invalidDir/test.txt -grep

###########################
## Tests expected grep   ##
###########################
echo "\n\n-------------------------------------"
echo "Test expected grep  "
echo "-------------------------------------"
echo "\nCase 1"
echo "Finds the test in the test resources"
echo "> ./$APP $SEARCH_DIR -grep char*"
./$APP $SEARCH_DIR -grep char*

echo "\n\nCase 2"
echo "Finds the test in the test resources"
echo "./$APP $SEARCH_DIR -grep @param"
./$APP $SEARCH_DIR -grep @param

echo "\n\nCase 3"
echo "Does not find anything in the test resources"
echo "./$APP $SEARCH_DIR -grep MICH_FINDET_MAN_NICHT"
./$APP $SEARCH_DIR -grep MICH_FINDET_MAN_NICHT

###########################
## Tests expected print  ##
###########################
echo "\n\n-------------------------------------"
echo "Test expected print  "
echo "-------------------------------------"
echo "\nCase 1"
echo "invalid $RE -grep"
./$APP $SEARCH_DIR -print

###########################
## Cleanup tests         ##
###########################
## Delete test resources
echo "\n\nremoving folder '$TEST_DIR'"
cd ..
rm -rf $TEST_DIR
echo "\ntests finished and resources released"



