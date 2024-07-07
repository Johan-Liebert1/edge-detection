#!/bin/bash

mkdir -p bin

gcc -o bin/main  -Wall main.c stb_image.h -lm

if [[ -z $1 ]]; then
    ./bin/main
fi
