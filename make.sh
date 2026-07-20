#!/bin/sh

gcc -I modules main.c modules/course.c modules/courseResult.c modules/gpa.c modules/student.c -o calculator.out

if [ $? -eq 0 ]; then
    echo "Build successful."
else
    echo "Build failed."
    exit 1
fi