#!/bin/bash

source env.sh
source functions.sh

# dependant packages
##
eups_dist lua 5.1.4
eups_dist luasocket 2.0.2 
eups_dist expat 2.0.1 
eups_dist luaexpat 1.1
eups_dist luaxmlrpc v1.2.1-2
eups_dist mysql 5.1.61
eups_dist xrootd qs5
eups_dist virtualenv 1.7
#eups_dist python 2.6.6
eups_dist python virtualenv 
eups_dist protobuf 2.4.1
eups_dist mysqlpython 1.2.3
eups_dist libevent 2.0.16-stable
eups_dist virtualenv 1.7
eups_dist python virtualenv
eups_dist qserv 533d661

# test this on remote machine

# for test purpose only
# undeclare everything
eups_undeclare_all
# install qserv
# eups distrib install virtualenv 1.7
eups distrib install mysqlpython 1.2.3
#eups distrib install qserv 533d661
# log access
# tail -f ${EUPS_PATH}/EupsBuildDir/Linux64/${PRODUCT}-${VERSION}/${PRODUCT}-${VERSION}.build.log
