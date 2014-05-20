
hooks.config.Eups.colorize = True

def cmdHook(Eups, cmd, opts, args):
    if cmd.split()[0] == "distrib":
        subcmd = cmd.split()[1]
        if subcmd == "create":
            opts.distribTypeName = "builder"
            opts.allowIncomplete = True
            opts.useFlavor = "generic"
            opts.serverDir = "~/tmp/pkgroot"

eups.commandCallbacks.add(cmdHook)

# Download and extract archive source file
# and goes in its top directory
#
# Third-party products' build files should contain at the top:
# @QSERV PREPARE@
# and then later:
# qserv_prepare @PRODUCT@ @VERSION@
hooks.config.distrib["builder"]["variables"]["QSERV FUNCTIONS"] = """

qserv_globals() {
    if [ -z "$1" -o -z "$2" ]; then
        echo "qserv_globals requires two arguments"
        false
	return
    fi

    # Hack to make curl work with a local repository. 
    #   note that :
    #   1. {EUPS_PKGROOT} consistency should have already been checked by eups
    #      => So it must exists.
    #   2. eups doesn't support EUPS_PKGROOT starting with file:// protocol because : 
    #      - LocalTransporter doesn't support this protocol 
    #      - It couldn't be added to WebTransporter because urllib2.urlopen() fail while listing a directory with this protocol
    if [ -d "${EUPS_PKGROOT}" ]; then
        EUPS_PKGROOT_URL="file://${EUPS_PKGROOT}"
    else
        EUPS_PKGROOT_URL=${EUPS_PKGROOT}
    fi

    PRODUCT=$1
    VERSION=$2

    PRODUCT_DIR=$(eups path 0)/$(eups flavor)/${PRODUCT}/${VERSION} &&
    SRC_DIR=${PRODUCT}-${VERSION}
}

# download and extract archive source file
# and goes in its top directory
qserv_prepare() {
    if [ -z "$1" -o -z "$2" ]; then
        echo "qserv_prepare requires at least two arguments"
        false
	return
    fi

    #url=http://www.slac.stanford.edu/exp/lsst/qserv/download/current

    tarballs_url=${EUPS_PKGROOT_URL}/tarballs

    productname=$1
    versionname=$2

    if [ -z "$4" ]
    then
        ext="tar.gz"
    else
	ext="$4"
    fi
    
    # $3 is the name of the software in the archive file
    if [ -z "$3" ]
    then
        archivename=${SRC_DIR}.${ext}
    else
	archivename=$3-${versionname}.${ext}
    fi

    if [ "${ext}" == "tar.gz" ]
    then
        tar_opt="xvf"
    elif [ "${ext}" == "tar.bz2" ]
    then
        tar_opt="jvf"
    else
        echo "qserv_prepare : Error, unable to analyse extension of ${archivename}"
        false 
	return
    fi

    # empty install dir if needed
    # but keep current build log file
    rm -rf ${archivename} ${SRC_DIR} &&
    echo "Downloading ${tarballs_url}/${archivename}" &&
    curl -L ${tarballs_url}/${archivename} > ${archivename} &&
    mkdir ${SRC_DIR} && 
    tar xf ${archivename} -C ${SRC_DIR} --strip-components 1 &&
    cd ${SRC_DIR} 
}

# How to install "ups" files for Qserv third-party products
#
# Third-party products' build files should contain at the top:
# @QSERV UPS@
# and then later:
# qserv_ups @PRODUCT@ @VERSION@
#
# copy remote ups directory in PRODUCT_DIR
# after having expanded build file
# NOTE : *.build and .table file could be also retrieved from $EUPS_PKGROOT
# but paths would then be harder to deduce
qserv_ups() {

    if [ -z "$1" -o -z "$2" ]; then
        echo "lsst_ups requires at least two arguments"
	false
	return
    fi
    productname=$1
    versionname=$2
    buildfile=${productname}-${versionname}.build
    tablefile=${productname}-${versionname}.table
    mkdir -p ${PRODUCT_DIR}/ups &&
    echo "Downloading ${EUPS_PKGROOT_URL}/builds/${buildfile}" &&  
    curl -L ${EUPS_PKGROOT_URL}/builds/${buildfile} > ${PRODUCT_DIR}/ups/${buildfile} &&
    echo "Downloading ${EUPS_PKGROOT_URL}/tables/${tablefile}" &&
    curl -L ${EUPS_PKGROOT_URL}/tables/${tablefile} > ${PRODUCT_DIR}/ups/${tablefile} 
}
"""
