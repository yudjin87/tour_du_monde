#!/bin/sh
# run:
# 
#   ./test_runner.sh linux32/debug_static/unittest/
#   ./test_runner.sh linux32/release_static/unittest/
#
# using MinGW:
#
#   ./test_runner.sh win32/debug_static/unittest/
#   ./test_runner.sh win32/release_static/unittest/

PATH_TO_TESTS=$1
echo "Path to tests: $PATH_TO_TESTS"

EXECUTABLE_PATTERN=*_test

# If script is started from the MinGW, find all *_test.exe files
if [ ${OS} = "Windows_NT" ]; then
	EXECUTABLE_PATTERN=*_test.exe
fi

# Run all test executables from specified directory
# and output Total Test Result
for file in ${PATH_TO_TESTS}${EXECUTABLE_PATTERN} ; do
	if [ -f $file ]; then    
        echo $file:
	    ./$file | grep Total 
	fi
done
