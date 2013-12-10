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

PRODUCT=luaxmlrpc
VERSION=v1.2.1-2

# dependant packages
##
eups_dist lua 5.1.4
eups_dist luasocket 2.0.2 
eups_dist expat 2.0.1 
eups_dist luaexpat 1.1
eups_dist ${PRODUCT} ${VERSION}

#eups_dist mysql 5.1.61
#eups_dist xrootd qs5
#eups_dist python 2.6.6
#eups_dist protobuf 2.4.1

# test this on remote machine

# for test purpose only
eups undeclare --force lua 5.1.4
eups undeclare --force expat 2.0.1
eups undeclare --force luasocket 2.0.2 
eups undeclare --force luaexpat 1.1
eups undeclare --force ${PRODUCT} ${VERSION} 
eups distrib install ${PRODUCT} ${VERSION}
# log acces
tail -f ${EUPS_PATH}/EupsBuildDir/Linux64/${PRODUCT}-${VERSION}/${PRODUCT}-${VERSION}.build.log
