#!/bin/bash

mkdir -p bin

gcc -o bin/main main.c stb_image.h -lm

if [[ -z $1 ]]; then
    ./bin/main
fi
