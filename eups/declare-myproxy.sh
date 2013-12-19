#!/bin/bash

source env.sh
source functions.sh

# dependant packages
##
eups_dist libevent 2.0.16-stable
eups_dist mysql 5.1.61
eups_dist mysqlproxy 0.8.2
# eups_dist python virtualenv

# test this on remote machine

# for test purpose only
# undeclare everything
eups_undeclare_all

eups distrib install mysqlproxy 0.8.2
#eups distrib install xxqserv 533d661
# log access
# tail -f ${EUPS_PATH}/EupsBuildDir/Linux64/${PRODUCT}-${VERSION}/${PRODUCT}-${VERSION}.build.log
