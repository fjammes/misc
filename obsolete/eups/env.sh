source /opt/lsst/eups/bin/setups.sh
# export EUPS_DISTRIB_PKGROOT=${HOME}/tmp/pkgroot
# install mode can use url, but not distrib mode
export EUPS_PKGROOT=${HOME}/tmp/pkgroot
export EUPS_STARTUP=$PWD/startup.py
export EUPS_WORK=$PWD
export QSERV_BUILD_REPO="~/misc/src"
