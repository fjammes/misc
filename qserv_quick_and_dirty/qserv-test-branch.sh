#!/bin/bash

set -x
set -e

STACK_DIR=$HOME/stack
QSERV_SRC_DIR=$HOME/src/qserv
QSERV_RUN_DIR=$HOME/qserv-run/bisect

. $STACK_DIR/loadLSST.bash
setup qserv_distrib -t qserv
setup -k -r ${QSERV_SRC_DIR}

killall mysqld mysql-proxy xrootd java pytho || printf "Unable to kill some services"
cd ${QSERV_SRC_DIR}
# rm -rf build lib proxy bin cfg
# "scons install" doesn't use all proc
eupspkg -e PREFIX=${QSERV_SRC_DIR} install
qserv-configure.py --all --force -R ${QSERV_RUN_DIR}
${QSERV_RUN_DIR}/bin/qserv-start.sh
qserv-test-integration.py
${QSERV_RUN_DIR}/bin/qserv-stop.sh
