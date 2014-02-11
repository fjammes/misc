#!/usr/bin/env python
import time

from DIRAC.Core.Base import Script
Script.parseCommandLine()
from DIRAC.Interfaces.API.Dirac import Dirac
from DIRAC.Interfaces.API.Job import Job


dirac = Dirac()

j = Job()
j.setCPUTime(500)

N_IMAGES=5
P_START=.000002
P_STEP=.000001
EXEC='mandelbrot'

j.setName('mandelbrot')
j.setInputSandbox([EXEC])
out_bmp_list=[]
step=P_START

for i in range(N_IMAGES):
        j.setName('mandelbrot_%d' % i)
        out_bmp='out_%d.bmp' % i
        out_bmp_list.append(out_bmp)
	j.setExecutable(EXEC,arguments="%s -W 600 -H 600 -X -0.46490 -Y -0.56480 -P %f -M 500" % (out_bmp,step))
        step+=P_STEP

j.setOutputSandbox(out_bmp_list + ["StdOut"] + ["StdErr"])
result = dirac.submit(j)
print 'Submission Result: ',result

jobid=result['Value']

state=''
while state != 'Done':
	status = dirac.status(jobid)
	state = status['Value'][jobid]['Status']
	print status
	print state
	time.sleep(2)
