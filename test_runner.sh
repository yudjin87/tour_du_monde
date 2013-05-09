#!/bin/sh
# run:
# 
#   ./test_runner.sh product/gnu-32-debug-static/unittest/
#   ./test_runner.sh product/gnu-32-debug-release/unittest/
#
# using MinGW:
#
#   ./test_runner.sh product/msvc10-x32-debug-static/unittest/
#   ./test_runner.sh product/msvc10-x32-release-static/unittest/

PATH_TO_TESTS=$1
echo "Path to tests: $PATH_TO_TESTS"

EXECUTABLE_PATTERN=*_test

# If script is started from the MinGW, find all *_test.exe files
if [ ${OS} = "Windows_NT" ]; then
	EXECUTABLE_PATTERN=*_test.exe
fi

cd $PATH_TO_TESTS

# Run all test executables from specified directory
# and output Total Test Result
for file in ./${EXECUTABLE_PATTERN} ; do
	if [ -f $file ]; then    
        echo $file:
	    ./$file | grep Total 
	fi
done
