#!/bin/bash

TMP_DIR=tmp
DIRAC_OUTPUT=${TMP_DIR}/dirac_output
BMP_DIR=${TMP_DIR}/bmp

rm -rf ${TMP_DIR} 
mkdir -p ${DIRAC_OUTPUT}
mkdir -p ${BMP_DIR}
doutput --JobGroup=mandelbrot --OutputDir=${DIRAC_OUPUT}
find ${DIRAC_OUTPUT} -name "*.bmp" -exec mv {} ${BMP_DIR} \; -print
convert tmp/out_*.bmp movie.gif
