#!/bin/bash

set -e
set -x

g++ -o main.o -c -std=c++11 -g -DLSST_HAVE_TR1=1 \
-DLSST_LITTLE_ENDIAN=1 -O0 -Iinclude \
-I$UTILS_DIR/include \
-I$PEX_EXCEPTIONS_DIR/include \
-I$BASE_DIR/include \
-I$BOOST_DIR/include \
-I$LOG4CXX_DIR/include \
-I$LOG_DIR/include \
main.cc

g++ -o run -Wl,-rpath-link \
-Wl,$LOG_DIR/lib:$BASE_DIR/lib:$LOG4CXX_DIR/lib:$APR_UTIL_DIR/lib:/home/qserv/src/qserv/lib:/home/qserv/stack/Linux64/libevent/2.0.16-stable/lib:$BOOST_DIR/lib:$PEX_EXCEPTIONS_DIR/lib:$UTILS_DIR/lib \
-L$UTILS_DIR/lib \
-L$PEX_EXCEPTIONS_DIR/lib \
-L$BASE_DIR/lib \
-L$BOOST_DIR/lib \
-L$LOG_DIR/lib \
-L$LOG4CXX_DIR/lib \
-L/usr/lib/python2.7/config-x86_64-linux-gnu -L/usr/lib \
main.o \
-llog -lutils \
-lpex_exceptions -lbase -lboost_regex -lpthread -llog4cxx \
-lboost_unit_test_framework

