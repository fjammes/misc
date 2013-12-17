eups_dist() {
    if [ -z "$1" -o -z "$2" ]; then
        echo "eups_dist requires two arguments"
        exit 1
    fi
    product=$1
    version=$2
    cd ${EUPS_WORK}/pkg/$product/$version/
    cmd="eups declare ${product} ${version} -r ."
    echo $cmd
    $cmd
    eups distrib create ${product} ${version} -vvv -S buildFilePath=:ups/
    # for debug purpose only : build file generation
    eups expandbuild -V ${version} ups/${product}.build > ${product}-${version}.build
    cd ${EUPS_WORK}/ 
}

eups_undeclare_all() {
    eups list  | cut -f1 |  awk '{print "eups undeclare --force "$1"  "$2}' | bash
}
