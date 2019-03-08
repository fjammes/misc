#!/bin/bash
# used to debug eups process for Qserv

source env.sh
source functions.sh

#PRODUCT=helloworld
#VERSION=1.0
PRODUCT=libevent
VERSION=debug-eups
eups_dist ${PRODUCT} ${VERSION}

eups_undeclare_all

ln -sf ${EUPS_PKGROOT}/tarballs/libevent-2.0.16-stable.tar.gz ${EUPS_PKGROOT}/tarballs/${PRODUCT}-${VERSION}.tar.gz
echo "Installing ${PRODUCT} ${VERSION}"
eups distrib install -vvv ${PRODUCT} ${VERSION}
# tail -f ${EUPS_PATH}/EupsBuildDir/Linux64/${PRODUCT}-${VERSION}/${PRODUCT}-${VERSION}.build.log
