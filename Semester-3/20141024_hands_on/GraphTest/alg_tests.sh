#!/bin/sh
TEST_FOLDER=tests
i=1
TEST_CASES=27

echo "creating test folder: $TEST_FOLDER"

mkdir $TEST_FOLDER

echo "test folder created"
echo "\ncopying test resources to test folder"
echo "cp dg_adt_alg_tests.c ../$1/*.c ../$1/*.h ../GraphAlg/makefile ../GraphAlg/*.h ../GraphAlg/*.c ../Graph/*.h   $TEST_FOLDER"

cp dg_adt_alg_tests.c ../$1/*.c ../$1/*.h ../GraphAlg/makefile ../GraphAlg/*.h ../GraphAlg/*.c ../Graph/*.h  $TEST_FOLDER
cd $TEST_FOLDER

echo "\nin directory: $(pwd)"
echo "build test source"
echo "make clean depend $2"

make clean depend $2

echo "\n\n#################################################"
echo "performing tests"
echo "#################################################"
while [ $i -le $TEST_CASES ]
do
	echo "-------------------------------"
	echo "Invoking test case with id $i: "
	echo "-------------------------------"
	./$2 $i	
	echo
	i=`expr $i + 1`
done

echo "\n\nremoving test resources"
cd ..
rm -rf $TEST_FOLDER
echo "test finished"
echo "in directory: $(pwd)"