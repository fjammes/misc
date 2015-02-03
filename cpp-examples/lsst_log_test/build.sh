#!/bin/bash

set -e
set -x

g++ -o main.o -c -std=c++11 -g -DLSST_HAVE_TR1=1 \
-DLSST_LITTLE_ENDIAN=1 -O0 -Iinclude \
-I/home/qserv/stack/Linux64/utils/9.2+13/include \
-I/home/qserv/stack/Linux64/pex_exceptions/9.2+13/include \
-I/home/qserv/stack/Linux64/base/9.1+14/include \
-I/home/qserv/stack/Linux64/boost/master-g2e1a7fad74/include \
-I$LOG4CXX_DIR/include \
-I$LOG_DIR/include \
main.cc

g++ -o run -Wl,-rpath-link \
-Wl,$LOG_DIR/lib:/home/qserv/stack/Linux64/base/9.1+14/lib:/home/qserv/stack/Linux64/log4cxx/0.10.0.lsst1/lib:/home/qserv/stack/Linux64/apr_util/1.3.4.lsst1/lib:/home/qserv/stack/Linux64/apr/1.3.3.lsst1/lib:/home/qserv/src/qserv/lib:/home/qserv/stack/Linux64/zookeeper/3.4.6/c-binding/lib/:/home/qserv/stack/Linux64/xrootd/4.0.0rc4-qsClient2/lib:/home/qserv/stack/Linux64/protobuf/2.4.1/lib:/home/qserv/stack/Linux64/libevent/2.0.16-stable/lib:/home/qserv/stack/Linux64/mysqlclient/5.1.73/lib:/home/qserv/stack/Linux64/mysql/5.1.65/lib:/home/qserv/stack/Linux64/boost/master-g2e1a7fad74/lib:/home/qserv/stack/Linux64/pex_exceptions/9.2+13/lib:/home/qserv/stack/Linux64/utils/9.2+13/lib \
-L/home/qserv/stack/Linux64/utils/9.2+13/lib \
-L/home/qserv/stack/Linux64/pex_exceptions/9.2+13/lib \
-L/home/qserv/stack/Linux64/base/9.1+14/lib \
-L/home/qserv/stack/Linux64/boost/master-g2e1a7fad74/lib \
-L$LOG_DIR/lib \
-L$LOG4CXX_DIR/lib \
-L/usr/lib/python2.7/config-x86_64-linux-gnu -L/usr/lib \
main.o \
-llog -lutils \
-lpex_exceptions -lbase -lboost_regex -lpthread -llog4cxx \
-lboost_unit_test_framework

