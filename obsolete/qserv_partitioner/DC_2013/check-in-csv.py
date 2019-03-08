#!/usr/bin/python

import sys

for i, line in enumerate(open(sys.argv[1],'rb')):
    size=len(line)
    f1=open('./linetoolong.txt', 'w+')
    # print "l %s  : size %s" % (i,size)
    if size > 65536 - 24 :
        print "Line %s too long : size %s" % (i,size)
	print >> f1, line
	break
    f1.close()
