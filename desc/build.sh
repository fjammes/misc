#!/bin/sh

set -x
set -e

DIR=$(cd "$(dirname "$0")"; pwd -P)

export https_proxy="http://ccqservproxy.in2p3.fr:3128"

if [ ! -d "$DIR/qserv" ]
then
    git clone https://github.com/fjammes/qserv.git
fi

if [ ! -d "$DIR/qserv_testdata" ]
then
    git clone https://github.com/fjammes/qserv_testdata.git
fi

# Setup dependencies
. /qserv/stack/loadLSST.bash
setup qserv_distrib -t qserv-dev
 
# Build Qserv
cd "$DIR/qserv"
git pull 
setup -k -r .
eupspkg -e build
# install dependency in-place (if possible)
eupspkg -e PREFIX=$PWD install
eupspkg -e PREFIX=$PWD decl -t qserv-dev

# Build qserv_testdata
cd "$DIR/qserv_testdata"
git pull
setup -k -r .
scons
eups declare qserv_testdata -t qserv-dev -r .
