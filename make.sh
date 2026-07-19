#!/bin/sh

gcc -I modules main.c modules/*.c -o calculator.out

if [ $? -ne 0 ]; then
    echo "Build failed."
    exit 1
fi

echo "Build successful."