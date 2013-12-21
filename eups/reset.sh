source env.sh
rm -rf ${EUPS_PATH}/* ~/.eups/ups_db ~/.eups/_caches_ ${EUPS_PKGROOT}
mkdir -p  ${EUPS_PKGROOT}/tarballs
cp /opt/qserv-dev/build/*  ${EUPS_PKGROOT}/tarballs 
cd /opt/src/eups; make install
