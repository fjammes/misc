#!/bin/bash

source env.sh

eups_dist() {
    if [ -z "$1" -o -z "$2" ]; then
        echo "eups_dist requires two arguments"
        exit 1
    fi
    product=$1
    version=$2
    cd $product/$version/
    cmd="eups declare ${product} ${version} -r ."
    echo $cmd
    $cmd
    eups distrib create ${product} ${version} -vvv -S buildFilePath=:ups/
    # for debug purpose only : build file generation
    eups expandbuild -V ${version} ups/${product}.build > ${product}-${version}.build
    cd ../..
}

cd pkg

# dependant packages
##
eups_dist lua 5.1.4
eups_dist luasocket 2.0.2 
eups_dist expat 2.0.1 
eups_dist luaexpat 1.1
eups_dist luaxmlrpc v1.2.1-2
eups_dist mysql 5.1.61
eups_dist xrootd qs5
eups_dist python 2.6.6
eups_dist virtualenv 1.7
eups_dist protobuf 2.4.1
eups_dist mysqlpython 1.2.3
eups_dist libevent 2.0.16-stable
eups_dist qserv 533d661

# test this on remote machine

# for test purpose only
# undeclare everything
eups list  | cut -f1 |  awk '{print "eups undeclare --force "$1"  "$2}' | bash
# install qserv
# eups distrib install virtualenv 1.7
eups distrib install mysqlpython 1.2.3
#eups distrib install qserv 533d661
# log access
# tail -f ${EUPS_PATH}/EupsBuildDir/Linux64/${PRODUCT}-${VERSION}/${PRODUCT}-${VERSION}.build.log
