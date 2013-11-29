PRODUCT=protobuf
VERSION=2.4.1

eups distrib create ${PRODUCT} ${VERSION} -vvv -S buildFilePath=:ups/

# for debug purpose only : build file generation
eups expandbuild -V ${VERSION} ups/${PRODUCT}.build > ${PRODUCT}-${VERSION}.build

# for test purpose only
eups undeclare ${PRODUCT} ${VERSION} 
eups distrib install ${PRODUCT} ${VERSION}
