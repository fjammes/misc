#!/bin/bash

TMP_DIR=tmp
DIRAC_OUTPUT=${TMP_DIR}/dirac_output
BMP_DIR=${TMP_DIR}/bmp
JOBGROUP=fjammes_mandelbrot

rm -rf ${TMP_DIR} 
mkdir -p ${DIRAC_OUTPUT}
mkdir -p ${BMP_DIR}
#doutput --JobGroup=${JOBGROUP} --OutputDir=${DIRAC_OUPUT} &&
echo "Output data dest dir : ${DIRAC_OUTPUT}"
dirac-wms-job-get-output --JobGroup=${JOBGROUP} --Dir=${DIRAC_OUTPUT}
find ${DIRAC_OUTPUT} -name "*.bmp" -exec mv {} ${BMP_DIR} \; -print
convert ${BMP_DIR}/out_*.bmp movie.gif
