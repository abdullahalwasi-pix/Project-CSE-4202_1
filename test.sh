#!/bin/sh

gcc -I modules tests/test_course.c modules/course.c -o test_course.out

if [ $? -ne 0 ]; then
    echo "Compilation failed."
    exit 1
fi

chmod +x test_course.out
./test_course.out