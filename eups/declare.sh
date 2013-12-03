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

eups_dist lua 5.1.4
eups_dist luasocket 2.0.2 
#eups_dist mysql 5.1.61
#eups_dist xrootd qs5
#eups_dist python 2.6.6
#eups_dist protobuf 2.4.1

# test this on remote machine

# for test purpose only
# eups undeclare ${PRODUCT} ${VERSION} 
# eups distrib install ${PRODUCT} ${VERSION}
# log acces
# tail -f ${EUPS_PATH}/EupsBuildDir/Linux64/protobuf-2.4.1/protobuf-2.4.1.build.log
