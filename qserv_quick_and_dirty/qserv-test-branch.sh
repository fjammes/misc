killall mysqld mysql-proxy xrootd java python
setup -k -r . &&
rm -rf build lib proxy bin cfg  &&
eupspkg -e PREFIX=$PWD install &&
qserv-configure.py --all --force &&
~/qserv-run/2014_11.0/bin/qserv-start.sh &&
qserv-test-integration.py &&
~/qserv-run/2014_11.0/bin/qserv-stop.sh 
