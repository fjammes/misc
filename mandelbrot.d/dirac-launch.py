#!/usr/bin/env python
import time

from DIRAC.Core.Base import Script
Script.parseCommandLine()
from DIRAC.Interfaces.API.Dirac import Dirac
from DIRAC.Interfaces.API.Job import Job


dirac = Dirac()


N_PICT=2000
N_PICT_BATCH=5
P_START=.000002
P_STEP=.000001
EXEC='mandelbrot'
JOBGROUP="fjammes_%s" % EXEC


def launch_batch_pict( pitch_start, step, n_pict ):

	j = Job()
	j.setCPUTime(500)
        j.setName('%s_%f' % (EXEC, pitch_start))
	j.setJobGroup(JOBGROUP)
	j.setInputSandbox([EXEC])
	out_bmp_list=[]
	pitch=pitch_start

	for i in range(n_pict):
        	j.setName('mandelbrot_%d' % i)
        	out_bmp='out_%f.bmp' % pitch
        	out_bmp_list.append(out_bmp)
		j.setExecutable(EXEC,arguments="-W 600 -H 600 -X -0.77568377 -Y -0.13646737 -P %f -M 500 %s" % (pitch, out_bmp))
        	pitch+=step
		
	j.setOutputSandbox(out_bmp_list + ["StdOut"] + ["StdErr"])
	result = dirac.submit(j)
	print 'Submission Result: ',result
	return result

n_produced_pict = 0
jobinfo_list = []
while n_produced_pict < N_PICT:
	pitch_start = n_produced_pict * P_STEP + P_START
	jobinfo = launch_batch_pict(pitch_start, P_STEP, N_PICT_BATCH)
	jobinfo_list.append(jobinfo)
	n_produced_pict += N_PICT_BATCH


job_state_dict = dict()
job_in_flight = ['start'] 
while len(job_in_flight) != 0  :
	for jobinfo in jobinfo_list :
		jobid=jobinfo['Value']
		status = dirac.status(jobid)
		state = status['Value'][jobid]['Status']
		job_state_dict[jobid] = state
	job_in_flight = [k for k, v in job_state_dict.items() if v != 'Done']
	print "Job still running :"
	print job_in_flight
	time.sleep(2)

