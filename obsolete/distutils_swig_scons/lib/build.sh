#!/bin/bash

BASEDIR=$(dirname $0)

cd ${BASEDIR}
gcc -shared -o libexample.so -fPIC example.c
