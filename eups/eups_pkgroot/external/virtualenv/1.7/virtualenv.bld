:sp
#!/bin/sh
        
echo "Installing Virtualenv from source."

INSTALL_BASE=~/products
PRODUCT=virtualenv
VERSION=1.7

BUILD_DIR=${INSTALL_BASE}/build
SRC_DIR=${BUILD_DIR}/${PRODUCT}-${VERSION}
INSTALL_DIR=${INSTALL_BASE}/${PRODUCT}-${VERSION}
TARBALL=${PRODUCT}-${VERSION}.tar.gz

cd ${BUILD_DIR} &&
tar zxvf ${TARBALL} &&
cd ${SRC_DIR} &&
python virtualenv.py ${INSTALL_DIR}

echo "${PRODUCT}-${VERSION} successfully installed : PATH ${PATH}"

cd ${INSTALL_DIR}
eups declare ${PRODUCT} ${VERSION} -r .

# TODO (but not used by eups
PATH=${INSTALL_DIR}/bin:${PATH}
