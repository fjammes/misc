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

eups_dist python 2.6.6
eups_dist protobuf 2.4.1


# for test purpose only
# eups undeclare ${PRODUCT} ${VERSION} 
# eups distrib install ${PRODUCT} ${VERSION}
