JOBGROUP=fjammes_mandelbrot

dirac-wms-job-delete --JobGroup ${JOBGROUP} --debug
dstat --JobGroup=${JOBGROUP}
