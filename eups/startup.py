
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

# How to install "ups" files for LSST third-party products (grab from git)
#
# Third-party products' build files should contain at the top:
# @QSERV UPS@
# and then later:
# qserv_ups @PRODUCT@ @VERSION@ <INSTALL-DIR> [GIT-HASH]
hooks.config.distrib["builder"]["variables"]["QSERV UPS"] = """
# copy remote ups directory in product_dir
# after having expanded build file
# NOTE : *.build and .table file could be also retrieved from $EUPS_PKGROOT
# but paths would then be harder to deduce
qserv_ups() {


    # TODO use by default git distant repos
    # would it be possible to get the real EUPS_PKGROOT build files instead of re-generating them ?
    gitrepo=${QSERV_BUILD_REPO}

    if [ -z "$1" -o -z "$2" ]; then
        echo "lsst_ups requires at least two arguments"
        exit 1
    fi
    productname=$1
    versionname=$2
    githash=$3
    if [ -z "$githash" ]; then
        githash="HEAD"
    fi
    currentdir=$(pwd)
    eups_files="eups/pkg/${productname}/${versionname}/ups"
    mkdir -p ${product_dir}/ups &&
    buildfile=${productname}-${versionname}.build &&
    echo "Downloading ${pkgroot_url}/builds/${buildfile}" &&  
    curl -L ${pkgroot_url}/builds/${buildfile} > ${product_dir}/ups/${buildfile} &&
    tablefile=${productname}-${versionname}.table && 
    echo "Downloading ${pkgroot_url}/tables/${tablefile}" &&
    curl -L ${pkgroot_url}/tables/${tablefile} > ${product_dir}/ups/${tablefile}
    
}
"""

# @QSERV PREPARE@
# and then later:
# qserv_prepare @PRODUCT@ @VERSION@
hooks.config.distrib["builder"]["variables"]["QSERV PREPARE"] = """
# download and extract archive source file
# and goes in its top directory
qserv_prepare() {
    if [ -z "$1" -o -z "$2" ]; then
        echo "qserv_prepare requires at least two arguments"
        exit 1
    fi

    #url=http://www.slac.stanford.edu/exp/lsst/qserv/download/current

    if [ -d "${EUPS_PKGROOT}" ]; then
      # Hack to make curl work with a local repository, 
      # note that :
      # 1. {EUPS_PKGROOT} consistency should have already been checked by eups
      #    => So it must exists.
      # 2. eups doesn't support EUPS_PKGROOT starting with file:// protocol because : 
      #    - LocalTransporter doesn't support this protocol 
      #    - It couldn't be added to WebTransporter because urllib2.urlopen() fail while listing a directory with this protocol
      pkgroot_url="file://${EUPS_PKGROOT}"
    else
      pkgroot_url=${EUPS_PKGROOT}
    fi
    tarballs_url=${pkgroot_url}/tarballs

    productname=$1
    versionname=$2

    extractname=${productname}-${versionname}

    if [ -z "$4" ]
    then
        ext="tar.gz"
    else
	ext="$4"
    fi
    
    # $3 is the name of the software in the archive file
    if [ -z "$3" ]
    then
        archivename=${extractname}.${ext}
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
        return 1
    fi

    # empty install dir if needed
    rm -rf * &&
    echo "Downloading ${tarballs_url}/${archivename}"
    curl -L ${tarballs_url}/${archivename} > ${archivename} &&
    mkdir ${extractname} && 
    tar xf ${archivename} -C ${extractname} --strip-components 1 &&
    product_dir=$(eups path 0)/$(eups flavor)/${productname}/${versionname} &&
    cd ${extractname}
}
"""
