#!/bin/bash

source env.sh
source functions.sh

# dependant packages
##
eups_dist virtualenv 1.7
eups_dist python virtualenv

# test this on remote machine

# for test purpose only
# undeclare everything
eups_undeclare_all
# install qserv
# eups distrib install virtualenv 1.7
eups distrib install python virtualenv
#eups distrib install qserv 533d661
# log access
# tail -f ${EUPS_PATH}/EupsBuildDir/Linux64/${PRODUCT}-${VERSION}/${PRODUCT}-${VERSION}.build.log
