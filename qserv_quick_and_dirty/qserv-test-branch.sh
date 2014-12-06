killall mysqld mysql-proxy xrootd java python
QSERV_SRC_DIR=$HOME/src/qserv
cd ${QSERV_SRC_DIR} &&
setup -k -r . &&
rm -rf build lib proxy bin cfg  &&
eupspkg -e PREFIX=$PWD install &&
qserv-configure.py --all --force &&
~/qserv-run/2014_12/bin/qserv-start.sh &&
qserv-test-integration.py &&
~/qserv-run/2014_12/bin/qserv-stop.sh 
