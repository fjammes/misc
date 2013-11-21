#!/bin/sh

echo "Installing Protobuf from source."

INSTALL_DIR=~/products
PRODUCT=protobuf
VERSION=2.4.1

BUILD_DIR=${INSTALL_DIR}/build
SRC_DIR=${BUILD_DIR}/${PRODUCT}-${VERSION}
TARBALL=${PRODUCT}-${VERSION}.tar.gz


cd ${BUILD_DIR} &&
tar zxvf ${TARBALL} &&
cd ${SRC_DIR} &&
./configure --prefix=${INSTALL_DIR} &&
make &&
make install &&
cd ${SRC_DIR}/python &&
python setup.py install &&
echo "${PRODUCT}-${VERSION} successfully installed"
