#!/bin/sh

gcc -I modules tests/test_course.c modules/course.c -o test_course.out
chmod +x test_course.out
./test_course.out

if [ $? -ne 0 ]; then
    exit 1
fi

gcc -I modules tests/test_course_result.c modules/course.c modules/courseResult.c -o test_course_result.out
chmod +x test_course_result.out
./test_course_result.out

if [ $? -ne 0 ]; then
    exit 1
fi
gcc -I modules tests/test_gpa.c modules/course.c modules/courseResult.c modules/gpa.c -o test_gpa.out
chmod +x test_gpa.out
./test_gpa.out

if [ $? -ne 0 ]; then
    exit 1
fi